/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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
#ifndef _SVX_FWDTITEM_HXX
#define _SVX_FWDTITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXPOOLITEM_HXX //autogen
#include <bf_svtools/poolitem.hxx>
#endif
#ifndef   ITEMID_FONTWIDTH
#define   ITEMID_FONTWIDTH 0
#endif
namespace binfilter {

// class SvxFontWidthItem -----------------------------------------------

/*	[Beschreibung]

    Dieses Item beschreibt die Font-Breite.
*/

class SvxFontWidthItem : public SfxPoolItem
{
    UINT16	nWidth;			// 0 = default
    USHORT	nProp;			// default 100%
public:
    UINT16 GetWidth() const { return nWidth; }

};

}//end of namespace binfilter
#endif

