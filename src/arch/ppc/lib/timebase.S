/* $Id: timebase.S,v 1.1 2003/04/15 18:29:11 rminnich Exp $ */
/* Copyright 1999-2000  AG Electronics Ltd. */
/* This code is distributed without warranty under the GPL v2 (see COPYING) */

	.text
	.globl	_timebase
_timebase:
	mftbu	3
	mftb    4
	mftbu	5
	cmpw	3, 5
	bne	_timebase
	blr
