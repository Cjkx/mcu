#include <mcu.h>
#include <adc.h>
#include <stdio.h>
#include <i2c01_slave.h>
#include <string.h>

#define REG_BOARD_TYPE		0x00
#define REG_SW_VER		0x01
#define REG_HW_VER		0x02
#define REG_CMD		0x03
#define REG_SG2042_TMP		0x04
#define REG_BOARD_TMP		0x05
#define REG_INT_STATUS1		0x06
#define REG_INT_STATUS2		0x07
#define REG_INT_MASK1		0x08
#define REG_INT_MASK2 		0x09

#define REG_SOC_RST_TIMES		0x0a
#define REG_UPTIME_LO		0x0b
#define REG_UPTIME_HI		0x0c
#define REG_POWEROFF_REASON		0x0d

#define RTC_SECONDS		0x0e
#define RTC_MINUTES		0x0f
#define RTC_HOURS		0x10
#define RTC_DATE		0x11
#define RTC_MONTH		0x12
#define RTC_YEAR		0x13

#define SG2042_TMP_OVER_REPORT			1<<0
#define POWER_68127_TMP_OVER_REPORT		1<<1
#define BOARD_TMP_OVER_REPORT			1<<2
#define BOARD_TMP_OVER_POWEROFF			1<<3
#define BM1686_TMP_OVER_POWEROFF		1<<4
#define SYS_POWER_EXCEPTION_POWEROFF	1<<5
#define V12_EXCEPTION_POWEROFF			1<<6
#define BM1686_REBOOT_CMD				1<<7

#define WATCH_DOG 						1<<0
#define TEST_INT						1<<1

#define I_12V_ATX_L		0x28
#define REG_I_5V_ADC		0x29
#define REG_I_DDR_VDD_0V8		0x30
#define REG_I_DDR01_VDDQ_1V2		0x31
#define REG_I_DDR23_VDDQ_1V2		0x32
#define REG_I_VDD_12V		0x33
#define REG_I_VDD_EMMC_1V8		0x34
#define REG_I_VDD_EMMC_3V3		0x35
#define REG_I_VDD_PCIE_C_0V8		0x36
#define REG_I_VDD_PCIE_D_0V8		0x37
#define REG_I_VDD_PCIE_H_1V8		0x38
#define REG_I_VDD_PLL_0V8		0x39
#define REG_I_VDD_RGMII_1V8		0x40
#define REG_I_VDDC		0x41
#define REG_I_VDDIO18		0x42
#define REG_I_VQPS18		0x43
#define MCU_REG_MAX		0x44

struct mcu_ctx {
	int set_idx;
	int idx;
	int cmd_tmp;
	uint8_t cmd;
	uint16_t tmp;
	uint8_t int_status[2];
	uint8_t int_mask[2];
	uint8_t critical_action;
	uint8_t	repoweron_temp;
	uint8_t critical_temp;
};

static struct mcu_ctx mcu_ctx;

static inline void idx_set(struct mcu_ctx *ctx, uint8_t idx)
{
	ctx->idx = idx % MCU_REG_MAX;
}

static inline void idx_inc(struct mcu_ctx *ctx)
{
	ctx->idx = (ctx->idx + 1) % MCU_REG_MAX;
}

static void mcu_match(void *priv, int dir)
{
	struct mcu_ctx *ctx = priv;

	if (dir == I2C_SLAVE_WRITE)
		ctx->set_idx = 1;
}

static void mcu_write(void *priv, volatile uint8_t data)
{
	struct mcu_ctx *ctx = priv;

	if (ctx->set_idx) {
		idx_set(ctx, data);
		ctx->set_idx = 0;
		return;
	}

	switch (ctx->idx) {
	case REG_CMD:
		ctx->cmd_tmp = data;
		break;
	default:
		break;
	}

	idx_inc(ctx);
}

