#ifndef CPU_DC21264_H
#define CPU_DC21264_H

/*
 * src/cpu/ev6/dc21264.h
 *
 * Copyright (C) 2001 Linux Networx
 *
 */


/* 
 * Ebox IPR scorboard bits 
 * =========================================================
 */
#define EV6_SCB__CC		(1 << 5)
#define EV6_SCB__CC_CTL		(1 << 5)
#define EV6_SCB__VA		((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))
#define EV6_SCB__VA_CTL		(1 << 5)
#define EV6_SCB__VA_FORM	((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))

/* 
 * Ibox IPR scorboard bits 
 * =========================================================
 */
#define EV6_SCB__ITB_TAG	(1 << 6)
#define EV6_SCB__ITB_PTE	((1 << 0) | (1 << 4))
#define EV6_SCB__ITB_IAP	(1 << 4)
#define EV6_SCB__ITB_IA		(1 << 4)
#define EV6_SCB__ITB_IS		((1 << 4) | (1 << 6))
#define EV6_SCB__EXC_ADDR	0
#define EV6_SCB__IVA_FORM	(1 << 5)
#define EV6_SCB__CM		(1 << 4)
#define EV6_SCB__IER		(1 << 4)
#define EV6_SCB__IER_CM		(1 << 4)
#define EV6_SCB__SIRR		(1 << 4)
#define EV6_SCB__ISUM		0
#define EV6_SCB__HW_INT_CLR	(1 << 4)
#define EV6_SCB__EXC_SUM	0
#define EV6_SCB__PAL_BASE	(1 << 4)
#define EV6_SCB__I_CTL		(1 << 4)
#define EV6_SCB__I_STAT		(1 << 4)
#define EV6_SCB__IC_FLUSH	(1 << 4)
#define EV6_SCB__IC_FLUSH_ASM	(1 << 4)
#define EV6_SCB__CLR_MAP	((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))
#define EV6_SCB__SLEEP		((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))
#define EV6_SCB__PCTX		(1 << 4)
#define EV6_SCB__PCTR_CTL	(1 << 4)

/* 
 * Mbox IPR scorboard bits 
 * =========================================================
 */
#define EV6_SCB__DTB_TAG0	((1 << 2) | (1 << 6))
#define EV6_SCB__DTB_TAG1	((1 << 1) | (1 << 5))
#define EV6_SCB__DTB_PTE0	((1 << 0) | (1 << 4))
#define EV6_SCB__DTB_PTE1	((1 << 3) | (1 << 7))
#define EV6_SCB__DTB_ALT_MODE	(1 << 6)
#define EV6_SCB__DTB_IAP	(1 << 7)
#define EV6_SCB__DTB_IA		(1 << 7)
#define EV6_SCB__DTB_IS0	(1 << 6)
#define EV6_SCB__DTB_IS1	(1 << 7)
#define EV6_SCB__DTB_ASN0	(1 << 4)
#define EV6_SCB__DTB_ASN1	(1 << 7)
#define EV6_SCB__MM_STAT	0
#define EV6_SCB__M_CTL		(1 << 6)
#define EV6_SCB__DC_CTL		(1 << 6)
#define EV6_SCB__DC_STAT	(1 << 6)

/* 
 * Cbox IPR scorboard bits 
 * =========================================================
 */

#define EV6_SCB__C_DATA		(1 << 6)
#define EV6_SCB__C_SHFT		(1 << 6)

/* 
 * Ebox IPRs 
 * =========================================================
 */
#define EV6__CC			((0xC0 << 8) | EV6_SCB__CC)
#define EV6__CC_CTL		((0xC1 << 8) | EV6_SCB__CC_CTL) 
#define EV6__VA			((0xC2 << 8) | EV6_SCB__VA)
#define EV6__VA_CTL		((0xC4 << 8) | EV6_SCB__VA_CTL)
#define EV6__VA_FORM		((0xC3 << 8) | EV6_SCB__VA_FORM)

/* 
 * Ibox IPRs 
 * =========================================================
 */
#define EV6__ITB_TAG		((0x00 << 8) | EV6_SCB__ITB_TAG)
#define EV6__ITB_PTE		((0x01 << 8) | EV6_SCB__ITB_PTE)
#define EV6__ITB_IAP		((0x02 << 8) | EV6_SCB__ITB_IAP)
#define EV6__ITB_IA		((0x03 << 8) | EV6_SCB__ITB_IA)
#define EV6__ITB_IS		((0x04 << 8) | EV6_SCB__ITB_IS)
#define EV6__EXC_ADDR		((0x06 << 8) | EV6_SCB__EXC_ADDR)
#define EV6__IVA_FORM		((0x07 << 8) | EV6_SCB__IVA_FORM)
#define EV6__CM			((0x09 << 8) | EV6_SCB__CM)
#define EV6__IER		((0x0A << 8) | EV6_SCB__IER)
#define EV6__IER_CM		((0x0B << 8) | EV6_SCB__IER_CM)
#define EV6__SIRR		((0x0C << 8) | EV6_SCB__SIRR)
#define EV6__ISUM		((0x0D << 8) | EV6_SCB__ISUM)
#define EV6__HW_INT_CLR		((0x0E << 8) | EV6_SCB__HW_INT_CLR)
#define EV6__EXC_SUM		((0x0F << 8) | EV6_SCB__EXC_SUM)
#define EV6__PAL_BASE		((0x10 << 8) | EV6_SCB__PAL_BASE)
#define EV6__I_CTL		((0x11 << 8) | EV6_SCB__I_CTL)
#define EV6__I_STAT		((0x16 << 8) | EV6_SCB__I_STAT)
#define EV6__IC_FLUSH		((0x13 << 8) | EV6_SCB__IC_FLUSH)
#define EV6__IC_FLUSH_ASM	((0x12 << 8) | EV6_SCB__IC_FLUSH_ASM)
#define EV6__CLR_MAP		((0x15 << 8) | EV6_SCB__CLR_MAP)
#define EV6__SLEEP		((0x17 << 8) | EV6_SCB__SLEEP)
#define EV6__PCTX		((0x5f << 8) | EV6_SCB__PCTX)
#define EV6__PCTR_CTL		((0x14 << 8) | EV6_SCB__PCTR_CTL)

/* 
 * Mbox IPRs 
 * =========================================================
 */
