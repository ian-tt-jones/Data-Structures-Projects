%define STDOUT 1
%define SYSCALL_EXIT 60
%define SYSCALL_WRITE 1


        section .data

msg1:   db      "Hello!", 10, 0  ;C-style \0 terminated string

msg2:   db      10, "Good-bye :)",10, 0

char:   db      0, 0



        section .text
        global main

main:
        mov     rdi, msg1
        call    print

        mov     di, 5
        call recurse

        mov     rdi, msg2
        call    print

exit:
        mov     rax, SYSCALL_EXIT
        xor     rdi, rdi
        syscall



;Print subroutine, writes characters until a null
;string address is found in rdi

print:
        mov     rax, rdi
        xor     rdx, rdx

count:
        cmp     [rdi], byte 0   ;null character
        je      end_count
        inc     rdx
        inc     rdi
        jmp     count

end_count:
        mov     rsi, rax
        mov     rax, SYSCALL_WRITE
        mov     rdi, STDOUT
        syscall

        ret

;Recursive subroutine
recurse:
        cmp     di, 0
        jge     rcont
        ret

rcont:
        push    di
        dec     di
        call    recurse
        xor     rax, rax
        pop     ax
        add     al, 48
        mov     [char], al
        mov     rdi, char
        call    print
        ret