/* irq_init.c
 *
 *  This file contains the implementation of rtems initialization
 *  related to interrupt handling.
 *
 *  CopyRight (C) 2000 Canon Research Centre France SA.
 *  Emmanuel Raguet, mailto:raguet@crf.canon.fr
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  bsp_irq_init.c,v 1.1.6.1 2003/09/04 18:43:44 joel Exp
 */
#include <irq.h>
#include <bsp.h>

extern void default_int_handler();

void BSP_rtems_irq_mngt_init() {

  /*
   * Here is the code to initialize the INT for
   * the specified BSP
   */
    
}
