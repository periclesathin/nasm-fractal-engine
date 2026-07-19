; Mandelbrot escape-time algorithm (Q16.16 fixed-point)
; edi = c_real, esi = c_imag, edx = max_iterations -> al = iteration count

section .text
    global mandelbrot_pixel

mandelbrot_pixel:
    movsxd  r8, edi          ; c_real
    movsxd  r9, esi          ; c_imag
    mov     r10d, edx        ; max_iterations

    xor     eax, eax         ; x = 0
    xor     ecx, ecx         ; y = 0
    xor     r11d, r11d       ; iter = 0

.loop:
    mov     rdi, rax
    imul    rdi, rax
    sar     rdi, 16          ; xx = x*x  (>>16 renormalizes Q16.16)

    mov     rsi, rcx
    imul    rsi, rcx
    sar     rsi, 16          ; yy = y*y

    mov     rdx, rdi
    add     rdx, rsi
    cmp     rdx, 0x40000     ; escape if x*x + y*y > 4.0
    jg      .done

    cmp     r11d, r10d       ; stop at iteration limit
    jae     .done

    mov     rdx, rax
    imul    rdx, rcx
    sar     rdx, 15          ; 2*x*y  (>>15 = *2 and >>16 in one shift)
    add     rdx, r9          ; y' = 2*x*y + c_imag

    sub     rdi, rsi
    add     rdi, r8          ; x' = xx - yy + c_real

    mov     rax, rdi
    mov     rcx, rdx
    inc     r11d
    jmp     .loop

.done:
    mov     eax, r11d        ; iteration count in al
    ret
