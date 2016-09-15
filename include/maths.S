
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

ENTER cgc_sin
cgc_sinl:
    fldt    4(%esp)
    jmp     1f
cgc_sinf:
    flds    4(%esp)
    jmp     1f
cgc_sin:
    fldl    4(%esp)
1:
    fsin
    fnstsw  %ax
    sahf
    jp      2f
    ret
2:
    call    cgc_twopi_rem
    fsin
    ret
END cgc_sin

ENTER cgc_cos
cgc_cosl:
    fldt    4(%esp)
    jmp     1f
cgc_cosf:
    flds    4(%esp)
    jmp     1f
cgc_cos:
    fldl    4(%esp)
1:
    fcos
    fnstsw  %ax
    sahf
    jp      2f
    ret
2:
    call    cgc_twopi_rem
    fcos
    ret
END cgc_cos

ENTER cgc_tan
cgc_tanl:
    fldt    4(%esp)
    jmp     1f
cgc_tanf:
    flds    4(%esp)
    jmp     1f
cgc_tan:
    fldl    4(%esp)
1:
    fptan
    fnstsw  %ax
    sahf
    jp      2f
    fstp    %st(0)
    ret
2:
    call    cgc_twopi_rem
    fptan
    fstp    %st(0)
    ret
END cgc_tan

.type cgc_twopi_rem, @function
cgc_twopi_rem:
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
.size    cgc_twopi_rem, . - cgc_twopi_rem

ENTER cgc_remainder
cgc_remainderl:
    fldt    16(%esp)
    fldt    4(%esp)
    jmp     1f
cgc_remainderf:
    flds    8(%esp)
    flds    4(%esp)
    jmp     1f
cgc_remainder:
    fldl    12(%esp)
    fldl    4(%esp)
1:
    fprem1
    fstsw   %ax
    sahf
    jp      1b
    fstp    %st(1)
    ret
END cgc_remainder

ENTER cgc_log
cgc_logl:
    fldt    4(%esp)
    jmp     1f
cgc_logf:
    flds    4(%esp)
    jmp     1f
cgc_log:
    fldl    4(%esp)
1:
    fldln2
    fxch    %st(1)
    fyl2x
    ret
END cgc_log

ENTER cgc_log10
cgc_log10l:
    fldt    4(%esp)
    jmp     1f
cgc_log10f:
    flds    4(%esp)
    jmp     1f
cgc_log10:
    fldl    4(%esp)
1:
    fldlg2
    fxch    %st(1)
    fyl2x
    ret
END cgc_log10

ENTER cgc_significand
cgc_significandl:
    fldt    4(%esp)
    jmp     1f
cgc_significandf:
    flds    4(%esp)
    jmp     1f
cgc_significand:
    fldl    4(%esp)
1:
    fxtract
    fstp    %st(1)
    ret
END cgc_significand

ENTER cgc_scalbn
ENTER cgc_scalbln
cgc_scalbnl:
cgc_scalblnl:
    fildl   16(%esp)
    fldt    4(%esp)
    jmp     1f
cgc_scalbnf:
cgc_scalblnf:
    fildl   8(%esp)
    flds    4(%esp)
    jmp     1f
cgc_scalbn:
cgc_scalbln:
    fildl   12(%esp)
    fldl    4(%esp)
1:
    fscale
    fstp    %st(1)
    ret
END cgc_scalbn
END cgc_scalbln

ENTER cgc_rint
cgc_rintl:
    fldt    4(%esp)
    jmp     1f
cgc_rintf:
    flds    4(%esp)
    jmp     1f
cgc_rint:
    fldl    4(%esp)
1:
    frndint
    ret
END cgc_rint

ENTER cgc_sqrt
cgc_sqrtl:
    fldt    4(%esp)
    jmp     1f
cgc_sqrtf:
    flds    4(%esp)
    jmp     1f
cgc_sqrt:
    fldl    4(%esp)
1:
    fsqrt
    ret
END cgc_sqrt

ENTER cgc_fabs
cgc_fabsl:
    fldt    4(%esp)
    jmp     1f
cgc_fabsf:
    flds    4(%esp)
    jmp     1f
cgc_fabs:
    fldl    4(%esp)
1:
    fabs
    ret
END cgc_fabs

ENTER cgc_atan2
cgc_atan2l:
    fldt    4(%esp)
    fldt    16(%esp)
    jmp     1f
cgc_atan2f:
    flds    4(%esp)
    flds    8(%esp)
    jmp     1f
cgc_atan2:
    fldl    4(%esp)
    fldl    12(%esp)
1:
    fpatan
    ret
END cgc_atan2

ENTER cgc_log2
cgc_log2l:
    fldt    4(%esp)
    jmp     1f
cgc_log2f:
    flds    4(%esp)
    jmp     1f
cgc_log2:
    fldl    4(%esp)
1:
    fld1
    fxch
    fyl2x
    ret
END cgc_log2

ENTER cgc_exp2
    .type    cgc_exp2x, @function
cgc_exp2l:
    fldt    4(%esp)
    jmp     cgc_exp2x
cgc_exp2f:
    flds    4(%esp)
    jmp     cgc_exp2x
cgc_exp2:
    fldl    4(%esp)
cgc_exp2x:
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
END cgc_exp2
.size    cgc_exp2x, . - cgc_exp2x

ENTER cgc_pow
cgc_powl:
    fldt    16(%esp)
    fldt    4(%esp)
    jmp     1f
cgc_powf:
    flds    8(%esp)
    flds    4(%esp)
    jmp     1f
cgc_pow:
    fldl    12(%esp)
    fldl    4(%esp)
1:
    fyl2x
    jmp     cgc_exp2x
END cgc_pow

ENTER cgc_exp
cgc_expl:
    fldt    4(%esp)
    jmp     1f
cgc_expf:
    flds    4(%esp)
    jmp     1f
cgc_exp:
    fldl    4(%esp)
1:
    fldl2e
    fmulp
    jmp     cgc_exp2x
END cgc_exp

.global cgc_setjmp
.type cgc_setjmp, @function
cgc_setjmp:
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
.size cgc_setjmp, . - cgc_setjmp

.global cgc_longjmp
.type cgc_longjmp, @function
cgc_longjmp:
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
.size cgc_longjmp, . - cgc_longjmp
