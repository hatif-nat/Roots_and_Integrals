section .rodata
    _0 dq 0.0
    _2 dq 2.0
    _1 dq 1.0
    _3 dq 3.0
    _minus1 dq -1.0

section .text
global f1
f1:
    push ebp
    mov ebp, esp
    fld qword[esp+8]
    fld qword[_minus1]
    fmulp 
    fldl2e
    fmulp
    fld st0
    frndint
    fsub st1, st0
    fxch st1
    f2xm1
    fld1
    fadd
    fscale
    fstp st1
    fld qword [_3]
    faddp
    pop ebp
    ret

global f2
f2:
    push ebp
    mov ebp, esp
    fld qword[_2]
    fld qword[ebp + 8]
    fmulp
    fld qword[_2]
    fsubp
    pop ebp
    ret

global f3
f3:
    push ebp
    mov ebp, esp
    fld qword[_1]
    fld qword[ebp + 8]
    fdivp
    pop ebp
    ret
    
global derf1
derf1:
    push ebp
    mov ebp, esp
    fld qword[esp+8]
    fld qword[_minus1]
    fmulp 
    fldl2e
    fmulp
    fld st0
    frndint
    fsub st1, st0
    fxch st1
    f2xm1
    fld1
    fadd
    fscale
    fstp st1
    FCHS
    pop ebp
    ret
    
    
global derf2
derf2:
    push ebp
    mov ebp, esp
    fld qword[_2]
    pop ebp
    ret     

global derf3
derf3:
    push ebp
    mov ebp, esp
    fld qword[_minus1]
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fmulp
    fdivp
    pop ebp
    ret
            
