[global printasm] ; void  printasm(char *out_buf, const char *format, const char *hex_number);

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

    mov ebp, [esp + 32 + 12]; достаем указатель на const char *hex_number с учетом того, что esp сместился из за pushей
    mov al, [ebp]
    cmp al, '-'
    je eat_minus
    jmp read_number

eat_minus: ; просто проглатываем минус, если встретили
    inc ebp

read_number:
    mov al, [ebp] ; считываем код символа
    cmp al, 0
    je make_number

    or al, 20h ; просто превращает большие буквы в маленькие, с цифрами ничего не делает.
    cmp al, 'a'
    jge is_symbol
    sub al, '0'
    jmp add_number

is_symbol:
    sub al, 'a'
    add al, 10

add_number: ; считываем число в регистры edi, edx, esi, ebx
    shld edi, edx, 4 ; двигаем все регистры влево старшего бита в следующий регистр (умножаем 128битное число на 16)
    shld edx, esi, 4
    shld esi, ebx, 4
    shl ebx, 4
    add bl, al ; добавляем считанную цифру.

    inc ebp
    jmp read_number


make_number: ; считываем опять минус и если надо инвертируем число
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

    mov edx, edi ; запоминаем знак числа
    and edx, 0x80000000
    or ecx, edx
    xor edx, edx

next_digit: ; последовательно делим части числа на 10 пока оно не обнулится, остаток кладем в стек
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

read_flags: ;всякая работа с флагами
    mov eax, ecx
    mov ebp, [esp + 32 + 8 + eax * 4] ; достаем const char *format с учетом того, что esp сместился из за pushей
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
    mov ebp, [esp + 32 + 4 + eax * 4] ; достаем char *out_buf

print_symbol:
    pop eax
    mov [ebp], al

    inc ebp
    dec cl
    cmp cl, 0
    jne print_symbol

    popad
    ret
