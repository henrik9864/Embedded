MEMORY
{
  boot  (rx) : ORIGIN = 0x10000000, LENGTH = 256
  flash (rx) : ORIGIN = 0x10000100, LENGTH = 2048K - 256
  ram  (rwx) : ORIGIN = 0x20000000, LENGTH = 264K
}

/*ENTRY(ResetHandler)*/

/* Highest address of the user mode stack */
_estack = 0x20000000 + LENGTH(ram);    /* end of RAM */
/* Generate a link error if heap and stack don't fit into RAM */

SECTIONS
{
  .boot2 : ALIGN(4)
  {
    _boot2 = .;
    KEEP(*(.boot2))
    *(.boot2*)
    . = 256 - 4; /* Ensure bootloader is 256 bytes and make space for CRC checksum */
    LONG(0x7A4EB274) /* CRC */
    _eboot2 = .;
  } > boot

  .text :
	{
		KEEP(*(.isr_vector))
		. = ALIGN(4);
		*(.text)
		*(.text*)
		*(.glue_7)         /* glue arm to thumb code */
		*(.glue_7t)        /* glue thumb to arm code */

		*(.init)
		*(.fini)

		. = ALIGN(4);
		/* .ctors */
		__ctors_begin = .;
		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
		*(SORT(.ctors.*))
		*(.ctors)
		__ctors_end = .;

		/* .dtors */
		*crtbegin.o(.dtors)
		*crtbegin?.o(.dtors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
		*(SORT(.dtors.*))
		*(.dtors)

		. = ALIGN(4);
		/* preinit data */
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);

		. = ALIGN(4);
		/* init data */
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);


		. = ALIGN(4);
		/* finit data */
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);

		*(.rodata*)
		*(.eh_frame*)
		etext = .; /* define a global symbols at end of code */
	} > flash

	.ARM.extab : 
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > flash

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > flash
	__exidx_end = .;

	/* To copy multiple ROM to RAM sections,
	 * uncomment .copy.table section and,
	 * define __STARTUP_COPY_MULTIPLE in startup_ARMCMx.S */
	/*
	.copy.table :
	{
		. = ALIGN(4);
		__copy_table_start__ = .;
		LONG (__etext)
		LONG (__data_start__)
		LONG (__data_end__ - __data_start__)
		LONG (__etext2)
		LONG (__data2_start__)
		LONG (__data2_end__ - __data2_start__)
		__copy_table_end__ = .;
	} > flash
	*/

	/* To clear multiple BSS sections,
	 * uncomment .zero.table section and,
	 * define __STARTUP_CLEAR_BSS_MULTIPLE in startup_ARMCMx.S */
	/*
	.zero.table :
	{
		. = ALIGN(4);
		__zero_table_start__ = .;
		LONG (__bss_start__)
		LONG (__bss_end__ - __bss_start__)
		LONG (__bss2_start__)
		LONG (__bss2_end__ - __bss2_start__)
		__zero_table_end__ = .;
	} > flash
	*/

	/* Location counter can end up 2byte aligned with narrow Thumb code but
	   __etext is assumed by startup code to be the LMA of a section in RAM
	   which must be 4byte aligned */
	__etext = ALIGN (4);

	/* used by the startup to initialize data */
	_sidata = LOADADDR(.data);

	.data :
	{
		__data_start__ = .;
		_sdata = .;        /* create a global symbol at data start */
		*(vtable)
		*(.data*)

		KEEP(*(.jcr*))
		. = ALIGN(4);
		/* All data end */
		__data_end__ = .;
		_edata = .;        /* define a global symbol at data end */

	} > ram AT> flash

	.bss :
	{
		. = ALIGN(4);
		_sbss = .;         /* define a global symbol at bss start */
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;         /* define a global symbol at bss end */
		__bss_end__ = .;
	} > ram
	
	.heap (COPY):
	{
                __end__ = .;
		PROVIDE(end = .);
		*(.heap*)
		__HeapLimit = .;
	} > ram

	/* .stack_dummy section doesn't contains any symbols. It is only
	 * used for linker to calculate size of stack sections, and assign
	 * values to stack symbols later */
	.stack_dummy (COPY):
	{
		*(.stack*)
	} > ram

	/* Set stack top to end of RAM, and stack limit move down by
	 * size of stack_dummy section */
	__StackTop = ORIGIN(ram) + LENGTH(ram);
	__StackLimit = __StackTop - SIZEOF(.stack_dummy);
	PROVIDE(__stack = __StackTop);
	
	/* Check if data + heap + stack exceeds RAM limit */
	ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}