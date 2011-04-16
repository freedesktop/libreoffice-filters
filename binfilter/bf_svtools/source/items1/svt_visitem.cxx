/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

// MARKER(update_precomp.py): autogen include statement, do not remove


#include <bf_svtools/visitem.hxx>
#include <com/sun/star/uno/Any.hxx>
#include <tools/stream.hxx>

namespace binfilter
{

//============================================================================
//
//  class SfxVisibilityItem
//
//============================================================================

DBG_NAME(SfxVisibilityItem)

//============================================================================
TYPEINIT1_AUTOFACTORY(SfxVisibilityItem, SfxPoolItem);

//============================================================================
SfxVisibilityItem::SfxVisibilityItem(USHORT which, SvStream & rStream):
    SfxPoolItem(which)
{
    DBG_CTOR(SfxVisibilityItem, 0);
    sal_Bool bValue = 0;
    rStream >> bValue;
    m_nValue.bVisible = bValue;
}

//============================================================================
// virtual
int SfxVisibilityItem::operator ==(const SfxPoolItem & rItem) const
{
    DBG_CHKTHIS(SfxVisibilityItem, 0);
    DBG_ASSERT(SfxPoolItem::operator ==(rItem), "unequal type");
    return m_nValue.bVisible == SAL_STATIC_CAST(const SfxVisibilityItem *, &rItem)->
                        m_nValue.bVisible;
}

//============================================================================
// virtual
int SfxVisibilityItem::Compare(const SfxPoolItem & rWith) const
{
    DBG_ASSERT(rWith.ISA(SfxVisibilityItem), "SfxVisibilityItem::Compare(): Bad type");
    return m_nValue.bVisible == static_cast< SfxVisibilityItem const * >(&rWith)->m_nValue.bVisible ?
               0 : m_nValue.bVisible ? -1 : 1;
}

//============================================================================
// virtual
SfxItemPresentation SfxVisibilityItem::GetPresentation(SfxItemPresentation,
                                                  SfxMapUnit, SfxMapUnit,
                                                  XubString & rText,
                                                  const ::IntlWrapper *) const
{
    rText = GetValueTextByVal(m_nValue.bVisible);
    return SFX_ITEM_PRESENTATION_NAMELESS;
}


//============================================================================
// virtual
bool SfxVisibilityItem::QueryValue(com::sun::star::uno::Any& rVal,BYTE) const
{
    rVal <<= m_nValue;
    return true;
}

//============================================================================
// virtual
bool SfxVisibilityItem::PutValue(const com::sun::star::uno::Any& rVal,BYTE)
{
    if (rVal >>= m_nValue)
        return true;

    OSL_FAIL( "SfxInt16Item::PutValue - Wrong type!" );
    return false;
}

//============================================================================
// virtual
SfxPoolItem * SfxVisibilityItem::Create(SvStream & rStream, USHORT) const
{
    DBG_CHKTHIS(SfxVisibilityItem, 0);
    return new SfxVisibilityItem(Which(), rStream);
}

//============================================================================
// virtual
SfxPoolItem * SfxVisibilityItem::Clone(SfxItemPool *) const
{
    DBG_CHKTHIS(SfxVisibilityItem, 0);
    return new SfxVisibilityItem(*this);
}

//============================================================================
// virtual
USHORT SfxVisibilityItem::GetValueCount() const
{
    return 2;
}

//============================================================================
// virtual
UniString SfxVisibilityItem::GetValueTextByVal(BOOL bTheValue) const
{
    return
        bTheValue ?
            UniString::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("TRUE")) :
            UniString::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("FALSE"));
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
