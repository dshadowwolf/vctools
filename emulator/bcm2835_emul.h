
#ifndef BCM2835_EMUL_H_INCLUDED
#define BCM2835_EMUL_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

#include "devices/mult.h"
#include "devices/inte.h"
//#include "devices/timer.h"
#include "devices/pm.h"
#include "devices/cm.h"
#include "devices/a2w.h"
#include "devices/gpio.h"
//#include "devices/mmc.h"
#include "devices/otp.h"
//#include "devices/aux.h"
#include "devices/sdco.h"

#define BOOTROM_BASE_ADDRESS 0x60000000
#define DRAM_BASE_ADDRESS 0x80000000

struct vc4_emul;

struct bcm2835_emul {
  struct vc4_emul *vc4;

  char *dram;
  char *bootram;

  struct mult_data mult;
  struct inte_data inte;
//  struct timer_data timer;
  struct pm_data pm;
  struct cm_data cm;
  struct a2w_data a2w;
  struct gpio_data gpio;
//  struct mmc_data mmc;
  struct otp_data otp;
//  struct aux_data aux;
  struct sdco_data sdco;
};

void memory_init ( struct bcm2835_emul *emul );
void memory_fill ( struct bcm2835_emul *emul,
                   uint32_t address, const void *data, size_t size );

void mult_init ( struct bcm2835_emul *emul );
uint32_t mult_load ( struct bcm2835_emul *emul, uint32_t address );
void mult_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void ccpt_init ( struct bcm2835_emul *emul );
uint32_t ccpt_load ( struct bcm2835_emul *emul, uint32_t address );
void ccpt_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void inte_init ( struct bcm2835_emul *emul );
uint32_t inte_load ( struct bcm2835_emul *emul, uint32_t address );
void inte_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void timer_init ( struct bcm2835_emul *emul );
uint32_t timer_load ( struct bcm2835_emul *emul, uint32_t address );
void timer_store ( struct bcm2835_emul *emul, uint32_t address,
                   uint32_t value );

void txp_init ( struct bcm2835_emul *emul );
uint32_t txp_load ( struct bcm2835_emul *emul, uint32_t address );
void txp_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void jpeg_init ( struct bcm2835_emul *emul );
uint32_t jpeg_load ( struct bcm2835_emul *emul, uint32_t address );
void jpeg_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void mphi_init ( struct bcm2835_emul *emul );
uint32_t mphi_load ( struct bcm2835_emul *emul, uint32_t address );
void mphi_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void dma_init ( struct bcm2835_emul *emul );
uint32_t dma_load ( struct bcm2835_emul *emul, uint32_t address );
void dma_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void nu_init ( struct bcm2835_emul *emul );
uint32_t nu_load ( struct bcm2835_emul *emul, uint32_t address );
void nu_store ( struct bcm2835_emul *emul, uint32_t address, uint32_t value );

void arba_init ( struct bcm2835_emul *emul );
uint32_t arba_load ( struct bcm2835_emul *emul, uint32_t address );
void arba_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void brdg_init ( struct bcm2835_emul *emul );
uint32_t brdg_load ( struct bcm2835_emul *emul, uint32_t address );
void brdg_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void armcb_init ( struct bcm2835_emul *emul );
uint32_t armcb_load ( struct bcm2835_emul *emul, uint32_t address );
void armcb_store ( struct bcm2835_emul *emul, uint32_t address,
                   uint32_t value );

void pm_init ( struct bcm2835_emul *emul );
uint32_t pm_load ( struct bcm2835_emul *emul, uint32_t address );
void pm_store ( struct bcm2835_emul *emul, uint32_t address, uint32_t value );

void cm_init ( struct bcm2835_emul *emul );
uint32_t cm_load ( struct bcm2835_emul *emul, uint32_t address );
void cm_store ( struct bcm2835_emul *emul, uint32_t address, uint32_t value );

void a2w_init ( struct bcm2835_emul *emul );
uint32_t a2w_load ( struct bcm2835_emul *emul, uint32_t address );
void a2w_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void avs_init ( struct bcm2835_emul *emul );
uint32_t avs_load ( struct bcm2835_emul *emul, uint32_t address );
void avs_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void rng_init ( struct bcm2835_emul *emul );
uint32_t rng_load ( struct bcm2835_emul *emul, uint32_t address );
void rng_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void gpio_init ( struct bcm2835_emul *emul );
uint32_t gpio_load ( struct bcm2835_emul *emul, uint32_t address );
void gpio_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void uart0_init ( struct bcm2835_emul *emul );
uint32_t uart0_load ( struct bcm2835_emul *emul, uint32_t address );
void uart0_store ( struct bcm2835_emul *emul, uint32_t address,
                   uint32_t value );

