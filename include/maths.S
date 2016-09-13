
#
# Copyright (c) 2014 Jason L. Wright (jason@thought.net)
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

# basic assembly math routines for DARPA Cyber Grand Challenge

#ifdef APPLE
.macro .type
.endm

.macro .size
.endm
#endif

.macro ENTER base
    .global \base, \base\()f, \base\()l
    .type \base, @function
    .type \base\()f, @function
    .type \base\()l, @function
.endm

.macro END base
    .size \base, . - \base
    .size \base\()f, . - \base\()f
    .size \base\()l, . - \base\()l
.endm

ENTER _sin
_sinl:
    fldt    4(%esp)
    jmp     1f
_sinf:
    flds    4(%esp)
    jmp     1f
_sin:
    fldl    4(%esp)
1:
    fsin
    fnstsw  %ax
    sahf
    jp      2f
    ret
2:
    call    _twopi_rem
    fsin
    ret
END _sin

ENTER _cos
_cosl:
    fldt    4(%esp)
    jmp     1f
_cosf:
    flds    4(%esp)
    jmp     1f
_cos:
    fldl    4(%esp)
1:
    fcos
    fnstsw  %ax
    sahf
    jp      2f
    ret
2:
    call    _twopi_rem
    fcos
    ret
END _cos

ENTER _tan
_tanl:
    fldt    4(%esp)
    jmp     1f
_tanf:
    flds    4(%esp)
    jmp     1f
_tan:
    fldl    4(%esp)
1:
    fptan
    fnstsw  %ax
    sahf
    jp      2f
    fstp    %st(0)
    ret
2:
    call    _twopi_rem
    fptan
    fstp    %st(0)
    ret
END _tan

.type _twopi_rem, @function
_twopi_rem:
    fldpi
    fadd    %st(0)
    fxch    %st(1)
1:
    fprem
    fnstsw  %ax
    sahf
    jp      1b
    fstp    %st(1)
    ret
.size    _twopi_rem, . - _twopi_rem

ENTER _remainder
_remainderl:
    fldt    16(%esp)
    fldt    4(%esp)
    jmp     1f
_remainderf:
    flds    8(%esp)
    flds    4(%esp)
    jmp     1f
_remainder:
    fldl    12(%esp)
    fldl    4(%esp)
1:
    fprem1
    fstsw   %ax
    sahf
    jp      1b
    fstp    %st(1)
    ret
END _remainder

ENTER _log
_logl:
    fldt    4(%esp)
    jmp     1f
_logf:
    flds    4(%esp)
    jmp     1f
_log:
    fldl    4(%esp)
1:
    fldln2
    fxch    %st(1)
    fyl2x
    ret
END _log

ENTER _log10
_log10l:
    fldt    4(%esp)
    jmp     1f
_log10f:
    flds    4(%esp)
    jmp     1f
_log10:
    fldl    4(%esp)
1:
    fldlg2
    fxch    %st(1)
    fyl2x
    ret
END _log10

ENTER _significand
_significandl:
    fldt    4(%esp)
    jmp     1f
_significandf:
    flds    4(%esp)
    jmp     1f
_significand:
    fldl    4(%esp)
1:
    fxtract
    fstp    %st(1)
    ret
END _significand

ENTER _scalbn
ENTER _scalbln
_scalbnl:
_scalblnl:
    fildl   16(%esp)
    fldt    4(%esp)
    jmp     1f
_scalbnf:
_scalblnf:
    fildl   8(%esp)
    flds    4(%esp)
    jmp     1f
_scalbn:
_scalbln:
    fildl   12(%esp)
    fldl    4(%esp)
1:
    fscale
    fstp    %st(1)
    ret
END _scalbn
END _scalbln

ENTER _rint
_rintl:
    fldt    4(%esp)
    jmp     1f
_rintf:
    flds    4(%esp)
    jmp     1f
_rint:
    fldl    4(%esp)
1:
    frndint
    ret
END _rint

ENTER _sqrt
_sqrtl:
    fldt    4(%esp)
    jmp     1f
_sqrtf:
    flds    4(%esp)
    jmp     1f
_sqrt:
    fldl    4(%esp)
1:
    fsqrt
    ret
END _sqrt

ENTER _fabs
_fabsl:
    fldt    4(%esp)
    jmp     1f
_fabsf:
    flds    4(%esp)
    jmp     1f
_fabs:
    fldl    4(%esp)
1:
    fabs
    ret
END _fabs

ENTER _atan2
_atan2l:
    fldt    4(%esp)
    fldt    16(%esp)
    jmp     1f
_atan2f:
    flds    4(%esp)
    flds    8(%esp)
    jmp     1f
_atan2:
    fldl    4(%esp)
    fldl    12(%esp)
1:
    fpatan
    ret
END _atan2

ENTER _log2
_log2l:
    fldt    4(%esp)
    jmp     1f
_log2f:
    flds    4(%esp)
    jmp     1f
_log2:
    fldl    4(%esp)
1:
    fld1
    fxch
    fyl2x
    ret
END _log2

ENTER _exp2
    .type    _exp2x, @function
_exp2l:
    fldt    4(%esp)
    jmp     _exp2x
_exp2f:
    flds    4(%esp)
    jmp     _exp2x
_exp2:
    fldl    4(%esp)
_exp2x:
    fld     %st(0)
    frndint
    fsubr   %st,%st(1)
    fxch
    f2xm1
    fld1
    faddp
    fscale
    fstp    %st(1)
    ret
END _exp2
.size    _exp2x, . - _exp2x

ENTER _pow
_powl:
    fldt    16(%esp)
    fldt    4(%esp)
    jmp     1f
_powf:
    flds    8(%esp)
    flds    4(%esp)
    jmp     1f
_pow:
    fldl    12(%esp)
    fldl    4(%esp)
1:
    fyl2x
    jmp     _exp2x
END _pow

ENTER _exp
_expl:
    fldt    4(%esp)
    jmp     1f
_expf:
    flds    4(%esp)
    jmp     1f
_exp:
    fldl    4(%esp)
1:
    fldl2e
    fmulp
    jmp     _exp2x
END _exp

.global _setjmp
.type _setjmp, @function
_setjmp:
    movl    4(%esp), %ecx
    movl    0(%esp), %edx
    movl    %edx, 0(%ecx)
    movl    %ebx, 4(%ecx)
    movl    %esp, 8(%ecx)
    movl    %ebp, 12(%ecx)
    movl    %esi, 16(%ecx)
    movl    %edi, 20(%ecx)
    xorl    %eax, %eax
    ret
.size _setjmp, . - _setjmp

.global _longjmp
.type _longjmp, @function
_longjmp:
    movl    4(%esp), %edx
    movl    8(%esp), %eax
    movl    0(%edx), %ecx
    movl    4(%edx), %ebx
    movl    8(%edx), %esp
    movl    12(%edx), %ebp
    movl    16(%edx), %esi
    movl    20(%edx), %edi
    testl   %eax, %eax
    jnz    1f
    incl    %eax
1:
    movl    %ecx, 0(%esp)
    ret
.size _longjmp, . - _longjmp
