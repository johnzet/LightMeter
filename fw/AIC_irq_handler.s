/*****************************************************************************
  ctl IRQ handler for an Atmel AT91 AIC

  Copyright (c) 2005, 2007 Rowley Associates Limited.

  This file may be distributed under the terms of the License Agreement
  provided with this software. 
 
  THIS FILE IS PROVIDED AS IS WITH NO WARRANTY OF ANY KIND, INCLUDING THE
  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *****************************************************************************/

#define AIC_BASE         0xFFFFF000
#define AIC_IVR_OFFSET   0x100
#define AIC_EOICR_OFFSET 0x130

  .code 32
  .global irq_handler

irq_handler:
  // Check if I bit is set in SPSR to detect spurious interrupts
  stmfd sp!, {r0}
  mrs r0, spsr
  tst r0, #0x80
  ldmfd sp!, {r0}
  subnes pc, lr, #4
#ifdef CTL_TASKING
  // Store all registers in the tasking case
  stmfd sp!, {r0-r12, lr}
  mrs r0, spsr
  stmfd sp!, {r0}
  // Increment ctl_interrupt_count
  ldr r2, =ctl_interrupt_count
  ldrb r3, [r2]
  add r3, r3, #1
  strb r3, [r2]
#else 
  // Store the APCS registers in the non-tasking case
  stmfd sp!, {r0-r4, r12, lr}
#endif
  // Call ISR
  ldr r0, =AIC_BASE
  ldr r1, [r0, #AIC_IVR_OFFSET]
#ifndef NO_PROTECTION_MODE
  // Write to IVR in order to support protect mode - as an optimization this
  // can be removed if protect mode is not being used
  str r0, [r0, #AIC_IVR_OFFSET]
#endif
#ifdef NESTED_INTERRUPTS
  mrs r2, spsr
  stmfd sp!, {r2}
  msr cpsr_c, #0x1f // system mode, interrupts enabled
  stmfd sp!, {lr}
#endif
  mov lr, pc
  bx r1
#ifdef NESTED_INTERRUPTS
  ldmfd sp!, {lr}
  msr cpsr_c, #0x92 // irq mode, interrupts disabled
  ldmfd sp!, {r2}
  msr spsr_cxsf, r2
#endif
  // Mark end of interrupt
  ldr r0, =AIC_BASE
  str r0, [r0, #AIC_EOICR_OFFSET]
#ifdef CTL_TASKING
  // Return from interrupt via ctl_exit_isr
  mov r0, sp
  ldr r1, =ctl_exit_isr
  bx r1
#else
  // Return from interrupt
  ldmfd sp!, {r0-r4, r12, lr}
  subs pc, lr, #4
#endif
