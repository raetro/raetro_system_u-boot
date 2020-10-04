/*
 * Copyright (C) 2017 Arrow Electronics
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIG_CHAMELEON96_H__
#define __CONFIG_CHAMELEON96_H__

#include <asm/arch/base_addr_ac5.h>

#define CONFIG_SYS_BOOTM_LEN    (64 << 20)

/* U-Boot Commands */
#define CONFIG_FS_FAT
#define CONFIG_HW_WATCHDOG

#define CONFIG_ENV_IS_IN_MMC

#ifndef CONFIG_SYS_MMCSD_FS_BOOT_PARTITION
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION 1
#endif

/* Memory configurations */
#define PHYS_SDRAM_1_SIZE       0x20000000    /* 500MiB */

/* Booting */
#define CONFIG_BOOTARGS         "console=ttyS0," __stringify(CONFIG_BAUDRATE) " $v loop.max_part=8"
#define CONFIG_BOOTCOMMAND      "run usb_reset; mw 0xff709004 0x800; run mmcload; run mmcboot"
#define CONFIG_LOADADDR         0x01000000
#define CONFIG_SYS_LOAD_ADDR    CONFIG_LOADADDR

/* Kernel and RootFS */
#define C96_CORE_FILE        "menu.rbf"
#define C96_BOOT_FILE        "/linux/zImage_dtb"
#define C96_LINUX_FILE       "/linux/linux.img"
#define C96_DEVICE_TREE      "/linux/chameleon96.dtb"
#define C96_U_BOOT_SCR       "/linux/u-boot.txt"

/* Extra Environment */
#define CONFIG_EXTRA_ENV_SETTINGS \
    "fpga=0\0"                    \
    "verify=n\0"                  \
    "v=loglevel=4\0"              \
    "fdt_addr=100\0"              \
    "fpgadata=0x02000000\0"       \
    \
    "core=" C96_CORE_FILE "\0"  \
    "bootimage=" C96_BOOT_FILE "\0" \
    "loadaddr=" __stringify(CONFIG_SYS_LOAD_ADDR) "\0" \
    "mmc_boot=" __stringify(CONFIG_SYS_MMCSD_FS_BOOT_PARTITION) "\0" \
    "mmcroot=/dev/mmcblk0p" __stringify(CONFIG_SYS_MMCSD_FS_BOOT_PARTITION) "\0" \
    "bootm $loadaddr - $fdt_addr\0" \
    \
    "scrtest=" \
		"if test -e mmc 0:$mmc_boot " C96_U_BOOT_SCR ";" \
			"then load mmc 0:$mmc_boot $loadaddr " C96_U_BOOT_SCR ";" \
			"env import -t $loadaddr;" \
		"fi\0" \
    \
    "fpgacheck=" \
    	"if mt 0xFFD05054 0;"                   \
    		"then run fpgaload;"                \
			"else if mt 0x1FFFF000 0x87654321;" \
				"then mw 0x1FFFF000 0;"         \
				"env import -t 0x1FFFF004;"     \
				"run fpgaload;"                 \
			"fi;"                               \
		"fi\0"  \
    \
    "fpgaload=" \
        "echo Programming FPGA...;"             \
    	"load mmc 0:$mmc_boot $fpgadata $core;" \
    	"fpga load 0 $fpgadata $filesize;"      \
        "echo Enabling FPGA to HPS bridges...;" \
    	"bridge enable;"                        \
    	"mw 0x1FFFF000 0; mw 0xFFD05054 0\0"    \
    \
    "mmcload=" \
    	"mmc rescan;"                 \
        "run fpgacheck;"              \
        "run scrtest;"                \
        "run kernel_init\0"           \
    "kernel_init=" \
        "echo Loading Kernel and Device Tree...;"     \
        "load mmc 0:$mmc_boot $loadaddr $bootimage;"  \
        "setexpr.l fdt_addr $loadaddr + 0x2C;"        \
        "setexpr.l fdt_addr *$fdt_addr + $loadaddr\0" \
	"mmcboot=" \
		"echo Booting Linux kernel...;" \
		"setenv bootargs " CONFIG_BOOTARGS " root=$mmcroot loop=" C96_LINUX_FILE " rw rootwait;" \
		"bootz $loadaddr - $fdt_addr\0"

/* The rest of the configuration is shared */
#include <configs/socfpga_common.h>

#endif    /* __CONFIG_CHAMELEON96_H__ */
