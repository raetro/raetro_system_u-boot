/*
 *  Copyright (C) 2013 Altera Corporation <www.altera.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef    _CLOCK_MANAGER_H_
#define    _CLOCK_MANAGER_H_

#ifndef __ASSEMBLER__

/* Clock speed accessors */
unsigned long cm_get_mpu_clk_hz(void);

unsigned long cm_get_sdram_clk_hz(void);

unsigned int cm_get_l4_sp_clk_hz(void);

unsigned int cm_get_mmc_controller_clk_hz(void);

unsigned int cm_get_qspi_controller_clk_hz(void);

unsigned int cm_get_spi_controller_clk_hz(void);

const unsigned int cm_get_osc_clk_hz(const int osc);

const unsigned int cm_get_f2s_per_ref_clk_hz(void);

const unsigned int cm_get_f2s_sdr_ref_clk_hz(void);

/* Clock configuration accessors */
const struct cm_config *const cm_get_default_config(void);

#endif

struct cm_config {
	/* main group */
	uint32_t main_vco_base;
	uint32_t mpuclk;
	uint32_t mainclk;
	uint32_t dbgatclk;
	uint32_t mainqspiclk;
	uint32_t mainnandsdmmcclk;
	uint32_t cfg2fuser0clk;
	uint32_t maindiv;
	uint32_t dbgdiv;
	uint32_t tracediv;
	uint32_t l4src;

	/* peripheral group */
	uint32_t peri_vco_base;
	uint32_t emac0clk;
	uint32_t emac1clk;
	uint32_t perqspiclk;
	uint32_t pernandsdmmcclk;
	uint32_t perbaseclk;
	uint32_t s2fuser1clk;
	uint32_t perdiv;
	uint32_t gpiodiv;
	uint32_t persrc;

	/* sdram pll group */
	uint32_t sdram_vco_base;
	uint32_t ddrdqsclk;
	uint32_t ddr2xdqsclk;
	uint32_t ddrdqclk;
	uint32_t s2fuser2clk;

	/* altera group */
	uint32_t altera_grp_mpuclk;
};

void cm_basic_init(const struct cm_config *const cfg);

struct socfpga_clock_manager_main_pll {
	u32 vco;
	u32 misc;
	u32 mpuclk;
	u32 mainclk;
	u32 dbgatclk;
	u32 mainqspiclk;
	u32 mainnandsdmmcclk;
	u32 cfgs2fuser0clk;
	u32 en;
	u32 maindiv;
	u32 dbgdiv;
	u32 tracediv;
	u32 l4src;
	u32 stat;
	u32 _pad_0x38_0x40[2];
};

struct socfpga_clock_manager_per_pll {
	u32 vco;
	u32 misc;
	u32 emac0clk;
	u32 emac1clk;
	u32 perqspiclk;
	u32 pernandsdmmcclk;
	u32 perbaseclk;
	u32 s2fuser1clk;
	u32 en;
	u32 div;
	u32 gpiodiv;
	u32 src;
	u32 stat;
	u32 _pad_0x34_0x40[3];
};

struct socfpga_clock_manager_sdr_pll {
	u32 vco;
	u32 ctrl;
	u32 ddrdqsclk;
	u32 ddr2xdqsclk;
	u32 ddrdqclk;
	u32 s2fuser2clk;
	u32 en;
	u32 stat;
};

struct socfpga_clock_manager_altera {
	u32 mpuclk;
	u32 mainclk;
};

struct socfpga_clock_manager {
	u32 ctrl;
	u32 bypass;
	u32 inter;
	u32 intren;
	u32 dbctrl;
	u32 stat;
	u32 _pad_0x18_0x3f[10];
	struct socfpga_clock_manager_main_pll main_pll;
	struct socfpga_clock_manager_per_pll per_pll;
	struct socfpga_clock_manager_sdr_pll sdr_pll;
	struct socfpga_clock_manager_altera altera;
	u32 _pad_0xe8_0x200[70];
};

#define CLKMGR_CTRL_SAFEMODE                          (1 << 0)
#define CLKMGR_CTRL_SAFEMODE_OFFSET                   0

#define CLKMGR_BYPASS_PERPLLSRC                       (1 << 4)
#define CLKMGR_BYPASS_PERPLLSRC_OFFSET                4
#define CLKMGR_BYPASS_PERPLL                          (1 << 3)
#define CLKMGR_BYPASS_PERPLL_OFFSET                   3
#define CLKMGR_BYPASS_SDRPLLSRC                       (1 << 2)
#define CLKMGR_BYPASS_SDRPLLSRC_OFFSET                2
#define CLKMGR_BYPASS_SDRPLL                          (1 << 1)
#define CLKMGR_BYPASS_SDRPLL_OFFSET                   1
#define CLKMGR_BYPASS_MAINPLL                         (1 << 0)
#define CLKMGR_BYPASS_MAINPLL_OFFSET                  0

