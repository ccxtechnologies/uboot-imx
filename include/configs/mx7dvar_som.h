/*
 * Copyright (C) 2015-2016 Freescale Semiconductor, Inc.
 * Copyright (C) 2016-2018 Variscite Ltd.
 *
 * Author: Eran Matityahu <eran.m@variscite.com>
 *
 * Configuration settings for the Variscite i.MX7D VAR-SOM-MX7 board family.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MX7D_VAR_SOM_CONFIG_H
#define __MX7D_VAR_SOM_CONFIG_H

#ifdef CONFIG_SPL
#include "imx7_spl.h"
#endif

#include "mx7_common.h"

#define CONFIG_DBG_MONITOR
#define PHYS_SDRAM_SIZE			SZ_1G

#define CONFIG_MXC_UART_BASE		UART1_IPS_BASE_ADDR

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(32 * SZ_1M)

/* Networtk */
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define CONFIG_FEC_XCV_TYPE		RGMII
#define CONFIG_FEC_ENET_DEV		0

#define CONFIG_PHYLIB
#define CONFIG_PHY_ATHEROS

#if (CONFIG_FEC_ENET_DEV == 0)
#define IMX_FEC_BASE			ENET_IPS_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR		0x0
#ifdef CONFIG_DM_ETH
#define CONFIG_ETHPRIME			"eth0"
#else
#define CONFIG_ETHPRIME			"FEC0"
#endif
#elif (CONFIG_FEC_ENET_DEV == 1)
#define IMX_FEC_BASE			ENET2_IPS_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR		0x1
#ifdef CONFIG_DM_ETH
#define CONFIG_ETHPRIME			"eth1"
#else
#define CONFIG_ETHPRIME			"FEC1"
#endif
#endif

#define CONFIG_FEC_MXC_MDIO_BASE	ENET_IPS_BASE_ADDR

/* Framebuffer */
#ifndef CONFIG_SPL_BUILD
#ifdef CONFIG_VIDEO
#define	CONFIG_VIDEO_MXS
#define	CONFIG_VIDEO_LOGO
#define	CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define	CONFIG_CMD_BMP
#define	CONFIG_BMP_16BPP
#define	CONFIG_VIDEO_BMP_RLE8
#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_IMX_VIDEO_SKIP
#endif
#endif

/* SPLASH SCREEN Configs  */
#ifdef CONFIG_SPLASH_SCREEN
/* Framebuffer and LCD  */
#define CONFIG_CMD_BMP
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_SPLASH_SOURCE
#endif

#undef CONFIG_BOOTM_NETBSD
#undef CONFIG_BOOTM_PLAN9
#undef CONFIG_BOOTM_RTEMS

/* I2C configs */
#ifndef CONFIG_DM_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */
#endif
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_SPEED		100000

/* PMIC */
#ifndef CONFIG_DM_PMIC
#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_PFUZE3000
#define CONFIG_POWER_PFUZE3000_I2C_ADDR	0x08
#endif

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#define CONFIG_SYS_AUXCORE_BOOTDATA 0x7F8000 /* Set to TCML address */

#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x20000000)

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

#define CONFIG_STACKSIZE		SZ_128K

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */
#ifdef CONFIG_NAND_BOOT
#define CONFIG_NAND_MXS
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x200000
#else
#define CONFIG_ENV_IS_IN_FAT
#define FAT_ENV_INTERFACE "mmc"
#define FAT_ENV_DEVICE_AND_PART "0:1"
#define FAT_ENV_FILE "uboot-env.bin"
#define CONFIG_ENV_SIZE (16 << 10) /* 16 KiB env size */
#endif

#ifdef CONFIG_NAND_MXS
#define CONFIG_CMD_NAND
#define CONFIG_CMD_NAND_TRIMFFS

/* NAND stuff */
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x40000000
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_ONFI_DETECTION

/* DMA stuff, needed for GPMI/MXS NAND support */
#define CONFIG_APBH_DMA
#define CONFIG_APBH_DMA_BURST
#define CONFIG_APBH_DMA_BURST8

#define MTDIDS_DEFAULT		"nand0=nandflash-0"

/*
 * Partitions layout for NAND is:
 *     mtd0: 2M       (spl)
 *     mtd1: 2M       (u-boot)
 *     mtd2: 2M       (u-boot environment)
 *     mtd3: 8M       (kernel)
 *     mtd4: left     (rootfs)
 */
/* Default mtd partition table */
#define MTDPARTS_DEFAULT	"mtdparts=nandflash-0:"\
					"2m(spl),"\
					"2m(u-boot),"\
					"2m(u-boot_env),"\
					"8m(kernel),"\
					"-(rootfs)"     /* ubifs */

/* UBI/UBIFS support */
#define CONFIG_CMD_UBIFS
#define CONFIG_UBI_SILENCE_MSG
#define CONFIG_RBTREE
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_MTDPARTS
#define CONFIG_LZO
#endif

#if defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_ENV_OFFSET		(14 * SZ_64K)
#define CONFIG_ENV_SIZE			SZ_8K
#elif defined(CONFIG_ENV_IS_IN_NAND)
#define CONFIG_ENV_OFFSET		(4 << 20)
#define CONFIG_ENV_SIZE			SZ_128K
#endif

#ifdef CONFIG_NAND_MXS
#define CONFIG_SYS_FSL_USDHC_NUM	1
#else
#define CONFIG_SYS_FSL_USDHC_NUM	2
#endif

/* MMC Config */
#define CONFIG_SYS_FSL_ESDHC_ADDR	0
#define CONFIG_SYS_MMC_ENV_DEV		0	/* USDHC1 */
#define CONFIG_SYS_MMC_ENV_PART		0	/* user area */

#define CONFIG_IMX_THERMAL

#define CONFIG_CMD_BMODE
#define CONFIG_FAT_WRITE

/* USB Configs */
#ifndef CONFIG_DM_USB
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_MXC_USB_FLAGS   0
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#endif
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_MXC_USB_PORTSC  (PORT_PTS_UTMI | PORT_PTS_PTW)

#define CONFIG_USBD_HS

/* Uncomment for USB Ethernet Gadget support */
/*
 * #define CONFIG_USB_ETHER
 * #define CONFIG_USB_ETH_CDC
 */
#define CONFIG_NETCONSOLE

#define CONFIG_USB_FUNCTION_MASS_STORAGE

#if defined(CONFIG_ANDROID_SUPPORT)
#include "mx7dvar_som_android.h"
#endif

#endif	/* __MX7D_VAR_SOM_CONFIG_H */
