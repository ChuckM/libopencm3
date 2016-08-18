/** @defgroup usb_defines USB Defines
 *
 * @ingroup STM32F4xx_defines
 *
 * @brief Defined Constants and Macros for the STM32x4xx USB OTG Peripheral
 *
 * @version 1.0.0
 *
 * @date 15 August 2016
 * LGPL License Terms @ref lgpl_license
 *
 * ###Endpoint control and configuration registers
 *
 * IN Endpoints have the following registers: 
 * - **DIEPCTL** : Control register
 * - **DIEPINT** : Interrupt register 
 * - **DIEPTSIZ** : Transfer size
 * - **DTXFSTS** - xmit FIFO status
 *
 * OUT Endpoints have the following registers:
 * - **DOEPCTL** : Control register
 * - **DOEPINT** : Interrupt register
 * - **DOEPTSIZ** : Transfer size
 *
 * There are 5 endpoints in the FS core and 7 endpoints in the
 * HS core. Endpoint 0 is always a CONTROL endpoint and so its
 * version of these registers may are limited to flags associated
 * with control endpoints.
 *
 * Specifying an endpoint takes the form `OTG_Difffff(usb, x)`
 * Where the value _i_ is either **I** for an IN endpoint or **O** for
 * an OUT endpoint. The value _fff_ is one of **EPCTL**, **EPINT**, **EPTSIZ**,
 * or **TXFSTS**.
 *
 * ### OTG USB Host channels
 *
 * @brief Each host channel has :
 * - **HCCHAR** : Characteristics
 * - **HCSPLT** : Split control
 * - **HCINT** : Interrupt
 * - **HCINTMSK** : Interrupt Mask
 * - **HCTSIZ** : Transfer Size
 * - **HCDMA** : DMA Address (HS only)
 *
 * 15 channels in HS, 11 channels in FS
 *
 *
 * You reference a channel in code with `OTG_HCCHAR(USB_FS, 1) = 0xbabe;`
 *
 */

/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2016 Chuck McManis <cmcmanis@mcmanis.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

/**@{*/

/**
 * @brief Macro for Extracting register bitfields
 *
 * This macro will extract the bit field value from the named
 * _register_, the named _field_. The value in _x_ is assumed to
 * come from the register. The field value is returned shifted
 * right into the least significant bits and masked to the defined
 * number of bits of the field.
 *
 * @param[in] reg The data sheet register name
 * @param[in] field The data sheet bit field name
 * @param[in] x A value from that register.
 *
 * **Example:**
 *
 * \code{.c}
 *  uint32_t x = USB_GET(DCFG, DAD, OTG_DCFG);
 * \endcode
 *
 * You could also extract directly from GHCR with this code:
 *
 * \code{.c}
 *  uint8_t data0 = DSI_GET(GHCR, DATA0, DSI_GHCR);
 * \endcode
 *
 */
