/* THIS IS AUTO GENERATED CODE */

#ifndef __PIN_H__
#define __PIN_H__

#include <gd32e50x_gpio.h>

/* port A definition */
#define PCB_VER_PORT		GPIOA
#define PCB_VER_PIN		GPIO_PIN_0
#define PCB_VER_EXTI		EXTI_0
#define BOM_VER_PORT		GPIOA
#define BOM_VER_PIN		GPIO_PIN_1
#define BOM_VER_EXTI		EXTI_1
#define PCIEE_RST_X_MCU_PORT		GPIOA
#define PCIEE_RST_X_MCU_PIN		GPIO_PIN_15
#define PCIEE_RST_X_MCU_EXTI		EXTI_15
#define EN_VDDR_2H_1V1_PORT		GPIOA
#define EN_VDDR_2H_1V1_PIN		GPIO_PIN_8
#define EN_VDDR_2H_1V1_EXTI		EXTI_8
#define EN_VDDC_0V75_PORT		GPIOA
#define EN_VDDC_0V75_PIN		GPIO_PIN_9
#define EN_VDDC_0V75_EXTI		EXTI_9
#define EN_VDD_PLL_0V75_PORT		GPIOA
#define EN_VDD_PLL_0V75_PIN		GPIO_PIN_10
#define EN_VDD_PLL_0V75_EXTI		EXTI_10
#define EN_VDDIO_1V2_PORT		GPIOA
#define EN_VDDIO_1V2_PIN		GPIO_PIN_11
#define EN_VDDIO_1V2_EXTI		EXTI_11
#define EN_DDR_VDD_0V75_PORT		GPIOA
#define EN_DDR_VDD_0V75_PIN		GPIO_PIN_12
#define EN_DDR_VDD_0V75_EXTI		EXTI_12
#define MCU_SWDIO_PORT		GPIOA
#define MCU_SWDIO_PIN		GPIO_PIN_13
#define MCU_SWDIO_EXTI		EXTI_13
#define MCU_SWCLK_PORT		GPIOA
#define MCU_SWCLK_PIN		GPIO_PIN_14
#define MCU_SWCLK_EXTI		EXTI_14


/* port B definition */
#define MCU_BOOT1_PORT		GPIOB
#define MCU_BOOT1_PIN		GPIO_PIN_2
#define MCU_BOOT1_EXTI		EXTI_2
#define MCU_I2C1_SCL_PORT		GPIOB
#define MCU_I2C1_SCL_PIN		GPIO_PIN_6
#define MCU_I2C1_SCL_EXTI		EXTI_6
#define MCU_I2C1_SDA_PORT		GPIOB
#define MCU_I2C1_SDA_PIN		GPIO_PIN_7
#define MCU_I2C1_SDA_EXTI		EXTI_7
#define MCU_I2C2_SCL_PORT		GPIOB
#define MCU_I2C2_SCL_PIN		GPIO_PIN_10
#define MCU_I2C2_SCL_EXTI		EXTI_10
#define MCU_I2C2_SDA_PORT		GPIOB
#define MCU_I2C2_SDA_PIN		GPIO_PIN_11
#define MCU_I2C2_SDA_EXTI		EXTI_11
#define EN_VDD_1V8_PORT		GPIOB
#define EN_VDD_1V8_PIN		GPIO_PIN_12
#define EN_VDD_1V8_EXTI		EXTI_12
#define MCU_VDDR_VRHOT_PORT		GPIOB
#define MCU_VDDR_VRHOT_PIN		GPIO_PIN_13
#define MCU_VDDR_VRHOT_EXTI		EXTI_13
#define CPU_PWR_BUTTON_N_PORT		GPIOB
#define CPU_PWR_BUTTON_N_PIN		GPIO_PIN_14
#define CPU_PWR_BUTTON_N_EXTI		EXTI_14

/* port C definition */
#define EN_DDR_VDDQ_0V6_PORT		GPIOC
#define EN_DDR_VDDQ_0V6_PIN		GPIO_PIN_6
#define EN_DDR_VDDQ_0V6_EXTI		EXTI_6
#define EN_CXP_VP_PORT		GPIOC
#define EN_CXP_VP_PIN		GPIO_PIN_8
#define EN_CXP_VP_EXTI		EXTI_8
#define EN_CXP_VPH_PORT		GPIOC
#define EN_CXP_VPH_PIN		GPIO_PIN_9
#define EN_CXP_VPH_EXTI		EXTI_9
#define MCU_ATX_ON_PORT		GPIOC
#define MCU_ATX_ON_PIN		GPIO_PIN_12
#define MCU_ATX_ON_EXTI		EXTI_12
#define MCU_PS_ON_PORT		GPIOC
#define MCU_PS_ON_PIN		GPIO_PIN_13
#define MCU_PS_ON_EXTI		EXTI_13

/* port D definition */
#define MCU_USART1_TX_PORT		GPIOD
#define MCU_USART1_TX_PIN		GPIO_PIN_5
#define MCU_USART1_TX_EXTI		EXTI_5
#define MCU_USART1_RX_PORT		GPIOD
#define MCU_USART1_RX_PIN		GPIO_PIN_6
#define MCU_USART1_RX_EXTI		EXTI_6
#define EN_DDR_VAA_PORT		GPIOD
#define EN_DDR_VAA_PIN		GPIO_PIN_9
#define EN_DDR_VAA_EXTI		EXTI_9
#define CPU_SYS_RST_H_PORT		GPIOD
#define CPU_SYS_RST_H_PIN		GPIO_PIN_10
#define CPU_SYS_RST_H_EXTI		EXTI_10
#define VDDIO_EFUSE_EN_PORT		GPIOD
#define VDDIO_EFUSE_EN_PIN		GPIO_PIN_11
#define VDDIO_EFUSE_EN_EXTI		EXTI_11
#define PG_VDDC_0V75_PORT		GPIOD
#define PG_VDDC_0V75_PIN		GPIO_PIN_13
#define PG_VDDC_0V75_EXTI		EXTI_13
#define EN_VDD_DDR_1V8_PORT		GPIOD
#define EN_VDD_DDR_1V8_PIN		GPIO_PIN_15
#define EN_VDD_DDR_1V8_EXTI		EXTI_15

/* port E definition */
#define EN_VDDR_0V75_PORT		GPIOE
#define EN_VDDR_0V75_PIN		GPIO_PIN_2
#define EN_VDDR_0V75_EXTI		EXTI_2
#define POWER_LED_PORT		GPIOE
#define POWER_LED_PIN		GPIO_PIN_3
#define POWER_LED_EXTI		EXTI_3
#define EN_VDD_3V3_PORT		GPIOE
#define EN_VDD_3V3_PIN		GPIO_PIN_4
#define EN_VDD_3V3_EXTI		EXTI_4
#define VDDR_PG_PORT		GPIOE
#define VDDR_PG_PIN		GPIO_PIN_5
#define VDDR_PG_EXTI		EXTI_5
#define MCU_ALERT_VDDR_PORT		GPIOE
#define MCU_ALERT_VDDR_PIN		GPIO_PIN_6
#define MCU_ALERT_VDDR_EXTI		EXTI_6
#define MCU_STATUS_LED_PORT		GPIOE
#define MCU_STATUS_LED_PIN		GPIO_PIN_9
#define MCU_STATUS_LED_EXTI		EXTI_9

#endif
/* AUTO GENERATED CODE END */
