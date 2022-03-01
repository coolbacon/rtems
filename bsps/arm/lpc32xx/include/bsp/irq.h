/**
 * @file
 *
 * @ingroup lpc32xx_interrupt
 *
 * @brief Interrupt definitions.
 */

/*
 * Copyright (c) 2009 embedded brains GmbH.  All rights reserved.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifndef LIBBSP_ARM_LPC32XX_IRQ_H
#define LIBBSP_ARM_LPC32XX_IRQ_H

#ifndef ASM

#include <rtems.h>
#include <rtems/irq.h>
#include <rtems/irq-extension.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup lpc32xx_interrupt Interrupt Support
 *
 * @ingroup RTEMSBSPsARMLPC32XX
 *
 * @ingroup bsp_interrupt
 *
 * @{
 */

#define LPC32XX_IRQ_INDEX(module, subindex) ((module) + (subindex))

#define LPC32XX_IRQ_MODULE_MIC 0U
#define LPC32XX_IRQ_MODULE_SIC_1 32U
#define LPC32XX_IRQ_MODULE_SIC_2 64U
#define LPC32XX_IRQ_MODULE_COUNT 3U

/* MIC interrupts */
#define LPC32XX_IRQ_SIC_1_IRQ LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 0)
#define LPC32XX_IRQ_SIC_2_IRQ LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 1)
#define LPC32XX_IRQ_TIMER_4_OR_MCPWM LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 3)
#define LPC32XX_IRQ_TIMER_5 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 4)
#define LPC32XX_IRQ_TIMER_HS LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 5)
#define LPC32XX_IRQ_WDG LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 6)
#define LPC32XX_IRQ_UART_3 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 7)
#define LPC32XX_IRQ_UART_4 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 8)
#define LPC32XX_IRQ_UART_5 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 9)
#define LPC32XX_IRQ_UART_6 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 10)
#define LPC32XX_IRQ_NAND_FLASH LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 11)
#define LPC32XX_IRQ_SDCARD_1 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 13)
#define LPC32XX_IRQ_LCD LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 14)
#define LPC32XX_IRQ_SDCARD_2 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 15)
#define LPC32XX_IRQ_TIMER_0 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 16)
#define LPC32XX_IRQ_TIMER_1 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 17)
#define LPC32XX_IRQ_TIMER_2 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 18)
#define LPC32XX_IRQ_TIMER_3 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 19)
#define LPC32XX_IRQ_SSP_0 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 20)
#define LPC32XX_IRQ_SSP_1 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 21)
#define LPC32XX_IRQ_I2S_0 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 22)
#define LPC32XX_IRQ_I2S_1 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 23)
#define LPC32XX_IRQ_UART_7 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 24)
#define LPC32XX_IRQ_UART_2 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 25)
#define LPC32XX_IRQ_UART_1 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 26)
#define LPC32XX_IRQ_TIMER_MS LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 27)
#define LPC32XX_IRQ_DMA LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 28)
#define LPC32XX_IRQ_ETHERNET LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 29)
#define LPC32XX_IRQ_SIC_1_FIQ LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 30)
#define LPC32XX_IRQ_SIC_2_FIQ LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_MIC, 31)

/* SIC 1 interrupts */
#define LPC32XX_IRQ_JTAG_COMM_TX LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 1)
#define LPC32XX_IRQ_JTAG_COMM_RX LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 2)
#define LPC32XX_IRQ_GPI_28 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 4)
#define LPC32XX_IRQ_TS_P LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 6)
#define LPC32XX_IRQ_TS_IRQ_OR_ADC LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 7)
#define LPC32XX_IRQ_TS_AUX LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 8)
#define LPC32XX_IRQ_SPI_2 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 12)
#define LPC32XX_IRQ_PLL_USB LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 13)
#define LPC32XX_IRQ_PLL_HCLK LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 14)
#define LPC32XX_IRQ_PLL_397 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 17)
#define LPC32XX_IRQ_I2C_2 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 18)
#define LPC32XX_IRQ_I2C_1 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 19)
#define LPC32XX_IRQ_RTC LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 20)
#define LPC32XX_IRQ_KEYSCAN LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 22)
#define LPC32XX_IRQ_SPI_1 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 23)
#define LPC32XX_IRQ_SW LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 24)
#define LPC32XX_IRQ_USB_OTG_TIMER LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 25)
#define LPC32XX_IRQ_USB_OTG_ATX LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 26)
#define LPC32XX_IRQ_USB_HOST LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 27)
#define LPC32XX_IRQ_USB_DEV_DMA LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 28)
#define LPC32XX_IRQ_USB_DEV_LP LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 29)
#define LPC32XX_IRQ_USB_DEV_HP LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 30)
#define LPC32XX_IRQ_USB_I2C LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_1, 31)

