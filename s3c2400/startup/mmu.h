#ifndef __MMU_H__
#define __MMU_H__

#define MMU_SECT_SIZE         0x100000 /*1MB*/

#define MMU_CACHE_NONE        0x0
#define MMU_CACHE_BUFFERED    0x1
#define MMU_CACHE_WTHROUGH    0x2
#define MMU_CACHE_WBACK       0x3

typedef struct {
    unsigned32 paddr;
    unsigned32 vaddr;
    unsigned32 size;         /* in MB */
    unsigned8  cache_flags;
} mmu_sect_map_t;


void mmu_init(mmu_sect_map_t *map, int num);

#endif /* __MMU_H__ */
