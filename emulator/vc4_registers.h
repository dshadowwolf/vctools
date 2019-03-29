#ifndef VC4_REGISTERS_H
#define VC4_REGISTERS_H

// General
#define REGISTER_0   0
#define REGISTER_1   1
#define REGISTER_2   2
#define REGISTER_3   3
#define REGISTER_4   4
#define REGISTER_5   5
#define REGISTER_6   6
#define REGISTER_7   7
#define REGISTER_8   8
#define REGISTER_9   9
#define REGISTER_10  10
#define REGISTER_11  11
#define REGISTER_12  12
#define REGISTER_13  13
#define REGISTER_14  14
#define REGISTER_15  15

// Extended
#define REGISTER_16  16
#define REGISTER_17  17
#define REGISTER_18  18
#define REGISTER_19  19
#define REGISTER_20  20
#define REGISTER_21  21
#define REGISTER_22  22
#define REGISTER_23  23

// Special
#define REGISTER_24  24
#define REGISTER_GP  24
#define REGISTER_25  25
#define REGISTER_SP  25
#define REGISTER_26  26
#define REGISTER_LR  26
#define REGISTER_27  27
//#define REGISTER_??  27
#define REGISTER_28  28
#define REGISTER_ESP 28
#define REGISTER_29  29
#define REGISTER_TP  29
#define REGISTER_30  30
#define REGISTER_SR  30
#define REGISTER_31  31
#define REGISTER_PC  31

// Processor Status Register Flags
#define PSR_FLAG_OVERFLOW   (1 << 0)
#define PSR_FLAG_CARRY      (1 << 1)
#define PSR_FLAG_NEGATIVE   (1 << 2)
#define PSR_FLAG_ZERO       (1 << 3)
//#define PSR_CB_OFFSET      4+5
#define PSR_FLAG_SUPERVISOR (1 << 29)
#define PSR_FLAG_INTERRUPT  (1 << 30)
#define PSR_FLAG_USER       (1 << 31)

// PRocessor Control Registers
#define PROCESSOR_PRFPXCS   0
#define PROCESSOR_PRCANARY  1
#define PROCESSOR_PRPOWCTL 10
#define PROCESSOR_PRTIMCTL 11
#define PROCESSOR_PRCORTIM 12
#define PROCESSOR_PRSLPTIM 13
#define PROCESSOR_PROWTCNT 14
#define PROCESSOR_PRORCNT  15
#define PROCESSOR_PRSPINL  16

#define MIN_REGISTER  0
#define MAX_REGISTER 32         // Always one less than this

#endif