#define EV6__DTB_TAG0		((0x20 << 8) | EV6_SCB__DTB_TAG0)
#define EV6__DTB_TAG1		((0xA0 << 8) | EV6_SCB__DTB_TAG1)
#define EV6__DTB_PTE0		((0x21 << 8) | EV6_SCB__DTB_PTE0)
#define EV6__DTB_PTE1		((0xA1 << 8) | EV6_SCB__DTB_PTE1)
#define EV6__DTB_ALT_MODE	((0x26 << 8) | EV6_SCB__DTB_ALT_MODE)
#define EV6__DTB_IAP		((0xA2 << 8) | EV6_SCB__DTB_IAP)
#define EV6__DTB_IA		((0xA3 << 8) | EV6_SCB__DTB_IA)
#define EV6__DTB_IS0		((0x24 << 8) | EV6_SCB__DTB_IS0)
#define EV6__DTB_IS1		((0xA4 << 8) | EV6_SCB__DTB_IS1)
#define EV6__DTB_ASN0		((0x25 << 8) | EV6_SCB__DTB_ASN0)
#define EV6__DTB_ASN1		((0xA5 << 8) | EV6_SCB__DTB_ASN1)
#define EV6__MM_STAT		((0x27 << 8) | EV6_SCB__MM_STAT)
#define EV6__M_CTL		((0x28 << 8) | EV6_SCB__M_CTL)
#define EV6__DC_CTL		((0x29 << 8) | EV6_SCB__DC_CTL)
#define EV6__DC_STAT		((0x2A << 8) | EV6_SCB__DC_STAT)

/* 
 * Cbox IPRs 
 * =========================================================
 */
#define EV6__C_DATA		((0x2B << 8) | EV6_SCB__C_DATA)
#define EV6__C_SHFT		((0x2C << 8) | EV6_SCB__C_SHFT)

/* 
 * Ebox IPR fields 
 * =========================================================
 */

/* EV6__CC */
#define EV6__CC__COUNTER__S	0
#define EV6__CC__COUNTER__V	32
#define EV6__CC__COUNTER__M	((1 << EV6__CC__COUNTER__V) -1)

#define EV6__CC__OFFSET__S	32
#define EV6__CC__OFFSET__V	32
#define EV6__CC__OFFSET__M	((1 << EV6__CC__OFFSET__V) -1)

/* EV6__CC_CTL */
#define EV6__CC_CTL__COUNTER__S	4
#define EV6__CC_CTL__COUNTER__V	1
#define EV6__CC_CTL__COUNTER__M	((1 << EV6__CC_CTL__COUNTER__V) -1)

#define EV6__CC_CTL__CC_ENA__S	32
#define EV6__CC_CTL__CC_ENA__V	28
#define EV6__CC_CTL__CC_ENA__M	((1 << EV6__CC_CTL__CC_ENA__V) -1)

/* EV6__VA (no sub fields) */

/* EV6__VA_CTL */
#define EV6__VA_CTL__B_ENDIAN__S	0
#define EV6__VA_CTL__B_ENDIAN__V	1
#define EV6__VA_CTL__B_ENDIAN__M	((1 << EV6__VA_CTL__B_ENDIAN__V) -1)
#define EV6__VA_CTL__VA_48__S		1
#define EV6__VA_CTL__VA_48__V		1
#define EV6__VA_CTL__VA_48__M		((1 << EV6__VA_CTL__VA_48__V) -1)
#define EV6__VA_CTL__VA_FORM_32__S	2
#define EV6__VA_CTL__VA_FORM_32__V	1
#define EV6__VA_CTL__VA_FORM_32__M	((1 << EV6__VA_CTL__VA_FORM32__V) -1)
#define EV6__VA_CTL__VPTB__S		30
#define EV6__VA_CTL__VPTB__V		34
#define EV6__VA_CTL__VPTB__M		((1 << EV6__VA_CTL__VPTB__V) -1)

/* EV6__VA_FORM (no sub fields) */

/* 
 * Ibox IPR fields 
 * =========================================================
 */

/* EV6__ITB_TAG (no subfields) */

/* EV6__ITB_PTE */
#define EV6__ITB_PTE__ASM__S	4
#define EV6__ITB_PTE__ASM__V	1
#define EV6__ITB_PTE__ASM__M	((1 << EV6__ITB_PTE__ASM__V) - 1)
#define EV6__ITB_PTE__GH__S	5
#define EV6__ITB_PTE__GH__V	2
#define EV6__ITB_PTE__GH__M	((1 << EV6__ITB_PTE__GH__V) - 1)
#define EV6__ITB_PTE__KRE__S	8
#define EV6__ITB_PTE__KRE__V	1
#define EV6__ITB_PTE__KRE__M	((1 << EV6__ITB_PTE__KRE__V) - 1)
#define EV6__ITB_PTE__ERE__S	9
#define EV6__ITB_PTE__ERE__V	1
#define EV6__ITB_PTE__ERE__M	((1 << EV6__ITB_PTE__ERE__V) - 1)
#define EV6__ITB_PTE__SRE__S	10
#define EV6__ITB_PTE__SRE__V	1
#define EV6__ITB_PTE__SRE__M	((1 << EV6__ITB_PTE__SRE__V) - 1)
#define EV6__ITB_PTE__URE__S	11
#define EV6__ITB_PTE__URE__V	1
#define EV6__ITB_PTE__URE__M	((1 << EV6__ITB_PTE__URE__V) - 1)
#define EV6__ITB_PTE__PFN__S	13
#define EV6__ITB_PTE__PFN__V	31
#define EV6__ITB_PTE__PFN__M	((1 << EV6__ITB_PTE__PFN__V) - 1)

/* EV6__ITB_IAP (no subfields) */
/* EV6__ITB_IA (no subfields) */
/* EV6__ITB_IS (no subfields */

/* EV6__EXC_ADDR */
#define EV6__EXC_ADDR__PAL__S	0
#define EV6__EXC_ADDR__PAL__V	1
#define EV6__EXC_ADDR__PAL__M	((1 << EV6__EXC_ADDR__PAL__V) -1)
#define EV6__EXC_ADDR__PC__S	2
#define EV6__EXC_ADDR__PC__V	2
#define EV6__EXC_ADDR__PC__M	((1 << EV6__EXC_ADDR__PC__V) -1)

/* EV6__IVA_FORM (no subfields) */

