#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:14:41 $
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

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sw_layout

AUTOSEG=true

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw

.IF "$(mydebug)" != ""
CDEFS+=-Dmydebug
.ENDIF

.IF "$(madebug)" != ""
CDEFS+=-DDEBUG
.ENDIF

#		"Querdarstellung des Dokumentes"
#		CDEFS=$(CDEFS) -DQUER

# 		CDEFS=$(CDEFS) -DPAGE

.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS=/NOI /NOE /PAGE:512
.ENDIF


# --- Files --------------------------------------------------------

CXXFILES = \
        sw_atrfrm.cxx \
        sw_calcmove.cxx \
        sw_colfrm.cxx \
        sw_findfrm.cxx \
        sw_flowfrm.cxx \
        sw_fly.cxx \
        sw_flycnt.cxx \
        sw_flyincnt.cxx \
        sw_flylay.cxx \
        sw_flypos.cxx \
        sw_frmtool.cxx \
        sw_ftnfrm.cxx \
        sw_hffrm.cxx \
        sw_layact.cxx \
                sw_laycache.cxx \
        sw_layouter.cxx \
        sw_newfrm.cxx \
        sw_pagechg.cxx \
        sw_pagedesc.cxx \
        sw_pageiter.cxx \
        sw_paintfrm.cxx \
        sw_sectfrm.cxx \
        sw_ssfrm.cxx \
        sw_tabfrm.cxx \
        sw_trvlfrm.cxx \
        sw_unusedf.cxx \
        sw_virtoutp.cxx \
        sw_wsfrm.cxx



SLOFILES =  \
        $(SLO)$/sw_atrfrm.obj \
        $(SLO)$/sw_calcmove.obj \
        $(SLO)$/sw_colfrm.obj \
        $(SLO)$/sw_findfrm.obj \
        $(SLO)$/sw_flowfrm.obj \
        $(SLO)$/sw_fly.obj \
        $(SLO)$/sw_flycnt.obj \
        $(SLO)$/sw_flyincnt.obj \
        $(SLO)$/sw_flylay.obj \
        $(SLO)$/sw_flypos.obj \
        $(SLO)$/sw_frmtool.obj \
        $(SLO)$/sw_ftnfrm.obj \
        $(SLO)$/sw_hffrm.obj \
        $(SLO)$/sw_layact.obj \
                $(SLO)$/sw_laycache.obj \
        $(SLO)$/sw_layouter.obj \
        $(SLO)$/sw_newfrm.obj \
        $(SLO)$/sw_pagechg.obj \
        $(SLO)$/sw_pagedesc.obj \
        $(SLO)$/sw_pageiter.obj \
        $(SLO)$/sw_paintfrm.obj \
        $(SLO)$/sw_sectfrm.obj \
        $(SLO)$/sw_ssfrm.obj \
        $(SLO)$/sw_tabfrm.obj \
        $(SLO)$/sw_trvlfrm.obj \
        $(SLO)$/sw_unusedf.obj \
        $(SLO)$/sw_virtoutp.obj \
        $(SLO)$/sw_wsfrm.obj

.IF "$(product)"==""
.IF "$(cap)"==""
CXXFILES += \
        sw_dbg_lay.cxx
SLOFILES +=  \
        $(SLO)$/sw_dbg_lay.obj
.ENDIF
.ENDIF

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

