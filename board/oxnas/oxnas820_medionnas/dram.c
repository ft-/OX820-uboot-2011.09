#include <common.h>
#include <asm/arch/ox820/regs.h>

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
    gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE; /* convert to MBytes */

    gd->bd->bi_dram[0].start = PHYS_SDRAM_1_PA;
    
    gd->ram_size = CONFIG_MAX_RAM_BANK_SIZE;

    return 0;
}
