
#ifndef DEVICES_OTP_H_INCLUDED
#define DEVICES_OTP_H_INCLUDED
#include <inttypes.h>

struct otp_data {
  uint32_t registers[9];
  uint32_t *otp_memory;
};

#endif

