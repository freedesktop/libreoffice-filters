/*************************************************************************
 *
 *  $RCSfile: sw_ndarr.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:18 $
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


#pragma hdrstop

#ifndef _INDEX_HXX
#include <index.hxx>
#endif
#ifndef _NDARR_HXX
#include <ndarr.hxx>
#endif
namespace binfilter {


void SwNds::Insert(const SwNodePtr &aElement, const SwIndex & aPos)
{
    theArr.Insert((const ElementPtr&) aElement, aPos.GetIndex());
    SwIndexReg::Update(aPos, 1);
}

void SwNds::Insert(const SwNodePtr* pElement, USHORT nLen, const SwIndex & aPos)
{
    theArr.Insert((const ElementPtr*) pElement, nLen, aPos.GetIndex());
    SwIndexReg::Update(aPos, nLen);
}

void SwNds::Remove(const SwIndex & aPos, USHORT nLen)
{
    if(nLen)
    {
        theArr.Remove(aPos.GetIndex(), nLen);
        SwIndexReg::Update(aPos, nLen, TRUE);
    }
}

BOOL SwNds::Move( const SwIndex & rOldPos, const SwIndex & rNewPos )
{
    register USHORT nDelPos = rOldPos.GetIndex(),
                    nInsPos = rNewPos.GetIndex();
    if( nDelPos == nInsPos || nDelPos +1 == nInsPos )
        return FALSE;
    theArr.Move( nDelPos, nInsPos );
    SwIndexReg::MoveIdx( rOldPos, rNewPos );
    return TRUE;
}

}