/* EV6__IER_CM */
#define EV6__IER_CM__CM__S	3
#define EV6__IER_CM__CM__V	2
#define EV6__IER_CM__CM__M	((1 << EV6__IER_CM__CM__M) -1)
#define EV6__IER_CM__ASTEN__S	13
#define EV6__IER_CM__ASTEN__V	1
#define EV6__IER_CM__ASTEN__M	((1 << EV6__IER_CM__ASTEN__M) -1)
#define EV6__IER_CM__SIEN__S	14
#define EV6__IER_CM__SIEN__V	15
#define EV6__IER_CM__SIEN__M	((1 << EV6__IER_CM__SIEN__M) -1)
#define EV6__IER_CM__PCEN__S	29
#define EV6__IER_CM__PCEN__V	2
#define EV6__IER_CM__PCEN__M	((1 << EV6__IER_CM__PCEN__M) -1)
#define EV6__IER_CM__CREN__S	31
#define EV6__IER_CM__CREN__V	1
#define EV6__IER_CM__CREN__M	((1 << EV6__IER_CM__CREN__M) -1)
#define EV6__IER_CM__SLEN__S	32
#define EV6__IER_CM__SLEN__V	1
#define EV6__IER_CM__SLEN__M	((1 << EV6__IER_CM__SLEN__M) -1)
#define EV6__IER_CM__EIEN__S	33
#define EV6__IER_CM__EIEN__V	6
#define EV6__IER_CM__EIEN__M	((1 << EV6__IER_CM__EIEN__M) -1)

/* EV6__SIRR */
#define EV6__SIRR__SIR__S	14
#define EV6__SIRR__SIR__V	15
#define EV6__SIRR__SIR__M	((1 << EV6__SIRR__SIR__V) -1)


/* EV6__ISUM */
#define EV6__ISUM__ASTK__S	3
#define EV6__ISUM__ASTK__V	1
#define EV6__ISUM__ASTK__M	((1 << EV6__ISUM__ASTK__V) -1)
#define EV6__ISUM__ASTE__S	4
#define EV6__ISUM__ASTE__V	4
#define EV6__ISUM__ASTE__M	((1 << EV6__ISUM__ASTE__V) -1)
#define EV6__ISUM__ASTS__S	1
#define EV6__ISUM__ASTS__V	9
#define EV6__ISUM__ASTS__M	((1 << EV6__ISUM__ASTS__V) -1)
#define EV6__ISUM__ASTU__S	10
#define EV6__ISUM__ASTU__V	1
#define EV6__ISUM__ASTU__M	((1 << EV6__ISUM__ASTU__V) -1)
#define EV6__ISUM__SI__S	14
#define EV6__ISUM__SI__V	15
#define EV6__ISUM__SI__M	((1 << EV6__ISUM__SI__V) -1)
#define EV6__ISUM__PC__S	29
#define EV6__ISUM__PC__V	2
#define EV6__ISUM__PC__M	((1 << EV6__ISUM__PC__V) -1)
#define EV6__ISUM__CR__S	31
#define EV6__ISUM__CR__V	1
#define EV6__ISUM__CR__M	((1 << EV6__ISUM__CR__V) -1)
#define EV6__ISUM__SL__S	32
#define EV6__ISUM__SL__V	1
#define EV6__ISUM__SL__M	((1 << EV6__ISUM__SL__V) -1)
#define EV6__ISUM__EI__S	33
#define EV6__ISUM__EI__V	6
#define EV6__ISUM__EI__M	((1 << EV6__ISUM__EI__V) -1)

/* EV6__HW_INT_CLR */
#define EV6__HW_INT_CLR__FBTP__S	26
#define EV6__HW_INT_CLR__FBTP__V	1
#define EV6__HW_INT_CLR__FBTP__M	((1 << EV6__HW_INT_CLR__FBTP__V) -1)
#define EV6__HW_INT_CLR__MCHK_D__S	28
#define EV6__HW_INT_CLR__MCHK_D__V	1
#define EV6__HW_INT_CLR__MCHK_D__M	((1 << EV6__HW_INT_CLR__MCHK_D__V) -1)
#define EV6__HW_INT_CLR__PC__S		29
#define EV6__HW_INT_CLR__PC__V		2
#define EV6__HW_INT_CLR__PC__M		((1 << EV6__HW_INT_CLR__PC__V) -1)
#define EV6__HW_INT_CLR__CR__S		31
#define EV6__HW_INT_CLR__CR__V		1
#define EV6__HW_INT_CLR__CR__M		((1 << EV6__HW_INT_CLR__CR__V) -1)
#define EV6__HW_INT_CLR__SL__S		32
#define EV6__HW_INT_CLR__SL__V		1
#define EV6__HW_INT_CLR__SL__M		((1 << EV6__HW_INT_CLR__SL__V) -1)

/* EV6__EXC_SUM */
#define EV6__EXC_SUM__SWC__S		0
#define EV6__EXC_SUM__SWC__V		1
#define EV6__EXC_SUM__SWC__M		((1 << EV6__EXC_SUM__SWC__V) -1)
#define EV6__EXC_SUM__INV__S		1
#define EV6__EXC_SUM__INV__V		1
#define EV6__EXC_SUM__INV__M		((1 << EV6__EXC_SUM__INV__V) -1)
#define EV6__EXC_SUM__DZE__S		2
#define EV6__EXC_SUM__DZE__V		1
#define EV6__EXC_SUM__DZE__M		((1 << EV6__EXC_SUM__DZE__V) -1)
#define EV6__EXC_SUM__FOV__S		3
#define EV6__EXC_SUM__FOV__V		1
#define EV6__EXC_SUM__FOV__M		((1 << EV6__EXC_SUM__FOV__V) -1)
#define EV6__EXC_SUM__UNF__S		4
#define EV6__EXC_SUM__UNF__V		1
#define EV6__EXC_SUM__UNF__M		((1 << EV6__EXC_SUM__UNF__V) -1)
#define EV6__EXC_SUM__INE__S		5
#define EV6__EXC_SUM__INE__V		1
#define EV6__EXC_SUM__INE__M		((1 << EV6__EXC_SUM__INE__V) -1)
#define EV6__EXC_SUM__IOV__S		6
#define EV6__EXC_SUM__IOV__V		1
#define EV6__EXC_SUM__IOV__M		((1 << EV6__EXC_SUM__IOV__V) -1)
#define EV6__EXC_SUM__INT__S		7
#define EV6__EXC_SUM__INT__V		1
#define EV6__EXC_SUM__INT__M		((1 << EV6__EXC_SUM__INT__V) -1)
#define EV6__EXC_SUM__REG__S		8
#define EV6__EXC_SUM__REG__V		5
#define EV6__EXC_SUM__REG__M		((1 << EV6__EXC_SUM__REG__V) -1)
#define EV6__EXC_SUM__BAD_IVA__S	13
#define EV6__EXC_SUM__BAD_IVA__V	1
#define EV6__EXC_SUM__BAD_IVA__M	((1 << EV6__EXC_SUM__BAD_IVA__V) -1)
#define EV6__EXC_SUM__PC_OVFL__S	41
#define EV6__EXC_SUM__PC_OVFL__V	1
#define EV6__EXC_SUM__PC_OVFL__M	((1 << EV6__EXC_SUM__PC_OVFL__V) -1)
#define EV6__EXC_SUM__SET_INV__S	42
#define EV6__EXC_SUM__SET_INV__V	1
#define EV6__EXC_SUM__SET_INV__M	((1 << EV6__EXC_SUM__SET_INV__V) -1)
#define EV6__EXC_SUM__SET_DZE__S	43
#define EV6__EXC_SUM__SET_DZE__V	1
#define EV6__EXC_SUM__SET_DZE__M	((1 << EV6__EXC_SUM__SET_DZE__V) -1)
#define EV6__EXC_SUM__SET_OVF__S	44
#define EV6__EXC_SUM__SET_OVF__V	1
#define EV6__EXC_SUM__SET_OVF__M	((1 << EV6__EXC_SUM__SET_OVF__V) -1)
#define EV6__EXC_SUM__SET_UNF__S	45
#define EV6__EXC_SUM__SET_UNF__V	1
#define EV6__EXC_SUM__SET_UNF__M	((1 << EV6__EXC_SUM__SET_UNF__V) -1)
#define EV6__EXC_SUM__SET_INE__S	46
#define EV6__EXC_SUM__SET_INE__V	1
#define EV6__EXC_SUM__SET_INE__M	((1 << EV6__EXC_SUM__SET_INE__V) -1)
#define EV6__EXC_SUM__SET_IOV__S	47
#define EV6__EXC_SUM__SET_IOV__V	1
#define EV6__EXC_SUM__SET_IOV__M	((1 << EV6__EXC_SUM__SET_IOV__V) -1)
#define EV6__EXC_SUM__SEXT__S		48
#define EV6__EXC_SUM__SEXT__V		16
#define EV6__EXC_SUM__SEXT__M		((1 << EV6__EXC_SUM__SEXT__V) -1)

