#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:14:06 $
#
#   The Contents of this file are made available subject to the terms of
#   either of the following licenses
#
#          - GNU Lesser General Public License Version 2.1
#          - Sun Industry Standards Source License Version 1.1
#
#   Sun Microsystems Inc., October, 2000
#
#   GNU Lesser General Public License Version 2.1
#   =============================================
#   Copyright 2000 by Sun Microsystems, Inc.
#   901 San Antonio Road, Palo Alto, CA 94303, USA
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License version 2.1, as published by the Free Software Foundation.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA  02111-1307  USA
#
#
#   Sun Industry Standards Source License Version 1.1
#   =================================================
#   The contents of this file are subject to the Sun Industry Standards
#   Source License Version 1.1 (the "License"); You may not use this file
#   except in compliance with the License. You may obtain a copy of the
#   License at http://www.openoffice.org/license.html.
#
#   Software provided under this License is provided on an "AS IS" basis,
#   WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
#   WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
#   MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
#   See the License for the specific provisions governing your rights and
#   obligations concerning the Software.
#
#   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
#
#   Copyright: 2000 by Sun Microsystems, Inc.
#
#   All Rights Reserved.
#
#   Contributor(s): _______________________________________
#
#
#
#*************************************************************************

PRJ=..$/..
BFPRJ=..
PRJNAME=binfilter
TARGET=smath3
LIBTARGET=NO
#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE

# --- Settings -----------------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_starmath
# --- Files --------------------------------------------------------

RESLIB1NAME=bf_sm
RESLIB1SRSFILES=\
    $(SRS)$/starmath_smres.srs \
    $(SRS)$/starmath_smslots.srs \
    $(SRS)$/sfx2_sfx.srs

SHL1TARGET= bf_sm$(UPD)$(DLLPOSTFIX)
SHL1IMPLIB= bf_smimp

SHL1VERSIONMAP= bf_sm.map
SHL1DEF=$(MISC)$/$(SHL1TARGET).def
DEF1NAME=		$(SHL1TARGET)

SHL1STDLIBS= \
            $(BFSVXLIB) \
            $(LEGACYSMGRLIB)	\
            $(SO2LIB) \
            $(XMLOFFLIB) \
            $(SVTOOLLIB) \
            $(TKLIB) \
            $(VCLLIB) \
            $(SVLLIB)	\
            $(SOTLIB) \
            $(UNOTOOLSLIB) \
            $(TOOLSLIB) \
            $(COMPHELPERLIB) \
            $(CPPUHELPERLIB) \
            $(CPPULIB) \
            $(SALLIB)
.IF "$(GUI)" == "UNX"
SHL1STDLIBS+= \
            $(BFSFXLIB)
.ENDIF                        

SHL1DEPN=	makefile.mk
SHL1LIBS=   $(SLB)$/bf_starmath.lib

.IF "$(GUI)" != "UNX"
SHL1OBJS=   $(SLO)$/starmath_smdll.obj
.ENDIF # ! UNX

.IF "$(GUI)" == "WNT"
SHL1RES=	$(RCTARGET)
.ENDIF # WNT

# --- Targets -------------------------------------------------------------

.INCLUDE :  target.mk