#define CLKMGR_INTER_SDRPLLLOCKED_MASK                0x00000100
#define CLKMGR_INTER_PERPLLLOCKED_MASK                0x00000080
#define CLKMGR_INTER_MAINPLLLOCKED_MASK               0x00000040
#define CLKMGR_INTER_PERPLLLOST_MASK                  0x00000010
#define CLKMGR_INTER_SDRPLLLOST_MASK                  0x00000020
#define CLKMGR_INTER_MAINPLLLOST_MASK                 0x00000008

#define CLKMGR_STAT_BUSY                              (1 << 0)

/* Main PLL */
#define CLKMGR_MAINPLLGRP_VCO_BGPWRDN                 (1 << 0)
#define CLKMGR_MAINPLLGRP_VCO_BGPWRDN_OFFSET          0
#define CLKMGR_MAINPLLGRP_VCO_DENOM_OFFSET            16
#define CLKMGR_MAINPLLGRP_VCO_DENOM_MASK              0x003f0000
#define CLKMGR_MAINPLLGRP_VCO_EN                      (1 << 1)
#define CLKMGR_MAINPLLGRP_VCO_EN_OFFSET               1
#define CLKMGR_MAINPLLGRP_VCO_NUMER_OFFSET            3
#define CLKMGR_MAINPLLGRP_VCO_NUMER_MASK              0x0000fff8
#define CLKMGR_MAINPLLGRP_VCO_OUTRESETALL_MASK        0x01000000
#define CLKMGR_MAINPLLGRP_VCO_PWRDN                   (1 << 2)

#define CLKMGR_MAINPLLGRP_VCO_PWRDN_OFFSET            2
#define CLKMGR_MAINPLLGRP_VCO_REGEXTSEL_MASK          0x80000000
#define CLKMGR_MAINPLLGRP_VCO_RESET_VALUE             0x8001000d

#define CLKMGR_MAINPLLGRP_MPUCLK_CNT_OFFSET           0
#define CLKMGR_MAINPLLGRP_MPUCLK_CNT_MASK             0x000001ff

#define CLKMGR_MAINPLLGRP_MAINCLK_CNT_OFFSET          0
#define CLKMGR_MAINPLLGRP_MAINCLK_CNT_MASK            0x000001ff

#define CLKMGR_MAINPLLGRP_DBGATCLK_CNT_OFFSET         0
#define CLKMGR_MAINPLLGRP_DBGATCLK_CNT_MASK           0x000001ff

#define CLKMGR_MAINPLLGRP_MAINQSPICLK_CNT_OFFSET      0
#define CLKMGR_MAINPLLGRP_MAINQSPICLK_CNT_MASK        0x000001ff

#define CLKMGR_MAINPLLGRP_MAINNANDSDMMCCLK_CNT_OFFSET 0
#define CLKMGR_MAINPLLGRP_MAINNANDSDMMCCLK_CNT_MASK   0x000001ff

#define CLKMGR_MAINPLLGRP_CFGS2FUSER0CLK_CNT_OFFSET   0
#define CLKMGR_MAINPLLGRP_CFGS2FUSER0CLK_CNT_MASK     0x000001ff

#define CLKMGR_MAINPLLGRP_EN_DBGATCLK_MASK            0x00000010
#define CLKMGR_MAINPLLGRP_EN_DBGCLK_MASK              0x00000020
#define CLKMGR_MAINPLLGRP_EN_DBGTIMERCLK_MASK         0x00000080
#define CLKMGR_MAINPLLGRP_EN_DBGTRACECLK_MASK         0x00000040
#define CLKMGR_MAINPLLGRP_EN_L4MPCLK_MASK             0x00000004
#define CLKMGR_MAINPLLGRP_EN_S2FUSER0CLK_MASK         0x00000200

#define CLKMGR_MAINPLLGRP_MAINDIV_L3MPCLK_OFFSET      0
#define CLKMGR_MAINPLLGRP_MAINDIV_L3MPCLK_MASK        0x00000003
#define CLKMGR_MAINPLLGRP_MAINDIV_L3SPCLK_OFFSET      2
#define CLKMGR_MAINPLLGRP_MAINDIV_L3SPCLK_MASK        0x0000000c
#define CLKMGR_MAINPLLGRP_MAINDIV_L4MPCLK_OFFSET      4
#define CLKMGR_MAINPLLGRP_MAINDIV_L4MPCLK_MASK        0x00000070
#define CLKMGR_MAINPLLGRP_MAINDIV_L4SPCLK_OFFSET      7
#define CLKMGR_MAINPLLGRP_MAINDIV_L4SPCLK_MASK        0x00000380