/* SIC 2 interrupts */
#define LPC32XX_IRQ_GPIO_0 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 0)
#define LPC32XX_IRQ_GPIO_1 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 1)
#define LPC32XX_IRQ_GPIO_2 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 2)
#define LPC32XX_IRQ_GPIO_3 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 3)
#define LPC32XX_IRQ_GPIO_4 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 4)
#define LPC32XX_IRQ_GPIO_5 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 5)
#define LPC32XX_IRQ_SPI_2_DATAIN LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 6)
#define LPC32XX_IRQ_UART_2_HCTS LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 7)
#define LPC32XX_IRQ_GPIO_P0_P1_IRQ LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 8)
#define LPC32XX_IRQ_GPI_8 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 9)
#define LPC32XX_IRQ_GPI_9 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 10)
#define LPC32XX_IRQ_GPI_19 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 11)
#define LPC32XX_IRQ_UART_7_HCTS LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 12)
#define LPC32XX_IRQ_GPI_7 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 15)
#define LPC32XX_IRQ_SDIO LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 18)
#define LPC32XX_IRQ_UART_5_RX LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 19)
#define LPC32XX_IRQ_SPI_1_DATAIN LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 20)
#define LPC32XX_IRQ_GPI_0 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 22)
#define LPC32XX_IRQ_GPI_1 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 23)
#define LPC32XX_IRQ_GPI_2 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 24)
#define LPC32XX_IRQ_GPI_3 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 25)
#define LPC32XX_IRQ_GPI_4 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 26)
#define LPC32XX_IRQ_GPI_5 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 27)
#define LPC32XX_IRQ_GPI_6 LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 28)
#define LPC32XX_IRQ_SYSCLK LPC32XX_IRQ_INDEX(LPC32XX_IRQ_MODULE_SIC_2, 31)

#define LPC32XX_IRQ_PRIORITY_VALUE_MIN 0U
#define LPC32XX_IRQ_PRIORITY_VALUE_MAX 15U
#define LPC32XX_IRQ_PRIORITY_COUNT (LPC32XX_IRQ_PRIORITY_VALUE_MAX + 1U)
#define LPC32XX_IRQ_PRIORITY_HIGHEST LPC32XX_IRQ_PRIORITY_VALUE_MIN
#define LPC32XX_IRQ_PRIORITY_LOWEST LPC32XX_IRQ_PRIORITY_VALUE_MAX

#define BSP_INTERRUPT_VECTOR_COUNT (LPC32XX_IRQ_SYSCLK + 1)

#define LPC32XX_IRQ_COUNT BSP_INTERRUPT_VECTOR_COUNT

void lpc32xx_irq_set_priority(rtems_vector_number vector, unsigned priority);

unsigned lpc32xx_irq_get_priority(rtems_vector_number vector);

typedef enum {
  LPC32XX_IRQ_ACTIVE_LOW_OR_FALLING_EDGE,
  LPC32XX_IRQ_ACTIVE_HIGH_OR_RISING_EDGE
} lpc32xx_irq_activation_polarity;

void lpc32xx_irq_set_activation_polarity(rtems_vector_number vector, lpc32xx_irq_activation_polarity activation_polarity);

lpc32xx_irq_activation_polarity lpc32xx_irq_get_activation_polarity(rtems_vector_number vector);

typedef enum {
  LPC32XX_IRQ_LEVEL_SENSITIVE,
  LPC32XX_IRQ_EDGE_SENSITIVE
} lpc32xx_irq_activation_type;

void lpc32xx_irq_set_activation_type(rtems_vector_number vector, lpc32xx_irq_activation_type activation_type);

lpc32xx_irq_activation_type lpc32xx_irq_get_activation_type(rtems_vector_number vector);

void lpc32xx_set_exception_handler(Arm_symbolic_exception_name exception, void (*handler)(void));

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ASM */

#endif /* LIBBSP_ARM_LPC32XX_IRQ_H */
