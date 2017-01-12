; MASM math definitions for libcgc
;
; Original license:
; Copyright (c) 2014 Jason L. Wright (jason@thought.net)
; All rights reserved.
;
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions
; are met:
; 1. Redistributions of source code must retain the above copyright
;    notice, this list of conditions and the following disclaimer.
; 2. Redistributions in binary form must reproduce the above copyright
;    notice, this list of conditions and the following disclaimer in the
;    documentation and/or other materials provided with the distribution.
;
; THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
; IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
; INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
; SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
; HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
; STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
; ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
; POSSIBILITY OF SUCH DAMAGE.
;
;
; # basic assembly math routines for DARPA Cyber Grand Challenge

.MODEL FLAT, C
.CODE

_ENTER MACRO base
    PUBLIC base&
    PUBLIC base&f
    base&l PROC
ENDM

_END MACRO base
    base&  ENDP
    base&f ENDP
    base&l ENDP
ENDM

cgc_sinl PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_sin
cgc_sinf PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_sin
cgc_sin PROC
    fld     QWORD PTR[esp+4]
_cgc_sin::
    fsin
    fnstsw  ax
    sahf
    jp      _2
    ret
_2:
    call    cgc_twopi_rem
    fsin
    ret
_END cgc_sin

cgc_cosl PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_cos
cgc_cosf PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_cos
cgc_cos PROC
    fld     QWORD PTR[esp+4]
_cgc_cos::
    fcos
    fnstsw  ax
    sahf
    jp      _2
    ret
_2:
    call    cgc_twopi_rem
    fcos
    ret
_END cgc_cos

cgc_tanl PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_tan
cgc_tanf PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_tan
cgc_tan PROC
    fld     QWORD PTR[esp+4]
_cgc_tan::
    fptan
    fnstsw  ax
    sahf
    jp      _2
    fstp    st(0)
    ret
_2:
    call    cgc_twopi_rem
    fptan
    fstp    st(0)
    ret
_END cgc_tan

cgc_twopi_rem PROC
    fldpi
    fadd    st(0), st(0)
    fxch    st(1)
_1:
    fprem
    fnstsw  ax
    sahf
    jp      _1
    fstp    st(1)
    ret
cgc_twopi_rem ENDP

cgc_remainderl PROC
    fld     TBYTE PTR[esp+16]
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_remainder
cgc_remainderf PROC
    fld     DWORD PTR[esp+8]
    fld     DWORD PTR[esp+4]
    jmp     _cgc_remainder
cgc_remainder PROC
    fld     QWORD PTR[esp+12]
    fld     QWORD PTR[esp+4]
_cgc_remainder::
    fprem1
    fstsw   ax
    sahf
    jp      _cgc_remainder
    fstp    st(1)
    ret
_END cgc_remainder

cgc_logl PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_log
cgc_logf PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_log
cgc_log PROC
    fld     QWORD PTR[esp+4]
_cgc_log::
    fldln2
    fxch    st(1)
    fyl2x
    ret
_END cgc_log

cgc_log10l PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_log10
cgc_log10f PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_log10
cgc_log10 PROC
    fld     QWORD PTR[esp+4]
_cgc_log10::
    fldlg2
    fxch    st(1)
    fyl2x
    ret
_END cgc_log10

cgc_significandl PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_significand
cgc_significandf PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_significand
cgc_significand PROC
    fld     QWORD PTR[esp+4]
_cgc_significand::
    fxtract
    fstp    st(1)
    ret
_END cgc_significand

cgc_scalbnl PROC
    fild    DWORD PTR[esp+16]
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_scalbn
cgc_scalbnf PROC
    fild    DWORD PTR[esp+8]
    fld     DWORD PTR[esp+4]
    jmp     _cgc_scalbn
cgc_scalbn PROC
    fild    DWORD PTR[esp+12]
    fld     QWORD PTR[esp+4]
_cgc_scalbn::
    fscale
    fstp    st(1)
    ret