// altmmc
int mmc_init ( struct bcm2835_emul *emul, const char *sdcard_file );
uint32_t mmc_load ( struct bcm2835_emul *emul, uint32_t address );
void mmc_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void pcm_init ( struct bcm2835_emul *emul );
uint32_t pcm_load ( struct bcm2835_emul *emul, uint32_t address );
void pcm_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void spi0_init ( struct bcm2835_emul *emul );
uint32_t spi0_load ( struct bcm2835_emul *emul, uint32_t address );
void spi0_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void bsc0_init ( struct bcm2835_emul *emul );
uint32_t bsc0_load ( struct bcm2835_emul *emul, uint32_t address );
void bsc0_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void pixv0_init ( struct bcm2835_emul *emul );
uint32_t pixv0_load ( struct bcm2835_emul *emul, uint32_t address );
void pixv0_store ( struct bcm2835_emul *emul, uint32_t address,
                   uint32_t value );

void pixv1_init ( struct bcm2835_emul *emul );
uint32_t pixv1_load ( struct bcm2835_emul *emul, uint32_t address );
void pixv1_store ( struct bcm2835_emul *emul, uint32_t address,
                   uint32_t value );

void dpi_init ( struct bcm2835_emul *emul );
uint32_t dpi_load ( struct bcm2835_emul *emul, uint32_t address );
void dpi_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void dsi0_init ( struct bcm2835_emul *emul );
uint32_t dsi0_load ( struct bcm2835_emul *emul, uint32_t address );
void dsi0_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void tb_init ( struct bcm2835_emul *emul );
uint32_t tb_load ( struct bcm2835_emul *emul, uint32_t address );
void tb_store ( struct bcm2835_emul *emul, uint32_t address, uint32_t value );

void pwm0_init ( struct bcm2835_emul *emul );
uint32_t pwm0_load ( struct bcm2835_emul *emul, uint32_t address );
void pwm0_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void perm_init ( struct bcm2835_emul *emul );
uint32_t perm_load ( struct bcm2835_emul *emul, uint32_t address );
void perm_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void tec_init ( struct bcm2835_emul *emul );
uint32_t tec_load ( struct bcm2835_emul *emul, uint32_t address );
void tec_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void otp_init ( struct bcm2835_emul *emul );
uint32_t otp_load ( struct bcm2835_emul *emul, uint32_t address );
void otp_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void slim_init ( struct bcm2835_emul *emul );
uint32_t slim_load ( struct bcm2835_emul *emul, uint32_t address );
void slim_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void cpg_init ( struct bcm2835_emul *emul );
uint32_t cpg_load ( struct bcm2835_emul *emul, uint32_t address );
void cpg_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void ts_init ( struct bcm2835_emul *emul );
uint32_t ts_load ( struct bcm2835_emul *emul, uint32_t address );
void ts_store ( struct bcm2835_emul *emul, uint32_t address, uint32_t value );

void avsp_init ( struct bcm2835_emul *emul );
uint32_t avsp_load ( struct bcm2835_emul *emul, uint32_t address );
void avsp_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void i2cspislv_init ( struct bcm2835_emul *emul );
uint32_t i2cspislv_load ( struct bcm2835_emul *emul, uint32_t address );
void i2cspislv_store ( struct bcm2835_emul *emul, uint32_t address,
                       uint32_t value );

void aux_init ( struct bcm2835_emul *emul );
uint32_t aux_load ( struct bcm2835_emul *emul, uint32_t address );
void aux_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void aveout_init ( struct bcm2835_emul *emul );
uint32_t aveout_load ( struct bcm2835_emul *emul, uint32_t address );
void aveout_store ( struct bcm2835_emul *emul, uint32_t address,
                    uint32_t value );

