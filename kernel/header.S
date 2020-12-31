bits 32

; multiboot magic
MAGIC equ 0x1BADB002
FLAGS equ 0x00
CHECKSUM equ -(MAGIC+FLAGS)
section .text
        align 4
        dd MAGIC               	
        dd FLAGS                    	
        dd CHECKSUM   	        ; CHECKSUM = -(MAGIC_FLAGS)

global start
extern kmain 				; kernel main entry

start:
	cli 				; block interrupts
	call kmain
	hlt                             ; never return 				
