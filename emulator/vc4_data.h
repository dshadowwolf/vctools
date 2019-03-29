
/**
 * VideoCore IV Emulator
 *
 * This file was automatically generated from the instruction database version
 * $VERSION (git) on $DATE.
 * Do not modify!
 */

#pragma once
#include "vc4_emul.h"
#include "vc4_registers.h"

#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

struct vc4_emul {
  void *user_data;

  uint32_t scalar_regs[MAX_REGISTER];
  int pc_changed;

  uint32_t ivt;

  sigjmp_buf exception_handler;
};

/* load/store formats */
#define WORD 0
#define HALFWORD 1
#define BYTE 2
#define SIGNED_HALFWORD 3

/* registers */
#define pc (31)
#define sr (30)
#define gp (24)
#define sp (25)
#define lr (26)
#define esp (28)
#define tp (29)
#define r15 (15)
#define get_reg(reg) _get_reg(emul, reg)
#define set_reg(reg, value) _set_reg(emul, reg, value)
#define sign_extend_1(x) sign_extend(x, 1)
#define sign_extend_2(x) sign_extend(x, 2)
#define sign_extend_3(x) sign_extend(x, 3)
#define sign_extend_4(x) sign_extend(x, 4)
#define sign_extend_5(x) sign_extend(x, 5)
#define sign_extend_6(x) sign_extend(x, 6)
#define sign_extend_7(x) sign_extend(x, 7)
#define sign_extend_8(x) sign_extend(x, 8)
#define sign_extend_9(x) sign_extend(x, 9)
#define sign_extend_10(x) sign_extend(x, 10)
#define sign_extend_11(x) sign_extend(x, 11)
#define sign_extend_12(x) sign_extend(x, 12)
#define sign_extend_13(x) sign_extend(x, 13)
#define sign_extend_14(x) sign_extend(x, 14)
#define sign_extend_15(x) sign_extend(x, 15)
#define sign_extend_16(x) sign_extend(x, 16)
#define sign_extend_17(x) sign_extend(x, 17)
#define sign_extend_18(x) sign_extend(x, 18)
#define sign_extend_19(x) sign_extend(x, 19)
#define sign_extend_20(x) sign_extend(x, 20)
#define sign_extend_21(x) sign_extend(x, 21)
#define sign_extend_22(x) sign_extend(x, 22)
#define sign_extend_23(x) sign_extend(x, 23)
#define sign_extend_24(x) sign_extend(x, 24)
#define sign_extend_25(x) sign_extend(x, 25)
#define sign_extend_26(x) sign_extend(x, 26)
#define sign_extend_27(x) sign_extend(x, 27)
#define sign_extend_28(x) sign_extend(x, 28)
#define sign_extend_29(x) sign_extend(x, 29)
#define sign_extend_30(x) sign_extend(x, 30)
#define sign_extend_31(x) sign_extend(x, 31)

/* type conversion */
#define to_uint64(x) (uint64_t)(x)
#define to_int64(x) (int64_t)(int32_t)(x)
#define load(address, format) _load(emul, address, format)
#define store(address, format, value) _store(emul, address, format, value)
#define push(x) _push(emul, x)
#define pop() _pop(emul)

struct vc4_emul *vc4_emul_init (void *user_data);
void vc4_emul_free (struct vc4_emul *emul);
void vc4_emul_exec (struct vc4_emul *emul, unsigned int steps);
void vc4_emul_exception (struct vc4_emul *emul, unsigned int interrupt,
                         const char *reason);
void vc4_emul_set_scalar_reg (struct vc4_emul *emul, int reg, uint32_t value);
uint32_t vc4_emul_get_scalar_reg (struct vc4_emul *emul, int reg);
uint32_t _get_reg (struct vc4_emul *emul, int reg);
void _set_reg (struct vc4_emul *emul, int reg, uint32_t value);

/* sign extension */
uint32_t sign_extend (uint32_t value, int bits);
float int_to_float (uint32_t x);
int32_t float_to_int (float x);
int size (int format);
uint32_t _load (struct vc4_emul *emul, uint32_t address, int format);
void _store (struct vc4_emul *emul, uint32_t address, int format,
             uint32_t value);

/* push/pop */
void _push (struct vc4_emul *emul, uint32_t value);
uint32_t _pop (struct vc4_emul *emul);

typedef void (*instruction_function) (struct vc4_emul * emul,
                                      uint16_t * instr);