void emmc_init ( struct bcm2835_emul *emul );
uint32_t emmc_load ( struct bcm2835_emul *emul, uint32_t address );
void emmc_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void ddrv_init ( struct bcm2835_emul *emul );
uint32_t ddrv_load ( struct bcm2835_emul *emul, uint32_t address );
void ddrv_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void smi_init ( struct bcm2835_emul *emul );
uint32_t smi_load ( struct bcm2835_emul *emul, uint32_t address );
void smi_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void dsi1_init ( struct bcm2835_emul *emul );
uint32_t dsi1_load ( struct bcm2835_emul *emul, uint32_t address );
void dsi1_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void cam0_init ( struct bcm2835_emul *emul );
uint32_t cam0_load ( struct bcm2835_emul *emul, uint32_t address );
void cam0_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void cam1_init ( struct bcm2835_emul *emul );
uint32_t cam1_load ( struct bcm2835_emul *emul, uint32_t address );
void cam1_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void cmi_init ( struct bcm2835_emul *emul );
uint32_t cmi_load ( struct bcm2835_emul *emul, uint32_t address );
void cmi_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void bsc1_init ( struct bcm2835_emul *emul );
uint32_t bsc1_load ( struct bcm2835_emul *emul, uint32_t address );
void bsc1_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void bsc2_init ( struct bcm2835_emul *emul );
uint32_t bsc2_load ( struct bcm2835_emul *emul, uint32_t address );
void bsc2_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void vec_init ( struct bcm2835_emul *emul );
uint32_t vec_load ( struct bcm2835_emul *emul, uint32_t address );
void vec_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void pixv2_init ( struct bcm2835_emul *emul );
uint32_t pixv2_load ( struct bcm2835_emul *emul, uint32_t address );
void pixv2_store ( struct bcm2835_emul *emul, uint32_t address,
                   uint32_t value );

void hd_init ( struct bcm2835_emul *emul );
uint32_t hd_load ( struct bcm2835_emul *emul, uint32_t address );
void hd_store ( struct bcm2835_emul *emul, uint32_t address, uint32_t value );

void hdcp_init ( struct bcm2835_emul *emul );
uint32_t hdcp_load ( struct bcm2835_emul *emul, uint32_t address );
void hdcp_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void piarbctl_init ( struct bcm2835_emul *emul );
uint32_t piarbctl_load ( struct bcm2835_emul *emul, uint32_t address );
void piarbctl_store ( struct bcm2835_emul *emul, uint32_t address,
                      uint32_t value );

void hdmi_init ( struct bcm2835_emul *emul );
uint32_t hdmi_load ( struct bcm2835_emul *emul, uint32_t address );
void hdmi_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void avein_init ( struct bcm2835_emul *emul );
uint32_t avein_load ( struct bcm2835_emul *emul, uint32_t address );
void avein_store ( struct bcm2835_emul *emul, uint32_t address,
                   uint32_t value );

void usb_init ( struct bcm2835_emul *emul );
uint32_t usb_load ( struct bcm2835_emul *emul, uint32_t address );
void usb_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void isp_init ( struct bcm2835_emul *emul );
uint32_t isp_load ( struct bcm2835_emul *emul, uint32_t address );
void isp_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void v3d_init ( struct bcm2835_emul *emul );
uint32_t v3d_load ( struct bcm2835_emul *emul, uint32_t address );
void v3d_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

void sdco_init ( struct bcm2835_emul *emul );
uint32_t sdco_load ( struct bcm2835_emul *emul, uint32_t address );
void sdco_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void l2cc_init ( struct bcm2835_emul *emul );
uint32_t l2cc_load ( struct bcm2835_emul *emul, uint32_t address );
void l2cc_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void l1cc_init ( struct bcm2835_emul *emul );
uint32_t l1cc_load ( struct bcm2835_emul *emul, uint32_t address );
void l1cc_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void arbr_init ( struct bcm2835_emul *emul );
uint32_t arbr_load ( struct bcm2835_emul *emul, uint32_t address );
void arbr_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void dma15_init ( struct bcm2835_emul *emul );
uint32_t dma15_load ( struct bcm2835_emul *emul, uint32_t address );
void dma15_store ( struct bcm2835_emul *emul, uint32_t address,
                   uint32_t value );

void aphycsr_init ( struct bcm2835_emul *emul );
uint32_t aphycsr_load ( struct bcm2835_emul *emul, uint32_t address );
void aphycsr_store ( struct bcm2835_emul *emul, uint32_t address,
                     uint32_t value );

void dcrc_init ( struct bcm2835_emul *emul );
uint32_t dcrc_load ( struct bcm2835_emul *emul, uint32_t address );
void dcrc_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void axip_init ( struct bcm2835_emul *emul );
uint32_t axip_load ( struct bcm2835_emul *emul, uint32_t address );
void axip_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void h264_init ( struct bcm2835_emul *emul );
uint32_t h264_load ( struct bcm2835_emul *emul, uint32_t address );
void h264_store ( struct bcm2835_emul *emul, uint32_t address,
                  uint32_t value );

void vce_init ( struct bcm2835_emul *emul );
uint32_t vce_load ( struct bcm2835_emul *emul, uint32_t address );
void vce_store ( struct bcm2835_emul *emul, uint32_t address,
                 uint32_t value );

#endif