/* EV6__PAL_BASE (no subfields) */

/* EV6__I_CTL */
#define EV6__I_CTL__SPCE__S		0
#define EV6__I_CTL__SPCE__V		1
#define EV6__I_CTL__SPCE__M		((1 << EV6__I_CTL__SPCE__V) -1)
#define EV6__I_CTL__IC_EN__S		1
#define EV6__I_CTL__IC_EN__V		2
#define EV6__I_CTL__IC_EN__M		((1 << EV6__I_CTL__IC_EN__V) -1)
#define EV6__I_CTL__SPE__S		3
#define EV6__I_CTL__SPE__V		3
#define EV6__I_CTL__SPE__M		((1 << EV6__I_CTL__SPE__V) -1)
#define EV6__I_CTL__SDE__S		6
#define EV6__I_CTL__SDE__V		2
#define EV6__I_CTL__SDE__M		((1 << EV6__I_CTL__SDE__V) -1)
#define EV6__I_CTL__SBE__S		8
#define EV6__I_CTL__SBE__V		2
#define EV6__I_CTL__SBE__M		((1 << EV6__I_CTL__SBE__V) -1)
#define EV6__I_CTL__BP_MODE__S		10
#define EV6__I_CTL__BP_MODE__V		2
#define EV6__I_CTL__BP_MODE__M		((1 << EV6__I_CTL__BP_MODE__V) -1)
#define EV6__I_CTL__HWE__S		12
#define EV6__I_CTL__HWE__V		1
#define EV6__I_CTL__HWE__M		((1 << EV6__I_CTL__HWE__V) -1)
#define EV6__I_CTL__SL_XMIT__S		13
#define EV6__I_CTL__SL_XMIT__V		1
#define EV6__I_CTL__SL_XMIT__M		((1 << EV6__I_CTL__SL_XMIT__V) -1)
#define EV6__I_CTL__SL_RCV__S		14
#define EV6__I_CTL__SL_RCV__V		1
#define EV6__I_CTL__SL_RCV__M		((1 << EV6__I_CTL__SL_RCV__V) -1)
#define EV6__I_CTL__VA_48__S		15
#define EV6__I_CTL__VA_48__V		1
#define EV6__I_CTL__VA_48__M		((1 << EV6__I_CTL__VA_48__V) -1)
#define EV6__I_CTL__VA_FORM_32__S	16
#define EV6__I_CTL__VA_FORM_32__V	1
#define EV6__I_CTL__VA_FORM_32__M	((1 << EV6__I_CTL__VA_FORM_32__V) -1)
#define EV6__I_CTL__SINGLE_ISSUE_H__S	17
#define EV6__I_CTL__SINGLE_ISSUE_H__V	1
#define EV6__I_CTL__SINGLE_ISSUE_H__M	((1 << EV6__I_CTL__SINGLE_ISSUE_H__V) -1)
#define EV6__I_CTL__PCT0_EN__S		18
#define EV6__I_CTL__PCT0_EN__V		1
#define EV6__I_CTL__PCT0_EN__M		((1 << EV6__I_CTL__PCT0_EN__V) -1)
#define EV6__I_CTL__PCT1_EN__S		19
#define EV6__I_CTL__PCT1_EN__V		1
#define EV6__I_CTL__PCT1_EN__M		((1 << EV6__I_CTL__PCT1_EN__V) -1)
#define EV6__I_CTL__CALL_PAL_R23__S	20
#define EV6__I_CTL__CALL_PAL_R23__V	1
#define EV6__I_CTL__CALL_PAL_R23__M	((1 << EV6__I_CTL__CALL_PAL_R23__V) -1)
#define EV6__I_CTL__MCHK_EN__S		21
#define EV6__I_CTL__MCHK_EN__V		1
#define EV6__I_CTL__MCHK_EN__M		((1 << EV6__I_CTL__MCHK_EN__V) -1)
#define EV6__I_CTL__TB_MB_EN__S		22
#define EV6__I_CTL__TB_MB_EN__V		1
#define EV6__I_CTL__TB_MB_EN__M		((1 << EV6__I_CTL__TB_MB_EN__V) -1)
#define EV6__I_CTL__BIST_FAIL__S	23
#define EV6__I_CTL__BIST_FAIL__V	1
#define EV6__I_CTL__BIST_FAIL__M	((1 << EV6__I_CTL__BIST_FAIL__V) -1)
#define EV6__I_CTL__CHIP_ID__S		24
#define EV6__I_CTL__CHIP_ID__V		6
#define EV6__I_CTL__CHIP_ID__M		((1 << EV6__I_CTL__CHIP_ID__V) -1)
#define EV6__I_CTL__VPTB__S		30
#define EV6__I_CTL__VPTB__V		18
#define EV6__I_CTL__VPTB__M		((1 << EV6__I_CTL__VPTB__V) -1)