#define OTG_GET(reg, field, x) \
    (((x) >> OTG_ ## reg ##_## field ##_SHIFT) & OTG_## reg ##_## field ##_MASK)

/**
 * @brief Macro for Setting register bitfields
 *
 * This macro will prepare the bit field value to be inserted
 * into the register named _reg_, in the bit field position named
 * _field_. The value in _x_ is assumed to be unshifted.
 *
 *  @param[in] reg The data sheet register name
 *  @param[in] field The data sheet bit field name
 *  @param[in] x A value from that register.
 *
 *  **Example:**
 *
 * \code{.c}


 * \endcode
 *

 *
 * \code{.c}
 
 * \endcode
 *
 */
#define OTG_SET(reg, field, x) \
    (((x) & OTG_ ## reg ##_## field ##_MASK) << OTG_## reg ##_## field ##_SHIFT)

/**
 * @brief Macro for generating Masks to clear  register bitfields
 *
 * This macro will return a sequence of 1 bits of the same size
 * and bit position as the field named _field_, in the register
 * named _reg_. You can use this to clear a previous value from
 * the field by ANDing the register with its binary inverse.
 *
 *  @param[in] reg The data sheet register name
 *  @param[in] field The data sheet bit field name
 *
 *  **Example:**
 *
 * \code{.c}


 * \endcode
 *

 *
 * \code{.c}
 
 * \endcode
 *
 */
#define OTG_MASK(reg, field) \
    ((OTG_ ## reg ##_## field ##_MASK) << OTG_## reg ##_## field ##_SHIFT)

/** }@ */

#pragma once

/* Allow the different register groups to address both the HS and FS Set */
#define USB_FS				USB_OTG_FS_BASE
#define USB_HS				USB_OTG_HS_BASE

/** Control and Status Register */
#define OTG_GOTGCTL(usb)		MMIO32((usb) + 0x000)

#define OTG_GOTGCTL_VER			(1 << 20)	/* FS */
#define OTG_GOTGCTL_BSVLD		(1 << 19)	/* FS/HS */
#define OTG_GOTGCTL_ASVLD		(1 << 18)	/* FS/HS */
#define OTG_GOTGCTL_DBCT		(1 << 17)	/* FS/HS */
#define OTG_GOTGCTL_CIDSTS		(1 << 16)	/* FS/HS */
#define OTG_GOTGCTL_EHEN		(1 << 12)	/* FS/HS */
#define OTG_GOTGCTL_DHNPEN		(1 << 11)	/* FS/HS */
#define OTG_GOTGCTL_HSHNPEN		(1 << 10)	/* FS/HS */
#define OTG_GOTGCTL_HNPRQ		(1 << 9)	/* FS/HS */
#define OTG_GOTGCTL_HNGSCS		(1 << 8)	/* FS/HS */
#define OTG_GOTGCTL_BVALOVAL		(1 << 7)	/* HS */
#define OTG_GOTGCTL_BVALOEN		(1 << 6)	/* HS */
#define OTG_GOTGCTL_AVALOVAL		(1 << 5)	/* HS */
#define OTG_GOTGCTL_AVALOEN		(1 << 4)	/* HS */
#define OTG_GOTGCTL_VBVALOVAL		(1 << 3)	/* HS */
#define OTG_GOTGCTL_VBVALOEN		(1 << 2)	/* HS */
#define OTG_GOTGCTL_SRQ			(1 << 1)	/* FS/HS */
#define OTG_GOTGCTL_SRQSCS		(1 << 0)	/* FS/HS */

/** OTG Interrupt Register */
#define OTG_GOTGINT(usb)		MMIO32((usb) + 0x004)

#define OTG_GOTGINT_IDCHNG		(1 << 20)	/* FS/HS */
#define OTG_GOTGINT_DBCDNE		(1 << 19)	/* FS/HS */
#define OTG_GOTGINT_ADTOCHG		(1 << 18)	/* FS/HS */
#define OTG_GOTGINT_HNGDET		(1 << 17)	/* FS/HS */
#define OTG_GOTGINT_HNSSCHG		(1 << 9)	/* FS/HS */
#define OTG_GOTGINT_SRSSCHG		(1 << 8)	/* FS/HS */
#define OTG_GOTGINT_SEDET		(1 << 2)	/* FS/HS */

/** OTG AHB Configuration Register */
#define OTG_GAHBCFG(usb)		MMIO32((usb) + 0x008)

#define OTG_GAHBCFG_PTXFELVL		(1 << 8)	/* FS/HS */
#define OTG_GAHBCFG_TXFELVL		(1 << 7)	/* FS/HS */
#define OTG_GAHBCFG_DMAEN		(1 << 5)	/* HS */
#define OTG_GAHBCFG_HBSTLEN_SHIFT	1		/* HS */
#define OTG_GAHBCFG_HBSTLEN_MASK	0xf		/* HS */
#define OTG_GAHBCFG_HBSTLEN_SINGLE	0		/* HS */
#define OTG_GAHBCFG_HBSTLEN_INCR	1		/* HS */
#define OTG_GAHBCFG_HBSTLEN_INCR4	3		/* HS */
#define OTG_GAHBCFG_HBSTLEN_INCR8	5		/* HS */
#define OTG_GAHBCFG_HBSTLEN_INCR16	7		/* HS */
#define OTG_GAHBCFG_GINTMSK		(1 << 0)	/* FS/HS */

/** OTG USB Configuration Register */
#define OTG_GUSBCFG(usb)		MMIO32((usb) + 0x00C)

#define OTG_GUSBCFG_FDMOD		(1 << 30)	/* FS/HS */
#define OTG_GUSBCFG_FHMOD		(1 << 29)	/* FS/HS */
#define OTG_GUSBCFG_ULPIIPD		(1 << 25)	/* HS */
#define OTG_GUSBCFG_PTCI		(1 << 24)	/* HS */
#define OTG_GUSBCFG_PCCI		(1 << 23)	/* HS */
#define OTG_GUSBCFG_TSDPS		(1 << 22)	/* HS */
#define OTG_GUSBCFG_ULPIEVBUSI		(1 << 21)	/* HS */
#define OTG_GUSBCFG_ULPIEVBUSD		(1 << 20)	/* HS */
#define OTG_GUSBCFG_ULPICSM		(1 << 19)	/* HS */
#define OTG_GUSBCFG_ULPIAR		(1 << 18)	/* HS */
#define OTG_GUSBCFG_ULPIFSLS		(1 << 17)	/* HS */
#define OTG_GUSBCFG_PHYLPCS		(1 << 15)	/* HS */
#define OTG_GUSBCFG_TRDT_SHIFT		10		/* FS/HS */
#define OTG_GUSBCFG_TRDT_MASK		0xf		/* FS/HS */
#define OTG_GUSBCFG_HNPCAP		(1 << 9)	/* FS/HS */
#define OTG_GUSBCFG_SRPCAP		(1 << 8)	/* FS/HS */
#define OTG_GUSBCFG_PHYSEL		(1 << 6)	/* FS/HS */
#define OTG_GUSBCFG_TOCAL_SHIFT		0		/* FS/HS */
#define OTG_GUSBCFG_TOCAL_MASK		0x7		/* FS/HS */

/** OTG Reset Register */
#define OTG_GRSTCTL(usb)		MMIO32((usb) + 0x010)

#define OTG_GRSTCTL_AHBIDL		(1 << 31)	/* FS/HS */
#define OTG_GRSTCTL_DMAREQ		(1 << 30)	/* HS */
#define OTG_GRSTCTL_TXFNUM_MASK		0x1f		/* FS/HS */
#define OTG_GRSTCTL_TXFNUM_SHIFT	6		/* FS/HS */
#define OTG_GRSTCTL_TXFFLSH		(1 << 5)	/* FS/HS */
#define OTG_GRSTCTL_RXFFLSH		(1 << 4)	/* FS/HS */
#define OTG_GRSTCTL_FCRST		(1 << 2)	/* FS */
#define OTG_GRSTCTL_HSRST		(1 << 1)	/* HS */
#define OTG_GRSTCTL_CSRST		(1 << 0)	/* FS/HS */

/** OTG Core Interrupt Register */
#define OTG_GINTSTS(usb)		MMIO32((usb) + 0x014)

#define OTG_GINTSTS_WKUPINT		(1 << 31)	/* FS/HS */
#define OTG_GINTSTS_SRQINT		(1 << 30)	/* FS/HS */
#define OTG_GINTSTS_DISCINT		(1 << 29)	/* FS/HS */
#define OTG_GINTSTS_CIDSCHG		(1 << 28)	/* FS/HS */
#define OTG_GINTSTS_LPMINT		(1 << 27)	/* FS */
#define OTG_GINTSTS_PTXFE		(1 << 26)	/* FS/HS */
#define OTG_GINTSTS_HCINT		(1 << 25)	/* FS/HS */
#define OTG_GINTSTS_HPRTINT		(1 << 24)	/* FS/HS */
#define OTG_GINTSTS_RSTDET		(1 << 23)	/* FS */
#define OTG_GINTSTS_DATAFSUSP		(1 << 22)	/* HS */
#define OTG_GINTSTS_IPXFR		(1 << 21)	/* FS/HS */
#define OTG_GINTSTS_INCOMPISOOUT	(1 << 21)	/* FS/HS */
#define OTG_GINTSTS_IISOIXFR		(1 << 20)	/* FS/HS */
#define OTG_GINTSTS_OEPINT		(1 << 19)	/* FS/HS */
#define OTG_GINTSTS_IEPINT		(1 << 18)	/* FS/HS */
#define OTG_GINTSTS_EOPF		(1 << 15)	/* FS/HS */
#define OTG_GINTSTS_ISOODRP		(1 << 14)	/* FS/HS */
#define OTG_GINTSTS_ENUMDNE		(1 << 13)	/* FS/HS */
#define OTG_GINTSTS_USBRST		(1 << 12)	/* FS/HS */
#define OTG_GINTSTS_USBSUSP		(1 << 11)	/* FS/HS */
#define OTG_GINTSTS_ESUSP		(1 << 10)	/* FS/HS */
#define OTG_GINTSTS_GONAKEFF		(1 << 7)	/* FS/HS */
#define OTG_GINTSTS_GINAKEFF		(1 << 6)	/* FS/HS */
#define OTG_GINTSTS_NPTXFE		(1 << 5)	/* FS/HS */
#define OTG_GINTSTS_RXFLVL		(1 << 4)	/* FS/HS */
#define OTG_GINTSTS_SOF			(1 << 3)	/* FS/HS */
#define OTG_GINTSTS_OTGINT		(1 << 2)	/* FS/HS */
#define OTG_GINTSTS_MMIS		(1 << 1)	/* FS/HS */
#define OTG_GINTSTS_CMOD		(1 << 0)	/* FS/HS */

/** OTG Interrupt Mask Register */
#define OTG_GINTMSK(usb)	MMIO32((usb) + 0x018)

#define OTG_GINTMSK_WUIM		(1 << 31)	/* FS/HS */
#define OTG_GINTMSK_SRQIM		(1 << 30)	/* FS/HS */
#define OTG_GINTMSK_DISCINT		(1 << 29)	/* FS/HS */
#define OTG_GINTMSK_CIDSCHGM		(1 << 28)	/* FS/HS */
#define OTG_GINTMSK_LPMINTM		(1 << 27)	/* FS/HS */
#define OTG_GINTMSK_PTXFEM		(1 << 26)	/* FS/HS */
#define OTG_GINTMSK_HCIM		(1 << 25)	/* FS/HS */
#define OTG_GINTMSK_PRTIM		(1 << 24)	/* FS/HS */
#define OTG_GINTMSK_RSTDETM		(1 << 23)	/* FS/HS */
#define OTG_GINTMSK_FSUSPM		(1 << 22)	/* HS */
#define OTG_GINTMSK_IPXFRM		(1 << 21)	/* Host */
#define OTG_GINTMSK_IISOOXFRM		(1 << 21)	/* Dev */
#define OTG_GINTMSK_IISOIXFRM		(1 << 20)	/* FS/HS */
#define OTG_GINTMSK_OEPINT		(1 << 19)	/* FS/HS */
#define OTG_GINTMSK_IEPINT		(1 << 18)	/* FS/HS */
#define OTG_GINTMSK_EOPFM		(1 << 15)	/* FS/HS */
#define OTG_GINTMSK_ISOODRPM		(1 << 14)	/* FS/HS */
#define OTG_GINTMSK_ENUMDENEM		(1 << 13)	/* FS/HS */
#define OTG_GINTMSK_USBRST		(1 << 12)	/* FS/HS */
#define OTG_GINTMSK_USBSUSPM		(1 << 11)	/* FS/HS */
#define OTG_GINTMSK_ESUSPM		(1 << 10)	/* FS/HS */
#define OTG_GINTMSK_GONAKEFFM		(1 << 7)	/* FS/HS */
#define OTG_GINTMSK_GINAKEFFM		(1 << 6)	/* FS/HS */
#define OTG_GINTMSK_NPTXFEM		(1 << 5)	/* FS/HS */
#define OTG_GINTMSK_RXFLVLM		(1 << 4)	/* FS/HS */
#define OTG_GINTMSK_SOFM		(1 << 3)	/* FS/HS */
#define OTG_GINTMSK_OTGINT		(1 << 2)	/* FS/HS */
#define OTG_GINTMSK_MMISM		(1 << 1)	/* FS/HS */

/** OTG Receive Status Debug / OTH Status Read and Pop Registers */
#define OTG_GRXSTSR(usb)		MMIO32((usb) + 0x01C)
#define OTG_GRXSTSP(usb)		MMIO32((usb) + 0x020)

/* OTG Receive Status Pop Register
 * Pop =  OTG_GRXSTP
 * Read = OTG_GRXSTR
 * Flags are of the form OTG_GRXSTx */
#define OTG_GRXSTx_PKTSTS_MASK		0xf
#define OTG_GRXSTx_PKTSTS_SHIFT		17
#define OTG_GRXSTx_HOST_PKTSTS_INR	2	/* IN packet recv'd */
#define OTG_GRXSTx_HOST_PKTSTS_ITC	3	/* IN xfer complete */
#define OTG_GRXSTx_HOST_PKTSTS_DTE	5	/* Data Toggle Error */ 
#define OTG_GRXSTx_HOST_PKTSTS_HALT	7	/* Channel Halt */ 
#define OTG_GRXSTx_DEV_PKTSTS_NAK	1	/* Global OUT NAK */
#define OTG_GRXSTx_DEV_PKTSTS_OPR	2	/* OUT packet recv'd */
#define OTG_GRXSTx_DEV_PKTSTS_OTC	3	/* OUT xfer completed */
#define OTG_GRXSTx_DEV_PKTSTS_SCMP	4	/* SETUP Complete */
#define OTG_GRXSTx_DEV_PKTSTS_SDR	6	/* SETUP Data Pkt Rec'd */
#define OTG_GRXSTx_FRMNUM_SHIFT		21
#define OTG_GRXSTx_FRMNUM_MASK		0xf
#define OTG_GRXSTx_DPID_MASK		0x3
#define OTG_GRXSTx_DPID_SHIFT		15
#define OTG_GRXSTx_DPID_DATA0		0
#define OTG_GRXSTx_DPID_DATA1		2
#define OTG_GRXSTx_DPID_DATA2		1
#define OTG_GRXSTx_DPID_MDATA		3
#define OTG_GRXSTx_BCNT_MASK		0x3ff
#define OTG_GRXSTx_BCNT_SHIFT		4
#define OTG_GRXSTx_CHNUM_MASK		0xf	/* host */
#define OTG_GRXSTx_CHNUM_SHIFT		0
#define OTG_GRXSTx_EPNUM_MASK		0xf	/* device */
#define OTG_GRXSTx_EPNUM_SHIFT		0

/** OTG Receive FIFO Depth */
#define OTG_GRXFSIZ(usb)		MMIO32((usb) + 0x024)
#define OTG_GRXFSIZ_RXFD_SHIFT		0		/* FS/HS */
#define OTG_GRXFSIZ_RXFD_MASK		0xffff		/* FS/HS */

/** OTG Periodic Transmit FIFO Size */
#define OTG_HNPTXFSIZ(usb)		MMIO32((usb) + 0x028)
#define OTG_DIEPTXF0(usb)		MMIO32((usb) + 0x028)

/* host mode */
#define OTG_HNPTXFSIZ_NPTXFD_MASK	0xffff		/* FS/HS */
#define OTG_HNPTXFSIZ_NPTXFD_SHIFT	16		/* FS/HS */
#define OTG_HNPTXFSIZ_NPTXFSA_MASK	0xffff		/* FS/HS */
#define OTG_HNPTXFSIZ_NPTXFSA_SHIFT	0		/* FS/HS */

/* device mode */
#define OTG_DIEPTXF0_TX0FD_MASK		0xffff		/* FS/HS */
#define OTG_DIEPTXF0_TX0FD_SHIFT	16		/* FS/HS */
#define OTG_DIEPTXF0_TX0FSA_MASK	0xffff		/* FS/HS */
#define OTG_DIEPTXF0_TX0FSA_SHIFT	0		/* FS/HS */

/** OTG Non-periodic transmit FIFO and Queue Status Register */
#define OTG_HNPTXSTS(usb)		MMIO32((usb) + 0x02C)

/* Host only */
#define OTG_HNPTXSTS_NPTXQTOP_MASK	0x7f
#define OTG_HNPTXSTS_NPTXQTOP_SHIFT	24
#define OTG_HNPTXSTS_NPTQXSAV_MASK	0xff
#define OTG_HNPTXSTS_NPTQXSAV_SHIFT	16
#define OTG_HNPTXSTS_NPTXFSAV_MASK	0xffff
#define OTG_HNPTXSTS_NPTXFSAV_SHIFT	0

/** OTG I2C Access Register
 * @brief This is used for the I2C port connected to the external HS PHY
 */
#define OTG_GI2CCTL(usb)		MMIO32((usb) + 0x30U)

#define OTG_GI2CCTL_BSYDNE		(1 << 31)	/* HS */
#define OTG_GI2CCTL_RW			(1 << 30)	/* HS */
#define OTG_GI2CCTL_I2CDATSE0		(1 << 28)	/* HS */
#define OTG_GI2CCTL_I2CDEVADR_SHIFT	26		/* HS */
#define OTG_GI2CCTL_I2CDEVADR_MASK	0x3		/* HS */
#define OTG_GI2CCTL_ACK			(1 << 24)	/* HS */
#define OTG_GI2CCTL_I2CEN		(1 << 23)	/* HS */
#define OTG_GI2CCTL_ADDR_SHIFT		16		/* HS */
#define OTG_GI2CCTL_ADDR_MASK		0x3		/* HS */
#define OTG_GI2CCTL_REGADDR_SHIFT	8		/* HS */
#define OTG_GI2CCTL_REGADDR_MASK	0x7f		/* HS */
#define OTG_GI2CCTL_RWDATA_SHIFT	0		/* HS */
#define OTG_GI2CCTL_RWDATA_MASK		0xff		/* HS */

/** OTG General Core configuration Register
 *
 * @brief This register varies incompatibly between devices in
 *        the family, use the helper functions.
 */
#define OTG_GCCFG(usb)		MMIO32((usb) + 0x038)

/* Ver 1.2 bits */
#define OTG_GCCFG_VBDEN			(1 << 21)

/* Older (pre 1.2 bit definitions */
#define OTG_GCCFG_NOVBUSSENS		(1 << 21)	/* Caution! */
#define OTG_GCCFG_SOFOUTEN		(1 << 20)
#define OTG_GCCFG_VBUSBSEN		(1 << 19)
#define OTG_GCCFG_VBUSASEN		(1 << 18)

/* defined in both new and older instances  */
#define OTG_GCCFG_PWRDWN		(1 << 16)

/** OTG Version number of the USB hardware core */
#define OTG_CID(usb)			MMIO32((usb) + 0x03C)

/** OTG core Link Power Management configuration register */
#define OTG_GLPMCFG(usb)		MMIO32((usb) + 0x054)

#define OTG_GLPMCFG_ENBESL		(1 << 28)
#define OTG_GLPMCFG_LPMRCNTSTS_SHIFT	25
#define OTG_GLPMCFG_LPMRCNTSTS_MASK	0x7
#define OTG_GLPMCFG_SNDLPM		(1 << 24)
#define OTG_GLPMCFG_LPMRCNT_SHIFT	21
#define OTG_GLPMCFG_LPMRCNT_MASK	0x7
#define OTG_GLPMCFG_LPMCHIDX_SHIFT	17
#define OTG_GLPMCFG_LPMCHIDX_MASK	0xf
#define OTG_GLPMCFG_L1RSMOK		(1 << 16)
#define OTG_GLPMCFG_SLPSTS		(1 << 15)
#define OTG_GLPMCFG_LPMRST_SHIFT	13
#define OTG_GLPMCFG_LPMRST_MASK		0x3
#define OTG_GLPMCFG_L1DSEN		(1 << 12)
#define OTG_GLPMCFG_BESLTHRS_SHIFT	8
#define OTG_GLPMCFG_BESLTHRS_MASK	0xf
#define OTG_GLPMCFG_L1SSEN		(1 << 7)
#define OTG_GLPMCFG_REMWAKE		(1 << 6)
#define OTG_GLPMCFG_BESL_SHIFT		2
#define OTG_GLPMCFG_BESL_MASK		0xf
#define OTG_GLPMCFG_LPMACK		(1 << 1)
#define OTG_GLPMCFG_LPMEN		(1 << 0)

/** OTG Host periodic transmit FIFO size register */
#define OTG_HPTXFSIZ(usb)		MMIO32((usb) + 0x100)

#define OTG_HPTXFSIZ_PTXFSIZ_SHIFT	16
#define OTG_HPTXFSIZ_PTXFSIZ_MASK	0xffff
#define OTG_HPTXFSIZ_PTXSA_SHIFT	0
#define OTG_HPTXFSIZ_PTXSA_MASK		0xffff

/** OTG Device IN endpoint FIFO Size Register 
 * @brief there are 5 (FS), or 7 (HS) IN endpoint FIFOs
 */
#define OTG_DIEPTXF(usb, x)	MMIO32((usb) + (0x104 + 4*((x)-1)))
#define OTG_DIEPTXF_INEPTXFD_SHIFT	16
#define OTG_DIEPTXF_INEPTXFD_MASK	0xffff
#define OTG_DIEPTXF_INEPTXSA_SHIFT	16
#define OTG_DIEPTXF_INEPTXSA_MASK	0xffff

/** OTG Host Configuration Register */
#define OTG_HCFG(usb)			MMIO32((usb) + 0x400)
#define OTG_HCFG_FSLSS			(1 << 2)
#define OTG_HCFG_FSLSPCS_SHIFT		0
#define OTG_HCFG_FSLSPCS_MASK		0x3
#define OTG_HCFG_FSLSPCS_48MHZ		1
#define OTG_HCFG_FSLSPCS_6MHZ		2

/** OTG Host Frame interval register */
#define OTG_HFIR(usb)			MMIO32((usb) + 0x404)
#define OTG_HFIR_RLDCTRL		(1 << 16)
#define OTG_HFIR_FRIVL_SHIFT		0
#define OTG_HFIR_FRIVL_MASK		0xffff

/** OTG Host Frame number / Frame Time remaining Register */
#define OTG_HFNUM(usb)			MMIO32((usb) + 0x408)
#define OTG_HFNUM_FTREM_SHIFT		16
#define OTG_HFNUM_FTREM_MASK		0xffff
#define OTG_HFNUM_FRNUM_SHIFT		16
#define OTG_HFNUM_FRNUM_MASK		0xffff

/** OTG Host periodic transmit FIFO / queue status register */
#define OTG_HPTXSTS(usb)		MMIO32((usb) + 0x410)

#define OTG_HPTXSTS_PTXQTOP_SHIFT	24
#define OTG_HPTXSTS_PTXQTOP_MASK	0xff
#define OTG_HPTXSTS_PTXQSAV_SHIFT	16
#define OTG_HPTXSTS_PTXQSAV_MASK	0xff
#define OTG_HPTXSTS_PTXFSAVL_SHIFT	0
#define OTG_HPTXSTS_PTXFSAVL_MASK	0xffff

/** OTG Host all channels interrupt register */
#define OTG_HAINT(usb)			MMIO32((usb) + 0x414)
#define OTG_HAINT_HAINT_SHIFT		0
#define OTG_HAINT_HAINT_MASK		0xffff

/** OTG Host all channels interrupt mask register */
#define OTG_HAINTMSK(usb)		MMIO32((usb) + 0x418)
#define OTG_HAINT_HAINTM_SHIFT		0
#define OTG_HAINT_HAINTM_MASK		0xffff

/** OTH Host Port control and status register */
#define OTG_HPRT(usb)			MMIO32((usb) + 0x440)
#define OTG_HPRT_PSPD_SHIFT		17
#define OTG_HPRT_PSPD_MASK		0x3
#define OTG_HPRT_PCTL_SHIFT		13
#define OTG_HPRT_PCTL_MASK		0xf
#define OTG_HPRT_PPWR			(1 << 12)
#define OTG_HPRT_PLSTS_SHIFT		10
#define OTG_HPRT_PLSTS_MASK		3
#define OTG_HPRT_PRST			(1 << 8)
#define OTG_HPRT_PSUSP			(1 << 7)
#define OTG_HPRT_PRES			(1 << 6)
#define OTG_HPRT_POCCHNG		(1 << 5)
#define OTG_HPRT_POCA			(1 << 4)
#define OTG_HPRT_PENCHNG		(1 << 3)
#define OTG_HPRT_PENA			(1 << 2)
#define OTG_HPRT_PCDET			(1 << 1)
#define OTG_HPRT_PCSTS			(1 << 0)


/** OTG Host, Channel x characteristics register. */
#define OTG_HCCHAR(usb, x)		MMIO32((usb) + (0x500 + 0x20 * (x)))

#define OTG_HCCHAR_CHENA		(1 << 31)
#define OTG_HCCHAR_CHDIS		(1 << 30)
#define OTG_HCCHAR_ODDFRM		(1 << 29)
#define OTG_HCCHAR_DAD_SHIFT		22
#define OTG_HCCHAR_DAD_MASK		0x7f
#define OTG_HCCHAR_MCNT_SHIFT		20
#define OTG_HCCHAR_MCNT_MASK		3
#define OTG_HCCHAR_EPTYP_SHIFT		18
#define OTG_HCCHAR_EPTYP_MASK		3
#define OTG_HCCHAR_EPTYP_CONTROL	0
#define OTG_HCCHAR_EPTYP_ISOCHRONOUS	1
#define OTG_HCCHAR_EPTYP_BULK		2
#define OTG_HCCHAR_EPTYP_INTERRUPT	3
#define OTG_HCCHAR_LSDEV		(1 << 17)
#define OTG_HCCHAR_EPDIR		(1 << 15)
#define OTG_HCCHAR_EPDIR_OUT		0
#define OTG_HCCHAR_EPDIR_IN		(1 << 15)
#define OTG_HCCHAR_EPNUM_SHIFT		11
#define OTG_HCCHAR_EPNUM_MASK		0xf
#define OTG_HCCHAR_MPSIZE_SHIFT		0
#define OTG_HCCHAR_MPSIZE_MASK		0x7ff

/** OTG Host, Channel x split control register */
#define OTG_HCSPLT(usb, x)		MMIO32((usb) + (0x504 + 0x20 * (x)))

#define OTG_HCSPLT_SPLITEN		(1 << 31)
#define OTG_HCSPLT_COMPLSPLT		(1 << 16)
#define OTG_HCSPLT_XACTPOS_SHIFT	14
#define OTG_HCSPLT_XACTPOS_MASK		0x3
#define OTG_HCSPLT_XACTPOS_ALL		0x3
#define OTG_HCSPLT_XACTPOS_BEGIN	0x2
#define OTG_HCSPLT_XACTPOS_MID		0x0
#define OTG_HCSPLT_XACTPOS_END		0x1
#define OTG_HCSPLT_HUBADDR_SHIFT	7
#define OTG_HCSPLT_HUBADDR_MASK		0x7f
#define OTG_HCSPLT_PORTADDR_SHIFT	0
#define OTG_HCSPLT_PORTADDR_MASK	0x7f

/** OTG Host, Channel x interrupt register */
#define OTG_HCINT(usb, x)		MMIO32((usb) + (0x508 + 0x20 * (x)))

#define OTG_HCINT_DTERR			(1 << 10)	/* FS/HS */
#define OTG_HCINT_FRMOR			(1 << 9)	/* FS/HS */
#define OTG_HCINT_BBERR			(1 << 8)	/* FS/HS */
#define OTG_HCINT_TXERR			(1 << 7)	/* FS/HS */
#define OTG_HCINT_NYET			(1 << 6) 	/* HS */
#define OTG_HCINT_ACK			(1 << 5)	/* FS/HS */
#define OTG_HCINT_NAK			(1 << 4)	/* FS/HS */
#define OTG_HCINT_STALL			(1 << 3)	/* FS/HS */
#define OTG_HCINT_AHBERR		(1 << 2)	/* HS */
#define OTG_HCINT_CHH			(1 << 1)	/* FS/HS */
#define OTG_HCINT_XFRC			(1 << 0)	/* FS/HS */

/** OTG Host, Channel x Interrupt Mask register */
#define OTG_HCINTMSK(usb, x)		MMIO32((usb) + (0x50C + 0x20 * (x)))

#define OTG_HCINT_DTERRM		(1 << 10)	/* FS/HS */
#define OTG_HCINT_FRMORM		(1 << 9)	/* FS/HS */
#define OTG_HCINT_BBERRM		(1 << 8)	/* FS/HS */
#define OTG_HCINT_TXERRM		(1 << 7)	/* FS/HS */
#define OTG_HCINT_NYETM			(1 << 6) 	/* HS */
#define OTG_HCINT_ACKM			(1 << 5)	/* FS/HS */
#define OTG_HCINT_NAKM			(1 << 4)	/* FS/HS */
#define OTG_HCINT_STALLM		(1 << 3)	/* FS/HS */
#define OTG_HCINT_AHBERRM		(1 << 2)	/* HS */
#define OTG_HCINT_CHHM			(1 << 1)	/* FS/HS */
#define OTG_HCINT_XFRCM			(1 << 0)	/* FS/HS */

/** OTG Host, Channel x Transfer Size Register */
#define OTG_HCTSIZ(usb, x)		MMIO32((usb) + (0x510 + 0x20 * (x)))

/* Only in v 1.2 parts */
#define OTG_HCTSIZ_DOPING		(1 << 31)

#define OTG_HCTSIZ_DPID_SHIFT		29
#define OTG_HCTSIZ_DPID_MASK		3
#define OTG_HCTSIZ_DPID_DATA0		0		/* FS/HS */
#define OTG_HCTSIZ_DPID_DATA2		1		/* FS/HS */
#define OTG_HCTSIZ_DPID_DATA1		2		/* FS/HS */
#define OTG_HCTSIZ_DPID_SETUP		3		/* FS */
#define OTG_HCTSIZ_DPID_MDATA		3		/* HS */
#define OTG_HCTSIZ_PKTCNT_SHIFT		19
#define OTG_HCTSIZ_PKTCNT_MASK		0x3ff
#define OTG_HCTSIZE_XFRSIZ_SHIFT	0
#define OTG_HCTSIZE_XFRSIZ_MASK		0x7ffff

/** OTG Host, Channel x DMA Address Register */
#define OTG_HCDMA(usb, x)		MMIO32((usb) + (0x514 + 0x20 * (x)))
#define OTG_HCDMA_DMAADDR_SHIFT		0		/* HS */
#define OTG_HCDMA_DMAADDR_MASK		0xffffffff	/* HS */


/** @brief These registers must be programmed every time the core
 *	   changes to device mode.
 */

/** OTG Device configuration register */
#define OTG_DCFG(usb)			MMIO32((usb) + 0x800)

#define OTG_DCFG_PERSCHIVL_SHIFT	24		/* HS */
#define OTG_DCFG_PERSCHIVL_MASK		0x3		/* HS */
#define OTG_DCFG_PERSCHIVL_25PCT	0x0		/* HS */
#define OTG_DCFG_PERSCHIVL_50PCT	0x1		/* HS */
#define OTG_DCFG_PERSCHIVL_75PCT	0x2		/* HS */
#define OTG_DCFG_ERRATIM		(1 << 15)	/* FS/HS */
#define OTG_DCFG_PFIVL_SHIFT		11		/* FS/HS */
#define OTG_DCFG_PFIVL_MASK		0x3		/* FS/HS */
#define OTG_DCFG_DAD_SHIFT		4		/* FS/HS */
#define OTG_DCFG_DAD_MASK		0x7f		/* FS/HS */
#define OTH_DCFG_NZLSOHSK		(1 << 2)	/* FS/HS */
#define OTG_DCFG_DSPD_SHIFT		0		/* FS/HS */
#define OTG_DCFG_DSPD_MASK		0x3		/* FS/HS */

/** OTG Device control register */
#define OTG_DCTL(usb)			MMIO32((usb) + 0x804)

#define OTG_DCTL_DSBESLRJCT		(1 << 18)
#define OTG_DCTL_POPRGDNE		(1 << 11)
#define OTG_DCTL_CGONAK			(1 << 10)
#define OTG_DCTL_SGONAK			(1 << 9)
#define OTG_DCTL_CGINAK			(1 << 8)
#define OTG_DCTL_SGINAK			(1 << 7)
#define OTG_DCTL_TCTL_SHIFT		4
#define OTG_DCTL_TCTL_MASK		0x7
#define OTG_DCTL_TCTL_DISABLE		0
#define OTG_DCTL_TCTL_TEST_J		1
#define OTG_DCTL_TCTL_TEST_K		2
#define OTG_DCTL_TCTL_TEST_SE0_NAK	3
#define OTG_DCTL_TCTL_TEST_PACKET	4
#define OTG_DCTL_TCTL_TEST_FORCE_ENABLE	5
#define OTG_DCTL_GONSTS			(1 << 3)
#define OTG_DCTL_GINSTS			(1 << 2)
#define OTG_DCTL_SDIS			(1 << 1)
#define OTG_DCTL_RWUSIG			(1 << 0)

/** OTG Device Status Register */
#define OTG_DSTS(usb)			MMIO32((usb) + 0x808)

#define OTG_DSTS_DEVLNSTS_SHIFT		22
#define OTG_DSTS_DEVLNSTS_MASK		0x3
#define OTG_DSTS_FNSOF_SHIFT		8
#define OTG_DSTS_FNSOF_MASK		0x3fff
#define OTG_DSTS_EERR			(1 << 3)
#define OTG_DSTS_ENUMSPD_SHIFT		1
#define OTG_DSTS_ENUMSPD_MASK		0x3
#define OTG_DSTS_SUSPSTS		(1 << 0)

/** OTG Device IN endpoint, common interrupt mask register */
#define OTG_DIEPMSK(usb)		MMIO32((usb) + 0x810)

#define OTG_DIEPMSK_NAKM		(1 << 13)	/* FS/HS */
#define OTG_DIEPMSK_BMA			(1 << 9)	/* HS */
#define OTG_DIEPMSK_TXFURM		(1 << 8)	/* HS */
#define OTG_DIEPMSK_INEPNEM		(1 << 6)	/* FS/HS */
#define OTG_DIEPMSK_INEPNMM		(1 << 5)	/* FS/HS */
#define OTG_DIEPMSK_ITTXFEMSK		(1 << 4)	/* FS/HS */
#define OTG_DIEPMSK_TOM			(1 << 3)	/* FS/HS */
#define OTG_DIEPMSK_EPDM		(1 << 1)	/* FS/HS */
#define OTG_DIEPMSK_XFRCM		(1 << 0)	/* FS/HS */

/** OTG Device OUT endpoint, common interrupt mask register */
#define OTG_DOEPMSK(usb)		MMIO32((usb) + 0x814)

#define OTG_DOEPMSK_NYETMSK		(1 << 14)	/* HS */
#define OTG_DOEPMSK_BOIM		(1 << 9)	/* HS */
#define OTG_DOEPMSK_TXFURM		(1 << 8)	/* HS */
#define OTG_DOEPMSK_B2BSTUP		(1 << 6)	/* HS */
#define OTG_DOEPMSK_OTEPDM		(1 << 4)	/* FS/HS */
#define OTG_DOEPMSK_STUPM		(1 << 3)	/* FS/HS */
#define OTG_DOEPMSK_EPDM		(1 << 1)	/* FS/HS */
#define OTG_DOEPMSK_XFRCM		(1 << 0)	/* FS/HS */

/** OTG Device all endpoints interrupt register */
#define OTG_DAINT(usb)			MMIO32((usb) + 0x818)

#define OTG_DAINT_OEPINT_SHIFT		16
#define OTG_DAINT_OEPINT_MASK		0xffff
#define OTG_DAINT_IEPINT_SHIFT		0
#define OTG_DAINT_IEPINT_MASK		0xffff

/** OTG Device all endpoints interrupt mask register */
#define OTG_DAINTMSK(usb)		MMIO32((usb) + 0x81C)

#define OTG_DAINTMSK_OEPM_SHIFT		16
#define OTG_DAINTMSK_OEPM_MASK		0xffff
#define OTG_DAINTMSK_IEPM_SHIFT		0
#define OTG_DAINTMSK_IEPM_MASK		0xffff

/** OTG Device VBUS Discharge time register */
#define OTG_DVBUSDIS(usb)		MMIO32((usb) + 0x828)

#define OTG_DVBUSDIS_VBUSDT_SHIFT	0
#define OTG_DVBUSDIS_VBUSDT_MASK	0xffff

/** OTG Device VBUS Pulsing time register */
#define OTG_DVBUSPULSE(usb)		MMIO32((usb) + 0x82C)

#define OTG_DVBUSPULSE_DVBUSP_SHIFT	0
#define OTG_DVBUSPULSE_DVBUSP_MASK	0xffff

/** OTG Device threshold control register */
#define OTG_DTHRCTL(usb)		MMIO32((usb) + 0x830)

#define OTG_DTHRCTL_ARPEN		(1 << 27)
#define OTG_DTHRCTL_RXTHRLEN_SHIFT	17
#define OTG_DTHRCTL_RXTHRLEN_MASK	0x1ff
#define OTG_DTHRCTL_RXTHREN		(1 << 16)
#define OTG_DTHRCTL_TXTHRLEN_SHIFT	2
#define OTG_DTHRCTL_TXTHRLEN_MASK	0x1ff
#define OTG_DTHRCTL_ISOTHREN		(1 << 1)
#define OTG_DTHRCTL_NONISOTHREN		(1 << 0)

/** OTG Device IN endpoint FIFO empty interrupt mask register */
#define OTG_DIEPEMPMSK(usb)		MMIO32((usb) + 0x834)

#define OTG_DIEPEMPMSK_INEPTXFEM_SHIFT	0
#define OTG_DIEPEMPMSK_INEPTXFEM_MASK	0xffff

/** OTG Device each endpoint interrupt register */
#define OTG_DEACHINT(usb)		MMIO32((usb) + 0x838)

#define OTG_DEACHINT_OEP1INT		(1 << 17)	/* HS */
#define OTG_DEACHINT_IEP1INT		(1 << 1)	/* HS */

/** OTG Device each endpoint interrupt mask register */
#define OTG_DEACHINTMSK(usb)		MMIO32((usb) + 0x83c)

#define OTG_DEACHINTMSK_OEP1INTM	(1 << 17)	/* HS */
#define OTG_DEACHINTMSK_IEP1INTM	(1 << 1)	/* HS */


/** OTG Device IN Endpoint _x_ control register */
#define OTG_DIEPCTL(usb, x)		MMIO32((usb) + 0x900 + (x * 0x20))

/** OTG Device IN Endpoint 0 control register
 *
 * @brief Not all flags are present or as wide see data sheet
 */
#define OTG_DIEPCTL0(usb)		OTG_DIEPCLTL(usb, 0)

/** @brief IN Endpoint Control flags */
#define OTG_DIEPCTLx_EPENA		(1 << 31)
#define OTG_DIEPCTLx_EPDIS		(1 << 30)
#define OTG_DIEPCTLx_SD1PID		(1 << 29)	/* 1+ */
#define OTG_DIEPCTLx_SODDFRM		(1 << 29)	/* 1+ */
#define OTG_DIEPCTLx_SD0PID		(1 << 28)	/* 1+ */
#define OTG_DIEPCTLx_SEVNFRM		(1 << 28)	/* 1+ (ISOC) */
#define OTG_DIEPCTLx_SNAK		(1 << 27)
#define OTG_DIEPCTLx_CNAK		(1 << 26)
#define OTG_DIEPCTLx_TXFNUM_SHIFT	22
#define OTG_DIEPCTLx_TXFNUM_MASK	0xf
#define OTG_DIEPCTLx_STALL		(1 << 21)
#define OTG_DIEPCTLx_EPTYP_SHIFT	18
#define OTG_DIEPCTLx_EPTYP_MASK		0x3
#define OTG_DIEPCTLx_EPTYP_CTRL		0
#define OTG_DIEPCTLx_EPTYP_ISOC		1
#define OTG_DIEPCTLx_EPTYP_BULK		2
#define OTG_DIEPCTLx_EPTYP_INTR		3
#define OTG_DIEPCTLx_NAKSTS		(1 << 17)
#define OTG_DIEPCTLx_EONUM		(1 << 16)	/* 1+ (ISOC) */
#define OTG_DIEPCTLx_DPID		(1 << 16)	/* 1+ */
#define OTG_DIEPCTLx_USBAEP		(1 << 15)
#define OTG_DIEPCTLx_MPSIZ_SHIFT	0
#define OTG_DIEPCTLx_MPSIZ_MASK		0x3ff


/** OTG Device IN Endpoint _x_ Interrupt Register */
#define OTG_DIEPINT(usb, x)		MMIO32((usb) + 0x908 + (x * 0x20))
/** OTG Device IN Endpoint 0 Interrupt register
 *
 * @brief Not all flags are present or as wide see data sheet
 */
#define OTG_DIEPINT0(usb)		OTG_DIEPINT(usb, 0)

#define OTG_DIEPINTx_NAX		(1 << 13)	/* HS */
#define OTG_DIEPINTx_BERR		(1 << 12)	/* HS */
#define OTG_DIEPINTx_PKTDRPSTS		(1 << 11)	/* HS */
#define OTG_DIEPINTx_BNA		(1 << 9)	/* HS */
#define OTG_DIEPINTx_TXFIFOUDRN		(1 << 8)	/* HS */
#define OTG_DIEPINTx_TXFE		(1 << 7)	/* FS/HS */
#define OTG_DIEPINTx_INEPNE		(1 << 6)	/* FS/HS */
#define OTG_DIEPINTx_ITTXFE		(1 << 4)	/* FS/HS */
#define OTG_DIEPINTx_TOC		(1 << 3)	/* FS/HS */
#define OTG_DIEPINTx_EPDISD		(1 << 1)	/* FS/HS */
#define OTG_DIEPINTx_XFRC		(1 << 0)	/* FS/HS */

/** OTG Device IN Endpoint _x_ transfer size register */
#define OTG_DIEPTSIZ(usb, x)		MMIO32((usb) + 0x910 + (x * 0x20))
/** OTG Device IN Endpoint 0 Transfer Size register
 *
 * @brief Not all flags are present or as wide see data sheet
 */
#define OTG_DIEPTSIZ0(usb)		MMIO32((usb) + 0x910)

#define OTG_DIEPTSIZx_MCNT_SHIFT	29
#define OTG_DIEPTSIZx_MCNT_MASK		0x3
#define OTG_DIEPTSIZx_PKTCNT_SHIFT	19
#define OTG_DIEPTSIZx_PKTCNT_MASK	0x3ff
#define OTG_DIEPTSIZx_XFRSIZ_SHIFT	0
#define OTG_DIEPTSIZx_XFRSIZ_MASK	0x7ffff

/** OTG Device IN Endpoint _x_ Transmit FIFO Status Register */
#define OTG_DTXFSTS(usb, x)		MMIO32((usb) + (0x918 + 0x20 * (x)))
/** OTG Device IN Endpoint 0 Transfer FIFO Status register */
#define OTG_DTXFSTS0(usb)		OTG_DTXFSTS(usb, 0)

#define OTG_DTXFSTSx_INEPTFSAV_SHIFT	0
#define OTG_DTXFSTSx_INEPTFSAV_MASK	0xffff

/** OTG Device OUT Endpoint _x_ control register */
#define OTG_DOEPCTL(usb, x)		MMIO32((usb) + 0xb00 + (x * 0x20))
/** OTG Device OUT Endpoint 0 control register
 *
 * @brief Not all flags are present or as wide see data sheet
 */
#define OTG_DOEPCTL0(usb)		OTF_DOEPCTL(usb, 0)

#define OTG_DOEPCTLx_EPENA		(1 << 31)
#define OTG_DOEPCTLx_EPDIS		(1 << 30)
#define OTG_DOEPCTLx_SD1PID		(1 << 29)	/* 1+ */
#define OTG_DOEPCTLx_SODDFRM		(1 << 29)	/* 1+ */
#define OTG_DOEPCTLx_SD0PID		(1 << 28)	/* 1+ */
#define OTG_DOEPCTLx_SEVNFRM		(1 << 28)	/* 1+ (ISOC) */
#define OTG_DOEPCTLx_SNAK		(1 << 27)
#define OTG_DOEPCTLx_CNAK		(1 << 26)
#define OTG_DOEPCTLx_STALL		(1 << 21)
#define OTG_DOEPCTLx_SNPM		(1 << 20)
#define OTG_DOEPCTLx_EPTYP_SHIFT	18
#define OTG_DOEPCTLx_EPTYP_MASK		0x3
#define OTG_DOEPCTLx_EPTYP_CTRL		0
#define OTG_DOEPCTLx_EPTYP_ISOC		1
#define OTG_DOEPCTLx_EPTYP_BULK		2
#define OTG_DOEPCTLx_EPTYP_INTR		3
#define OTG_DOEPCTLx_NAKSTS		(1 << 17)
#define OTG_DOEPCTLx_EONUM		(1 << 16)	/* 1+ (ISOC) */
#define OTG_DOEPCTLx_DPID		(1 << 16)	/* 1+ */
#define OTG_DOEPCTLx_USBAEP		(1 << 15)
#define OTG_DOEPCTLx_MPSIZ_SHIFT	0
#define OTG_DOEPCTLx_MPSIZ_MASK		0x3ff

/** OTG Device OUT Endpoint _x_ Interrupt Register */
#define OTG_DOEPINT(usb, x)		MMIO32((usb) + 0xB08 + (x * 0x20))
/** OTG Device OUT Endpoint 0 Interrupt Register */
#define OTG_DOEPINT0(usb)		OTG_DOEPINT(usb, 0)

#define OTG_DOEPINTx_B2BSTUP		(1 << 6)
#define OTG_DOEPINTx_OTEPDIS		(1 << 4)
#define OTG_DOEPINTx_STUP		(1 << 3)
#define OTG_DOEPINTx_EPDISD		(1 << 1)
#define OTG_DOEPINTx_XFRC		(1 << 0)

/** OTG Device OUT Endpoint _x_ transfer size  register */
#define OTG_DOEPTSIZ(usb, x)		MMIO32((usb) + 0xB10 + (x * 0x20))
/** OTG Device OUT Endpoint 0 control register
 *
 * @brief Not all flags are present or as wide see data sheet on EP 0
 */
#define OTG_DOEPTSIZ0(usb)		OTG_DOEPTSIZ(usb, 0)

#define OTG_DOEPTSIZx_STUPCNT_SHIFT	29
#define OTG_DOEPTSIZx_STUPCNT_MASK	0x3
#define OTG_DOEPTSIZx_RXDPID_SHIFT	29	/* 1+ */
#define OTG_DOEPTSIZx_RXDPID_MASK	0x3	/* 1+ */
#define OTG_DOEPTSIZx_PKTCNT_SHIFT	19
#define OTG_DOEPTSIZx_PKTCNT_MASK	0x3ff
#define OTG_DOEPTSIZx_XFRSIZ_SHIFT	0
#define OTG_DOEPTSIZx_XFRSIZ_MASK	0x7ffff

/** OTG Power and clock gating control and status register */
#define OTG_PCGCCTL(usb)		MMIO32((usb) + 0xE00)

#define OTG_PCGCCTL_SUSP		(1 << 7)
#define OTG_PCGCCTL_PHYSLEEP		(1 << 6)
#define OTG_PCGCCTL_ENL1GTG		(1 << 5)
#define OTG_PCGCCTL_PHYSUSP		(1 << 4)
#define OTG_PCGCCTL_GATEHCLK		(1 << 1)
#define OTG_PCGCCTL_STPPCLK		(1 << 0)

/**@}*/
#endif
