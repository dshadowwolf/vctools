#include <stdint.h>
#include "vc4_data.h"
 struct vc4_emul *
vc4_emul_init (void *user_data) {
  struct vc4_emul *emul = calloc (1, sizeof (struct vc4_emul));

  emul->scalar_regs[REGISTER_SP] = 0x600087AC;
  emul->user_data = user_data;
  return emul;
}

void
vc4_emul_free (struct vc4_emul *emul) {
  free (emul);
}  void
vc4_emul_exec (struct vc4_emul *emul, unsigned int steps) {
  unsigned int i;

  for (i = 0; i < steps; i++) {
    vc4_emul_step (emul);
  }
}

 void
vc4_emul_exception (struct vc4_emul *emul, unsigned int interrupt,
                    const char *reason) {
  
//    uint16_t instr;
  int i;

  print_log ("Exception %d: %s\\n", interrupt, reason);
  for (i = MIN_REGISTER; i < MAX_REGISTER; i++) {
    print_log ("  r%d = %08x\\n", i, emul->scalar_regs[i]);
  }
   siglongjmp (emul->exception_handler, interrupt + 1);
}

 void
vc4_emul_set_scalar_reg (struct vc4_emul *emul, int reg, uint32_t value) {
  assert (reg >= MIN_REGISTER && reg < MAX_REGISTER);
  emul->scalar_regs[reg] = value;
} uint32_t vc4_emul_get_scalar_reg (struct vc4_emul *emul, int reg) {

  assert (reg >= MIN_REGISTER && reg < MAX_REGISTER);
  return emul->scalar_regs[reg];
}
uint32_t _get_reg (struct vc4_emul * emul, int reg) {
  assert (reg >= MIN_REGISTER && reg < MAX_REGISTER);
  if ((emul->scalar_regs[REGISTER_SR] & (1 << 30)) != 0
       && reg == REGISTER_SP) {
    reg = REGISTER_ESP;
  }
  return emul->scalar_regs[reg];
}

void
_set_reg (struct vc4_emul *emul, int reg, uint32_t value) {
  assert (reg >= MIN_REGISTER && reg < MAX_REGISTER);
  if ((emul->scalar_regs[REGISTER_SR] & (1 << 30)) != 0
       && reg == REGISTER_SP) {
    reg = REGISTER_ESP;
  }
  if (reg == REGISTER_PC) {
    emul->pc_changed = 1;
  }
  
    /*
     * print_log("r%d <= %08x\\n", reg, value);
     */ 
    emul->scalar_regs[reg] = value;
}
inline uint32_t sign_extend (uint32_t value, int bits) {
  value &= (1 << bits) - 1;
  if (value & (1 << (bits - 1))) {
    return value | ~((1 << bits) - 1);
  } else {
    return value;
  }
}

float
int_to_float (uint32_t x) {
  return *(float *) &x;
} int32_t float_to_int (float x) {

  return *(int32_t *) & x;
}

 

/* memory access functions */ 
  int
size (int format) {
  switch (format) {
  case WORD:
    return 4;
  case HALFWORD:
  case SIGNED_HALFWORD:
    return 2;
  case BYTE:
    return 1;
  default:
    return 0;
  }
}
 uint32_t _load (struct vc4_emul * emul, uint32_t address, int format) {
  uint32_t value;
  int format_size = size (format);

  if (address & (format_size - 1)) {
    
      /*
       * TODO: Is this the correct exception number? 
       */ 
      interrupt (1, "load: invalid alignment.");
  }
  value = vc4_emul_load (emul->user_data, address, format_size);
  if (format == SIGNED_HALFWORD) {
    value = sign_extend (value, 16);
  }
  return value;
}

void
_store (struct vc4_emul *emul, uint32_t address, int format,
        uint32_t value) {
  int format_size = size (format);

  if (address & (format_size - 1)) {
    
      /*
       * TODO: Is this the correct exception number? 
       */ 
      interrupt (1, "store: invalid alignment.");
  }
  vc4_emul_store (emul->user_data, address, format_size, value);
}

void
_push (struct vc4_emul *emul, uint32_t value) {
  _set_reg (emul, sp, _get_reg (emul, sp) - 4);
  _store (emul, _get_reg (emul, sp), WORD, value);
} uint32_t _pop (struct vc4_emul *emul) {

  uint32_t value = _load (emul, _get_reg (emul, sp), WORD);
  _set_reg (emul, sp, _get_reg (emul, sp) + 4);
  return value;
}


