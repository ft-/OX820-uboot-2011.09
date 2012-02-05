#include <common.h>
#include <asm/arch/ox820/regs.h>

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
    DECLARE_GLOBAL_DATA_PTR;
    
    gd->bd->bi_dram[0].size = 128 << 20; /* convert to MBytes */

    gd->bd->bi_dram[0].start = PHYS_SDRAM_1_PA;

    return 0;
}
