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

/* Memory configurations */
#define PHYS_SDRAM_1_SIZE        0x20000000    /* 500MiB */

/* Booting Linux */
#define CONFIG_BOOTFILE         "/linux/zImage_dtb"
#define CONFIG_BOOTARGS         "console=ttyS0," __stringify(CONFIG_BAUDRATE) " $v loop.max_part=8"
#define CONFIG_BOOTCOMMAND      "run usb_reset; mw 0xff709004 0x800; run mmcload; run hdmi_init; run mmcboot"
#define CONFIG_LOADADDR         0x01000000
#define CONFIG_SYS_LOAD_ADDR    CONFIG_LOADADDR

/* Ethernet on SoC (EMAC) */
#if defined(CONFIG_CMD_NET)
#define CONFIG_PHY_MICREL
#define CONFIG_PHY_MICREL_KSZ9031
#endif

#define CONFIG_ENV_IS_IN_MMC

#ifndef CONFIG_SYS_MMCSD_FS_BOOT_PARTITION
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION 1
#endif

/* Extra Environment */
#define CONFIG_EXTRA_ENV_SETTINGS \
    "core=menu.rbf\0" \
    "loadaddr=" __stringify(CONFIG_SYS_LOAD_ADDR) "\0" \
    "bootimage=" CONFIG_BOOTFILE "\0" \
    "mmc_boot=" __stringify(CONFIG_SYS_MMCSD_FS_BOOT_PARTITION) "\0" \
    "mmcroot=/dev/mmcblk0p" __stringify(CONFIG_SYS_MMCSD_FS_BOOT_PARTITION) "\0" \
    "fdt_addr=100\0" \
    "scrtest=if test -e mmc 0:$mmc_boot /linux/u-boot.txt;then load mmc 0:$mmc_boot $loadaddr /linux/u-boot.txt;env import -t $loadaddr;fi\0" \
    "fpgadata=0x02000000\0" \
    "fpgacheck=if mt 0xFFD05054 0;then run fpgaload;else if mt 0x1FFFF000 0x87654321;then mw 0x1FFFF000 0;env import -t 0x1FFFF004;run fpgaload;fi;fi\0" \
    "fpgaload=load mmc 0:$mmc_boot $fpgadata $core;fpga load 0 $fpgadata $filesize;bridge enable;mw 0x1FFFF000 0;mw 0xFFD05054 0\0" \
    "ethaddr=02:03:04:05:06:07\0" \
    "bootm $loadaddr - $fdt_addr\0" \
    "v=loglevel=4\0"                             \
    "usb_reset="                                 \
        "echo Resetting USB HUB...; "            \
        "gpio clear porta0; "                    \
        "sleep 1; "                              \
        "gpio set porta0\0"                      \
    \
    "hdmi_init="                                 \
        "echo Initializing HDMI Transmitter for 720p...; "    \
        "i2c dev 2; "                            \
        "i2c mw 37 FF.1 02 1; "                  \
        "i2c mw 73 FF.1 00 1; "                  \
        "i2c mw 73 A0.1 02 1; "                  \
        "i2c mw 73 CB.1 00 1; "                  \
        "i2c mw 73 F0.1 00 1; "                  \
        "i2c mw 73 18.1 FF 1; "                  \
        "i2c mw 73 19.1 FF 1; "                  \
        "i2c mw 73 1A.1 FF 1; "                  \
        "i2c mw 73 20.1 45 1; "                  \
        "i2c mw 73 21.1 23 1; "                  \
        "i2c mw 73 22.1 01 1; "                  \
        "i2c mw 73 23.1 14 1; "                  \
        "i2c mw 37 23.1 20 1; "                  \
        "i2c dev 0\0 "                           \
    "mmcload=mmc rescan;" \
        "run fpgacheck;" \
        "run scrtest;" \
        "load mmc 0:$mmc_boot $loadaddr $bootimage;" \
        "setexpr.l fdt_addr $loadaddr + 0x2C;" \
        "setexpr.l fdt_addr *$fdt_addr + $loadaddr\0" \
	"mmcboot=setenv bootargs " CONFIG_BOOTARGS " root=$mmcroot loop=linux/linux.img rw rootwait;" "bootz $loadaddr - $fdt_addr\0"

/* The rest of the configuration is shared */
#include <configs/socfpga_common.h>

#endif    /* __CONFIG_CHAMELEON96_H__ */
