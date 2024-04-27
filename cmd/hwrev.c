/*
 * (C) Copyright 2020 Hardkernel Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <adc.h>

#define check_range(min,max,val) (val > 0 && val > min && val < max ? 1 : 0)

int do_hwrev(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int hwrev_adc, hwdet_adc;

	if (adc_channel_single_shot("saradc", 0, &hwrev_adc)) {
		printf("board hw rev failed\n");
		return CMD_RET_FAILURE;
	}
	if (adc_channel_single_shot("saradc", 2, &hwdet_adc)) {
		printf("board hw det failed\n");
		return CMD_RET_FAILURE;
	}
	/* R50S */
	if (check_range(40, 126, hwrev_adc)) {
		env_set("hwrev", "r50s");
		env_set("dtb_uboot", "rg351mp-uboot.dtb");
		env_set("dtb_kernel", "rk3326-r50s-linux.dtb");
	}
	/* RG351MP */
	if (check_range(146, 186, hwrev_adc)) {
		env_set("hwrev", "rg351mp");
		env_set("dtb_uboot", "rg351mp-uboot.dtb");
		env_set("dtb_kernel", "rk3326-rg351mp-linux.dtb");
	}
	/* RG351V and D007*/
	else if (check_range(494, 534, hwrev_adc)) {
		if (check_range(600, 1100, hwdet_adc)) {
			env_set("hwrev", "d007");
			env_set("dtb_uboot", "rk3326-d007-linux.dtb");
			env_set("dtb_kernel", "rk3326-d007-linux.dtb");
		}
		else {
			env_set("hwrev", "rg351v");
			env_set("dtb_uboot", "rg351v-uboot.dtb");
			env_set("dtb_kernel", "rk3326-rg351v-linux.dtb");
		}
	}
	/* RG351P */
	else if (check_range(655, 695, hwrev_adc)) {
		env_set("hwrev", "rg351p");
		env_set("dtb_uboot", "rg351p-uboot.dtb");
		env_set("dtb_kernel", "rk3326-rg351p-linux.dtb");
	}
	/* XU10 */
	else if (check_range(1000, 1050, hwrev_adc)) {
		env_set("hwrev", "xu10");
		env_set("dtb_uboot", "rg351mp-uboot.dtb");
		env_set("dtb_kernel", "rk3326-xu10-linux.dtb");
	}
	/* Unknown */
	else {
		env_set("hwrev", "rg351mp");
		env_set("dtb_uboot", "rg351mp-uboot.dtb");
		env_set("dtb_kernel", "rk3326-rg351mp-linux.dtb");
	}
	printf("adc0 (hw rev) %d\n", hwrev_adc);
printf("Model = %s\n",env_get("hwrev"));
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	hwrev, 1, 1, do_hwrev,
	"check hw revision of OGA",
	""
);
