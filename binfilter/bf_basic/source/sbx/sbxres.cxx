/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sbxres.cxx,v $
 * $Revision: 1.3 $
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

#include "sbxres.hxx"

namespace binfilter {

static const char* pSbxRes[] = {
    "Empty",
    "Null",
    "Integer",
    "Long",
    "Single",
    "Double",
    "Currency",
    "Date",
    "String",
    "Object",
    "Error",
    "Boolean",
    "Variant",
    "Any",
    "Type14",
    "Type15",
    "Char",
    "Byte",
    "UShort",
    "ULong",
    "Long64",
    "ULong64",
    "Int",
    "UInt",
    "Void",
    "HResult",
    "Pointer",
    "DimArray",
    "CArray",
    "Any",
    "LpStr",
    "LpWStr",
    " As ",
    "Optional ",
    "Byref ",

    "Name",
    "Parent",
    "Application",
    "Count",
    "Add",
    "Item",
    "Remove",

    "Error ",	// mit Blank!
    "False",
    "True"
};

const char* GetSbxRes( USHORT nId )
{
    return ( ( nId > SBXRES_MAX ) ? "???" : pSbxRes[ nId ] );
}

SbxRes::SbxRes( USHORT nId )
    : XubString( String::CreateFromAscii( GetSbxRes( nId ) ) )
{}

}
