/* irq.c
 *
 *  This file contains the implementation of the function described in irq.h
 *
 *  CopyRight (C) 2000 Canon Research France SA.
 *  Emmanuel Raguet,  mailto:raguet@crf.canon.fr
 *
 *  The license and distribution terms for this file may be
 *  found in found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  irq.c,v 1.2.6.1 2003/09/04 18:43:44 joel Exp
 */


#include <bsp.h>
#include <irq.h>
#include <rtems/score/thread.h>
#include <rtems/score/apiext.h>


/*
 * This function check that the value given for the irq line
 * is valid.
 */

static int isValidInterrupt(int irq)
{
  if ( (irq < 0) || (irq > BSP_MAX_INT))
    return 0;
  return 1;
}

/*
 * ------------------------ RTEMS Single Irq Handler Mngt Routines ----------------
 */

int BSP_install_rtems_irq_handler  (const rtems_irq_connect_data* irq)
{
    rtems_irq_hdl *HdlTable;
    rtems_interrupt_level level;
    
    if (!isValidInterrupt(irq->name)) {
      return 0;
    }
    /*
     * Check if default handler is actually connected. If not issue an error.
     */
    HdlTable = VECTOR_TABLE;
    if (*(HdlTable + irq->name) != default_int_handler) {
      return 0;
    }
    
    _CPU_ISR_Disable(level);

    /*
     * store the new handler
     */
    *(HdlTable + irq->name) = irq->hdl;

    /*
     * Enable interrupt on device
     */
    if(irq->on)
    {
    	irq->on(irq);
    }

    _CPU_ISR_Enable(level);

    return 1;
}

int BSP_remove_rtems_irq_handler  (const rtems_irq_connect_data* irq)
{
    rtems_irq_hdl *HdlTable;
    rtems_interrupt_level level;
  
    if (!isValidInterrupt(irq->name)) {
      return 0;
    }
    /*
     * Check if the handler is actually connected. If not issue an error.
     */
    HdlTable = VECTOR_TABLE;
    if (*(HdlTable + irq->name) != irq->hdl) {
      return 0;
    }
    _CPU_ISR_Disable(level);

    /*
     * Disable interrupt on device
     */
    if(irq->off) {
        irq->off(irq);
    }

    /*
     * restore the default irq value
     */
    *(HdlTable + irq->name) = default_int_handler;
          
    _CPU_ISR_Enable(level);

    return 1;
}
