#include "boot.h"

static void enable_a20_fast(void)
{
	u8 port_a;

	port_a = inb(0x92);	/* Configuration port A */
	port_a |=  0x02;	/* Enable A20 */
	port_a &= ~0x01;	/* Do not reset machine */
	outb(port_a, 0x92);
}

/*
 * Set up the GDT
 */
static void setup_gdt(void)
{
	static const u64 boot_gdt[] __attribute__((aligned(16))) = {
		0x00CF9A000000FFFFULL, 0x00CF92000000FFFFULL
	};
	
	static struct gdt_ptr gdt;

	gdt.len = sizeof(boot_gdt);
	gdt.ptr = (u32)&boot_gdt + (ds() << 4);

	asm volatile("lgdtl %0" : : "m" (gdt));
}

/*
 * Set up the IDT
 */
static void setup_idt(void)
{	
	static const struct gdt_ptr null_idt = {0, 0};
	asm volatile("lidtl %0" : : "m" (null_idt));
}

void go_to_protected_mode(void){
    enable_a20_fast();
    asm volatile("cli");
    setup_idt();
    setup_gdt();
}
