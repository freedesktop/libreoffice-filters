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
# $Revision: 1.4 $
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

PRJ=..$/..

PRJNAME=oox
TARGET=xls
AUTOSEG=true

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE: $(PRJ)$/util$/makefile.pmk

# --- Files --------------------------------------------------------

SLOFILES =										\
        $(SLO)$/addressconverter.obj			\
        $(SLO)$/autofiltercontext.obj			\
        $(SLO)$/biffcodec.obj					\
        $(SLO)$/biffdetector.obj				\
        $(SLO)$/bifffragmenthandler.obj			\
        $(SLO)$/biffhelper.obj					\
        $(SLO)$/biffinputstream.obj				\
        $(SLO)$/biffoutputstream.obj			\
        $(SLO)$/chartsheetfragment.obj			\
        $(SLO)$/condformatbuffer.obj			\
        $(SLO)$/condformatcontext.obj			\
        $(SLO)$/connectionsfragment.obj			\
        $(SLO)$/defnamesbuffer.obj				\
        $(SLO)$/drawingfragment.obj				\
        $(SLO)$/excelfilter.obj					\
        $(SLO)$/excelhandlers.obj				\
        $(SLO)$/externallinkbuffer.obj			\
        $(SLO)$/externallinkfragment.obj		\
        $(SLO)$/formulabase.obj					\
        $(SLO)$/formulaparser.obj				\
        $(SLO)$/headerfooterparser.obj			\
        $(SLO)$/numberformatsbuffer.obj			\
        $(SLO)$/pagesettings.obj				\
        $(SLO)$/pivotcachefragment.obj			\
        $(SLO)$/pivottablebuffer.obj			\
        $(SLO)$/pivottablefragment.obj			\
        $(SLO)$/querytablefragment.obj			\
        $(SLO)$/richstring.obj					\
        $(SLO)$/richstringcontext.obj			\
        $(SLO)$/sharedformulabuffer.obj			\
        $(SLO)$/sharedstringsbuffer.obj			\
        $(SLO)$/sharedstringsfragment.obj		\
        $(SLO)$/sheetcellrangemap.obj			\
        $(SLO)$/sheetdatacontext.obj			\
        $(SLO)$/stylesbuffer.obj				\
        $(SLO)$/stylesfragment.obj				\
        $(SLO)$/stylespropertyhelper.obj		\
        $(SLO)$/tablebuffer.obj					\
        $(SLO)$/tablefragment.obj				\
        $(SLO)$/themebuffer.obj					\
        $(SLO)$/unitconverter.obj				\
        $(SLO)$/validationpropertyhelper.obj	\
        $(SLO)$/viewsettings.obj				\
        $(SLO)$/webquerybuffer.obj				\
        $(SLO)$/workbookfragment.obj			\
        $(SLO)$/workbookhelper.obj				\
        $(SLO)$/workbooksettings.obj			\
        $(SLO)$/worksheetbuffer.obj				\
        $(SLO)$/worksheetfragment.obj			\
        $(SLO)$/worksheethelper.obj             \
        $(SLO)$/worksheetsettings.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk
