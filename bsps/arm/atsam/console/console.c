/*
 * Copyright (c) 2016 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Dornierstr. 4
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/fatal.h>
#include <rtems/console.h>

#include <rtems/termiostypes.h>

#include <chip.h>

#include <unistd.h>

typedef struct {
  rtems_termios_device_context base;
  Uart *regs;
  rtems_vector_number irq;
  uint32_t id;
  bool console;
  bool is_usart;
#ifdef ATSAM_CONSOLE_USE_INTERRUPTS
  bool transmitting;
#endif
} atsam_uart_context;

static atsam_uart_context atsam_usart_instances[] = {
  {
    .regs = (Uart *)USART0,
    .irq = USART0_IRQn,
    .id = ID_USART0,
    .is_usart = true,
  }
#ifdef USART1
  , {
    .regs = (Uart *)USART1,
    .irq = USART1_IRQn,
    .id = ID_USART1,
    .is_usart = true,
  }
#endif
#ifdef USART2
  , {
    .regs = (Uart *)USART2,
    .irq = USART2_IRQn,
    .id = ID_USART2,
    .is_usart = true,
  }
#endif
};

static atsam_uart_context atsam_uart_instances[] = {
  {
    .regs = UART0,
    .irq = UART0_IRQn,
    .id = ID_UART0,
    .is_usart = false,
  }
#ifdef UART1
  , {
    .regs = UART1,
    .irq = UART1_IRQn,
    .id = ID_UART1,
    .is_usart = false,
  }
#endif
#ifdef UART2
  , {
    .regs = UART2,
    .irq = UART2_IRQn,
    .id = ID_UART2,
    .is_usart = false,
  }
#endif
#ifdef UART3
  , {
    .regs = UART3,
    .irq = UART3_IRQn,
    .id = ID_UART3,
    .is_usart = false,
  }
#endif
#ifdef UART4
  , {
    .regs = UART4,
    .irq = UART4_IRQn,
    .id = ID_UART4,
    .is_usart = false,
  }
#endif
};

#ifdef ATSAM_CONSOLE_USE_INTERRUPTS
static void atsam_uart_interrupt(void *arg)
{
  rtems_termios_tty *tty = arg;
  atsam_uart_context *ctx = rtems_termios_get_device_context(tty);
  Uart *regs = ctx->regs;
  uint32_t sr = regs->UART_SR;

  while ((sr & UART_SR_RXRDY) != 0) {
    char c = (char) regs->UART_RHR;

    rtems_termios_enqueue_raw_characters(tty, &c, 1);

    sr = regs->UART_SR;
  }

  if (ctx->transmitting && (sr & UART_SR_TXEMPTY) != 0) {
    rtems_termios_dequeue_characters(tty, 1);
  }
}
#endif

static bool atsam_uart_set_attributes(
  rtems_termios_device_context *base,
  const struct termios *term
)
{
  atsam_uart_context *ctx = (atsam_uart_context *) base;
  Uart *regs = ctx->regs;
  rtems_termios_baud_t baud;
  uint32_t mr;

  baud = rtems_termios_baud_to_number(term->c_ospeed);
  regs->UART_BRGR = (BOARD_MCK / baud) / 16;

  if ((term->c_cflag & CREAD) != 0) {
    regs->UART_CR = UART_CR_RXEN | UART_CR_TXEN;
  } else {
    regs->UART_CR = UART_CR_TXEN;
  }

  if (ctx->is_usart) {
    mr = US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK;
  } else {
    mr = UART_MR_FILTER_DISABLED | UART_MR_BRSRCCK_PERIPH_CLK;
  }

  if (ctx->is_usart) {
    switch (term->c_cflag & CSIZE) {
      case CS5:
        mr |= US_MR_CHRL_5_BIT;
        break;
      case CS6:
        mr |= US_MR_CHRL_6_BIT;
        break;
      case CS7:
        mr |= US_MR_CHRL_7_BIT;
        break;
      default:
        mr |= US_MR_CHRL_8_BIT;
        break;
    }
  } else {
    if ((term->c_cflag & CSIZE) != CS8) {
      return false;
    }
  }

  if ((term->c_cflag & PARENB) != 0) {
    if ((term->c_cflag & PARODD) != 0) {
      mr |= UART_MR_PAR_ODD;
    } else {
      mr |= UART_MR_PAR_EVEN;
    }
  } else {
    mr |= UART_MR_PAR_NO;
  }

  if (ctx->is_usart) {
    if ((term->c_cflag & CSTOPB) != 0) {
      mr |= US_MR_NBSTOP_2_BIT;
    } else {
      mr |= US_MR_NBSTOP_1_BIT;
    }
  } else {
    if ((term->c_cflag & CSTOPB) != 0) {
      return false;
    }
  }

  regs->UART_MR = mr;

  return true;
}

static bool atsam_uart_first_open(
  rtems_termios_tty *tty,
  rtems_termios_device_context *base,
  struct termios *term,
  rtems_libio_open_close_args_t *args
)
{
  atsam_uart_context *ctx = (atsam_uart_context *) base;
  Uart *regs = ctx->regs;
#ifdef ATSAM_CONSOLE_USE_INTERRUPTS
  rtems_status_code sc;
#endif

  regs->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RSTSTA;
  regs->UART_IDR = 0xffffffff;

  PMC_EnablePeripheral(ctx->id);

  rtems_termios_set_initial_baud(tty, ATSAM_CONSOLE_BAUD);
  atsam_uart_set_attributes(base, term);

#ifdef ATSAM_CONSOLE_USE_INTERRUPTS
  regs->UART_IER = UART_IDR_RXRDY;
  sc = rtems_interrupt_handler_install(
    ctx->irq,
    ctx->is_usart ? "USART" : "UART",
    RTEMS_INTERRUPT_SHARED,
    atsam_uart_interrupt,
    tty
  );
  if (sc != RTEMS_SUCCESSFUL) {
    return false;
  }
#endif

  return true;
}

static void atsam_uart_last_close(
  rtems_termios_tty *tty,
  rtems_termios_device_context *base,
  rtems_libio_open_close_args_t *args
)
{
  atsam_uart_context *ctx = (atsam_uart_context *) base;

#ifdef ATSAM_CONSOLE_USE_INTERRUPTS
  rtems_interrupt_handler_remove(ctx->irq, atsam_uart_interrupt, tty);
#endif

  if (!ctx->console) {
    PMC_DisablePeripheral(ctx->id);
  }
}

static void atsam_uart_write(
  rtems_termios_device_context *base,
  const char *buf,
  size_t len
)
{
  atsam_uart_context *ctx = (atsam_uart_context *) base;
  Uart *regs = ctx->regs;

#ifdef ATSAM_CONSOLE_USE_INTERRUPTS
  if (len > 0) {
    ctx->transmitting = true;
    regs->UART_THR = buf[0];
    regs->UART_IER = UART_IDR_TXEMPTY;
  } else {
    ctx->transmitting = false;
    regs->UART_IDR = UART_IDR_TXEMPTY;
  }
#else
  size_t i;

  for (i = 0; i < len; ++i) {
    while ((regs->UART_SR & UART_SR_TXEMPTY) == 0) {
      /* Wait */
    }

    regs->UART_THR = buf[i];
  }
