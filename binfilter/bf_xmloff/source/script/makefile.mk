#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2000, 2010 Oracle and/or its affiliates.
#
# OpenOffice.org - a multi-platform office productivity suite
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

EXTERNAL_WARNINGS_NOT_ERRORS := TRUE

PRJ=..$/..$/..

PRJNAME=binfilter
TARGET=xmloff_script

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_xmloff
# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/xmloff_XMLEventExport.obj \
        $(SLO)$/xmloff_XMLEventImportHelper.obj \
        $(SLO)$/xmloff_XMLEventsImportContext.obj \
        $(SLO)$/xmloff_XMLScriptContextFactory.obj \
        $(SLO)$/xmloff_XMLScriptExportHandler.obj \
        $(SLO)$/xmloff_XMLStarBasicContextFactory.obj \
        $(SLO)$/xmloff_XMLStarBasicExportHandler.obj \
        $(SLO)$/xmloff_xmlscripti.obj \
        $(SLO)$/xmloff_xmlbasici.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

