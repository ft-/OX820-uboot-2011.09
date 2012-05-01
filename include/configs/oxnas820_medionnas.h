#ifndef __CONFIG_H
#define __CONFIG_H

#undef CONFIG_USE_IRQ

#define OXNAS_USE_NAND_ENV 1

#define RPSCLK 6250000
#define CONFIG_SYS_TEXT_BASE 0x60d00000
#define CONFIG_STANDALONE_LOAD_ADDR 0x60000000

#define CONFIG_IDENT_STRING "OX820"

#define CONFIG_SYS_HZ ((RPSCLK) / 16) 
/* Architecture */
#define CONFIG_ARM1136 1
#define CONFIG_OXNAS820 1
#define CONFIG_OXNAS820_MEDIONNAS 1

/*
 * Network
 */
#define CONFIG_NET_MULTI
#define CONFIG_ETHADDR      00:30:e0:00:00:01

/*
 * Serial
 */
#define CONFIG_BAUDRATE 115200
#define CONFIG_SYS_BAUDRATE_TABLE   { 9600, 19200, 38400, 57600, 115200 }

/*
 * Command line configuration
 */
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_IMI
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_EDITENV
#define CONFIG_CMD_SAVEENV
//#define CONFIG_CMD_NFS
#define CONFIG_CMD_NAND
#define CONFIG_CMD_MII
#define CONFIG_MII

/*
 * BOOTP
 */
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTFILE		"/tftpboot/mnas-uImage" /* file to load */

/*
 * Network
 */
#define CONFIG_NETMASK      255.255.0.0
#define CONFIG_IPADDR       192.168.50.100
#define CONFIG_SERVERIP     192.168.50.59
#define CONFIG_SYS_AUTOLOAD "n"

/*
 * Console
 */
#define CONFIG_SYS_CBSIZE 256
#define CONFIG_SYS_PROMPT "MNAS # "
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS 16
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE

/*
 * Stack
 */
#define CONFIG_STACKSIZE (128 * 1024)
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4 * 1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4 * 1024)	/* FIQ stack */
#endif

/*
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS 1
#define PHYS_SDRAM_1 0x60000000
#define PHYS_SDRAM_1_SIZE (128 * 1024 * 1024)

/*
 * Environment
 */
#if (OXNAS_USE_NAND && OXNAS_USE_NAND_ENV)
#define CONFIG_ENV_SIZE (128*1024)
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET 0x3c0000
#else
#define CONFIG_ENV_IS_NOWHERE
#endif

/*
 * NAND
 */
#define CONFIG_SYS_MAX_NAND_DEVICE 1
#define CONFIG_SYS_NAND_BASE 0x41000000
#define	CONFIG_SYS_NAND_ADDRESS_LATCH	(CONFIG_SYS_NAND_BASE + (1<<18))
#define	CONFIG_SYS_NAND_COMMAND_LATCH	(CONFIG_SYS_NAND_BASE + (1<<19))

//#define CONFIG_MTD_DEVICE
//#define CONFIG_MTD_PARTITIONS

/*
 * Flash
 */
#define CONFIG_SYS_NO_FLASH
#ifndef CONFIG_SYS_NO_FLASH
#define NUM_FLASH_MAIN_BLOCKS   63          /* For Intel 28F320B3T */
#define NUM_FLASH_PARAM_BLOCKS  8           /* For Intel 28F320B3T */
#define FLASH_MAIN_BLOCK_SIZE   (64*1024)   /* For Intel 28F320B3T family */
#define FLASH_PARAM_BLOCK_SIZE  (8*1024)    /* For Intel 28F320B3T family */

/* Assuming counts main blocks and parameter blocks, as the Intel/AMD detection */
/* I'm intending to copy would seem to indicate */
#define CONFIG_SYS_MAX_FLASH_SECT      (NUM_FLASH_MAIN_BLOCKS + NUM_FLASH_PARAM_BLOCKS)
#define CONFIG_SYS_MAX_FLASH_BANKS     1           /* Assume counts flash devices */
#endif

/*
 * Disk support
 */

/*
 * SDRAM
 */
#define CONFIG_SYS_SDRAM_BASE (0x60000000)
#define CONFIG_MAX_RAM_BANK_SIZE (128 * 1024 * 1024)
#define CONFIG_SYS_MALLOC_LEN (1024 * 1024)
#define CONFIG_SYS_INIT_SP_ADDR (0x60000000 + 128 * 1024 * 1024 - 64 * 1024)

#define CONFIG_SYS_MEMTEST_START 0x60000000
#define CONFIG_SYS_MEMTEST_END ((128 * 1024 * 1024 ) + CONFIG_SYS_MEMTEST_START - 1)

#define CONFIG_SYS_LOAD_ADDR 0x60000000

/*
 * UART
 */
#define CONFIG_SYS_NS16550 1
#define CONFIG_SYS_NS16550_SERIAL 1
#define CONFIG_SYS_NS16550_COM1 (0x44200000)
//#define CONFIG_SYS_NS16550_COM2 (0x44300000)
#define CONFIG_SYS_NS16550_REG_SIZE 1

#define CONFIG_CONS_INDEX 1

#define CONFIG_SYS_NS16550_CLK (RPSCLK)

/*
 * USB Host
 */

/*
 * Shell
 */
//#define CONFIG_SYS_HUSH_PARSER
//#define CONFIG_SYS_PROMPT_HUSH_PS2 "MNAS> "

#endif