static uint8_t mcu_read(void *priv)
{
	struct mcu_ctx *ctx = priv;
	uint8_t ret = 0;

	switch (ctx->idx) {
	case REG_BOARD_TYPE:
		ret = get_board_type();
		break;
	case REG_SW_VER:
		ret = get_firmware_version();
		break;
	case REG_HW_VER:
		ret = get_pcb_version();
		break;
	case REG_CMD:
		ret = 0;
		break;
	case REG_SG2042_TMP:
		ret = get_soc_temp();
		break;
	case REG_BOARD_TMP:
		ret = get_ntc_tmp();
		break;
	case REG_INT_STATUS1:
		ret = ctx->int_status[0];
		break;
	case REG_INT_STATUS2:
		ret = ctx->int_status[1];
		break;
	case REG_INT_MASK1:
		ret = ctx->int_mask[0];
		break;
	case REG_INT_MASK2:
		ret = ctx->int_mask[1];
		break;
	case REG_I_5V_ADC:
		ret = adc_read_I_5V();
		break;
	case REG_I_DDR_VDD_0V8:
		ret = adc_read_I_DDR_VDD_0V8();
		break;
	case REG_I_DDR01_VDDQ_1V2:
		ret = adc_read_I_DDR01_VDDQ_1V2();
		break;
	case REG_I_DDR23_VDDQ_1V2:
		ret = adc_read_I_DDR23_VDDQ_1V2();
		break;
	case REG_I_VDD_12V:
		ret = adc_read_I_VDD_12V();
		break;
	case REG_I_VDD_EMMC_1V8:
		ret = adc_read_I_VDD_EMMC_1V8();
		break;
	case REG_I_VDD_EMMC_3V3:
		ret = adc_read_I_VDD_EMMC_3V3();
		break;
	case REG_I_VDD_PCIE_C_0V8:
		ret = adc_read_I_VDD_PCIE_C_0V8();
		break;
	case REG_I_VDD_PCIE_D_0V8:
		ret = adc_read_I_VDD_PCIE_D_0V8();
		break;
	case REG_I_VDD_PCIE_H_1V8:
		ret = adc_read_I_VDD_PCIE_H_1V8();
		break;
	case REG_I_VDD_PLL_0V8:
		ret = adc_read_I_VDD_PLL_0V8();
		break;
	case REG_I_VDD_RGMII_1V8:
		ret = adc_read_I_VDD_RGMII_1V8();
		break;
	case REG_I_VDDC:
		ret = adc_read_I_VDDC();
		break;
	case REG_I_VDDIO18:
		ret = adc_read_I_VDDIO18();
		break;
	case REG_I_VQPS18:
		ret = adc_read_I_VQPS18();
		break;
	default:
		ret = 0xff;
		break;
	}

	idx_inc(ctx);
	return ret;
}

static void mcu_stop(void *priv)
{
	struct mcu_ctx *ctx = priv;
	ctx->cmd = ctx->cmd_tmp;
}

static void mcu_reset(void *priv)
{
	struct mcu_ctx *ctx = priv;
	memset(ctx, 0x00, sizeof(*ctx));
}

static struct i2c01_slave_op slave = {
	.addr = 0x17,	/* mcu common slave address */
	.mask = 0x00,
	.match = mcu_match,
	.write = mcu_write,
	.read = mcu_read,
	.stop = mcu_stop,
	.reset = mcu_reset,
	.priv = &mcu_ctx,
};

void mcu_init(struct i2c01_slave_ctx *i2c_slave_ctx)
{
	mcu_ctx.critical_action = CRITICAL_ACTION_POWERDOWN;
	mcu_ctx.critical_temp = 120;
	mcu_ctx.repoweron_temp = 85;
	slave.addr = 0x17;
	i2c01_slave_register(i2c_slave_ctx, &slave);
}

uint8_t get_critical_action(void)
{
	return mcu_ctx.critical_action;
}

uint8_t get_critical_temp(void)
{
	return mcu_ctx.critical_temp;
}

uint8_t get_repoweron_temp(void)
{
	return mcu_ctx.repoweron_temp;
}