#define CLKMGR_MAINPLLGRP_DBGDIV_DBGATCLK_OFFSET      0
#define CLKMGR_MAINPLLGRP_DBGDIV_DBGATCLK_MASK        0x00000003
#define CLKMGR_MAINPLLGRP_DBGDIV_DBGCLK_OFFSET        2
#define CLKMGR_MAINPLLGRP_DBGDIV_DBGCLK_MASK          0x0000000c

#define CLKMGR_MAINPLLGRP_TRACEDIV_TRACECLK_OFFSET    0
#define CLKMGR_MAINPLLGRP_TRACEDIV_TRACECLK_MASK      0x00000007


#define CLKMGR_MAINPLLGRP_L4SRC_L4MP                  (1 << 0)
#define CLKMGR_MAINPLLGRP_L4SRC_L4MP_OFFSET           0
#define CLKMGR_MAINPLLGRP_L4SRC_L4SP                  (1 << 1)
#define CLKMGR_MAINPLLGRP_L4SRC_L4SP_OFFSET           1
#define CLKMGR_MAINPLLGRP_L4SRC_RESET_VALUE           0x00000000
#define CLKMGR_L4_SP_CLK_SRC_MAINPLL                  0x0
#define CLKMGR_L4_SP_CLK_SRC_PERPLL                   0x1

/* Per PLL */
#define CLKMGR_PERPLLGRP_VCO_DENOM_OFFSET             16
#define CLKMGR_PERPLLGRP_VCO_DENOM_MASK               0x003f0000
#define CLKMGR_PERPLLGRP_VCO_NUMER_OFFSET             3
#define CLKMGR_PERPLLGRP_VCO_NUMER_MASK               0x0000fff8
#define CLKMGR_PERPLLGRP_VCO_OUTRESETALL_MASK         0x01000000
#define CLKMGR_PERPLLGRP_VCO_PSRC_OFFSET              22
#define CLKMGR_PERPLLGRP_VCO_PSRC_MASK                0x00c00000
#define CLKMGR_PERPLLGRP_VCO_REGEXTSEL_MASK           0x80000000
#define CLKMGR_PERPLLGRP_VCO_RESET_VALUE              0x8001000d
#define CLKMGR_PERPLLGRP_VCO_SSRC_OFFSET              22
#define CLKMGR_PERPLLGRP_VCO_SSRC_MASK                0x00c00000

#define CLKMGR_VCO_SSRC_EOSC1                         0x0
#define CLKMGR_VCO_SSRC_EOSC2                         0x1
#define CLKMGR_VCO_SSRC_F2S                           0x2

#define CLKMGR_PERPLLGRP_EMAC0CLK_CNT_OFFSET          0
#define CLKMGR_PERPLLGRP_EMAC0CLK_CNT_MASK            0x000001ff

#define CLKMGR_PERPLLGRP_EMAC1CLK_CNT_OFFSET          0
#define CLKMGR_PERPLLGRP_EMAC1CLK_CNT_MASK            0x000001ff

#define CLKMGR_PERPLLGRP_PERQSPICLK_CNT_OFFSET        0
#define CLKMGR_PERPLLGRP_PERQSPICLK_CNT_MASK          0x000001ff

#define CLKMGR_PERPLLGRP_PERNANDSDMMCCLK_CNT_OFFSET   0
#define CLKMGR_PERPLLGRP_PERNANDSDMMCCLK_CNT_MASK     0x000001ff

#define CLKMGR_PERPLLGRP_PERBASECLK_CNT_OFFSET        0
#define CLKMGR_PERPLLGRP_PERBASECLK_CNT_MASK          0x000001ff

#define CLKMGR_PERPLLGRP_S2FUSER1CLK_CNT_OFFSET       0
#define CLKMGR_PERPLLGRP_S2FUSER1CLK_CNT_MASK         0x000001ff

#define CLKMGR_PERPLLGRP_EN_NANDCLK_MASK              0x00000400
#define CLKMGR_PERPLLGRP_EN_SDMMCCLK_MASK             0x00000100

#define CLKMGR_PERPLLGRP_DIV_CAN0CLK_OFFSET           6
#define CLKMGR_PERPLLGRP_DIV_CAN0CLK_MASK             0x000001c0
#define CLKMGR_PERPLLGRP_DIV_CAN1CLK_OFFSET           9
#define CLKMGR_PERPLLGRP_DIV_CAN1CLK_MASK             0x00000e00
#define CLKMGR_PERPLLGRP_DIV_SPIMCLK_OFFSET           3
#define CLKMGR_PERPLLGRP_DIV_SPIMCLK_OFFSET           3
#define CLKMGR_PERPLLGRP_DIV_USBCLK_OFFSET            0
#define CLKMGR_PERPLLGRP_DIV_USBCLK_MASK              0x00000007