/* EV6__I_STAT */
#define EV6__I_STAT__TPE__S		29
#define EV6__I_STAT__TPE__V		1
#define EV6__I_STAT__TPE__M		((1 << EV6__I_STAT__TPE__V) -1)
#define EV6__I_STAT__DPE__S		30
#define EV6__I_STAT__DPE__V		1
#define EV6__I_STAT__DPE__M		((1 << EV6__I_STAT__DPE__V) -1)

/* EV6__IC_FLUSH (no subfields)  */
/* EV6__IC_FLUSH_ASM (no subfields) */
/* EV6__CLR_MAP (no subfields */
/* EV6__SLEEP (no subfields */

/* EV6__PCTX */
#define EV6__PCTX__PPCE__S	1
#define EV6__PCTX__PPCE__V	1
#define EV6__PCTX__PPCE__M	((1 << EV6__PCTX__PPCE__V) -1)
#define EV6__PCTX__FPE__S	2
#define EV6__PCTX__FPE__V	1
#define EV6__PCTX__FPE__M	((1 << EV6__PCTX__FPE__V) -1)
#define EV6__PCTX__ASTER__S	5
#define EV6__PCTX__ASTER__V	4
#define EV6__PCTX__ASTER__M	((1 << EV6__PCTX__ASTER__V) -1)
#define EV6__PCTX__ASTRR__S	9
#define EV6__PCTX__ASTRR__V	4
#define EV6__PCTX__ASTRR__M	((1 << EV6__PCTX__ASTRR__V) -1)
#define EV6__PCTX__ASN__S	39
#define EV6__PCTX__ASN__V	8
#define EV6__PCTX__ASN__M	((1 << EV6__PCTX__ASN__V) -1)


/* EV6__PCTR_CTL */
#define EV6__PCTR_CTL__SL1__S	0
#define EV6__PCTR_CTL__SL1__V	4
#define EV6__PCTR_CTL__SL1__M	((1 << EV6__PCTR_CTL__SL1__V) -1)
#define EV6__PCTR_CTL__SL0__S	4
#define EV6__PCTR_CTL__SL0__V	1
#define EV6__PCTR_CTL__SL0__M	((1 << EV6__PCTR_CTL__SL0__V) -1)
#define EV6__PCTR_CTL__PCTR1__S	6
#define EV6__PCTR_CTL__PCTR1__V	20
#define EV6__PCTR_CTL__PCTR1__M	((1 << EV6__PCTR_CTL__PCTR1__V) -1)
#define EV6__PCTR_CTL__PCTR0__S	28
#define EV6__PCTR_CTL__PCTR0__V	20
#define EV6__PCTR_CTL__PCTR0__M	((1 << EV6__PCTR_CTL__PCTR0__V) -1)

/* 
 * Mbox IPR fields 
 * =========================================================
 */

/* EV6__DTB_TAG0 (no subfields) */
/* EV6__DTB_TAG1 (no subfields) */

/* EV6__DTB_PTE0 */
#define EV6__DTB_PTE0__FOR__S	1
#define EV6__DTB_PTE0__FOR__V	1
#define EV6__DTB_PTE0__FOR__M	((1 << EV6__DTB_PTE0__FOR__V) -1)
#define EV6__DTB_PTE0__FOW__S	2
#define EV6__DTB_PTE0__FOW__V	1
#define EV6__DTB_PTE0__FOW__M	((1 << EV6__DTB_PTE0__FOW__V) -1)
#define EV6__DTB_PTE0__ASM__S	4
#define EV6__DTB_PTE0__ASM__V	1
#define EV6__DTB_PTE0__ASM__M	((1 << EV6__DTB_PTE0__ASM__V) -1)
#define EV6__DTB_PTE0__GH__S	5
#define EV6__DTB_PTE0__GH__V	2
#define EV6__DTB_PTE0__GH__M	((1 << EV6__DTB_PTE0__GH__V) -1)
#define EV6__DTB_PTE0__KRE__S	8
#define EV6__DTB_PTE0__KRE__V	1
#define EV6__DTB_PTE0__KRE__M	((1 << EV6__DTB_PTE0__KRE__V) -1)
#define EV6__DTB_PTE0__ERE__S	9
#define EV6__DTB_PTE0__ERE__V	1
#define EV6__DTB_PTE0__ERE__M	((1 << EV6__DTB_PTE0__ERE__V) -1)
#define EV6__DTB_PTE0__SRE__S	10
#define EV6__DTB_PTE0__SRE__V	1
#define EV6__DTB_PTE0__SRE__M	((1 << EV6__DTB_PTE0__SRE__V) -1)
#define EV6__DTB_PTE0__URE__S	11
#define EV6__DTB_PTE0__URE__V	1
#define EV6__DTB_PTE0__URE__M	((1 << EV6__DTB_PTE0__URE__V) -1)
#define EV6__DTB_PTE0__KWE__S	12
#define EV6__DTB_PTE0__KWE__V	1
#define EV6__DTB_PTE0__KWE__M	((1 << EV6__DTB_PTE0__KEW__V) -1)
#define EV6__DTB_PTE0__EWE__S	13
#define EV6__DTB_PTE0__EWE__V	1
#define EV6__DTB_PTE0__EWE__M	((1 << EV6__DTB_PTE0__EWE__V) -1)
#define EV6__DTB_PTE0__SWE__S	14
#define EV6__DTB_PTE0__SWE__V	1
#define EV6__DTB_PTE0__SWE__M	((1 << EV6__DTB_PTE0__SWE__V) -1)
#define EV6__DTB_PTE0__UWE__S	15
#define EV6__DTB_PTE0__UWE__V	1
#define EV6__DTB_PTE0__UWE__M	((1 << EV6__DTB_PTE0__UWE__V) -1)
#define EV6__DTB_PTE0__PFN__S	32
#define EV6__DTB_PTE0__PFN__V	31
#define EV6__DTB_PTE0__PFN__M	((1 << EV6__DTB_PTE0__PA__V) -1)


