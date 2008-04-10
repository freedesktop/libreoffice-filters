/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: redlndlg.hxx,v $
 * $Revision: 1.6 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#ifndef _SWREDLNDLG_HXX
#define _SWREDLNDLG_HXX

#include "chldwrap.hxx"

#ifndef _BASEDLGS_HXX //autogen
#include <bf_sfx2/basedlgs.hxx>
#endif
namespace binfilter {

class SwChildWinWrapper;

/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/


/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/


/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/

class SwRedlineAcceptChild : public SwChildWinWrapper
{
public:
    SwRedlineAcceptChild(	Window* pParent,USHORT nId, SfxBindings*, SfxChildWinInfo* ):SwChildWinWrapper( pParent, nId ){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 	SwRedlineAcceptChild(	Window* ,

    SFX_DECL_CHILDWINDOW( SwRedlineAcceptChild );

};


} //namespace binfilter
#endif


