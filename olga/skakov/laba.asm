[global _printasm]

[section .text]

_printasm:
    pushad

    xor eax, eax
    xor edi, edi
    xor ecx, ecx
    xor edx, edx
    xor esi, esi
    xor ebp, ebp

    mov ebp, [esp + 32 + 12]

    mov al, [ebp]

    cmp al, '-'
    je minus

minus:
    inc ebp

read_symbol:
    mov al, [ebp]
    cmp al, 0
    je number
    inc ah
    inc ebp
    jmp read_symbol

number:
    dec ah
    dec ebp
    mov al, [ebp]


;mov al, [ebp]
;inc ebp
;cmp al, '0'
;je gav
;cmp al, '-'
;je min

;;or al, 20h
;cmp al, 'a'
;jge buu

;jmp koo

;buu:
;sub al, 'a'
;add al, 10

;koo:
;sub al, '0'

;add edi, eax
;mov ebx, 7
;ab:
;cmp ebx, 0
;je aba
;imul edi, 4

;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu1

;jmp koo1

;buu1:
;sub al, 'a'
;add al, 10

;koo1:
;sub al, '0'

;cmp al, '0'
;je gav
;add edi, eax
;sub ebx, 1
;jmp ab
;aba:


;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu2

;jmp koo2

;buu2:
;sub al, 'a'
;add al, 10

;koo2:
;sub al, '0'

;cmp al, '0'
;je gav
;add ecx, eax
;mov ebx, 7
;ab2:
;cmp ebx, 0
;je aba2
;imul ecx, 4

;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu3

;jmp koo3

;buu3:
;sub al, 'a'
;add al, 10

;koo3:
;sub al, '0'

;cmp al, '0'
;je gav
;add ecx, eax
;sub ebx, 1
;jmp ab2
;aba2:



;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu4

;jmp koo4

;buu4:
;sub al, 'a'
;add al, 10

;koo4:
;sub al, '0'

;cmp al, '0'
;je gav
;add edx, eax
;mov ebx, 7
;ab3:
;cmp ebx, 0
;je aba3
;imul edx, 4

;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu5

;jmp koo5

;buu5:
;sub al, 'a'
;add al, 10

;koo5:
;sub al, '0'

;cmp al, '0'
;je gav
;add edx, eax
;sub ebx, 1
;jmp ab3
;aba3:


;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu6

;jmp koo6

;buu6:
;sub al, 'a'
;add al, 10

;koo6:
;sub al, '0'

;cmp al, '0'
;je gav
;add esi, eax
;mov ebx, 7
;ab4:
;cmp ebx, 0
;je aba4
;imul esi, 4

;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu7

;jmp koo7

;buu7:
;sub al, 'a'
;add al, 10

;koo7:
;sub al, '0'

;cmp al, '0'
;je gav
;add esi, eax
;sub ebx, 1
;jmp ab4
;aba4:
;jmp gav


;min:

;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu8

;jmp koo8

;buu8:
;sub al, 'a'
;add al, 10

;koo8:
;sub al, '0'

;cmp al, '0'
;je gav
;add edi, eax
;mov ebx, 7
;ab5:
;cmp ebx, 0
;je aba5
;imul edi, 4

;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu9

;jmp koo9

;buu9:
;sub al, 'a'
;add al, 10

;koo9:
;sub al, '0'

;cmp al, '0'
;je gav
;add edi, eax
;sub ebx, 1
;jmp ab5
;aba5:


;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu10

;jmp koo10

;buu10:
;sub al, 'a'
;add al, 10

;koo10:
;sub al, '0'

;cmp al, '0'
;je gav
;add ecx, eax
;mov ebx, 7
;ab6:
;cmp ebx, 0
;je aba6
;imul ecx, 4

;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu11

;jmp koo11

;buu11:
;sub al, 'a'
;add al, 10

;koo11:
;sub al, '0'

;cmp al, '0'
;je gav
;add ecx, eax
;sub ebx, 1
;jmp ab6
;aba6:


;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu12

;jmp koo12

;buu12:
;sub al, 'a'
;add al, 10

;koo12:
;sub al, '0'

;cmp al, '0'
;je gav
;add edx, eax
;mov ebx, 7
;ab7:
;cmp ebx, 0
;je aba7
;imul edx, 4

;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu13

;jmp koo13

;buu13:
;sub al, 'a'
;add al, 10

;koo13:
;sub al, '0'

;cmp al, '0'
;je gav
;add edx, eax
;sub ebx, 1
;jmp ab7
;aba7:


;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu14

;jmp koo14

;buu14:
;sub al, 'a'
;add al, 10

;koo14:
;sub al, '0'

;cmp al, '0'
;je gav
;add esi, eax
;mov ebx, 7
;ab8:
;cmp ebx, 0
;je aba8
;imul esi, 4

;mov al, [ebp]
;inc ebp
;or al, 20h
;cmp al, 'a'
;jge buu15

;jmp koo15

;buu15:
;sub al, 'a'
;add al, 10

;koo15:
;sub al, '0'

;cmp al, '0'
;je gav
;add esi, eax
;sub ebx, 1
;jmp ab8
;aba8:

;mov ebp, 10000000000000000000000000000000b
;and ebp, edi
;cmp ebp, 0
;jne rar
;jmp gav
;rar:
;not edi
;not edx
;not ecx
;not esi
;add esi, 1
;adc edx, 0
;adc ecx, 0
;adc edi, 0

;gav:

;mov ebx, edx

;xor ebp, ebp
;_convertToString:
;xor edx, edx

;mov eax, edi
;div dword[digit]
;mov edi, eax
;mov dh, al

;mov eax, ecx
;div dword[digit]
;mov ecx, eax
;or dh, al

;mov eax, ebx
;div dword[digit]
;mov ebx, eax
;or dh, al

;mov eax, esi
;div dword[digit]
;mov esi, eax
;or dh, al

;push edx
;inc ebp

;cmp dh, 0
;jnz _convertToString

;mov eax, ebp
;imul eax, 4
;mov edx, [esp + 32 + 4 + eax]

;xor ecx, ecx
;mov [edx + ebp], cl
;xor esi, esi


;kux:
;pop ecx
;mov [edx + esi], cl
;inc esi
;dec ebp
;cmp ebp, 0
;jnz kux

popad
ret