#define CLKMGR_PERPLLGRP_GPIODIV_GPIODBCLK_OFFSET     0
#define CLKMGR_PERPLLGRP_GPIODIV_GPIODBCLK_MASK       0x00ffffff


#define CLKMGR_PERPLLGRP_SRC_NAND_OFFSET              2
#define CLKMGR_PERPLLGRP_SRC_NAND_MASK                0x0000000c
#define CLKMGR_PERPLLGRP_SRC_QSPI_OFFSET              4
#define CLKMGR_PERPLLGRP_SRC_QSPI_MASK                0x00000030
#define CLKMGR_PERPLLGRP_SRC_RESET_VALUE              0x00000015
#define CLKMGR_PERPLLGRP_SRC_SDMMC_OFFSET             0
#define CLKMGR_PERPLLGRP_SRC_SDMMC_MASK               0x00000003
#define CLKMGR_SDMMC_CLK_SRC_F2S                      0x0
#define CLKMGR_SDMMC_CLK_SRC_MAIN                     0x1
#define CLKMGR_SDMMC_CLK_SRC_PER                      0x2
#define CLKMGR_QSPI_CLK_SRC_F2S                       0x0
#define CLKMGR_QSPI_CLK_SRC_MAIN                      0x1
#define CLKMGR_QSPI_CLK_SRC_PER                       0x2

/* SDR PLL */
#define CLKMGR_SDRPLLGRP_VCO_DENOM_OFFSET             16
#define CLKMGR_SDRPLLGRP_VCO_DENOM_MASK               0x003f0000
#define CLKMGR_SDRPLLGRP_VCO_NUMER_OFFSET             3
#define CLKMGR_SDRPLLGRP_VCO_NUMER_MASK               0x0000fff8
#define CLKMGR_SDRPLLGRP_VCO_OUTRESETALL              (1 << 24)
#define CLKMGR_SDRPLLGRP_VCO_OUTRESETALL_OFFSET       24
#define CLKMGR_SDRPLLGRP_VCO_OUTRESET_OFFSET          25
#define CLKMGR_SDRPLLGRP_VCO_OUTRESET_MASK            0x7e000000
#define CLKMGR_SDRPLLGRP_VCO_REGEXTSEL_MASK           0x80000000
#define CLKMGR_SDRPLLGRP_VCO_RESET_VALUE              0x8001000d
#define CLKMGR_SDRPLLGRP_VCO_SSRC_OFFSET              22
#define CLKMGR_SDRPLLGRP_VCO_SSRC_MASK                0x00c00000

#define CLKMGR_SDRPLLGRP_DDRDQSCLK_CNT_OFFSET         0
#define CLKMGR_SDRPLLGRP_DDRDQSCLK_CNT_MASK           0x000001ff
#define CLKMGR_SDRPLLGRP_DDRDQSCLK_PHASE_OFFSET       9
#define CLKMGR_SDRPLLGRP_DDRDQSCLK_PHASE_MASK         0x00000e00

#define CLKMGR_SDRPLLGRP_DDR2XDQSCLK_CNT_OFFSET       0
#define CLKMGR_SDRPLLGRP_DDR2XDQSCLK_CNT_MASK         0x000001ff
#define CLKMGR_SDRPLLGRP_DDR2XDQSCLK_PHASE_OFFSET     9
#define CLKMGR_SDRPLLGRP_DDR2XDQSCLK_PHASE_MASK       0x00000e00

#define CLKMGR_SDRPLLGRP_DDRDQCLK_CNT_OFFSET          0
#define CLKMGR_SDRPLLGRP_DDRDQCLK_CNT_MASK            0x000001ff
#define CLKMGR_SDRPLLGRP_DDRDQCLK_PHASE_OFFSET        9
#define CLKMGR_SDRPLLGRP_DDRDQCLK_PHASE_MASK          0x00000e00

#define CLKMGR_SDRPLLGRP_S2FUSER2CLK_CNT_OFFSET       0
#define CLKMGR_SDRPLLGRP_S2FUSER2CLK_CNT_MASK         0x000001ff
#define CLKMGR_SDRPLLGRP_S2FUSER2CLK_PHASE_OFFSET     9
#define CLKMGR_SDRPLLGRP_S2FUSER2CLK_PHASE_MASK       0x00000e00

#endif /* _CLOCK_MANAGER_H_ */
