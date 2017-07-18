
//
// Copyright (c) 2014 Jason L. Wright (jason@thought.net)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

// basic assembly math routines for DARPA Cyber Grand Challenge

#ifdef APPLE
.macro .type
.endm

.macro .size
.endm

// OSX symbols need a leading underscore
# define SYM(x) _##x

#else
# define SYM(x) x
#endif // APPLE

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

ENTER SYM(cgc_sin)
SYM(cgc_sinl):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_sinf):
    flds    4(%esp)
    jmp     1f
SYM(cgc_sin):
    fldl    4(%esp)
1:
    fsin
    fnstsw  %ax
    sahf
    jp      2f
    ret
2:
    call    SYM(cgc_twopi_rem)
    fsin
    ret
END SYM(cgc_sin)

ENTER SYM(cgc_cos)
SYM(cgc_cosl):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_cosf):
    flds    4(%esp)
    jmp     1f
SYM(cgc_cos):
    fldl    4(%esp)
1:
    fcos
    fnstsw  %ax
    sahf
    jp      2f
    ret
2:
    call    SYM(cgc_twopi_rem)
    fcos
    ret
END SYM(cgc_cos)

ENTER SYM(cgc_tan)
SYM(cgc_tanl):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_tanf):
    flds    4(%esp)
    jmp     1f
SYM(cgc_tan):
    fldl    4(%esp)
1:
    fptan
    fnstsw  %ax
    sahf
    jp      2f
    fstp    %st(0)
    ret
2:
    call    SYM(cgc_twopi_rem)
    fptan
    fstp    %st(0)
    ret
END SYM(cgc_tan)

.type SYM(cgc_twopi_rem), @function
SYM(cgc_twopi_rem):
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
.size    SYM(cgc_twopi_rem), . - SYM(cgc_twopi_rem)

ENTER SYM(cgc_remainder)
SYM(cgc_remainderl):
    fldt    16(%esp)
    fldt    4(%esp)
    jmp     1f
SYM(cgc_remainderf):
    flds    8(%esp)
    flds    4(%esp)
    jmp     1f
SYM(cgc_remainder):
    fldl    12(%esp)
    fldl    4(%esp)
1:
    fprem1
    fstsw   %ax
    sahf
    jp      1b
    fstp    %st(1)
    ret
END SYM(cgc_remainder)

ENTER SYM(cgc_log)
SYM(cgc_logl):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_logf):
    flds    4(%esp)
    jmp     1f
SYM(cgc_log):
    fldl    4(%esp)
1:
    fldln2
    fxch    %st(1)
    fyl2x
    ret
END SYM(cgc_log)

ENTER SYM(cgc_log10)
SYM(cgc_log10l):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_log10f):
    flds    4(%esp)
    jmp     1f
SYM(cgc_log10):
    fldl    4(%esp)
1:
    fldlg2
    fxch    %st(1)
    fyl2x
    ret
END SYM(cgc_log10)

ENTER SYM(cgc_significand)
SYM(cgc_significandl):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_significandf):
    flds    4(%esp)
    jmp     1f
SYM(cgc_significand):
    fldl    4(%esp)
1:
    fxtract
    fstp    %st(1)
    ret
END SYM(cgc_significand)

ENTER SYM(cgc_scalbn)
SYM(cgc_scalbnl):
    fildl   16(%esp)
    fldt    4(%esp)
    jmp     1f
SYM(cgc_scalbnf):
    fildl   8(%esp)
    flds    4(%esp)
    jmp     1f
SYM(cgc_scalbn):
    fildl   12(%esp)
    fldl    4(%esp)
1:
    fscale
    fstp    %st(1)
    ret
END SYM(cgc_scalbn)

ENTER SYM(cgc_scalbln)
SYM(cgc_scalblnl):
    jmp     SYM(cgc_scalbnl)
SYM(cgc_scalblnf):
    jmp     SYM(cgc_scalbnf)
SYM(cgc_scalbln):
    jmp     SYM(cgc_scalbn)
END SYM(cgc_scalbln)

ENTER SYM(cgc_rint)
SYM(cgc_rintl):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_rintf):
    flds    4(%esp)
    jmp     1f
SYM(cgc_rint):
    fldl    4(%esp)
1:
    frndint
    ret
END SYM(cgc_rint)

ENTER SYM(cgc_sqrt)
SYM(cgc_sqrtl):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_sqrtf):
    flds    4(%esp)
    jmp     1f
SYM(cgc_sqrt):
    fldl    4(%esp)
1:
    fsqrt
    ret
END SYM(cgc_sqrt)

ENTER SYM(cgc_fabs)
SYM(cgc_fabsl):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_fabsf):
    flds    4(%esp)
    jmp     1f
SYM(cgc_fabs):
    fldl    4(%esp)
1:
    fabs
    ret
END SYM(cgc_fabs)

ENTER SYM(cgc_atan2)
SYM(cgc_atan2l):
    fldt    4(%esp)
    fldt    16(%esp)
    jmp     1f
SYM(cgc_atan2f):
    flds    4(%esp)
    flds    8(%esp)
    jmp     1f
SYM(cgc_atan2):
    fldl    4(%esp)
    fldl    12(%esp)
1:
    fpatan
    ret
END SYM(cgc_atan2)

ENTER SYM(cgc_log2)
SYM(cgc_log2l):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_log2f):
    flds    4(%esp)
    jmp     1f
SYM(cgc_log2):
    fldl    4(%esp)
1:
    fld1
    fxch
    fyl2x
    ret
END SYM(cgc_log2)

ENTER SYM(cgc_exp2)
    .type    SYM(cgc_exp2x), @function
SYM(cgc_exp2l):
    fldt    4(%esp)
    jmp     SYM(cgc_exp2x)
SYM(cgc_exp2f):
    flds    4(%esp)
    jmp     SYM(cgc_exp2x)
SYM(cgc_exp2):
    fldl    4(%esp)
SYM(cgc_exp2x):
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
END SYM(cgc_exp2)
.size    SYM(cgc_exp2x), . - SYM(cgc_exp2x)

ENTER SYM(cgc_pow)
SYM(cgc_powl):
    fldt    16(%esp)
    fldt    4(%esp)
    jmp     1f
SYM(cgc_powf):
    flds    8(%esp)
    flds    4(%esp)
    jmp     1f
SYM(cgc_pow):
    fldl    12(%esp)
    fldl    4(%esp)
1:
    fyl2x
    jmp     SYM(cgc_exp2x)
END SYM(cgc_pow)

ENTER SYM(cgc_exp)
SYM(cgc_expl):
    fldt    4(%esp)
    jmp     1f
SYM(cgc_expf):
    flds    4(%esp)
    jmp     1f
SYM(cgc_exp):
    fldl    4(%esp)
1:
    fldl2e
    fmulp
    jmp     SYM(cgc_exp2x)
END SYM(cgc_exp)

.global SYM(cgc_setjmp)
.type SYM(cgc_setjmp), @function
SYM(cgc_setjmp):
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
.size SYM(cgc_setjmp), . - SYM(cgc_setjmp)

.global SYM(cgc_longjmp)
.type SYM(cgc_longjmp), @function
SYM(cgc_longjmp):
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
.size SYM(cgc_longjmp), . - SYM(cgc_longjmp)
