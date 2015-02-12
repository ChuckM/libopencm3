/** @defgroup usart_file USART
 *
 * @ingroup STM32L0xx
 * @ingroup STM32F0xx
 *
 * @brief <b>libopencm3 STM32L0xx USART</b>
 *
 * @version 1.1.0
 *
 * @date 1 Jan 2015
 *
 * LGPL License Terms @ref lgpl_license
 */

/*
 * This file is part of the libopencm3 project.
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

#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/rcc.h>

/*---------------------------------------------------------------------------*/
/** @brief USART Set Baudrate.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @param[in] baud unsigned 32 bit. Baud rate specified in Hz.
 */

void usart_set_baudrate(uint32_t usart, uint32_t baud)
{
	/* note usart_get_clock is in device specific usart.c */
	uint32_t clock = usart_get_clock(usart);
	uint32_t div;

	/*
	 * in both cases we used (V + (B>>1))/B to round up
     * when the floating point value would have had a
	 * fractional component greater than .50. In the 
	 * data sheet example of a divisor for a 9600 baud
	 * with /8 the error goes down from .004% to .002%
	 * and with /16 the error is unchanged.
	 */
	if (USART_CR1(usart) & USART_CR1_OVER8) {
		div = (2 * clock + (baud >> 1)) / baud;
		/* from ref manual when /8 */
		div = (div & 0xfff0) | ((div & 0xf) >> 1);
	} else {
		div = (clock+(baud >> 1)) / baud;
	}
	USART_BRR(usart) = div;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Automatically determine Baudrate
 *
 * @param[in] usart unsigned 32 bit, USART block register address base @ref
 * @param[in] mode int, baudrate detection mode
 *      00 - measure the start bit
 *      01 - falling edge to falling edge measurement
 *      10 - look for 0x7f frame
 *      11 - look for 0x55 frame (ascii 'U')
 */
void usart_set_autobaudrate(uint32_t usart, int mode) {
	USART_CR2(usart) = (USART_CR2(usart) & ~(USART_CR2_ABRMOD_MASK << USART_CR2_ABRMOD_SHIFT)) |
			   ((mode & USART_CR2_ABRMOD_MASK) << USART_CR2_ABRMOD_SHIFT);
}

/*---------------------------------------------------------------------------*/
/** @brief USART Set Word Length.
 *
 * The word length is set to 7, 8, or 9 bits. If you add parity it will have
 * an additional bit appended (so 8, 9, or 10 bits).
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @param[in] bits unsigned 32 bit. Word length in bits 7, 8, or 9.
 */

void usart_set_databits(uint32_t usart, uint32_t bits)
{
	switch (bits) {
		case 7:
			USART_CR1(usart) |= USART_CR1_M1;
			USART_CR1(usart) &= ~USART_CR1_M0;
			break;
		case 9:
			USART_CR1(usart) &= ~USART_CR1_M1;
			USART_CR1(usart) |= USART_CR1_M0;
		default:
		case 8:
			USART_CR1(usart) &= ~USART_CR1_M1;
			USART_CR1(usart) &= ~USART_CR1_M0;
	}
}

/*---------------------------------------------------------------------------*/
/** @brief USART Set Stop Bit(s).
 *
 * The stop bits are specified as 0.5, 1, 1.5 or 2.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @param[in] stopbits unsigned 32 bit. Stop bits @ref usart_cr2_stopbits.
 */

void usart_set_stopbits(uint32_t usart, uint32_t stopbits)
{
	USART_CR2(usart) = (USART_CR2(usart) & ~USART_CR2_STOP) | stopbits;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Set Parity.
 *
 * The parity bit can be selected as none, even or odd.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @param[in] parity unsigned 32 bit. Parity @ref usart_cr1_parity.
 */

void usart_set_parity(uint32_t usart, uint32_t parity)
{
	USART_CR1(usart) = (USART_CR1(usart) & ~USART_PARITY) | parity;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Set Rx/Tx Mode.
 *
 * The mode can be selected as Rx only, Tx only or Rx+Tx.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @param[in] mode unsigned 32 bit. Mode @ref usart_cr1_mode.
 */

void usart_set_mode(uint32_t usart, uint32_t mode)
{
	USART_CR1(usart) = (USART_CR1(usart) & ~USART_MODE) | mode;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Set Hardware Flow Control.
 *
 * The flow control bit can be selected as none, RTS, CTS or RTS+CTS.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @param[in] flowcontrol unsigned 32 bit. Flowcontrol @ref
 * usart_cr3_flowcontrol.
 */

void usart_set_flow_control(uint32_t usart, uint32_t flowctrl)
{
	USART_CR3(usart) = (USART_CR3(usart) & ~USART_FLOWCONTROL) | flowctrl;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Enable.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_enable(uint32_t usart)
{
	USART_CR1(usart) |= USART_CR1_UE;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Disable.
 *
 * At the end of the current frame, the USART is disabled to reduce power.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_disable(uint32_t usart)
{
	USART_CR1(usart) &= ~USART_CR1_UE;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Send a Data Word.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @param[in] data unsigned 16 bit.
 */

void usart_send(uint32_t usart, uint16_t data)
{
	USART_TDR(usart) = data;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Read a Received Data Word.
 *
 * If parity is enabled the MSB (bit 7 or 8 depending on the word length) is
 * the parity bit.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @returns unsigned 16 bit data word.
 */

uint16_t usart_recv(uint32_t usart)
{
	/* Receive data. */
	return USART_RDR(usart);
}

/*---------------------------------------------------------------------------*/
/** @brief USART Wait for Transmit Data Buffer Empty
 *
 * Blocks until the transmit data buffer becomes empty and is ready to accept
 * the next data word.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_wait_send_ready(uint32_t usart)
{
	/* Wait until the data has been transferred into the shift register. */
	while ((USART_ISR(usart) & USART_ISR_TXE) == 0);
}

/*---------------------------------------------------------------------------*/
/** @brief USART Wait for Received Data Available
 *
 * Blocks until the receive data buffer holds a valid received data word.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_wait_recv_ready(uint32_t usart)
{
	/* Wait until the data is ready to be received. */
	while ((USART_ISR(usart) & USART_ISR_RXNE) == 0);
}

/*---------------------------------------------------------------------------*/
/** @brief USART Send Data Word with Blocking
 *
 * Blocks until the transmit data buffer becomes empty then writes the next
 * data word for transmission.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @param[in] data unsigned 16 bit.
 */

void usart_send_blocking(uint32_t usart, uint16_t data)
{
	usart_wait_send_ready(usart);
	usart_send(usart, data);
}

/*---------------------------------------------------------------------------*/
/** @brief USART Read a Received Data Word with Blocking.
 *
 * Wait until a data word has been received then return the word.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @returns unsigned 16 bit data word.
 */

uint16_t usart_recv_blocking(uint32_t usart)
{
	usart_wait_recv_ready(usart);

	return usart_recv(usart);
}

/*---------------------------------------------------------------------------*/
/** @brief USART Receiver DMA Enable.
 *
 * DMA is available on:
 * @li USART1 Rx DMA1 channel 3 or 5.
 * @li USART2 Rx DMA1 channel 5.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_enable_rx_dma(uint32_t usart)
{
	USART_CR3(usart) |= USART_CR3_DMAR;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Receiver DMA Disable.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_disable_rx_dma(uint32_t usart)
{
	USART_CR3(usart) &= ~USART_CR3_DMAR;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Transmitter DMA Enable.
 *
 * DMA is available on:
 * @li USART1 Tx DMA1 channel 2 or 4.
 * @li USART2 Tx DMA1 channel 4.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_enable_tx_dma(uint32_t usart)
{
	USART_CR3(usart) |= USART_CR3_DMAT;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Transmitter DMA Disable.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_disable_tx_dma(uint32_t usart)
{
	USART_CR3(usart) &= ~USART_CR3_DMAT;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Receiver Interrupt Enable.

@param[in] usart unsigned 32 bit. USART block register address base @ref
usart_reg_base
*/

void usart_enable_rx_interrupt(uint32_t usart)
{
	USART_CR1(usart) |= USART_CR1_RXNEIE;
}


/*---------------------------------------------------------------------------*/
/** @brief USART Receiver Interrupt Disable.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_disable_rx_interrupt(uint32_t usart)
{
	USART_CR1(usart) &= ~USART_CR1_RXNEIE;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Transmitter Interrupt Enable.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_enable_tx_interrupt(uint32_t usart)
{
	USART_CR1(usart) |= USART_CR1_TXEIE;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Transmitter Interrupt Disable.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_disable_tx_interrupt(uint32_t usart)
{
	USART_CR1(usart) &= ~USART_CR1_TXEIE;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Error Interrupt Enable.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_enable_error_interrupt(uint32_t usart)
{
	USART_CR3(usart) |= USART_CR3_EIE;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Error Interrupt Disable.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 */

void usart_disable_error_interrupt(uint32_t usart)
{
	USART_CR3(usart) &= ~USART_CR3_EIE;
}

/*---------------------------------------------------------------------------*/
/** @brief USART Read a Status Flag.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @param[in] flag Unsigned int32. Status register flag  @ref usart_sr_flags.
 * @returns boolean: flag set.
 */

bool usart_get_flag(uint32_t usart, uint32_t flag)
{
	return ((USART_ISR(usart) & flag) != 0);
}

/*---------------------------------------------------------------------------*/
/** @brief USART Return Interrupt Source.
 *
 * Returns true if the specified interrupt flag (IDLE, RXNE, TC, TXE or OE) was
 * set and the interrupt was enabled. If the specified flag is not an interrupt
 * flag, the function returns false.
 *
 * @param[in] usart unsigned 32 bit. USART block register address base @ref
 * usart_reg_base
 * @param[in] flag Unsigned int32. Status register flag  @ref usart_sr_flags.
 * @returns boolean: flag and interrupt enable both set.
 */

bool usart_get_interrupt_source(uint32_t usart, uint32_t flag)
{
	uint32_t flag_set = (USART_ISR(usart) & flag);
	/* IDLE, RXNE, TC, TXE interrupts */
	if ((flag >= USART_ISR_IDLE) && (flag <= USART_ISR_TXE)) {
		return ((flag_set & USART_CR1(usart)) != 0);
	/* Overrun error */
	} else if (flag == USART_ISR_ORE) {
		return flag_set && (USART_CR3(usart) & USART_CR3_CTSIE);
	}

	return false;
}

/**@}*/
