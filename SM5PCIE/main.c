/**
 * @file main.c
 * @author chao.wei
 * @brief application logical start
 */
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <stdio.h>
#include <tick.h>
#include <system.h>
#include <i2c_master.h>
#include <i2c_slave.h>
#include <info.h>
#include <mcu.h>
#include <debug.h>
#include <mmc.h>

struct i2c_slave_ctx i2c1_slave_ctx;
struct mmc_port spi;

#define SAMPLE_NUM		(1024)
#define SAMPLE_DEPTH		(2)
#define CHANNEL_NUM		(5)
#define SAMPLE_TOTAL		(CHANNEL_NUM * SAMPLE_NUM)

#define ADC_DMA_CHANNEL		DMA_CHANNEL1

uint16_t sig_buf[SAMPLE_TOTAL];

int adc_setup(void)
{
	uint8_t channels[] = {0, 1, 5, 6, 7};
	/* init adc and dma */
	adc_power_off(ADC1);
	adc_calibrate(ADC1);
	adc_enable_dma(ADC1);
	adc_enable_dma_circular_mode(ADC1);
	adc_set_continuous_conversion_mode(ADC1);
	adc_disable_discontinuous_mode(ADC1);
	adc_set_right_aligned(ADC1);
	adc_set_resolution(ADC1, 0);
	adc_set_regular_sequence(ADC1, sizeof(channels), channels);
	/* about 10us per-sample, we have 5way, so 50us per-round */
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPTIME_160DOT5);
	adc_power_on(ADC1);

	return 0;
}

void adc_start(void)
{
	adc_start_conversion_regular(ADC1);
}

int dma_setup(void)
{
	dma_disable_channel(DMA1, ADC_DMA_CHANNEL);

	dma_enable_circular_mode(DMA1, ADC_DMA_CHANNEL);
	dma_enable_memory_increment_mode(DMA1, ADC_DMA_CHANNEL);

	dma_set_peripheral_size(DMA1, ADC_DMA_CHANNEL, DMA_CCR_PSIZE_16BIT);
	dma_set_memory_size(DMA1, ADC_DMA_CHANNEL, DMA_CCR_MSIZE_16BIT);

	dma_set_read_from_peripheral(DMA1, ADC_DMA_CHANNEL);
	dma_set_peripheral_address(DMA1, ADC_DMA_CHANNEL,
				   (uint32_t)&ADC_DR(ADC1));

	dma_set_memory_address(DMA1, ADC_DMA_CHANNEL, (uint32_t)sig_buf);
	dma_set_number_of_data(DMA1, ADC_DMA_CHANNEL, SAMPLE_TOTAL);

	dma_enable_transfer_complete_interrupt(DMA1, ADC_DMA_CHANNEL);
	dma_enable_channel(DMA1, ADC_DMA_CHANNEL);
	return 0;
}

int main(void)
{
	system_init();

	debug("BITMAIN SOPHONE SM5 PCIE BOARD -- %s\n", VERSION);

	i2c1_slave_ctx.id = 1;
	i2c_master_init(I2C1);
	i2c_slave_init(&i2c1_slave_ctx, (void *)I2C1_BASE);
	i2c_slave_start(&i2c1_slave_ctx);

	mcu_init();
	mmc_init(SPI1, GPIOA, GPIO15, &spi);

	adc_setup();
	dma_setup();
	adc_start();

	while (1) {
	}

	return 0;
}