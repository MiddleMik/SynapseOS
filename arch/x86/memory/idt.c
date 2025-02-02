/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <memory/idt.h>
#include <io/ports.h>
#include <io/keyboard.h>



struct IDT_entry IDT[IDT_SIZE]; // array of IDT entries


/*
    load_idt - is used to load idt
*/
void load_idt(uint32_t idt_ptr[2]);


/*
    idt_init - is used to provide idt to kernel
*/
void idt_init() {
	uint32_t keyboard_address;
	uint32_t idt_address;
	uint32_t idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
	keyboard_address = (uint32_t)keyboard_handler;
	IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
	IDT[0x21].selector = 0x08;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE;
	IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	port_outb(0x20 , 0x11);
	port_outb(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	port_outb(0x21 , 0x20);
	port_outb(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	port_outb(0x21 , 0x00);
	port_outb(0xA1 , 0x00);

	/* ICW4 - environment info */
	port_outb(0x21 , 0x01);
	port_outb(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	port_outb(0x21 , 0xff);
	port_outb(0xA1 , 0xff);

	/* fill the IDT descriptor */
	idt_address = (uint32_t)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	load_idt(idt_ptr); // load IDT to special cpu register
}