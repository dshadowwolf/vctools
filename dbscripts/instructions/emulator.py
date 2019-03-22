
import subprocess
import datetime
import string
import sys

decoder_count = 0

max_decoder_length = 4

def is_decoder_necessary(instructions, bits_handled):
    if len(instructions) == 0:
        return False;
    if len(instructions) > 1:
        return True;
    instruction = instructions[0]
    first_word = bits_handled // 16
    for i in range(first_word, instruction.length):
        mask = instruction.mask[i]
        if i == first_word:
            mask &= 0xffff >> (bits_handled % 16)
        if mask != 0:
            return True
    return False

text_base = """
#include "vc4_emul.h"
#include "vc4_data.h"
#include "vc4_registers.h"

#define error(x) error(emul, (x))
void illegal_instruction(struct vc4_emul *emul, uint16_t *instr) {
    interrupt(3, "illegal instruction");
}

"""

class Decoder:
    def __init__(self, instructions, bits_handled):
        # Create a new unique decoder name
        global decoder_count
        self.name = 'decoder_' + str(decoder_count)
        decoder_count += 1
        # Create the decoder tables
        self.generateDecoder(instructions, bits_handled)

    def generateDecoder(self, instructions, bits_handled):
        word = bits_handled // 16
        for instruction in instructions:
            if word >= instruction.length:
                print('Error, multiple instructions with the same pattern!')
                print(instruction.pattern)
                sys.exit(-1)
        word_offset = bits_handled % 16
        word_mask = 0xffff >> word_offset
        # Find the first bit to be checked
        high_bit = 0 
        for instruction in instructions:
            value = instruction.mask[word] & word_mask
            high_bit = max(high_bit, value.bit_length())
        if high_bit == 0:
            # Continue at the next word
            bits_handled = (word + 1) * 16
            return self.generateDecoder(instructions, bits_handled)
        high_mask = (1 << high_bit) - 1
        low_bit = max(high_bit - max_decoder_length, 0)
        low_mask = (1 << low_bit) - 1
        word_mask = high_mask ^ low_mask
        # Find the number of bits to be checked
        low_bit = high_bit
        for instruction in instructions:
            value = instruction.mask[word] & word_mask
            low_bit = min(low_bit, (value & -value).bit_length() - 1)
        if low_bit < 0:
            print('Error, multiple instructions with colliding patterns:')
            for instruction in instructions:
                print(instruction.pattern)
            sys.exit(-1)
        low_mask = (1 << low_bit) - 1
        word_mask = high_mask ^ low_mask
        # Create instruction lists
        table_size = (high_mask + 1) / (low_mask + 1)
        bits_handled = word * 16 + 16 - low_bit
        instruction_table = []
        for i in range(table_size):
            instruction_table.append([])
            value = i * (low_mask + 1)
            for instruction in instructions:
                if instruction.mask[word] & value == instruction.value[word] & word_mask:
                    instruction_table[i].append(instruction)
        # Recursively create more decoder tables where necessary
        decoder_table = []
        text = ''
        for i in range(table_size):
            if is_decoder_necessary(instruction_table[i], bits_handled):
                found = False
                for j in range(i):
                    if instruction_table[i] == instruction_table[j]:
                        decoder_table.append(decoder_table[j])
                        found = True
                        break
                if found:
                    continue
                decoder_table.append(Decoder(instruction_table[i],
                                             bits_handled))
                text += decoder_table[i].text + '\n'
            else:
                decoder_table.append(None)
        # Create the decoder
        text += 'instruction_function ' + self.name + '_table[] = {\n'
        for i in range(table_size):
            if decoder_table[i] is not None:
                text += '    ' + decoder_table[i].name + ',\n'
            elif instruction_table[i] != []:
                text += '    ' + instruction_table[i][0].function_name + ',\n'
            else:
                text += '    illegal_instruction,\n'
        text += '};\n\n'
        text += 'void ' + self.name
        text += '(struct vc4_emul *emul, uint16_t *instr) {\n'
        text += '    ' + self.name + '_table[(instr[' + str(word) + '] & '
        text += hex(word_mask) + ') >> ' + str(low_bit) + '](emul, instr);\n'
        text += '}\n\n'
        # TODO
        self.text = text

    word = 0
    offset = 0
    size = 0
    name = ''
    text = ''

