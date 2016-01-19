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
    jne to_string

    not edi
    not edx
    not esi
    not ebx

    add ebx, 1
    adc esi, 0
    adc edx, 0
    adc edi, 0

to_string:
    mov ebp, edx
    xor ecx, ecx
    mov ebx, edi
    and ebx, 0x80000000
    or ecx, ebx
    xor edx, edx

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

read_flags:
    mov eax, ecx
    mov ebp, [esp + 32 + 8 + eax * 4]
    mov esi, ebp

    mov al, [ebp]
    cmp al, 0
    je print_result

    inc ebp
    xor eax, eax
    xor ebx, ebx
    xor edi, edi
read_next:
    mov al, [ebp]

    cmp al, 0
    je make_flags
    sub al, '0'
    imul edi, 10
    add edi, eax
    inc ebp
    jmp read_next

make_flags:
    mov al, [esi]

    and ecx, 0x7fffffff

    cmp al, '-'
    je dash
    cmp al, ' '
    je space
    cmp al, '0'
    je align_zero

dash:
    jmp print_result

space:
    push ' '
    inc cl
    jmp align_space

align_space:
    mov esi, edi
    sub esi, ecx
align_space_next:
    cmp esi, 0
    jle print_result
    push ' '
    dec esi
    inc cl
    jmp align_space_next

align_zero:
    mov esi, edi
    sub esi, ecx
align_zero_next:
    cmp esi, 0
    jle print_result
    push '0'
    dec esi
    inc cl
    jmp align_zero_next

print_result:
    mov eax, ecx
    mov ebp, [esp + 32 + 4 + eax * 4]

print_symbol:
    pop eax
    mov [ebp], al

    inc ebp
    dec cl
    cmp cl, 0
    jne print_symbol

    popad
    ret
