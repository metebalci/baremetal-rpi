
#define IOBASE 0x3F000000

#define AUXENB			((volatile unsigned int*)(IOBASE + 0x00215004))
#define AUX_MU_IO_REG	((volatile unsigned int*)(IOBASE + 0x00215040))
#define AUX_MU_IER_REG	((volatile unsigned int*)(IOBASE + 0x00215044))
#define AUX_MU_IIR_REG	((volatile unsigned int*)(IOBASE + 0x00215048))
#define AUX_MU_LCR_REG	((volatile unsigned int*)(IOBASE + 0x0021504C))
#define AUX_MU_MCR_REG	((volatile unsigned int*)(IOBASE + 0x00215050))
#define AUX_MU_LSR_REG	((volatile unsigned int*)(IOBASE + 0x00215054))
#define AUX_MU_MSR_REG	((volatile unsigned int*)(IOBASE + 0x00215058))
#define AUX_MU_CNTL_REG ((volatile unsigned int*)(IOBASE + 0x00215060))
#define AUX_MU_STAT_REG ((volatile unsigned int*)(IOBASE + 0x00215064))
#define AUX_MU_BAUD		((volatile unsigned int*)(IOBASE + 0x00215068))
#define GPFSEL1			((volatile unsigned int*)(IOBASE + 0x00200004))

inline void configure_pins_as_uart() {
	register unsigned int r;
	r = *GPFSEL1;
	// reset the gpio14 and gpio15 3-bits fields
	r &= !((7<<12)|(7<<15));
	// set them to alt5
	r |= (2 <<12)|(2<<15);
	*GPFSEL1 = r;
}

inline void enable_uart() {
	*AUXENB |= 1;
}

inline void disable_uart() {
	*AUXENB &= 0xFFFFFFFE;
}

inline void disable_interrupts() {
	*AUX_MU_IER_REG = 0;
}

inline void set_baud_115200() {
	*AUX_MU_BAUD = 270;
}

inline void clear_rxtx() {
	*AUX_MU_IIR_REG = 0x6;
}

inline int is_data_ready() {
	return (*AUX_MU_LSR_REG & 0x1) == 0 ? 0 : 1;
}

inline int is_tx_empty() {
	return (*AUX_MU_LSR_REG & 0x40) == 0 ? 0 : 1;
}

inline int is_tx_ready() {
	return (*AUX_MU_LSR_REG & 0x20) == 0 ? 0 : 1;
}

inline int is_tx_done() {
	return (*AUX_MU_STAT_REG & (1 << 9)) == 0 ? 0 : 1;
}

inline void disable_rxtx() {
}

inline void enable_rxtx() {
	*AUX_MU_CNTL_REG |= 0x3;
}

inline void set_data_8bits() {
	*AUX_MU_LCR_REG = 3;
}

void set(unsigned int b) {

	while (is_tx_ready() == 0);
	*AUX_MU_IO_REG = b;

}

char get() {

	char r;

	while (is_data_ready() == 0);

	r = (char) *AUX_MU_IO_REG;

	return r;

}

void main(void) {

	enable_uart();
	disable_rxtx();
	set_data_8bits();
	disable_interrupts();
	clear_rxtx();
	set_baud_115200();
	configure_pins_as_uart();
	enable_rxtx();

	set('H');
	set('e');
	set('l');
	set('l');
	set('o');
	set(' ');
	set('W');
	set('o');
	set('r');
	set('l');
	set('d');
	set('!');

	while (1);

}