/* EV6__DTB_PTE1 */
#define EV6__DTB_PTE1__FOR__S	1
#define EV6__DTB_PTE1__FOR__V	1
#define EV6__DTB_PTE1__FOR__M	((1 << EV6__DTB_PTE1__FOR__V) -1)
#define EV6__DTB_PTE1__FOW__S	2
#define EV6__DTB_PTE1__FOW__V	1
#define EV6__DTB_PTE1__FOW__M	((1 << EV6__DTB_PTE1__FOW__V) -1)
#define EV6__DTB_PTE1__ASM__S	4
#define EV6__DTB_PTE1__ASM__V	1
#define EV6__DTB_PTE1__ASM__M	((1 << EV6__DTB_PTE1__ASM__V) -1)
#define EV6__DTB_PTE1__GH__S	5
#define EV6__DTB_PTE1__GH__V	2
#define EV6__DTB_PTE1__GH__M	((1 << EV6__DTB_PTE1__GH__V) -1)
#define EV6__DTB_PTE1__KRE__S	8
#define EV6__DTB_PTE1__KRE__V	1
#define EV6__DTB_PTE1__KRE__M	((1 << EV6__DTB_PTE1__KRE__V) -1)
#define EV6__DTB_PTE1__ERE__S	9
#define EV6__DTB_PTE1__ERE__V	1
#define EV6__DTB_PTE1__ERE__M	((1 << EV6__DTB_PTE1__ERE__V) -1)
#define EV6__DTB_PTE1__SRE__S	10
#define EV6__DTB_PTE1__SRE__V	1
#define EV6__DTB_PTE1__SRE__M	((1 << EV6__DTB_PTE1__SRE__V) -1)
#define EV6__DTB_PTE1__URE__S	11
#define EV6__DTB_PTE1__URE__V	1
#define EV6__DTB_PTE1__URE__M	((1 << EV6__DTB_PTE1__URE__V) -1)
#define EV6__DTB_PTE1__KWE__S	12
#define EV6__DTB_PTE1__KWE__V	1
#define EV6__DTB_PTE1__KWE__M	((1 << EV6__DTB_PTE1__KEW__V) -1)
#define EV6__DTB_PTE1__EWE__S	13
#define EV6__DTB_PTE1__EWE__V	1
#define EV6__DTB_PTE1__EWE__M	((1 << EV6__DTB_PTE1__EWE__V) -1)
#define EV6__DTB_PTE1__SWE__S	14
#define EV6__DTB_PTE1__SWE__V	1
#define EV6__DTB_PTE1__SWE__M	((1 << EV6__DTB_PTE1__SWE__V) -1)
#define EV6__DTB_PTE1__UWE__S	15
#define EV6__DTB_PTE1__UWE__V	1
#define EV6__DTB_PTE1__UWE__M	((1 << EV6__DTB_PTE1__UWE__V) -1)
#define EV6__DTB_PTE1__PFN__S	32
#define EV6__DTB_PTE1__PFN__V	31
#define EV6__DTB_PTE1__PFN__M	((1 << EV6__DTB_PTE1__PA__V) -1)

/* EV6__ALT_MODE (no subfields) */
/* EV6__DTB_IAP (no subfields) */
/* EV6__DTB_IA (no subfields) */
/* EV6__DTB_IS0 (no subfields) */
/* EV6__DTB_IS1 (no subfields) */

/* EV6__DTB_ASN0 */
#define EV6__DTB_ASN0__ASN__S	56
#define EV6__DTB_ASN0__ASN__V	8
#define EV6__DTB_ASN0__ASN__M	((1 << EV6__DTB_ASN0__ASN__V) -1)

/* EV6__DTB_ASN1 */
#define EV6__DTB_ASN1__ASN__S	56
#define EV6__DTB_ASN1__ASN__V	8
#define EV6__DTB_ASN1__ASN__M	((1 << EV6__DTB_ASN1__ASN__V) -1)

/* EV6__MM_STAT */
#define EV6__MM_STAT__WR__S		0
#define EV6__MM_STAT__WR__V		1
#define EV6__MM_STAT__WR__M		((1 << EV6__MM_STAT__WR__V) -1)
#define EV6__MM_STAT__ACV__S		1
#define EV6__MM_STAT__ACV__V		1
#define EV6__MM_STAT__ACV__M		((1 << EV6__MM_STAT__ACV__V) -1)
#define EV6__MM_STAT__FOR__S		2
#define EV6__MM_STAT__FOR__V		1
#define EV6__MM_STAT__FOR__M		((1 << EV6__MM_STAT__FOR__V) -1)
#define EV6__MM_STAT__FOW__S		3
#define EV6__MM_STAT__FOW__V		1
#define EV6__MM_STAT__FOW__M		((1 << EV6__MM_STAT__FOW__V) -1)
#define EV6__MM_STAT__OPCODE__S		4
#define EV6__MM_STAT__OPCODE__V		6
#define EV6__MM_STAT__OPCODE__M		((1 << EV6__MM_STAT__OPCODE__V) -1)
#define EV6__MM_STAT__DC_TAG_PERR__S	10
#define EV6__MM_STAT__DC_TAG_PERR__V	1
#define EV6__MM_STAT__DC_TAG_PERR__M	((1 << EV6__MM_STAT__DC_TAG_PERR__V) -1)

/* EV6__M_CTL */
#define EV6__M_CTL__SPE__S	1
#define EV6__M_CTL__SPE__V	3
#define EV6__M_CTL__SPE__M	((1 << EV6__M_CTL__SPE__V)-1)

/* EV6__DC_CTL */
#define EV6__DC_CTL__SET_EN__S		0
#define EV6__DC_CTL__SET_EN__V		2
#define EV6__DC_CTL__SET_EN__M		(( 1 << EV6__DC_CTL__SET_EN__V) -1)
#define EV6__DC_CTL__F_HIT__S		2
#define EV6__DC_CTL__F_HIT__V		1
#define EV6__DC_CTL__F_HIT__M		(( 1 << EV6__DC_CTL__F_HIT__V) -1)
#define EV6__DC_CTL__F_BAD_TPAR__S	4
#define EV6__DC_CTL__F_BAD_TPAR__V	1
#define EV6__DC_CTL__F_BAD_TPAR__M	(( 1 << EV6__DC_CTL__F_BAD_TPAR__V) -1)
#define EV6__DC_CTL__F_BAD_DECC__S	5
#define EV6__DC_CTL__F_BAD_DECC__V	1
#define EV6__DC_CTL__F_BAD_DECC__M	(( 1 << EV6__DC_CTL__F_BAD_DECC__V) -1)
#define EV6__DC_CTL__DCTAG_PAR_EN__S	6
#define EV6__DC_CTL__DCTAG_PAR_EN__V	1
#define EV6__DC_CTL__DCTAG_PAR_EN__M	(( 1 << EV6__DC_CTL__DCTAG_PAR_EN__V) -1)
#define EV6__DC_CTL__DCDAT_ERR_EN__S	7
#define EV6__DC_CTL__DCDAT_ERR_EN__V	1
#define EV6__DC_CTL__DCDAT_ERR_EN__M	(( 1 << EV6__DC_CTL__DCDAT_ERR_EN__V) -1)

