/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "CoreImp.h"
//#include "usbd_if.h"
#include "dwt.h"

//extern void __libc_init_array(void);
//extern void init(void);

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

// Weak empty pre init to allow the app to operate before
// we set clocks etc. Used by bootloader
void AppPreInit() __attribute__((weak));
void AppPreInit() { }

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need HAL may fail.
__attribute__((constructor(101))) void premain()
{
  // Make sure that we run the startup code with interrupts disabled
  IrqDisable();
  // Allow App to get in very early
  AppPreInit();
  // Required by FreeRTOS, see http://www.freertos.org/RTOS-Cortex-M3-M4.html
#ifdef NVIC_PRIORITYGROUP_4
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
#endif
#if (__CORTEX_M == 0x07U)
  // Defined in CMSIS core_cm7.h
#ifndef I_CACHE_DISABLED
  SCB_EnableICache();
#endif
#ifndef D_CACHE_DISABLED
  //SCB_EnableDCache();
#endif
#endif
	//__libc_init_array();	// initialize C library and call C++ constructors for static data
  /* Init DWT if present */
#ifdef DWT_BASE
  dwt_init();
#endif

  /* Initialize the HAL */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();
}

/*
 * \brief Main entry point of Arduino application
 */
int main(void)
{
  initVariant();
	// Initialise application, which includes setting up any additional clocks
	AppInit();
	AppMain();				// note: app must set up the system tick interrupt, either within FreeRTOS or by calling SysTickInit

  //setup();

  for (;;) {
#if defined(CORE_CALLBACK)
    CoreCallback();
#endif
    //loop();
    //if (serialEventRun) {
      //serialEventRun();
    //}
  }

  return 0;
}
