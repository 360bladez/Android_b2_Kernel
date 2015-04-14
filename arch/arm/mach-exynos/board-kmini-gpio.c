/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * EXYNOS - GPIO setting in set board
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/gpio.h>
#include <linux/serial_core.h>
#include <plat/devs.h>
#include <plat/gpio-cfg.h>
#include <plat/regs-serial.h>
#include <mach/gpio.h>
#include <mach/gpio-shannon222ap.h>
#include <plat/cpu.h>
#include <mach/pmu.h>
#include <mach/gpio-exynos.h>

#define S3C_GPIO_SLP_OUT0	((__force samsung_gpio_pull_t)0x00)
#define S3C_GPIO_SLP_OUT1	((__force samsung_gpio_pull_t)0x01)
#define S3C_GPIO_SLP_INPUT	((__force samsung_gpio_pull_t)0x02)
#define S3C_GPIO_SLP_PREV	((__force samsung_gpio_pull_t)0x03)

#define S3C_GPIO_SETPIN_ZERO	0
#define S3C_GPIO_SETPIN_ONE	1
#define S3C_GPIO_SETPIN_NONE	2

#define GPIO_TABLE(_ptr) \
	{.ptr = _ptr, \
	.size = ARRAY_SIZE(_ptr)} \

#define GPIO_TABLE_NULL \
	{.ptr = NULL, \
	.size = 0} \

struct sec_gpio_init_data {
	uint num;
	uint cfg;
	uint val;
	uint pud;
	uint drv;
};

/*
 * shannon222ap GPIO Init Table
 */
static struct sec_gpio_init_data shannon222ap_init_table[] = {