def indent_instruction(code):
    return '\n'.join("        " + line for line in code.splitlines())

def generateEmulator(db, filename, vcdbdir):
    # Retrieve the git hash of the version
    git = subprocess.Popen(['git', 'rev-parse', 'HEAD'], cwd=vcdbdir,
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if git.wait() != 0:
        version = 'UNKNOWN'
    else:
        version = git.stdout.read().rstrip('\n')
    # Generate the file header
    date = datetime.datetime.now().strftime("%Y-%m-%d %H:%M")
    text = ""+text_base;
    # Generate function auxiliary function definitions
    for group in db.function_lists:
        if len(group.functions) == 0:
            continue
        if group.brief != '' or group.desc != '':
            text += '/*\n'
            if group.brief != '':
                text += group.brief + '\n'
                if group.desc != '':
                    text += '\n'
            if group.desc != '':
                text += group.desc
            text += '*/\n\n'
        for function in group.functions:
            function_code = function.code.split('(', 1)
            text += function_code[0] + '(struct vc4_emul *emul, '
            text += function_code[1] + '\n'
        text += group.return_type + ' (*' + group.name
        text += '_table[])(struct vc4_emul *emul, ' + group.parameters
        text += ') = {\n'
        for function in group.functions:
            text +='\t' + function.name + ',\n'
        text += '};\n\n'
        param_count = len(group.parameters.split(','))
        parameters = ','.join(map(lambda x : 'p' + str(x), range(param_count)))
        text += '#define ' + group.name + '(index, ' + parameters + ') '
        text += group.name + '_table[index](emul, ' + parameters + ')\n\n'
    # Generate the instruction implementation
    text += '/* instructions */\n\n'
    for i in range(len(db.instructions)):
        instr = db.instructions[i]
        instr.function_name = 'instruction_' + str(i)
        text += 'void ' + instr.function_name
        text += '(struct vc4_emul *emul, uint16_t *instr) {\n'
        if instr.code != '':
            # Declare and compute the parameters
            for parameter in instr.parameters:
                if parameter.name[0] == 'R':
                    text += '    int ' + parameter.name + ' = '
                else:
                    text += '    uint32_t ' + parameter.name + ' = '
                first_word = parameter.offset // 16
                last_word = (parameter.offset + parameter.size - 1) // 16
                for word in range(first_word, last_word + 1):
                    if word != first_word:
                        text += ' | '
                    if word == first_word:
                        first_bit = parameter.offset % 16
                    else:
                        first_bit = 0
                    if word == last_word:
                        last_bit = (parameter.offset + parameter.size - 1) % 16 + 1
                        left_shift = 0
                    else:
                        last_bit = 16
                        left_shift = parameter.offset + parameter.size - (word + 1) * 16
                    mask = (0xffff >> first_bit) ^ (0xffff >> last_bit)
                    shift = 16 - last_bit - left_shift
                    if shift != 0:
                        text += '('
                    if mask != 0xffff:
                        text += '('
                    if word != last_word:
                        text += '(uint32_t)'
                    text += 'instr[' + str(word) + ']'
                    if mask != 0xffff:
                        text += ' & ' + hex(mask) + ')'
                    if shift < 0:
                        text += ' << ' + str(-shift) + ')'
                    elif shift > 0:
                        text += ' >> ' + str(shift) + ')'
                text += ';\n'
            # Insert the actual instruction implementation
            text += '    {\n' + indent_instruction(instr.code) + '\n    }\n'
            for parameter in instr.parameters:
                if parameter.name[0] == 'R':
                    text += '    #undef ' + parameter.name + '\n'
        else:
            text += '    error("Instruction not specified!\\n");\n'
        text += '}\n\n'
    # Generate the instruction decoder
    text += '/* decoder */\n\n'
    decoder = Decoder(db.instructions, 0)
    text += decoder.text
    # Generate the emulator step function
    text += '#define decode_instruction ' + decoder.name + '\n'

    with open(filename, 'w') as f:
        f.write(text)

