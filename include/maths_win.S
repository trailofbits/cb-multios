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
    base&l ENDP
ENDM

_ENTER cgc_sin
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_sinf::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_sin::
    fld     QWORD PTR[esp+4]
_1:
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

_ENTER cgc_cos
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_cosf::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_cos::
    fld     QWORD PTR[esp+4]
_1:
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

_ENTER cgc_tan
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_tanf::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_tan::
    fld     QWORD PTR[esp+4]
_1:
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

_ENTER cgc_remainder
    fld     TBYTE PTR[esp+16]
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_remainderf::
    fld     DWORD PTR[esp+8]
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_remainder::
    fld     QWORD PTR[esp+12]
    fld     QWORD PTR[esp+4]
_1:
    fprem1
    fstsw   ax
    sahf
    jp      _1
    fstp    st(1)
    ret
_END cgc_remainder

_ENTER cgc_log
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_logf::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_log::
    fld     QWORD PTR[esp+4]
_1:
    fldln2
    fxch    st(1)
    fyl2x
    ret
_END cgc_log

_ENTER cgc_log10
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_log10f::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_log10::
    fld     QWORD PTR[esp+4]
_1:
    fldlg2
    fxch    st(1)
    fyl2x
    ret
_END cgc_log10

_ENTER cgc_significand
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_significandf::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_significand::
    fld     QWORD PTR[esp+4]
_1:
    fxtract
    fstp    st(1)
    ret
_END cgc_significand

_ENTER cgc_scalbln
    fild    DWORD PTR[esp+16]
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_scalblnf::
    fild    DWORD PTR[esp+8]
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_scalbln::
    fild    DWORD PTR[esp+12]
    fld     QWORD PTR[esp+4]
_1:
    fscale
    fstp    st(1)
    ret
_END cgc_scalbln

_ENTER cgc_scalbn
    fild    DWORD PTR[esp+16]
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_scalbnf::
    fild    DWORD PTR[esp+8]
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_scalbn::
    fild    DWORD PTR[esp+12]
    fld     QWORD PTR[esp+4]
_1:
    fscale
    fstp    st(1)
    ret
_END cgc_scalbn

_ENTER cgc_rint
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_rintf::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_rint::
    fld     QWORD PTR[esp+4]
_1:
    frndint
    ret
_END cgc_rint

_ENTER cgc_sqrt
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_sqrtf::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_sqrt::
    fld     QWORD PTR[esp+4]
_1:
    fsqrt
    ret
_END cgc_sqrt

_ENTER cgc_fabs
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_fabsf::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_fabs::
    fld     QWORD PTR[esp+4]
_1:
    fabs
    ret
_END cgc_fabs

_ENTER cgc_atan2
    fld     TBYTE PTR[esp+4]
    fld     TBYTE PTR[esp+16]
    jmp     _1
cgc_atan2f::
    fld     DWORD PTR[esp+4]
    fld     DWORD PTR[esp+8]
    jmp     _1
cgc_atan2::
    fld     QWORD PTR[esp+4]
    fld     QWORD PTR[esp+12]
_1:
    fpatan
    ret
_END cgc_atan2

_ENTER cgc_log2
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_log2f::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_log2::
    fld     QWORD PTR[esp+4]
_1:
    fld1
    fxch
    fyl2x
    ret
_END cgc_log2

PUBLIC cgc_exp2x
_ENTER cgc_exp2
    fld     TBYTE PTR[esp+4]
    jmp     cgc_exp2x
cgc_exp2f::
    fld     DWORD PTR[esp+4]
    jmp     cgc_exp2x
cgc_exp2::
    fld     QWORD PTR[esp+4]
    jmp     cgc_exp2x
cgc_exp2x::
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
_END cgc_exp2

_ENTER cgc_pow
    fld     TBYTE PTR[esp+16]
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_powf::
    fld     DWORD PTR[esp+8]
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_pow::
    fld     QWORD PTR[esp+12]
    fld     QWORD PTR[esp+4]
_1:
    fyl2x
    jmp     cgc_exp2x
_END cgc_pow

_ENTER cgc_exp
    fld     TBYTE PTR[esp+4]
    jmp     _1
cgc_expf::
    fld     DWORD PTR[esp+4]
    jmp     _1
cgc_exp::
    fld     QWORD PTR[esp+4]
_1:
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