	{EXYNOS4_GPA1(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPA1(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */

	{EXYNOS4_GPB(0), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* 8M_EEP_SDA */
	{EXYNOS4_GPB(1), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* 8M_EEP_SCL */

	{EXYNOS4_GPC0(0), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* VT_CAM_STBY */

	{EXYNOS4_GPK1(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */

	{EXYNOS4_GPK0(7), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */

	{EXYNOS4_GPY0(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */

	{EXYNOS4_GPY1(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY1(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY1(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */

	{EXYNOS4_GPY3(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */

	{EXYNOS4_GPM0(7),S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
                S3C_GPIO_PULL_NONE,S5P_GPIO_DRVSTR_LV1 }, /* CODEC_LDO_EN */

        {EXYNOS4_GPM1(2), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
                S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* VT_CAM_nRST */
	{EXYNOS4_GPM1(6), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
                S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* CAM_SENSOR_CORE_EN */

        {EXYNOS4_GPM2(2), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
                S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* CAM_MCLK */

	{EXYNOS4_GPM3(2), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1 }, /* DC_MOTOR */
	{EXYNOS4_GPM3(4), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
                S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* CAM_FLASH_EN */
	{EXYNOS4_GPM3(6), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
                S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* CAM_TORCH_EN */

	{EXYNOS4_GPM4(0), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* 8M_CAM_SCL_1.8V */
	{EXYNOS4_GPM4(1), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* 8M_CAM_SDA_1.8V */

	{EXYNOS4_GPX1(2), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* 8M_CAM_RST */

	{EXYNOS4_GPX2(6), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* 3.5PI_DET_BB */

}; /* shannon222ap_init_table */

#ifdef CONFIG_SEC_PM
extern unsigned int system_rev;

static unsigned int shannon222ap_sleep_gpio_table_rev00[][3] = {
	{EXYNOS4_GPB(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPB(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPB(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPB(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	{EXYNOS4_GPC0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*FM_I2S_CLK*/
	{EXYNOS4_GPC0(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPC0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*FM_I2S_SYNC*/
	{EXYNOS4_GPC0(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*FM_I2S_DO*/

	{EXYNOS4_GPD0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SENSOR_I2C_SDA*/
	{EXYNOS4_GPD0(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SENSOR_I2C_SCL*/

	{EXYNOS4_GPF2(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF2(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	{EXYNOS4_GPM0(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	{EXYNOS4_GPM3(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*MOTOR_EN*/
};

static unsigned int shannon222ap_sleep_gpio_table_rev01[][3] = {
	{EXYNOS4_GPM3(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
};

static unsigned int shannon222ap_sleep_gpio_table_rev03[][3] = {
	{EXYNOS4_GPF0(6), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*TOUCH_KEY_RST*/
        {EXYNOS4_GPK3(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
};

static unsigned int shannon222ap_sleep_gpio_table_rev04[][3] = {
	{EXYNOS4_GPF0(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPK3(3), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*TOUCH_KEY_RST*/
};

static unsigned int shannon222ap_sleep_gpio_table_latest[][3] = {
	{EXYNOS4_GPA0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /* BT_UART_RXD */
	{EXYNOS4_GPA0(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /* BT_UART_TXD */
	{EXYNOS4_GPA0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /* BT_UART_CTS */
	{EXYNOS4_GPA0(3), S5P_GPIO_PD_OUTPUT1, S5P_GPIO_PD_UPDOWN_DISABLE}, /* BT_UART_RTS */
	{EXYNOS4_GPA0(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE},	/*GPS_RXD*/
	{EXYNOS4_GPA0(5), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE},	/*GPS_TXD*/
	{EXYNOS4_GPA0(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE},	/*GPS_CTS*/
	{EXYNOS4_GPA0(7), S5P_GPIO_PD_OUTPUT1, S5P_GPIO_PD_UPDOWN_DISABLE},	/*GPS_RTS*/

	{EXYNOS4_GPA1(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*AP_UART_RXD*/
	{EXYNOS4_GPA1(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*AP_UART_TXD*/
	{EXYNOS4_GPA1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*TSP_SDA*/
	{EXYNOS4_GPA1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*TSP_SCL*/
	{EXYNOS4_GPA1(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPA1(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	{EXYNOS4_GPB(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*8M_EEP_SDA*/
	{EXYNOS4_GPB(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*8M_EEP_SCL*/
	{EXYNOS4_GPB(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NFC_SDA*/
	{EXYNOS4_GPB(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NFC_SCL*/
        {EXYNOS4_GPB(4), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*BTP_SPI_CLK*/
        {EXYNOS4_GPB(5), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*BTP_SPI_CS_N*/
        {EXYNOS4_GPB(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*BTP_SPI_MISO*/
        {EXYNOS4_GPB(7), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*BTP_SPI_MOSI*/

	{EXYNOS4_GPC0(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*VT_CAM_STBY*/
	{EXYNOS4_GPC0(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*BTP_1V8_EN*/
	{EXYNOS4_GPC0(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*BTP_RST_N*/
	{EXYNOS4_GPC0(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*BTP_OCP_EN*/
	{EXYNOS4_GPC0(4), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*BTP_3V3_EN*/

	{EXYNOS4_GPC1(0), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*UART_SEL*/
	{EXYNOS4_GPC1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*MUIC_SCL*/
	{EXYNOS4_GPC1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*MUIC_SDA*/
	{EXYNOS4_GPC1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*IF_PMIC_SDA*/
	{EXYNOS4_GPC1(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*IF_PMIC_SDA*/

	{EXYNOS4_GPD0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPD0(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPD0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*GYRO_I2C_SDA*/
	{EXYNOS4_GPD0(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*GYRO_I2C_SCL*/

	{EXYNOS4_GPD1(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*PMIC_I2C_SDA0*/
	{EXYNOS4_GPD1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*PMIC_I2C_SCL0*/
	{EXYNOS4_GPD1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*CODEC_I2C_SDA*/
	{EXYNOS4_GPD1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*CODEC_I2C_SCL*/

	{EXYNOS4_GPF0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF0(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF0(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF0(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF0(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF0(6), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*TOUCH_KEY_EN*/
	{EXYNOS4_GPF0(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*FG_SDA*/

	{EXYNOS4_GPF1(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF1(4), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NFC_EN*/
	{EXYNOS4_GPF1(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*FG_SCL*/
	{EXYNOS4_GPF1(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF1(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	{EXYNOS4_GPF2(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF2(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SENSOR_I2C_SDA*/
	{EXYNOS4_GPF2(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SENSOR_I2C_SCL*/
	{EXYNOS4_GPF2(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
#if 1   /* controled by driver  */
	{EXYNOS4_GPF2(4), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*WLAN_EN*/
#endif
	{EXYNOS4_GPF2(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*HW_VER2*/
	{EXYNOS4_GPF2(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*HW_VER3*/
	{EXYNOS4_GPF2(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	{EXYNOS4_GPF3(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF3(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF3(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*HW_VER0*/
	{EXYNOS4_GPF3(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*HW_VER1*/
	{EXYNOS4_GPF3(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPF3(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	{EXYNOS4_GPK0(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NAND_CLK*/
	{EXYNOS4_GPK0(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NAND_CMD*/
	{EXYNOS4_GPK0(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*MMC_PWR_EN*/
	{EXYNOS4_GPK0(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NAND_D(0)*/
	{EXYNOS4_GPK0(4), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NAND_D(1)*/
	{EXYNOS4_GPK0(5), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NAND_D(2)*/
	{EXYNOS4_GPK0(6), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NAND_D(3)*/
	{EXYNOS4_GPK0(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	{EXYNOS4_GPL0(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NAND_D(4)*/
	{EXYNOS4_GPL0(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NAND_D(5)*/
	{EXYNOS4_GPL0(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NAND_D(6)*/
	{EXYNOS4_GPL0(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NAND_D(7)*/

	{EXYNOS4_GPK1(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*WLAN_SDIO_CLK*/
	{EXYNOS4_GPK1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*WLAN_SDIO_CMD*/
	{EXYNOS4_GPK1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*TP*/
	{EXYNOS4_GPK1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*WLAN_SDIO_DATA0*/
	{EXYNOS4_GPK1(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*WLAN_SDIO_DATA1*/
	{EXYNOS4_GPK1(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*WLAN_SDIO_DATA2*/
	{EXYNOS4_GPK1(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*WLAN_SDIO_DATA3*/

	{EXYNOS4_GPK2(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SDHI0_CLK*/
	{EXYNOS4_GPK2(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SDHI0_CMD*/
	{EXYNOS4_GPK2(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPK2(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SDHI0_DATA0*/
	{EXYNOS4_GPK2(4), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SDHI0_DATA1*/
	{EXYNOS4_GPK2(5), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SDHI0_DATA2*/
	{EXYNOS4_GPK2(6), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SDHI0_DATA3*/

	{EXYNOS4_GPK3(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPK3(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPK3(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPK3(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPK3(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPK3(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPK3(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	/*MP0_0*/
	{EXYNOS4_GPY0(0), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*SDCARD_PWR_EN*/
	{EXYNOS4_GPY0(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY0(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY0(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY0(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	/*MP0_1*/
	{EXYNOS4_GPY1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	/*MP0_3*/
	{EXYNOS4_GPY3(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY3(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY3(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY3(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY3(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY3(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY3(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY3(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	/*MP0_4*/
	{EXYNOS4_GPY4(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY4(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY4(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY4(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY4(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY4(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY4(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY4(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	/*MP0_5*/
	{EXYNOS4_GPY5(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY5(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY5(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY5(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY5(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY5(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY5(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY5(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	/*MP0_6*/
	{EXYNOS4_GPY6(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY6(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY6(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY6(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY6(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY6(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY6(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPY6(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	{EXYNOS4_GPM0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPM0(1), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*PMIC_WARM_RESET_n*/
	{EXYNOS4_GPM0(2), S5P_GPIO_PD_OUTPUT1, S5P_GPIO_PD_UPDOWN_DISABLE}, /*IRDA_WAKE*/
	{EXYNOS4_GPM0(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*COVER_ID_DET*/
	{EXYNOS4_GPM0(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*IRDA_IRQ*/
	{EXYNOS4_GPM0(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPM0(6), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*BT_EN*/
	{EXYNOS4_GPM0(7), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*CODEC_LDO_EN*/

	{EXYNOS4_GPM1(0), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NFC_CLK_EN_N*/
	{EXYNOS4_GPM1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPM1(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*VT_CAM_nRST*/
	{EXYNOS4_GPM1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*TSP_TA*/
	{EXYNOS4_GPM1(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPM1(5), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*NFC_FIRMWARE*/
	{EXYNOS4_GPM1(6), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*CAM_SENSOR_CORE_EN*/

	{EXYNOS4_GPM2(0), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*BT_WAKEUP*/
	{EXYNOS4_GPM2(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPM2(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*CAM_MCLK_AP*/
	{EXYNOS4_GPM2(3), S5P_GPIO_PD_OUTPUT1, S5P_GPIO_PD_UPDOWN_DISABLE}, /*RESET_CP*/
	{EXYNOS4_GPM2(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*TOUCH_KEY_SCL*/

	{EXYNOS4_GPM3(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*TOUCH_KEY_SDA*/
	{EXYNOS4_GPM3(1), S5P_GPIO_PD_OUTPUT1, S5P_GPIO_PD_UPDOWN_DISABLE}, /*IRDA_RESET*/
	{EXYNOS4_GPM3(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*DC MOTOR*/
	{EXYNOS4_GPM3(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPM3(4), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*CAM_FLASH_EN*/
	{EXYNOS4_GPM3(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*ISP_UART_TX(TP)*/
	{EXYNOS4_GPM3(6), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE}, /*CAM_TORCH_EN*/
	{EXYNOS4_GPM3(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*ISP_UART_RX(TP)*/

	{EXYNOS4_GPM4(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*8M_CAM_SCL_1.8V*/
	{EXYNOS4_GPM4(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*8M_CAM_SDA_1.8V*/
	{EXYNOS4_GPM4(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*1.9M_CAM_SCL_1.8V*/
	{EXYNOS4_GPM4(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE}, /*1.9M_CAM_SDA_1.8V*/
	{EXYNOS4_GPM4(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*IRDA_SDA*/
	{EXYNOS4_GPM4(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE}, /*IRDA_SCL*/
	{EXYNOS4_GPM4(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPM4(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	/*Do not set GPX in sleep table ,GPX are ALIVE BLOCK !!!!*/

#if 0 /*GPZ clock controled by audio */
	{EXYNOS4_GPZ(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPZ(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/
	{EXYNOS4_GPZ(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*NC*/

	{EXYNOS4_GPZ(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*MM_I2S_CLK*/
	{EXYNOS4_GPZ(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*MM_I2S_SYNC*/
	{EXYNOS4_GPZ(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*MM_I2S_DI*/
	{EXYNOS4_GPZ(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE}, /*MM_I2S_DO*/
#endif
	/*Do not set GPX in sleep table ,GPX are ALIVE BLOCK !!!!*/

}; /* shannon222ap_sleep_gpio_table */

struct shannon222ap_sleep_table {
	unsigned int (*ptr)[3];
	int size;
};

static struct shannon222ap_sleep_table shannon222ap_sleep_tables[] = {
        GPIO_TABLE(shannon222ap_sleep_gpio_table_rev00), /* Rev0.0 (0x00) */
        GPIO_TABLE(shannon222ap_sleep_gpio_table_rev01), /* Rev0.1 (0x01) */
        GPIO_TABLE_NULL,                                 /* Rev0.2 (0x02) */
        GPIO_TABLE_NULL,                                 /* Rev0.2A (0x03) */
        GPIO_TABLE(shannon222ap_sleep_gpio_table_rev03), /* Rev0.3 (0x04) */
	GPIO_TABLE(shannon222ap_sleep_gpio_table_rev04), /* Rev0.4 (0x05) */
	GPIO_TABLE(shannon222ap_sleep_gpio_table_latest),/* Rev0.5 (0x06) */
};

static void config_sleep_gpio_table(int array_size,
                                    unsigned int (*gpio_table)[3])
{
        u32 i, gpio;

        for (i = 0; i < array_size; i++) {
                gpio = gpio_table[i][0];
                s5p_gpio_set_pd_cfg(gpio, gpio_table[i][1]);
                s5p_gpio_set_pd_pull(gpio, gpio_table[i][2]);
        }
}

/* To save power consumption, gpio pin set before enterling sleep */
void sec_config_sleep_gpio_table(void)
{
        int i;
        int gpio_rev;

        i = ARRAY_SIZE(shannon222ap_sleep_tables) - 1;

        gpio_rev = system_rev;

        if (i < gpio_rev) {
                pr_err("%s: Error Need sleep table : i %d - gpio_rev %d \n",
                        __func__, i, gpio_rev );
                config_sleep_gpio_table(ARRAY_SIZE(shannon222ap_sleep_gpio_table_latest)
                        ,shannon222ap_sleep_gpio_table_latest);
                return;
        }

        for (; i >= gpio_rev ; i--) {
                if (shannon222ap_sleep_tables[i].ptr == NULL)
                        continue;

                config_sleep_gpio_table(shannon222ap_sleep_tables[i].size,
                                shannon222ap_sleep_tables[i].ptr);
        }
}
#endif

int board_universal_ss222ap_init_gpio(void)
{
	u32 i, gpio;
#ifdef CONFIG_SEC_PM
	exynos_config_sleep_gpio = sec_config_sleep_gpio_table;
#endif
	for (i = 0; i < ARRAY_SIZE(shannon222ap_init_table); i++) {

		gpio = shannon222ap_init_table[i].num;

		s3c_gpio_cfgpin(gpio, shannon222ap_init_table[i].cfg);
		s3c_gpio_setpull(gpio, shannon222ap_init_table[i].pud);

		if (shannon222ap_init_table[i].val != S3C_GPIO_SETPIN_NONE)
			gpio_set_value(gpio, shannon222ap_init_table[i].val);

		s5p_gpio_set_drvstr(gpio, shannon222ap_init_table[i].drv);
	}
	return 0;
}