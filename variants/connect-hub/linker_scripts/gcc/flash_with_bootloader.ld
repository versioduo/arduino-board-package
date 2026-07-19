MEMORY {
  /*
   * The first 16k are reserved for the bootloader. The last 16k
   * are reserved for the EEPROM emulation, configured in fuses.
   */
  FLASH (rx): ORIGIN =  16k, LENGTH = 512k - 16k - 16k
  RAM  (rwx): ORIGIN = 512m, LENGTH = 192k
}

ENTRY(Reset_Handler)

SECTIONS {
  .text : {
    __text_start__ = .;

    KEEP(*(.sketch_boot))

    . = ALIGN(0x4000);
    KEEP(*(.isr_vector))
    *(.text*)

    KEEP(*(.init))
    KEEP(*(.fini))

    /* .ctors */
    *crtbegin.o(.ctors)
    *crtbegin?.o(.ctors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
    *(SORT(.ctors.*))
    *(.ctors)

    /* .dtors */
    *crtbegin.o(.dtors)
    *crtbegin?.o(.dtors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
    *(SORT(.dtors.*))
    *(.dtors)

    *(.rodata*)

    KEEP(*(.eh_frame*))
  } > FLASH

  .ARM.extab : {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > FLASH

  .ARM.exidx : {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } > FLASH


  __etext = .;

  .data : AT (__etext) {
    __data_start__ = .;
    *(vtable)
    *(.data*)

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

    KEEP(*(.jcr*))

    /*
     * DMAC defines this section. Add it here to account for its size when
     * calculating the binary sketch size.
     */
    . = ALIGN(16);
    KEEP(*(.hsram))

    . = ALIGN(16);
    /* All data end */
    __data_end__ = .;
  } > RAM

  /* Offset value at the very end of the image, pointing to the metadata record */
  .metadata  __etext + (__data_end__ - __data_start__) : {
    . = ALIGN(4);
    __metadata_start = .;
    KEEP(*(.metadata))
    __metadata_end = .;
  } > FLASH


  .bss : {
    __bss_start__ = .;
    . = ALIGN(4);
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > RAM

  /*
   * Preserve section content across reboots
   */
  .noinit (NOLOAD) : {
    . = ALIGN(4);
    *(.noinit*)
    . = ALIGN(4);
  } > RAM

  .heap (COPY): {
    __end__ = .;
    PROVIDE(end = .);
    *(.heap*)
    __HeapLimit = .;
  } > RAM

  /* .stack_dummy section doesn't contains any symbols. It is only
   * used for linker to calculate size of stack sections, and assign
   * values to stack symbols later */
  .stack_dummy (COPY): {
    *(.stack*)
  } > RAM

  /* Set stack top to end of RAM, and stack limit move down by
   * size of stack_dummy section */
  __StackTop = ORIGIN(RAM) + LENGTH(RAM);
  __StackLimit = __StackTop - SIZEOF(.stack_dummy);
  PROVIDE(__stack = __StackTop);

  __ram_end__ = ORIGIN(RAM) + LENGTH(RAM) -1 ;

  /* Check if data + heap + stack exceeds RAM limit */
  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")

  PROVIDE(__sketch_size = (__etext - __text_start__) + (__data_end__ - __data_start__) + (__metadata_end - __metadata_start));
}
