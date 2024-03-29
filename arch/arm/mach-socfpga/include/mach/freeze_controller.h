/*
 *  Copyright (C) 2013 Altera Corporation <www.altera.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef    _FREEZE_CONTROLLER_H_
#define    _FREEZE_CONTROLLER_H_

struct socfpga_freeze_controller {
	u32 vioctrl;
	u32 padding[3];
	u32 hioctrl;
	u32 src;
	u32 hwctrl;
};

#define FREEZE_CHANNEL_NUM        (4)

typedef enum {
	FREEZE_CTRL_FROZEN = 0,
	FREEZE_CTRL_THAWED = 1
} FREEZE_CTRL_CHAN_STATE;

#define SYSMGR_FRZCTRL_ADDRESS                         0x40
#define SYSMGR_FRZCTRL_SRC_VIO1_ENUM_SW                0x0
#define SYSMGR_FRZCTRL_SRC_VIO1_ENUM_HW                0x1
#define SYSMGR_FRZCTRL_VIOCTRL_SLEW_MASK               0x00000010
#define SYSMGR_FRZCTRL_VIOCTRL_WKPULLUP_MASK           0x00000008
#define SYSMGR_FRZCTRL_VIOCTRL_TRISTATE_MASK           0x00000004
#define SYSMGR_FRZCTRL_VIOCTRL_BUSHOLD_MASK            0x00000002
#define SYSMGR_FRZCTRL_VIOCTRL_CFG_MASK                0x00000001
#define SYSMGR_FRZCTRL_HIOCTRL_SLEW_MASK               0x00000010
#define SYSMGR_FRZCTRL_HIOCTRL_WKPULLUP_MASK           0x00000008
#define SYSMGR_FRZCTRL_HIOCTRL_TRISTATE_MASK           0x00000004
#define SYSMGR_FRZCTRL_HIOCTRL_BUSHOLD_MASK            0x00000002
#define SYSMGR_FRZCTRL_HIOCTRL_CFG_MASK                0x00000001
#define SYSMGR_FRZCTRL_HIOCTRL_REGRST_MASK             0x00000080
#define SYSMGR_FRZCTRL_HIOCTRL_OCTRST_MASK             0x00000040
#define SYSMGR_FRZCTRL_HIOCTRL_OCT_CFGEN_CALSTART_MASK 0x00000100
#define SYSMGR_FRZCTRL_HIOCTRL_DLLRST_MASK             0x00000020
#define SYSMGR_FRZCTRL_HWCTRL_VIO1REQ_MASK             0x00000001
#define SYSMGR_FRZCTRL_HWCTRL_VIO1STATE_ENUM_FROZEN    0x2
#define SYSMGR_FRZCTRL_HWCTRL_VIO1STATE_ENUM_THAWED    0x1


void sys_mgr_frzctrl_freeze_req(void);

void sys_mgr_frzctrl_thaw_req(void);

#endif /* _FREEZE_CONTROLLER_H_ */
