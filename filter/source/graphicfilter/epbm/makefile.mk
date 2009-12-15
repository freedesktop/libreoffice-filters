#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2008 by Sun Microsystems, Inc.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# $RCSfile: makefile.mk,v $
#
# $Revision: 1.13 $
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.  If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
#
#*************************************************************************

PRJ=..$/..$/..

PRJNAME=goodies
TARGET=epbm
TARGET2=epb
DEPTARGET=vepbm

# --- Settings -----------------------------------------------------------

.INCLUDE :	settings.mk

# --- Allgemein ----------------------------------------------------------

.IF "$(editdebug)"!="" || "$(EDITDEBUG)"!=""
CDEFS+= -DEDITDEBUG
.ENDIF

SRS1NAME=$(TARGET)
SRC1FILES=	dlgepbm.src \
            epbmstr.src
.IF "$(L10N_framework)"==""
SLOFILES =	$(SLO)$/epbm.obj \
            $(SLO)$/dlgepbm.obj
.ENDIF
# ==========================================================================

RESLIB1NAME=$(TARGET2)
RESLIB1SRSFILES=$(SRS)$/$(TARGET).srs
.IF "$(L10N_framework)"==""
SHL1TARGET= 	epb$(DLLPOSTFIX)
SHL1IMPLIB= 	epbm
SHL1STDLIBS=	$(TOOLSLIB) $(VCLLIB) $(CPPULIB)	$(SVTOOLLIB) $(SALLIB)

SHL1LIBS=		$(SLB)$/epbm.lib

.IF "$(GUI)" != "UNX"
.IF "$(COM)" != "GCC"
SHL1OBJS=		$(SLO)$/epbm.obj
.ENDIF
.ENDIF

SHL1VERSIONMAP=exports.map
SHL1DEF=		$(MISC)$/$(SHL1TARGET).def
DEF1NAME=$(SHL1TARGET)
.ENDIF
# ==========================================================================

.INCLUDE :	target.mk