/* EV6__DC_STAT */
#define EV6__DC_STAT__TPERR_P0__S	0
#define EV6__DC_STAT__TPERR_P0__V	1
#define EV6__DC_STAT__TPERR_P0__M	((1 << EV6__DC_STAT__TPERR_P0__V) -1)
#define EV6__DC_STAT__TPERR_P1__S	1
#define EV6__DC_STAT__TPERR_P1__V	1
#define EV6__DC_STAT__TPERR_P1__M	((1 << EV6__DC_STAT__TPERR_P1__V) -1)
#define EV6__DC_STAT__ECC_ERR_ST__S	2
#define EV6__DC_STAT__ECC_ERR_ST__V	1
#define EV6__DC_STAT__ECC_ERR_ST__M	((1 << EV6__DC_STAT__ECC_ERR_ST__V) -1)
#define EV6__DC_STAT__ECC_ERR_LD__S	3
#define EV6__DC_STAT__ECC_ERR_LD__V	1
#define EV6__DC_STAT__ECC_ERR_LD__M	((1 << EV6__DC_STAT__ECC_ERR_LD__V) -1)
#define EV6__DC_STAT__SEO__S		4
#define EV6__DC_STAT__SEO__V		1
#define EV6__DC_STAT__SEO__M		((1 << EV6__DC_STAT__SEO__V) -1)


/* 
 * Cbox IPR fields 
 * =========================================================
 */
/* EV6__C_DATA (no subfields) */
/* EV6__C_SHIFT (no subfields) */

/* 
 * Palcode entry points 
 * =========================================================
 */

