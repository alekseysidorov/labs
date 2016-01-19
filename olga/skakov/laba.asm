[global printasm]

[section .text]

printasm:
    pushad

    xor eax, eax
    xor edi, edi
    xor ecx, ecx
    xor ebx, ebx
    xor edx, edx
    xor esi, esi
    xor ebp, ebp

    mov ebp, [esp + 32 + 12]
    mov al, [ebp]
    cmp al, '-'
    je eat_minus
    jmp read_number

eat_minus:
    inc ebp

read_number:
    mov al, [ebp]
    cmp al, 0
    je make_number

    or al, 20h
    cmp al, 'a'
    jge is_symbol
    sub al, '0'
    jmp add_number

is_symbol:
    sub al, 'a'
    add al, 10

add_number:
    shld edi, edx, 4
    shld edx, esi, 4
    shld esi, ebx, 4
    shl ebx, 4
    add bl, al

    inc ebp
    jmp read_number


make_number:
    mov ebp, [esp + 32 + 12]
    mov al, [ebp]
    cmp al, '-'
    jne read_flags

    not edi
    not edx
    not esi
    not ebx

    add ebx, 1
    adc esi, 0
    adc edx, 0
    adc edi, 0

read_flags:
    nop


to_string:
    mov ebp, edx
    xor edx, edx
    xor ecx, ecx

next_digit:
    push 10

    mov eax, edi
    div dword[esp]
    mov edi, eax
    mov ch, al

    mov eax, ebp
    div dword[esp]
    mov ebp, eax
    or ch, al

    mov eax, esi
    div dword[esp]
    mov esi, eax
    or ch, al

    mov eax, ebx
    div dword[esp]
    mov ebx, eax
    or ch, al

    pop eax

    add edx, '0'
    push edx
    xor edx, edx
    inc cl

    cmp ch, 0
    jne next_digit


print_result:
    mov eax, ecx
    imul eax, 4
    mov ebp, [esp + 32 + 4 + eax]

print_symbol:
    pop eax
    mov [ebp], al

    inc ebp
    dec cl
    cmp cl, 0
    jne print_symbol

    popad
    ret