_END cgc_scalbn

cgc_scalblnl PROC
    jmp     cgc_scalbnl
cgc_scalblnf PROC
    jmp     cgc_scalbnf
cgc_scalbln  PROC
    jmp     cgc_scalbn
_END cgc_scalbln

cgc_rintl PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_rint
cgc_rintf PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_rint
cgc_rint PROC
    fld     QWORD PTR[esp+4]
_cgc_rint::
    frndint
    ret
_END cgc_rint

cgc_sqrtl PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_sqrt
cgc_sqrtf PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_sqrt
cgc_sqrt PROC
    fld     QWORD PTR[esp+4]
_cgc_sqrt::
    fsqrt
    ret
_END cgc_sqrt

cgc_fabsl PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_fabs
cgc_fabsf PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_fabs
cgc_fabs PROC
    fld     QWORD PTR[esp+4]
_cgc_fabs::
    fabs
    ret
_END cgc_fabs

cgc_atan2l PROC
    fld     TBYTE PTR[esp+4]
    fld     TBYTE PTR[esp+16]
    jmp     _cgc_atan2
cgc_atan2f PROC
    fld     DWORD PTR[esp+4]
    fld     DWORD PTR[esp+8]
    jmp     _cgc_atan2
cgc_atan2 PROC
    fld     QWORD PTR[esp+4]
    fld     QWORD PTR[esp+12]
_cgc_atan2::
    fpatan
    ret
_END cgc_atan2

cgc_log2l PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_log2
cgc_log2f PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_log2
cgc_log2 PROC
    fld     QWORD PTR[esp+4]
_cgc_log2::
    fld1
    fxch
    fyl2x
    ret
_END cgc_log2

cgc_exp2l PROC
    fld     TBYTE PTR[esp+4]
    jmp     cgc_exp2x
cgc_exp2f PROC
    fld     DWORD PTR[esp+4]
    jmp     cgc_exp2x
cgc_exp2 PROC
    fld     QWORD PTR[esp+4]
    jmp     cgc_exp2x
cgc_exp2x PROC
    fld     st(0)
    frndint
    fsubr   st,st(1)
    fxch
    f2xm1
    fld1
    faddp
    fscale
    fstp    st(1)
    ret
cgc_exp2x ENDP
_END cgc_exp2

cgc_powl PROC
    fld     TBYTE PTR[esp+16]
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_pow
cgc_powf PROC
    fld     DWORD PTR[esp+8]
    fld     DWORD PTR[esp+4]
    jmp     _cgc_pow
cgc_pow PROC
    fld     QWORD PTR[esp+12]
    fld     QWORD PTR[esp+4]
_cgc_pow::
    fyl2x
    jmp     cgc_exp2x
_END cgc_pow

cgc_expl PROC
    fld     TBYTE PTR[esp+4]
    jmp     _cgc_exp
cgc_expf PROC
    fld     DWORD PTR[esp+4]
    jmp     _cgc_exp
cgc_exp PROC
    fld     QWORD PTR[esp+4]
_cgc_exp::
    fldl2e
    fmulp
    jmp     cgc_exp2x
_END cgc_exp

cgc_setjmp PROC
    mov     ecx, [esp+4]
    mov     edx, [esp+0]
    mov     [ecx+0], edx
    mov     [ecx+4], ebx
    mov     [ecx+8], esp
    mov     [ecx+12], ebp
    mov     [ecx+16], esi
    mov     [ecx+20], edi
    xor     eax, eax
    ret
cgc_setjmp ENDP

cgc_longjmp PROC
    mov     edx, [esp+4]
    mov     eax, [esp+8]
    mov     ecx, [edx+0]
    mov     ebx, [edx+4]
    mov     esp, [edx+8]
    mov     ebp, [edx+12]
    mov     esi, [edx+16]
    mov     edi, [edx+20]
    test    eax, eax
    jnz     _1
    inc     eax
_1:
    mov     [esp+0], ecx
    ret
cgc_longjmp ENDP

END
