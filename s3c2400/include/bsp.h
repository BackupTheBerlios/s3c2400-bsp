/*-------------------------------------------------------------------------+
| bsp.h - ARM BSP 
+--------------------------------------------------------------------------+
| This include file contains definitions related to the ARM BSP.
+--------------------------------------------------------------------------+
|
| Copyright (c) Canon Research France SA.]
| Emmanuel Raguet, mailto:raguet@crf.canon.fr
|
|  The license and distribution terms for this file may be
|  found in found in the file LICENSE in this distribution or at
|  http://www.rtems.com/license/LICENSE.
| 
|  bsp.h,v 1.4.4.1 2003/09/04 18:43:44 joel Exp
+--------------------------------------------------------------------------*/


#ifndef __BSP_H_
#define __BSP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <bspopts.h>

#include <rtems.h>
#include <iosupp.h>
#include <console.h>
#include <clockdrv.h>
#include <s3c2400.h>

/* What is the input clock freq in hertz? */
#define BSP_OSC_FREQ  12000000    /* 12 MHz oscillator */
//#define BSP_XTAL_FREQ 32768       /* 32.768 KHz crystal */

/* How many serial ports? */
#define CONFIGURE_NUMBER_OF_TERMIOS_PORTS 1

/* How big should the interrupt stack be? */
#define CONFIGURE_INTERRUPT_STACK_MEMORY  (16 * 1024)

  
/*
 *  Define the interrupt mechanism for Time Test 27
 *
 *  NOTE: Following are not defined and are board independent
 *
 */

#define MUST_WAIT_FOR_INTERRUPT 0

#define Install_tm27_vector( handler ) 

#define Cause_tm27_intr()  

#define Clear_tm27_intr()  

#define Lower_tm27_intr()

#ifdef __cplusplus
}
#endif

#endif /* __BSP_H_ */
/* end of include file */

