OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")

MEMORY
{
  /* Pico memory layout */
  boot   (rx) : ORIGIN = 0x10000000, LENGTH = 256
  flash  (rx) : ORIGIN = 0x10000100, LENGTH = 2048K - 256
  ram   (rwx) : ORIGIN = 0x20000000, LENGTH = 264K

  /* RP2040 pheripheral registers */
  sio     (r) : ORIGIN = 0xD0000000, LENGTH = 1K
  iobank0 (r) : ORIGIN = 0x40014000, LENGTH = 1K
  resets  (r) : ORIGIN = 0x4000C000, LENGTH = 1K
  clocks  (r) : ORIGIN = 0x40008000, LENGTH = 1K
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
    /*LONG(0x5D4C22EA)*/ /* CRC Generic */
    /*LONG(0xD965BC28)*/ /* CRC Custom*/
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

  .sio_regs (NOLOAD) : {
    *(.sio_regs)
  } > sio

  .io_bank_0_regs (NOLOAD) : {
    *(.io_bank_0_regs)
  } > iobank0

  .reset_regs (NOLOAD) : {
    *(.reset_regs)
  } > resets

  .clock_regs (NOLOAD) : {
    *(.clock_regs)
  } > clocks
};

_estack = ORIGIN(ram) + LENGTH(ram); /* stack starts at end of ram */