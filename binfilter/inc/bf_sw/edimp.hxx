/*************************************************************************
 *
 *  $RCSfile: edimp.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 21:39:00 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _EDIMP_HXX
#define _EDIMP_HXX

#include "crsrsh.hxx"
// auto strip #include "doc.hxx"
// auto strip #include "viscrs.hxx"
namespace binfilter {

/*
 * MACROS um ueber alle Bereiche zu iterieren
 */
#define PCURCRSR (_pStartCrsr)

#define FOREACHPAM_START(pCURSH) \
    {\
        SwPaM *_pStartCrsr = (pCURSH)->GetCrsr(), *__pStartCrsr = _pStartCrsr; \
        do {

#define FOREACHPAM_END() \
        } while( (_pStartCrsr=(SwPaM *)_pStartCrsr->GetNext()) != __pStartCrsr ); \
    }


#define FOREACHCURSOR_START(pCURSH) \
    {\
        SwShellCrsr *_pStartCrsr = *(pCURSH)->GetSwCrsr(), *__pStartCrsr = _pStartCrsr; \
        do {

#define FOREACHCURSOR_END() \
        } while( (_pStartCrsr=*(SwCursor*)_pStartCrsr->GetNext()) != __pStartCrsr ); \
    }


struct SwPamRange
{
    ULONG nStart, nEnd;

    SwPamRange() : nStart( 0 ), nEnd( 0 )	{}
    SwPamRange( ULONG nS, ULONG nE ) : nStart( nS ), nEnd( nE )	{}

    BOOL operator==( const SwPamRange& rRg )
        { return nStart == rRg.nStart ? TRUE : FALSE; }
    BOOL operator<( const SwPamRange& rRg )
        { return nStart < rRg.nStart ? TRUE : FALSE; }
};

SV_DECL_VARARR_SORT( _SwPamRanges, SwPamRange, 0, 1 )

class SwPamRanges : private _SwPamRanges
{
public:
    SwPamRanges( const SwPaM& rRing ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 SwPamRanges( const SwPaM& rRing );

//STRIP001 	void Insert( const SwNodeIndex& rIdx1, const SwNodeIndex& rIdx2 );
    SwPaM& SetPam( USHORT nArrPos, SwPaM& rPam ){DBG_BF_ASSERT(0, "STRIP"); return rPam;} //STRIP001 SwPaM& SetPam( USHORT nArrPos, SwPaM& rPam );

    USHORT Count() const
                {	return _SwPamRanges::Count(); }
//STRIP001 	SwPamRange operator[]( USHORT nPos ) const
//STRIP001 				{ return _SwPamRanges::operator[](nPos); }
};


} //namespace binfilter
#endif
