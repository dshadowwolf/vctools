#pragma once
#include <stdint.h>

#include "vc4_registers.h"

extern void print_log(const char *fmt, ...);
struct vc4_emul;

/**
 * Loads a value from memory. This function is called by the emulator and has
 * to be implemented externally.
 *
 * @param user_data Opaque pointer which has been specified in vc4_emul_init().
 * @param address Address of the memory access.
 * @param size Size of the data to be loaded from memory.
 * @return Data which is read from memory.
 */
uint32_t vc4_emul_load(void *user_data,
                       uint32_t address,
                       int size);
/**
 * Stores a value in the memory. This function is called by the emulator and
 * has to be implemented externally.
 *
 * @param user_data Opaque pointer which has been specified in vc4_emul_init().
 * @param address Address of the memory access.
 * @param size Size of the data to be stored in memory.
 * @param value Value which is stored in memory.
 */
void vc4_emul_store(void *user_data,
                    uint32_t address,
                    int size,
                    uint32_t value);
/**
 * Returns the address of the current interrupt vector table. This function is
 * called by the emulator when an interrupt occurs and has to be implemented
 * externally.
 *
 * @param user_data Opaque pointer which has been specified in vc4_emul_init().
 * @return Address of the interrupt vector table.
 */
uint32_t vc4_emul_get_ivt_address(void *user_data);

/**
 * Initializes a new emulator instance. Initially, all registers are zero.
 *
 * @param user_data Opaque user pointer which can be used for identification
 *                  in vc4_emul_load() and vc4_emul_store().
 * @return New emulator instance.
 */
struct vc4_emul *vc4_emul_init(void *user_data);
/**
 * Destroys an emulator instance which has been previously allocated by
 * vc4_emul_init().
 *
 * @param emul Emulator to be destroyed.
 */
void vc4_emul_free(struct vc4_emul *emul);

void vc4_emul_step(struct vc4_emul *emul);
void vc4_emul_exec(struct vc4_emul *emul, unsigned int steps);

__attribute__((noreturn))
void vc4_emul_interrupt(struct vc4_emul *emul,
                        unsigned int interrupt,
                        const char *reason);

void vc4_emul_set_scalar_reg(struct vc4_emul *emul, int reg, uint32_t value);
uint32_t vc4_emul_get_scalar_reg(struct vc4_emul *emul, int reg);
#define V(x) ((x & 0x1) != 0)
#define C(x) ((x & 0x2) != 0)
#define N(x) ((x & 0x4) != 0)
#define Z(x) ((x & 0x8) != 0)
/* interrupts/exceptions */
#define interrupt(index, reason) vc4_emul_exception(emul, index, reason)

uint32_t condition_flags(uint64_t cmp_result);
void error(struct vc4_emul *emul, const char *reason);
