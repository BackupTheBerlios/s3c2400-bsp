/*-------------------------------------------------------------------------+
| This file contains the ARM BSP startup package. It includes application,
| board, and monitor specific initialization and configuration. The generic CPU
| dependent initialization has been performed before this routine is invoked. 
+--------------------------------------------------------------------------+
|
| Copyright (c) 2000 Canon Research Centre France SA.
| Emmanuel Raguet, mailto:raguet@crf.canon.fr
|
|   The license and distribution terms for this file may be
|   found in found in the file LICENSE in this distribution or at
|   http://www.rtems.com/license/LICENSE.
|
+--------------------------------------------------------------------------*/


#include <bsp.h>
#include <rtems/libcsupport.h>
#include <rtems/libio.h>
#include "mmu.h"
#include <s3c2400x.h>

#include <uart.h>

/*-------------------------------------------------------------------------+
| Global Variables
+--------------------------------------------------------------------------*/

//extern void            *_flash_size;
//extern void            *_flash_base;
extern void            *_sdram_size;
extern void            *_sdram_base;
extern void            *_bss_free_start;

unsigned long           free_mem_start;
unsigned long           free_mem_end;

/* The original BSP configuration table from the application and our copy of it
   with some changes. */

extern rtems_configuration_table  Configuration;
       rtems_configuration_table  BSP_Configuration;

rtems_cpu_table Cpu_table;                     /* CPU configuration table.    */
char            *rtems_progname;               /* Program name - from main(). */

/*-------------------------------------------------------------------------+
| External Prototypes
+--------------------------------------------------------------------------*/
extern void rtems_irq_mngt_init(void);
void bsp_libc_init( void *, unsigned32, int );
void bsp_postdriver_hook(void);

/*-------------------------------------------------------------------------+
|         Function: bsp_pretasking_hook
|      Description: BSP pretasking hook.  Called just before drivers are
|                   initialized. Used to setup libc and install any BSP
|                   extensions. NOTE: Must not use libc (to do io) from here,
|                   since drivers are not yet initialized.
| Global Variables: None.
|        Arguments: None.
|          Returns: Nothing. 
+--------------------------------------------------------------------------*/
void bsp_pretasking_hook(void)
{

    unsigned32 heap_start;
    unsigned32 heap_size;


    /* 
     * Set up the heap. 
     */
    heap_start =  free_mem_start;
    heap_size = free_mem_end - free_mem_start;

    /* call rtems lib init - malloc stuff */
    bsp_libc_init((void *)heap_start, heap_size, 0);

#ifdef RTEMS_DEBUG

    rtems_debug_enable(RTEMS_DEBUG_ALL_MASK);

#endif /* RTEMS_DEBUG */

} /* bsp_pretasking_hook */
 

/*-------------------------------------------------------------------------+
|         Function: bsp_start
|      Description: Called before main is invoked.
| Global Variables: None.
|        Arguments: None.
|          Returns: Nothing. 
+--------------------------------------------------------------------------*/
void bsp_start_default( void )
{
    mmu_sect_map_t mem_map[] = {
        {0x00000000, 0x0c100000,   1, MMU_CACHE_NONE},    /* Mirror of SDRAM */
        {0x0c000000, 0x0c000000,   8, MMU_CACHE_WTHROUGH},     /* SDRAM */
        {0x14000000, 0x14000000,   1, MMU_CACHE_NONE},     /* Internals Regs - */
        {0x15000000, 0x15000000,   1, MMU_CACHE_NONE},     /* Specials Internal Regs - */
    };

  /* If we don't have command line arguments set default program name. */

  Cpu_table.pretasking_hook         = bsp_pretasking_hook; /* init libc, etc. */
  Cpu_table.predriver_hook          = NULL;                /* use system's    */
  Cpu_table.postdriver_hook         = bsp_postdriver_hook;
  Cpu_table.idle_task               = NULL;
                                          /* do not override system IDLE task */
  Cpu_table.do_zero_of_workspace    = TRUE;
  Cpu_table.interrupt_stack_size    = 4096;
  Cpu_table.extra_mpci_receive_server_stack = 0;

  /*disable interrupts */
  //FIXME
  //FIXME
  
  /*set interrupt priority to -1 (allow all priorties) */
  //FIXME
  
  /* Place RTEMS workspace at beginning of free memory. */
  BSP_Configuration.work_space_start = (void *)&_bss_free_start;
 
  free_mem_start = ((unsigned32)&_bss_free_start + BSP_Configuration.work_space_size);
    
  free_mem_end = ((unsigned32)&_sdram_base + (unsigned32)&_sdram_size);

  /*enable the MMU*/
  mmu_init(mem_map, (sizeof(mem_map) / sizeof(mmu_sect_map_t))); 
 
  /*
   * Init rtems exceptions management
   */
  rtems_exception_init_mngt();

  /*
   * Init rtems interrupt management
   */
  rtems_irq_mngt_init();

  /*
   *  The following information is very useful when debugging.
   */

#if 0
  printk( "work_space_size = 0x%x\n", BSP_Configuration.work_space_size );
  printk( "maximum_extensions = 0x%x\n", BSP_Configuration.maximum_extensions );
  printk( "microseconds_per_tick = 0x%x\n",
     BSP_Configuration.microseconds_per_tick );
  printk( "ticks_per_timeslice = 0x%x\n",
     BSP_Configuration.ticks_per_timeslice );
  printk( "maximum_devices = 0x%x\n", BSP_Configuration.maximum_devices );
  printk( "number_of_device_drivers = 0x%x\n",
     BSP_Configuration.number_of_device_drivers );
  printk( "Device_driver_table = 0x%x\n",
     BSP_Configuration.Device_driver_table );

  printk( "_heap_size = 0x%x\n", _heap_size );
  /*  printk( "_stack_size = 0x%x\n", _stack_size );*/
  printk( "rtemsFreeMemStart = 0x%x\n", rtemsFreeMemStart );
  printk( "work_space_start = 0x%x\n", BSP_Configuration.work_space_start );
  printk( "work_space_size = 0x%x\n", BSP_Configuration.work_space_size );
#endif

} /* bsp_start */

/*
 *  By making this a weak alias for bsp_start_default, a brave soul
 *  can override the actual bsp_start routine used.
 */

void bsp_start (void) __attribute__ ((weak, alias("bsp_start_default")));
