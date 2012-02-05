#include <common.h>
#include <asm/arch/ox820/regs.h>
#include <asm/io.h>

#define STATIC_NAND_ENABLE0  0x01fff000

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_CMD_NAND
#include <linux/mtd/nand.h>

static void nand_hwcontrol(struct mtd_info *mtdinfo, int cmd, unsigned int ctrl)
{
	struct nand_chip *this = mtdinfo->priv;
	u32 nand_baseaddr = (u32) CONFIG_SYS_NAND_BASE;

    if(ctrl & NAND_CTRL_CHANGE)
    {
        if(ctrl & NAND_CLE)
        {
			nand_baseaddr = CONFIG_SYS_NAND_COMMAND_LATCH;
        }
        if(ctrl & NAND_ALE)
        {
			nand_baseaddr = CONFIG_SYS_NAND_ADDRESS_LATCH;
        }
    }
	this->IO_ADDR_W = (void __iomem *)(nand_baseaddr);
}

static int nand_dev_ready(struct mtd_info *mtdinfo)
{
	return 1;
}

/*
extern struct nand_chip nand_dev_desc[CFG_MAX_NAND_DEVICE];
*/

int board_nand_init(struct nand_chip *nand)
{
 	///*enable static bus to device_select */
	///* enable secondary functions for: gpioa12 .. gpioa 19 (data bus), 
	 //* gpioa20(we) gpioa21(oe), gpioa 22(cs 0), gpiob 0 ..4 (address a0-a4)
	 //*/
	writel(STATIC_NAND_ENABLE0, SYS_CTRL_SECONDARY_SEL);

	///* enable clock and release static block reset */
	writel((1<<SYS_CTRL_CKEN_STATIC_BIT), SYS_CTRL_CKEN_SET_CTRL);
	writel((1<<SYS_CTRL_RSTEN_STATIC_BIT), SYS_CTRL_RSTEN_CLR_CTRL);

	//// enable CS_0
	//*(volatile u32*)SYS_CTRL_SECONDARY_SEL |=  0x00100000;
	//*(volatile u32*)SYS_CTRL_TERTIARY_SEL &= ~0x00100000;
	//*(volatile u32*)SYS_CTRL_DEBUG_SEL  &= ~0x00100000;
	

	// reset NAND unit
	*((volatile u8 *)(CONFIG_SYS_NAND_COMMAND_LATCH)) = 0xff;	// reset command
	udelay(500);

	nand->chip_delay = 100;
	nand->ecc.mode = NAND_ECC_SOFT;
	nand->cmd_ctrl = nand_hwcontrol;
	//nand->dev_ready = nand_dev_ready;

	return 0;
	/*
	if (nand_dev_desc[0].ChipID != NAND_ChipID_UNKNOWN) {
		print_size(nand_dev_desc[0].totlen, "\n");
	}
	*/
}
#endif