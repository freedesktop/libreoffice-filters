/*************************************************************************
 *
 *  $RCSfile: virtoutp.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:50:37 $
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
#ifndef _VIRTOUTP_HXX
#define _VIRTOUTP_HXX

#ifndef _SV_VIRDEV_HXX //autogen
#include <vcl/virdev.hxx>
#endif

#include "swtypes.hxx"		// UCHAR
#include "swrect.hxx"		// SwRect
namespace binfilter {

class ViewShell;
#define VIRTUALHEIGHT 64

/*************************************************************************
 *						class SwTxtVout
 *************************************************************************/

class SwLayVout
{
    friend void _FrmFinit();	//loescht das Vout
private:
    ViewShell*		pSh;
    OutputDevice*	pOut;
    VirtualDevice*	pVirDev;
    SwRect			aRect;
    SwRect			aOrgRect;
    Size			aSize;
    USHORT			nCount;

//STRIP001 	BOOL DoesFit( const Size &rOut );

public:
    SwLayVout() : pVirDev(NULL), pOut(0), aSize(0, VIRTUALHEIGHT), nCount(0) {}
    ~SwLayVout() { delete pVirDev; }

    /// OD 27.09.2002 #103636# - change 2nd parameter <rRect> - no longer <const>
//STRIP001     void Enter( ViewShell *pShell, SwRect &rRect, BOOL bOn );
//STRIP001 	void Leave() { --nCount; Flush(); }

    void SetOrgRect( SwRect &rRect ) { aOrgRect = rRect; }
    const SwRect& GetOrgRect() const { return aOrgRect; }

    BOOL IsFlushable() { return 0 != pOut; }
//STRIP001 	void _Flush();
//STRIP001 	void Flush() { if( pOut ) _Flush(); }
};



} //namespace binfilter
#endif
