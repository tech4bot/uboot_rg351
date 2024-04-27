/*
 * (C) Copyright 2019 Hardkernel Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#ifndef _ODROIDGOA_STATUS_H_
#define _ODROIDGOA_STATUS_H_

enum rg351_rev{
	MODEL_RG351P = 0,
	MODEL_RG351V,
	MODEL_RG351MP,
	MODEL_R50S,
};

enum logo_storage {
	LOGO_STORAGE_SPIFLASH = 0,
	LOGO_STORAGE_SDCARD,
	LOGO_STORAGE_ANYWHERE,
};

enum logo_mode {
	LOGO_MODE_HARDKERNEL = 0,
	LOGO_MODE_LOW_BATT,
	LOGO_MODE_RECOVERY,
	LOGO_MODE_SYSTEM_ERR,
	LOGO_MODE_NO_SDCARD,
};

int get_rg351_rev(void);
int odroid_display_status(int logo_mode, int logo_storage, const char *str);
void odroid_wait_pwrkey(void);
void odroid_alert_leds(void);
void odroid_drop_errorlog(const char *err, unsigned int size);

int board_check_recovery(void);
void board_odroid_recovery(void);
int board_check_power(void);
int odroid_check_dcjack(void);
#endif /* _ODROIDGOA_STATUS_H_ */
