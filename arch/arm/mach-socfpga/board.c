/*
 * Altera SoCFPGA common board code
 *
 * Copyright (C) 2015 Marek Vasut <marex@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <errno.h>
#include <asm/arch/system_manager.h>
#include <asm/arch/reset_manager.h>
#include <asm/io.h>
#include <i2c.h>

#include <usb.h>
#include <usb/dwc2_udc.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * Initialization function which happen at early stage of c code
 */
void s_init(void) {
#ifdef TARGET_SOCFPGA_ARROW_CHAMELEON96
	// YHN, turn USER LED 2
	int reg;
	reg = readl(0xFF708000); /* Get the current stae of GPIO0 */
	reg &= 0xFFBFFFFF;       /* Set GPIO 22 (USER 2) Low (on) */
	writel(reg, 0xFF708000);

	return 0;
#endif
}

/*
 * Miscellaneous platform dependent initialisations
 */
int board_init(void) {
	/* Address of boot parameters for ATAG (if ATAG is used) */
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;
	return 0;
}

#ifdef CONFIG_USB_GADGET
struct dwc2_plat_otg_data socfpga_otg_data = {
	.usb_gusbcfg    = 0x1417,
};

int board_usb_init(int index, enum usb_init_type init) {
	int node[2], count;
	fdt_addr_t addr;

	count = fdtdec_find_aliases_for_id(gd->fdt_blob, "udc", COMPAT_ALTERA_SOCFPGA_DWC2USB, node, 2);
	if(count <= 0) {    /* No controller found. */
		return 0;
	}

	addr = fdtdec_get_addr(gd->fdt_blob, node[0], "reg");
	if(addr == FDT_ADDR_T_NONE) {
		printf("UDC Controller has no 'reg' property!\n");
		return -EINVAL;
	}

	/* Patch the address from OF into the controller pdata. */
	socfpga_otg_data.regs_otg = addr;

	return dwc2_udc_probe(&socfpga_otg_data);
}

int g_dnl_board_usb_cable_connected(void) {
	return 1;
}
#endif

#ifdef CONFIG_BOARD_LATE_INIT
int board_late_init(void) {
//	int rc = 0;
//	int flag1 = 0;
//
//	int reg;
//
//	int tries = 0;
//	int i;
//	int error = 0;
//
//	/* YHN, add code for:
//	1. Put USB PHY in reset
//	2. Put USB HUB in reset
//	3. Load FPGA
//	4. Release USB PHY/HUB from reset*/
//
	// Step 1
	printf("Place USBOTG PHY in reset\n");  // Reset on RGMII0_TX_CTL => GPIO09 => bit 9 of GPIO0
	reg = readl(0xFF708000);
	reg |= 0x00000200;              // Set Bit 9 to high, USB PHY is a reset lhigh
	writel(reg, 0xFF708000);
	reg = readl(0xFF708004);
	reg |= 0x00000200;              // Set Bit 9 to high, make it an output
	writel(reg, 0xFF708004);
//
	// Step 2
	printf("Place USB HUB in reset\n");  // nReset on RGMII0_TX_CLK => GPIO00 => bit 0 of GPIO0
	reg = readl(0xFF708000);
	reg &= 0xFFFFFFFE;                   // Set Bit 0 to low, USB HUB is reset low
	writel(reg, 0xFF708000);
	reg = readl(0xFF708004);
	reg |= 0x00000001;                   // Set Bit 0 to high, make it an output
	writel(reg, 0xFF708004);
//
//
//	// Step 3
//	printf("\n");
//	printf("======================\n");
//	printf("Loading FPGA .rbf FILE\n");
//	printf("======================\n");
//
//	rc = run_command("fatload mmc 0:1 $fpgadata cv96.rbf ", flag1);
//
//	printf("Read FPGA File Status = 0x%x.\n", rc);
//
//	tries = 1;
//
//	while (tries <= 5) {
//		rc = run_command("fpga load 0 $fpgadata $filesize ", flag1);
//		//rc = run_command ("fpga load 0 0x2000000 $filesize ", flag1);
//		if(rc == 0) {
//			break;
//		} else {
//			tries++;
//		}
//
//	}
//	printf("Try # = 0x%x.\n", tries);
//	printf("Programming FPGA Status = 0x%x.\n", rc);
//	rc = run_command("run bridge_enable_handoff ", flag1);
//	printf("HPS2FPGA Bridge Status = 0x%x.\n", rc);
//	reg = readl(0xFF200000);
//	printf("FPGA HDL ID = 0x%x.\n", reg);
//
//
//	// Step 4
//	printf("USBOTG PHY is out of reset\n");  // Reset on RMGII0_TX_CTL => GPIO09 => bit 9 of GPIO0
//	reg = readl(0xFF708000);
//	reg &= 0xFFFFFDFF;              // Set Bit 1 to low
//	writel(reg, 0xFF708000);
//
//	printf("USB HUB is out of reset\n");  // nReset on RGMII0_TX_CLK => GPIO00 => bit 0 of GPIO0
//	reg = readl(0xFF708000);
//	reg |= 0x00000001;                   // Set Bit 0 to high, USB HUB is reset low
//	writel(reg, 0xFF708000);
//
//	// YHN, turn USER LED 3
//	reg = readl(0xFF708000); /* Get the current stae of GPIO0 */
//	reg &= 0xFDFFFFFF;       /* Set GPIO 25 (USER 3) Low (on) */
//	writel(reg, 0xFF708000);

	return 0;
}

#endif
