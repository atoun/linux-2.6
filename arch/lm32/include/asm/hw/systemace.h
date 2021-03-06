/*
 * Milkymist VJ SoC (Software)
 * Copyright (C) 2007, 2008, 2009 Sebastien Bourdeauducq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __HW_SYSTEMACE_H
#define __HW_SYSTEMACE_H

#define CSR_ACE_BUSMODE		(0x70000000)
#define CSR_ACE_STATUSL		(0x70000008)
#define CSR_ACE_STATUSH		(0x7000000C)
#define CSR_ACE_ERRORL		(0x70000010)
#define CSR_ACE_ERRORH		(0x70000014)
#define CSR_ACE_CLBAL		(0x70000018)
#define CSR_ACE_CLBAH		(0x7000001C)
#define CSR_ACE_MLBAL		(0x70000020)
#define CSR_ACE_MLBAH		(0x70000024)
#define CSR_ACE_SECCMD		(0x70000028)
#define CSR_ACE_VERSION		(0x7000002C)
#define CSR_ACE_CTLL		(0x70000030)
#define CSR_ACE_CTLH		(0x70000034)
#define CSR_ACE_FAT		(0x70000038)
#define CSR_ACE_DATA		(0x70000080)

#define ACE_BUSMODE_16BIT	0x0001

#define ACE_STATUSL_CFGLOCK	0x0001
#define ACE_STATUSL_MPULOCK	0x0002
#define ACE_STATUSL_CFDETECT	0x0010
#define ACE_STATUSL_DATARDY	0x0020
#define ACE_STATUSL_DATAWRONLY	0x0040
#define ACE_STATUSL_CFCMDRDY	0x0100

#define ACE_SECCMD_RESET	0x0100
#define ACE_SECCMD_IDENTIFY	0x0200
#define ACE_SECCMD_READ		0x0300
#define ACE_SECCMD_WRITE	0x0400
#define ACE_SECCMD_ABORT	0x0600

#define ACE_CTLL_LOCKREQ	0x0002
#define ACE_CTLL_CFGRESET	0x0080

#endif /* __HW_SYSTEMACE_H */