#endif
}

#ifndef ATSAM_CONSOLE_USE_INTERRUPTS
static int atsam_uart_read(rtems_termios_device_context *base)
{
  atsam_uart_context *ctx = (atsam_uart_context *) base;
  Uart *regs = ctx->regs;

  if ((regs->UART_SR & UART_SR_RXRDY) != 0) {
    return (char) regs->UART_RHR;
  } else {
    return -1;
  }
}
#endif

static const rtems_termios_device_handler atsam_uart_handler = {
  .first_open = atsam_uart_first_open,
  .last_close = atsam_uart_last_close,
  .write = atsam_uart_write,
  .set_attributes = atsam_uart_set_attributes,
#ifdef ATSAM_CONSOLE_USE_INTERRUPTS
  .mode = TERMIOS_IRQ_DRIVEN
#else
  .poll_read = atsam_uart_read,
  .mode = TERMIOS_POLLED
#endif
};

rtems_status_code console_initialize(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *arg
)
{
  size_t i;

  rtems_termios_initialize();

  for (i = 0; i < RTEMS_ARRAY_SIZE(atsam_usart_instances); ++i) {
    char usart[] = "/dev/ttyUSARTX";

    usart[sizeof(usart) - 2] = (char) ('0' + i);
    rtems_termios_device_install(
      &usart[0],
      &atsam_uart_handler,
      NULL,
      &atsam_usart_instances[i].base
    );

#if ATSAM_CONSOLE_DEVICE_TYPE == 0
    if (i == ATSAM_CONSOLE_DEVICE_INDEX) {
      atsam_usart_instances[i].console = true;
      link(&usart[0], CONSOLE_DEVICE_NAME);
    }
#endif
  }

  for (i = 0; i < RTEMS_ARRAY_SIZE(atsam_uart_instances); ++i) {
    char uart[] = "/dev/ttyUARTX";

    uart[sizeof(uart) - 2] = (char) ('0' + i);
    rtems_termios_device_install(
      &uart[0],
      &atsam_uart_handler,
      NULL,
      &atsam_uart_instances[i].base
    );

#if ATSAM_CONSOLE_DEVICE_TYPE == 1
    if (i == ATSAM_CONSOLE_DEVICE_INDEX) {
      atsam_uart_instances[i].console = true;
      link(&uart[0], CONSOLE_DEVICE_NAME);
    }
#endif
  }

  return RTEMS_SUCCESSFUL;
}
