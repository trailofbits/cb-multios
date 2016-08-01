
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

	ENTER	sin
sinl:	fldt	4(%esp)
	jmp	1f
sinf:	flds	4(%esp)
	jmp	1f
sin:
	fldl	4(%esp)
1:	fsin
	fnstsw	%ax
	sahf
	jp	2f
	ret
2:	call	twopi_rem
	fsin
	ret
	END	sin

	ENTER	cos
cosl:	fldt	4(%esp)
	jmp	1f
cosf:	flds	4(%esp)
	jmp	1f
cos:	fldl	4(%esp)
1:	fcos
	fnstsw	%ax
	sahf
	jp	2f
	ret
2:	call	twopi_rem
	fcos
	ret
	END	cos

	ENTER	tan
tanl:	fldt	4(%esp)
	jmp	1f
tanf:	flds	4(%esp)
	jmp	1f
tan:	fldl	4(%esp)
1:	fptan
	fnstsw	%ax
	sahf
	jp	2f
	fstp	%st(0)
	ret
2:	call	twopi_rem
	fptan
	fstp	%st(0)
	ret
	END	tan

	.type twopi_rem, @function
twopi_rem:
	fldpi
	fadd	%st(0)
	fxch	%st(1)
1:	fprem
	fnstsw	%ax
	sahf
	jp	1b
	fstp	%st(1)
	ret
	.size	twopi_rem, . - twopi_rem

	ENTER	remainder
remainderl:
	fldt	16(%esp)
	fldt	4(%esp)
	jmp	1f
remainderf:
	flds	8(%esp)
	flds	4(%esp)
	jmp	1f
remainder:
	fldl	12(%esp)
	fldl	4(%esp)
1:	fprem1
	fstsw	%ax
	sahf
	jp	1b
	fstp	%st(1)
	ret
	END	remainder

	ENTER	log
logl:	fldt	4(%esp)
	jmp	1f
logf:	flds	4(%esp)
	jmp	1f
log:	fldl	4(%esp)
1:	fldln2
	fxch	%st(1)
	fyl2x
	ret
	END	log

	ENTER	log10
log10l:	fldt	4(%esp)
	jmp	1f
log10f:	flds	4(%esp)
	jmp	1f
log10:	fldl	4(%esp)
1:	fldlg2
	fxch	%st(1)
	fyl2x
	ret
	END	log10

	ENTER	significand
significandl:
	fldt	4(%esp)
	jmp	1f
significandf:
	flds	4(%esp)
	jmp	1f
significand:
	fldl	4(%esp)
1:	fxtract
	fstp	%st(1)
	ret
	END	significand

	ENTER	scalbn
	ENTER	scalbln
scalbnl:
scalblnl:
	fildl	16(%esp)
	fldt	4(%esp)
	jmp	1f
scalbnf:
scalblnf:
	fildl	8(%esp)
	flds	4(%esp)
	jmp	1f
scalbn:
scalbln:
	fildl	12(%esp)
	fldl	4(%esp)
1:	fscale
	fstp	%st(1)
	ret
	END	scalbn
	END	scalbln

	ENTER	rint
rintl:	fldt	4(%esp)
	jmp	1f
rintf:	flds	4(%esp)
	jmp	1f
rint:	fldl	4(%esp)
1:	frndint
	ret
	END	rint

	ENTER	sqrt
sqrtl:	fldt	4(%esp)
	jmp	1f
sqrtf:	flds	4(%esp)
	jmp	1f
sqrt:	fldl	4(%esp)
1:	fsqrt
	ret
	END	sqrt

	ENTER	fabs
fabsl:	fldt	4(%esp)
	jmp	1f
fabsf:	flds	4(%esp)
	jmp	1f
fabs:	fldl	4(%esp)
1:	fabs
	ret
	END	fabs

	ENTER	atan2
atan2l:	fldt	4(%esp)
	fldt	16(%esp)
	jmp	1f
atan2f:	flds	4(%esp)
	flds	8(%esp)
	jmp	1f
atan2:	fldl	4(%esp)
	fldl	12(%esp)
1:	fpatan
	ret
	END	atan2

	ENTER	log2
log2l:	fldt	4(%esp)
	jmp	1f
log2f:	flds	4(%esp)
	jmp	1f
log2:	fldl	4(%esp)
1:	fld1
	fxch
	fyl2x
	ret
	END	log2

	ENTER	exp2
	.type	exp2x, @function
exp2l:	fldt	4(%esp)
	jmp	exp2x
exp2f:	flds	4(%esp)
	jmp	exp2x
exp2:	fldl	4(%esp)
exp2x:	fld	%st(0)
	frndint
	fsubr	%st,%st(1)
	fxch
	f2xm1
	fld1
	faddp
	fscale
	fstp	%st(1)
	ret
	END	exp2
	.size	exp2x, . - exp2x

	ENTER	pow
powl:	fldt	16(%esp)
	fldt	4(%esp)
	jmp	1f
powf:	flds	8(%esp)
	flds	4(%esp)
	jmp	1f
pow:	fldl	12(%esp)
	fldl	4(%esp)
1:	fyl2x
	jmp	exp2x
	END	pow

	ENTER	exp
expl:	fldt	4(%esp)
	jmp	1f
expf:	flds	4(%esp)
	jmp	1f
exp:	fldl	4(%esp)
1:	fldl2e
	fmulp
	jmp	exp2x
	END	exp

    .global setjmp
    .type setjmp, @function
setjmp:
	movl	4(%esp), %ecx
	movl	0(%esp), %edx
	movl	%edx, 0(%ecx)
	movl	%ebx, 4(%ecx)
	movl	%esp, 8(%ecx)
	movl	%ebp, 12(%ecx)
	movl	%esi, 16(%ecx)
	movl	%edi, 20(%ecx)
	xorl	%eax, %eax
	ret
    .size setjmp, . - setjmp

	.global longjmp
	.type longjmp, @function
longjmp:
	movl	4(%esp), %edx
	movl	8(%esp), %eax
	movl	0(%edx), %ecx
	movl	4(%edx), %ebx
	movl	8(%edx), %esp
	movl	12(%edx), %ebp
	movl	16(%edx), %esi
	movl	20(%edx), %edi
	testl	%eax, %eax
	jnz	1f
	incl	%eax
1:	movl	%ecx, 0(%esp)
	ret
    .size longjmp, . - longjmp