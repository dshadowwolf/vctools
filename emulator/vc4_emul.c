
/**
 * VideoCore IV Emulator
 *
 * This file was automatically generated from the instruction database version
 * $VERSION (git) on $DATE.
 * Do not modify!
 */

#include "vc4_emul.h"
#include "vc4_data.h"
#include "vc4_registers.h"

extern void decoder_0 (struct vc4_emul *emul, uint16_t * instr);

#define decode_instruction(em, in) decoder_0((em), (in))

/* SR status bits */
uint32_t
condition_flags (uint64_t cmp_result) {
  const unsigned int Z = 8, N = 4, C = 2, V = 1;
  unsigned int status = 0;

  if (cmp_result == 0) {
    status |= Z;
  }
  if (cmp_result & 0x80000000) {
    status |= N;
  }
  if (cmp_result & 0x100000000ull) {
    status |= C;
  }
  if (cmp_result != (int32_t) cmp_result) {
    status |= V;
  }
  return status;
}

/* fatal errors */
void
error (struct vc4_emul *emul, const char *reason) {
  /*
   * TODO 
   */
  print_log (reason);
  assert (0 && "Not implemented!\\n");
}

#define error(reason) error(emul, reason)

void
vc4_emul_interrupt (struct vc4_emul *emul,
                    unsigned int interrupt, const char *reason) {
  int i;

  print_log ("Interrupt %d: %s\\n", interrupt, reason);
  for (i = MIN_REGISTER; i < MAX_REGISTER; i++) {
    print_log ("  r%d = %08x\\n", i, emul->scalar_regs[i]);
  }
  uint32_t ivt = vc4_emul_get_ivt_address (emul->user_data);
  uint32_t int_stack = emul->scalar_regs[REGISTER_ESP];

  store (int_stack - 4, WORD, get_reg (pc));
  store (int_stack - 8, WORD, get_reg (sr));
  emul->scalar_regs[REGISTER_ESP] = int_stack - 8;

  set_reg (pc, load (ivt + (interrupt - 1) * 4, WORD));
  set_reg (sr, get_reg (sr) | (1 << 30));

  /*
   * TODO 
   */
  //assert(0 && "Not implemented.\\n");
  exit (EXIT_FAILURE);
}

void
vc4_emul_step (struct vc4_emul *emul) {
  uint16_t instr[5];
  uint32_t old_pc;
  uint32_t old_sr = emul->scalar_regs[REGISTER_SP];
  int instr_size = 2;

  /*
   * handle exceptions which occur during execution 
   */
  int exception_index = sigsetjmp (emul->exception_handler, 0);

  if (exception_index != 0) {
    uint32_t ivt = vc4_emul_get_ivt_address (emul->user_data);
    uint32_t int_stack = emul->scalar_regs[REGISTER_ESP];

    print_log ("Exception %d\\n", exception_index);
    /*
     * increment pc 
     */
    instr[0] = load (get_reg (pc), HALFWORD);
    set_reg (pc, get_reg (pc) + 2);
    if (instr[0] & 0x8000) {
      set_reg (pc, get_reg (pc) + 2);
      if (instr[0] > 0xe000) {
        set_reg (pc, get_reg (pc) + 2);
        if (instr[0] > 0xf000) {
          if (instr[0] > 0xf800) {
            set_reg (pc, get_reg (pc) + 4);
          }
        }
      }
    }
    /*
     * push pc and sr onto the stack 
     */
    store (int_stack - 4, WORD, get_reg (pc));
    store (int_stack - 8, WORD, get_reg (sr));
    emul->scalar_regs[REGISTER_ESP] = int_stack - 8;
    /*
     * load new pc and sr 
     */
    set_reg (pc, load (ivt + (exception_index - 1) * 4, WORD));
    /*
     * TODO: correct bit? 
     */
    set_reg (sr, get_reg (sr) | (1 << 30));
    return;
  }
  /*
   * fetch the instruction 
   */
  emul->pc_changed = 0;
  old_pc = get_reg (pc);
  instr[0] = load (get_reg (pc), HALFWORD);
  if (instr[0] & 0x8000) {      // Was 0x8000 or higher
    if ((instr[0] >= 0xe000) && (instr[0] < 0xf000)) {  // Was between 0xe000 and 0xefff
      instr[1] = load (get_reg (pc) + 2, HALFWORD); // Programmers Manual says these should be the other way round.
      instr[2] = load (get_reg (pc) + 4, HALFWORD); // ""
      instr_size = 6;
      // print_log("instr0 was a scalar48\\n");
    } else {                    /* instr[0] is 80 - df */// Was 0x8000 - 0xffff, but not between 0xe000 and 0xefff
      instr[1] = load (get_reg (pc) + 2, HALFWORD);
      if (instr[0] < 0xe000) {  // Was 0x8000 - 0xdfff
        instr_size = 4;
        // print_log("instr0 was a scalar32\\n");
      } else {                  // Was 0xf000-0xffff
        instr[2] = load (get_reg (pc) + 4, HALFWORD);
        if (instr[0] >= 0xf800) { // Was 0xf8000
          instr[3] = load (get_reg (pc) + 6, HALFWORD);
          instr[4] = load (get_reg (pc) + 8, HALFWORD);
          instr_size = 10;
          // print_log("instr0 was a vector80\\n");
        } else {
          instr_size = 6;
          // print_log("instr0 was a vector48\\n");
        }
      }
    }
  } else {
    // print_log("instr0 was a scalar16\\n");
  }
  /*
   * if (instr[0] & 0x8000) {
   * instr[1] = load(get_reg(pc) + 2, HALFWORD);
   * instr_size = 4;
   * if (instr[0] > 0xe000) {
   * instr[2] = load(get_reg(pc) + 4, HALFWORD);
   * instr_size = 6;
   * }
   * }
   */
  /*
   * switch r25 to r28 if necessary 
   */
  /*
   * TODO 
   */
  /*
   * decode and execute the instruction 
   */
  if (get_reg (sr) & (1 << 30)) {
    uint32_t old_sp = emul->scalar_regs[REGISTER_SP];

    emul->scalar_regs[REGISTER_SP] = emul->scalar_regs[REGISTER_ESP];
    decode_instruction (emul, instr);
    emul->scalar_regs[REGISTER_SP] = old_sp;
  } else {
    decode_instruction (emul, instr);
  }
  /*
   * increase the program counter 
   */
  if (emul->pc_changed == 0) {
    set_reg (pc, get_reg (pc) + instr_size);
  }
}
