/*
 * STM32F746 SoC
 *
 * Copyright (c) 2023 lockbox <lockbox.06@protonmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef HW_ARM_STM32F746_SOC_H
#define HW_ARM_STM32F746_SOC_H

#include "hw/adc/stm32f2xx_adc.h"
#include "hw/arm/armv7m.h"
#include "hw/char/stm32f2xx_usart.h"
#include "hw/misc/stm32f4xx_exti.h"
#include "hw/misc/stm32f4xx_syscfg.h"
#include "hw/or-irq.h"
#include "hw/ssi/stm32f2xx_spi.h"
#include "hw/timer/stm32f2xx_timer.h"
#include "qom/object.h"

#define TYPE_STM32F746_SOC "stm32f746-soc"
OBJECT_DECLARE_SIMPLE_TYPE(STM32F746State, STM32F746_SOC)

#define STM_NUM_USARTS 7
#define STM_NUM_TIMERS 4
#define STM_NUM_ADCS 6
#define STM_NUM_SPIS 6

/* For the following addresses and sizes see:
 * section 2.2.2 Figure 1 */
#define FLASH_BASE_ADDRESS 0x08000000
#define FLASH_SIZE (1024 * 1024)
/* Coalesce SRAM1 + SRAM2 */
#define SRAM_BASE_ADDRESS 0x20010000
#define SRAM_SIZE (240 * 1024 + 16 * 1024)
#define DTCM_BASE_ADDRESS 0x20000000
#define DTCM_SIZE (64 * 1024)
#define ITCM_BASE_ADDRESS 0x0UL
#define ITCM_SIZE (0x4000UL)
#define OTP_BASE_ADDRESS 0x1FF0F000
#define OTP_SIZE (0x440UL)

struct STM32F746State {
  /*< private >*/
  SysBusDevice parent_obj;
  /*< public >*/

  char *cpu_type;

  ARMv7MState armv7m;

  STM32F4xxSyscfgState syscfg;
  STM32F4xxExtiState exti;
  STM32F2XXUsartState usart[STM_NUM_USARTS];
  STM32F2XXTimerState timer[STM_NUM_TIMERS];
  qemu_or_irq adc_irqs;
  STM32F2XXADCState adc[STM_NUM_ADCS];
  STM32F2XXSPIState spi[STM_NUM_SPIS];

  MemoryRegion otp;
  MemoryRegion itcm;
  MemoryRegion dtcm;
  MemoryRegion sram;
  MemoryRegion flash;
  MemoryRegion flash_alias;

  Clock *sysclk;
  Clock *refclk;
};

#endif
