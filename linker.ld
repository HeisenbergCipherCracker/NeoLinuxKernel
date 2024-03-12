/* linker.ld */
ENTRY(start)
SECTIONS
{
  . = 0x1000;          /* Kernel starts at 0x1000:0x0000 */
  .text ALIGN(0x1000) :
  {
    *(.text)
  }
  .data ALIGN(0x1000) :
  {
    *(.data)
  }
  .bss ALIGN(0x1000) :
  {
    *(.bss)
  }
}
