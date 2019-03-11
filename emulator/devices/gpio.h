
#ifndef DEVICES_GPIO_H_INCLUDED
#define DEVICES_GPIO_H_INCLUDED

struct gpio_data {
  uint32_t fsel[7];
  uint32_t lev[3];
  uint32_t eds[3];
  uint32_t ren[3];
  uint32_t fen[3];
  uint32_t hen[3];
  uint32_t len[3];
  uint32_t aren[3];
  uint32_t afen[3];
  uint32_t pud;
  uint32_t pudclk[3];
  uint32_t sen[2];
  uint32_t gptest;
  uint32_t ajbconf;
  uint32_t ajbtms;
  uint32_t ajbtdi;
  uint32_t ajbtdo;
  uint32_t output_level[2];
};

#endif
