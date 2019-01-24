
#ifndef DEVICES_OTP_H_INCLUDED
#define DEVICES_OTP_H_INCLUDED
#include <stdint.h>
#include <stdbool.h>

struct otp_data {
  uint32_t registers[9];
  uint32_t *otp_memory;
  bool awake;
  struct {
    bool seen_three;
    bool seen_lo_zero;
    bool seen_hi_zero;
    bool seen_two;
  } state;
};

#endif

