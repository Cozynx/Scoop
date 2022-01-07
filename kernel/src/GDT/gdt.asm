[bits 64]
LoadGDT:
    lgdt [rdi]
    mov ax, 0x10        ; segment selector for the Kernel Data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    pop rdi             ; pop the return address in the stack to the rdi register
    mov rax, 0x08       ; segment selector for the Kernel Code segment
    push rax            ; push the segment to the stack
    push rdi            ; push the return address
    retfq
GLOBAL LoadGDT