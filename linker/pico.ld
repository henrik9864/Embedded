OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")

MEMORY
{
  /* Pico memory layout */
  boot   (rx) : ORIGIN = 0x10000000, LENGTH = 256
  flash  (rx) : ORIGIN = 0x10000100, LENGTH = 2048K - 256
  ram   (rwx) : ORIGIN = 0x20000000, LENGTH = 264K

  /* RP2040 pheripheral registers */
  sio        (r) : ORIGIN = 0xD0000000, LENGTH = 1K
  iobank0    (r) : ORIGIN = 0x40014000, LENGTH = 1K
  padsbank0  (r) : ORIGIN = 0x4001c000, LENGTH = 1K
  resets     (r) : ORIGIN = 0x4000C000, LENGTH = 1K
  clocks     (r) : ORIGIN = 0x40008000, LENGTH = 1K
  rsoc       (r) : ORIGIN = 0x40060000, LENGTH = 1K
  xsoc       (r) : ORIGIN = 0x40024000, LENGTH = 1K
  pll_sys    (r) : ORIGIN = 0x40028000, LENGTH = 1K
  pll_usb    (r) : ORIGIN = 0x4002c000, LENGTH = 1K
  pio_0      (r) : ORIGIN = 0x50200000, LENGTH = 1K
  pio_1      (r) : ORIGIN = 0x50300000, LENGTH = 1K
  pwm        (r) : ORIGIN = 0x40050000, LENGTH = 1K
  i2c_0      (r) : ORIGIN = 0x40044000, LENGTH = 1K
  i2c_1      (r) : ORIGIN = 0x40048000, LENGTH = 1K
  uart_0     (r) : ORIGIN = 0x40034000, LENGTH = 1K
  uart_1     (r) : ORIGIN = 0x40038000, LENGTH = 1K

  /* PIO memory registers */
  pio_0_mem (rw) : ORIGIN = 0x50200000 + 0x048, LENGTH = 1K
  pio_1_mem (rw) : ORIGIN = 0x50300000 + 0x048, LENGTH = 1K
}

SECTIONS
{
  /* RP2040 second stage bootloader is inserted at the start of the program before the vector table */
  .boot2 : ALIGN(4)
  {
    KEEP(*(.boot2))
    *(.boot2*)
    . = 256 - 4; /* Ensure bootloader is 256 bytes and make space for CRC checksum */
    LONG(0x7A4EB274) /* CRC w25q080 */
  } > boot

  /* Vector Table */
	.vtable : ALIGN(4)
	{
		KEEP(*(.isr_vector))
	} > flash

  /* C/C++ Code */
  .text : ALIGN(4)
  {
    *(.text .text.* .gnu.linkonce.t.*)
    *(.rodata .rodata* .gnu.linkonce.r.*)

    *(.init)
    *(.fini)

    /* Pre Initializers */
    . = ALIGN(4);
    _preinit_array_start = .;
    KEEP (*(.preinit_array))
    _preinit_array_end = .;

    /* Initializer Array */
    . = ALIGN(4);
    _init_array_start = .;
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    _init_array_end = .;

    /* Finalizers */
    . = ALIGN(4);
    _fini_array_start = .;
    KEEP (*(.fini_array))
    KEEP (*(SORT(.fini_array.*)))
    _fini_array_end = .;

    /* Static Constructors */
    . = ALIGN(4);
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend.o(.ctors))

    /* Static Destructors */
    . = ALIGN(4);
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*crtend.o(.dtors))
  } > flash

    /* PIO memory setup */
  .pio_0_mem :
	{
    _spio0 = .;
		KEEP(*(.pio_0_mem))
    _epio0 = .;
	} > pio_0_mem AT> flash

  _sipio0 = LOADADDR(.pio_0_mem);

  .pio_1_mem :
	{
    _epio1 = .;
		KEEP(*(.pio_1_mem))
    _spio1 = .;
	} > pio_1_mem AT> flash

  _sipio1 = LOADADDR(.pio_1_mem);

  /* Runtime Variables */
  .data :
	{
		_sdata = .;
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	} > ram AT> flash

  /* used by the startup to initialize data */
	_sidata = LOADADDR(.data);

  /* Uninitialized Variables */
  .bss (NOLOAD) : ALIGN(4)
  {
    _sbss = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  }

  /* RP2040 Registers */
  .sio_regs (NOLOAD) : {
    *(.sio_regs)
  } > sio

  .io_bank_0_regs (NOLOAD) : {
    *(.io_bank_0_regs)
  } > iobank0

  .pads_bank_0_regs (NOLOAD) : {
    *(.pads_bank_0_regs)
  } > padsbank0

  .reset_regs (NOLOAD) : {
    *(.reset_regs)
  } > resets

  .clock_regs (NOLOAD) : {
    *(.clock_regs)
  } > clocks

  .rsoc_regs (NOLOAD) : {
    *(.rsoc_regs)
  } > rsoc

  .xsoc_regs (NOLOAD) : {
    *(.xsoc_regs)
  } > xsoc

  .pll_sys_regs (NOLOAD) : {
    *(.pll_sys_regs)
  } > pll_sys

  .pll_usb_regs (NOLOAD) : {
    *(.pll_usb_regs)
  } > pll_usb

  .pio_0_regs (NOLOAD) : {
    *(.pio_0_regs)
  } > pio_0

  .pio_1_regs (NOLOAD) : {
    *(.pio_1_regs)
  } > pio_1

  .pwm_regs (NOLOAD) : {
    *(.pwm_regs)
  } > pwm

  .i2c_0_regs (NOLOAD) : {
    *(.i2c_0_regs)
  } > i2c_0

  .i2c_1_regs (NOLOAD) : {
    *(.i2c_1_regs)
  } > i2c_1

  .uart_0_regs (NOLOAD) : {
    *(.uart_0_regs)
  } > uart_0

  .uart_1_regs (NOLOAD) : {
    *(.uart_1_regs)
  } > uart_1
};

_estack = ORIGIN(ram) + LENGTH(ram); /* stack starts at end of ram */