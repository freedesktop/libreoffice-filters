/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: SwGetPoolIdFromName.hxx,v $
 * $Revision: 1.4 $
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
#ifndef _GETPOOLIDFROMNAMEENUM_HXX
#define _GETPOOLIDFROMNAMEENUM_HXX
namespace binfilter {

/* When using the NameMapper to translate pool ids to UI or programmatic
 * names, this enum is used to define which family is required */

enum SwGetPoolIdFromName
{
    GET_POOLID_TXTCOLL 	= 0x01,
    GET_POOLID_CHRFMT	= 0x02,
    GET_POOLID_FRMFMT	= 0x04,
    GET_POOLID_PAGEDESC	= 0x08,
    GET_POOLID_NUMRULE	= 0x10
};

} //namespace binfilter
#endif 
