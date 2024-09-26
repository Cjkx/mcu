#include <loop.h>
#include <pin.h>
#include <i2c_slave.h>
#include <common.h>
#include <power.h>
#include <wdt.h>
#include <chip.h>
#include <mcu-e2prom.h>

static int power_state = 0;

void power_gpio_process(void)
{
	if (!gpio_get(MCU_INT_PORT, MCU_INT_PIN) && power_state == 1){
		power_state = 0;
		mcu_eeprom_power_off_reason(EEPROM_POWER_OFF_REASON_EXT_GPIO);
		power_off();
		chip_disable();
		wdt_reset();
	} else if (gpio_get(MCU_INT_PORT, MCU_INT_PIN) && power_state == 0){
		power_state = 1;
		chip_popd_reset_end();
		wdt_reset();
	}

}

int detect_power_gpio(void)
{
	if (gpio_get(MCU_INT_PORT, MCU_INT_PIN)) {
		power_state = 1;
		return 1;
	} else {
		power_state = 0;
		return 0;
	}

}

void power_gpio_init(void)
{
	loop_add(power_gpio_process);
}