/* Exception pal entry points */
#define EV6__DTBM_DOUBLE_3_ENTRY	0x100
#define EV6__DTBM_DOUBLE_4_ENTRY	0x180
#define EV6__FEN_ENTRY			0x200
#define EV6__UNALIGN_ENTRY		0x280
#define EV6__DTBM_SINGLE_ENTRY		0x300
#define EV6__DFAULT_ENTRY		0x380
#define EV6__OPCDEC_ENTRY		0x400
#define EV6__IACV_ENTRY			0x480
#define EV6__MCHK_ENTRY			0x500
#define EV6__ITB_MISS_ENTRY		0x580
#define EV6__ARITH_ENTRY		0x600
#define EV6__INTERRUPT_ENTRY		0x680
#define EV6__MT_FPCR_ENTRY		0x700
#define EV6__RESET_ENTRY		0x780
/* Privelidged pal entry points */
#define EV6__CALL_PAL_00_ENTRY		0x2000 /* aka Halt */
#define EV6__CALL_PAL_01_ENTRY		0x2040
#define EV6__CALL_PAL_02_ENTRY		0x2080
#define EV6__CALL_PAL_03_ENTRY		0x20C0
#define EV6__CALL_PAL_04_ENTRY		0x2100
#define EV6__CALL_PAL_05_ENTRY		0x2140
#define EV6__CALL_PAL_06_ENTRY		0x2180
#define EV6__CALL_PAL_07_ENTRY		0x21C0
#define EV6__CALL_PAL_08_ENTRY		0x2200
#define EV6__CALL_PAL_09_ENTRY		0x2240
#define EV6__CALL_PAL_0A_ENTRY		0x2280
#define EV6__CALL_PAL_0B_ENTRY		0x22C0
#define EV6__CALL_PAL_0C_ENTRY		0x2300
#define EV6__CALL_PAL_0D_ENTRY		0x2340
#define EV6__CALL_PAL_0E_ENTRY		0x2380
#define EV6__CALL_PAL_0F_ENTRY		0x23C0
#define EV6__CALL_PAL_10_ENTRY		0x2400
#define EV6__CALL_PAL_11_ENTRY		0x2440
#define EV6__CALL_PAL_12_ENTRY		0x2480
#define EV6__CALL_PAL_13_ENTRY		0x24C0
#define EV6__CALL_PAL_14_ENTRY		0x2500
#define EV6__CALL_PAL_15_ENTRY		0x2540
#define EV6__CALL_PAL_16_ENTRY		0x2580
#define EV6__CALL_PAL_17_ENTRY		0x25C0
#define EV6__CALL_PAL_18_ENTRY		0x2600
#define EV6__CALL_PAL_19_ENTRY		0x2640
#define EV6__CALL_PAL_1A_ENTRY		0x2680
#define EV6__CALL_PAL_1B_ENTRY		0x26C0
#define EV6__CALL_PAL_1C_ENTRY		0x2700
#define EV6__CALL_PAL_1D_ENTRY		0x2740
#define EV6__CALL_PAL_1E_ENTRY		0x2780
#define EV6__CALL_PAL_1F_ENTRY		0x27C0
#define EV6__CALL_PAL_20_ENTRY		0x2800
#define EV6__CALL_PAL_21_ENTRY		0x2840
#define EV6__CALL_PAL_22_ENTRY		0x2880
#define EV6__CALL_PAL_23_ENTRY		0x28C0
#define EV6__CALL_PAL_24_ENTRY		0x2900
#define EV6__CALL_PAL_25_ENTRY		0x2940
#define EV6__CALL_PAL_26_ENTRY		0x2980
#define EV6__CALL_PAL_27_ENTRY		0x29C0
#define EV6__CALL_PAL_28_ENTRY		0x2A00
#define EV6__CALL_PAL_29_ENTRY		0x2A40
#define EV6__CALL_PAL_2A_ENTRY		0x2A80
#define EV6__CALL_PAL_2B_ENTRY		0x2AC0
#define EV6__CALL_PAL_2C_ENTRY		0x2B00
#define EV6__CALL_PAL_2D_ENTRY		0x2B40
#define EV6__CALL_PAL_2E_ENTRY		0x2B80
#define EV6__CALL_PAL_2F_ENTRY		0x2BC0
#define EV6__CALL_PAL_30_ENTRY		0x2C00
#define EV6__CALL_PAL_31_ENTRY		0x2C40
#define EV6__CALL_PAL_32_ENTRY		0x2C80
#define EV6__CALL_PAL_33_ENTRY		0x2CC0
#define EV6__CALL_PAL_34_ENTRY		0x2D00
#define EV6__CALL_PAL_35_ENTRY		0x2D40
#define EV6__CALL_PAL_36_ENTRY		0x2D80
#define EV6__CALL_PAL_37_ENTRY		0x2DC0
#define EV6__CALL_PAL_38_ENTRY		0x2E00
#define EV6__CALL_PAL_39_ENTRY		0x2E40
#define EV6__CALL_PAL_3A_ENTRY		0x2E80
#define EV6__CALL_PAL_3B_ENTRY		0x2EC0
#define EV6__CALL_PAL_3C_ENTRY		0x2F00
#define EV6__CALL_PAL_3D_ENTRY		0x2F40
#define EV6__CALL_PAL_3E_ENTRY		0x2F80
#define EV6__CALL_PAL_3F_ENTRY		0x2FC0
/* Unpriveledged pal entry points */
#define EV6__CALL_PAL_80_ENTRY		0x3000
#define EV6__CALL_PAL_81_ENTRY		0x3040
#define EV6__CALL_PAL_82_ENTRY		0x3080
#define EV6__CALL_PAL_83_ENTRY		0x30C0
#define EV6__CALL_PAL_84_ENTRY		0x3100
#define EV6__CALL_PAL_85_ENTRY		0x3140
#define EV6__CALL_PAL_86_ENTRY		0x3180
#define EV6__CALL_PAL_87_ENTRY		0x31C0
#define EV6__CALL_PAL_88_ENTRY		0x3200
#define EV6__CALL_PAL_89_ENTRY		0x3240
#define EV6__CALL_PAL_8A_ENTRY		0x3280
#define EV6__CALL_PAL_8B_ENTRY		0x32C0
#define EV6__CALL_PAL_8C_ENTRY		0x3300
#define EV6__CALL_PAL_8D_ENTRY		0x3340
#define EV6__CALL_PAL_8E_ENTRY		0x3380
#define EV6__CALL_PAL_8F_ENTRY		0x33C0
#define EV6__CALL_PAL_90_ENTRY		0x3400
#define EV6__CALL_PAL_91_ENTRY		0x3440
#define EV6__CALL_PAL_92_ENTRY		0x3480
#define EV6__CALL_PAL_93_ENTRY		0x34C0
#define EV6__CALL_PAL_94_ENTRY		0x3500
#define EV6__CALL_PAL_95_ENTRY		0x3540
#define EV6__CALL_PAL_96_ENTRY		0x3580
#define EV6__CALL_PAL_97_ENTRY		0x35C0
#define EV6__CALL_PAL_98_ENTRY		0x3600
#define EV6__CALL_PAL_99_ENTRY		0x3640
#define EV6__CALL_PAL_9A_ENTRY		0x3680
#define EV6__CALL_PAL_9B_ENTRY		0x36C0
#define EV6__CALL_PAL_9C_ENTRY		0x3700
#define EV6__CALL_PAL_9D_ENTRY		0x3740
#define EV6__CALL_PAL_9E_ENTRY		0x3780
#define EV6__CALL_PAL_9F_ENTRY		0x37C0
#define EV6__CALL_PAL_A0_ENTRY		0x3800
#define EV6__CALL_PAL_A1_ENTRY		0x3840
#define EV6__CALL_PAL_A2_ENTRY		0x3880
#define EV6__CALL_PAL_A3_ENTRY		0x38C0
#define EV6__CALL_PAL_A4_ENTRY		0x3900
#define EV6__CALL_PAL_A5_ENTRY		0x3940
#define EV6__CALL_PAL_A6_ENTRY		0x3980
#define EV6__CALL_PAL_A7_ENTRY		0x39C0
#define EV6__CALL_PAL_A8_ENTRY		0x3A00
#define EV6__CALL_PAL_A9_ENTRY		0x3A40
#define EV6__CALL_PAL_AA_ENTRY		0x3A80
#define EV6__CALL_PAL_AB_ENTRY		0x3AC0
#define EV6__CALL_PAL_AC_ENTRY		0x3B00
#define EV6__CALL_PAL_AD_ENTRY		0x3B40
#define EV6__CALL_PAL_AE_ENTRY		0x3B80
#define EV6__CALL_PAL_AF_ENTRY		0x3BC0
#define EV6__CALL_PAL_B0_ENTRY		0x3C00
#define EV6__CALL_PAL_B1_ENTRY		0x3C40
#define EV6__CALL_PAL_B2_ENTRY		0x3C80
#define EV6__CALL_PAL_B3_ENTRY		0x3CC0
#define EV6__CALL_PAL_B4_ENTRY		0x3D00
#define EV6__CALL_PAL_B5_ENTRY		0x3D40
#define EV6__CALL_PAL_B6_ENTRY		0x3D80
#define EV6__CALL_PAL_B7_ENTRY		0x3DC0
#define EV6__CALL_PAL_B8_ENTRY		0x3E00
#define EV6__CALL_PAL_B9_ENTRY		0x3E40
#define EV6__CALL_PAL_BA_ENTRY		0x3E80
#define EV6__CALL_PAL_BB_ENTRY		0x3EC0
#define EV6__CALL_PAL_BC_ENTRY		0x3F00
#define EV6__CALL_PAL_BD_ENTRY		0x3F40
#define EV6__CALL_PAL_BE_ENTRY		0x3F80
#define EV6__CALL_PAL_BF_ENTRY		0x3FC0
/* All other pall call entry points are handled by OPCDEC entry */


/* Alpha Logical Register Definitions
 * =========================================================
 */

/*  PAL Shadow Registers */
#define	p0 $4
#define p1 $5
#define p2 $6
#define p3 $7
#define p4 $20
#define p5 $21
#define p6 $22
#define p7 $23

/* Alpha Logical Instruction Definitions
 * =========================================================
 */

#define	mtpr	    hw_mtpr
#define	mfpr	    hw_mfpr

#define ldl_p	    hw_ldl/p
#define ldq_p	    hw_ldq/p
#define stl_p	    hw_stl/p
#define stq_p	    hw_stq/p

/* Virtual PTE fetch variants of HW_LD.
 */
#define ld_vpte     hw_ldq/v

/*
 * Physical mode load-lock and store-conditional variants of
 * HW_LD and HW_ST.
 */
#define ldq_lp	    hw_ldq/pl
#define stq_cp	    hw_stq/pc

#define STALL       bis $31, $31, $31

/* Align the code to a hardware fetch block */
#define FETCH_BLOCK_ALIGN 	.p2alignl 4, 0x47ff041f

#endif /* DC21264_H */	
