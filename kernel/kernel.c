/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <kernel.h>



/*
    kernel_main is the main function of the kernel. 
    It initializes the core modules and the main cycle has been declared.
*/
void kernel_main() {
    clean_screen();
    

    puts("SynapseOS 0.0.1");
    
    gdt_init();
    puts("gdt inited");
    
    idt_init();
    puts("idt inited");


    while(1);
}