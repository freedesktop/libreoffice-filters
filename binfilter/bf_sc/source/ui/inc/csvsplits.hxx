/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: csvsplits.hxx,v $
 * $Revision: 1.5 $
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

// ============================================================================

#ifndef _SC_CSVSPLITS_HXX
#define _SC_CSVSPLITS_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

#include <vector>
namespace binfilter {


// ============================================================================

/** Constant for an invalid vector index. */
const sal_uInt32 CSV_VEC_NOTFOUND   = ~0UL;
/** Constant for an invalid ruler position. */
const sal_Int32 CSV_POS_INVALID     = -1;


// ----------------------------------------------------------------------------

/** A vector of column splits that supports inserting, removing and moving splits. */
class ScCsvSplits
{
private:
    typedef ::std::vector< sal_Int32 >      ScSplitVector;
    typedef ScSplitVector::iterator         iterator;
    typedef ScSplitVector::const_iterator   const_iterator;

    ScSplitVector               maVec;          /// The split containter.

};


// ============================================================================

} //namespace binfilter
#endif

