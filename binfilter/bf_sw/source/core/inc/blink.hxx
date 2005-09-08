/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: blink.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:23:01 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef	_BLINK_HXX
#define	_BLINK_HXX

class SwLinePortion;
class SwRootFrm;
class SwTxtFrm;

#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif
// auto strip #ifndef _TIMER_HXX //autogen
// auto strip #include <vcl/timer.hxx>
// auto strip #endif
#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
namespace binfilter {

class SwBlinkPortion
{
    Point               aPos;
    const SwLinePortion	*pPor;
    const SwRootFrm		*pFrm;
    USHORT              nDir;
public:
    SwBlinkPortion( const SwLinePortion* pPortion, USHORT nDirection )
            { pPor = pPortion; nDir = nDirection; }
    SwBlinkPortion( const SwBlinkPortion* pBlink, const SwLinePortion* pPort )
    {   pPor = pPort; pFrm = pBlink->pFrm; aPos = pBlink->aPos; nDir = pBlink->nDir; }
    void SetPos( const Point& aNew ){ aPos = aNew; }
    const Point& GetPos() const{ return aPos; }
    void SetRootFrm( const SwRootFrm* pNew ){ pFrm = pNew; }
    const SwRootFrm* GetRootFrm() const{ return pFrm; }
    const SwLinePortion *GetPortion() const{ return pPor; }
    USHORT GetDirection() const { return nDir; }
    BOOL operator<( const SwBlinkPortion& rBlinkPortion ) const
    { return (long)pPor < (long)rBlinkPortion.pPor; }
    BOOL operator==( const SwBlinkPortion& rBlinkPortion ) const
    { return (long)pPor == (long)rBlinkPortion.pPor; }
};

typedef SwBlinkPortion* SwBlinkPortionPtr;
SV_DECL_PTRARR_SORT_DEL(SwBlinkList, SwBlinkPortionPtr, 0, 10)

class SwBlink
{
//STRIP001 	SwBlinkList		aList;
//STRIP001 	AutoTimer		aTimer;
//STRIP001 	BOOL			bVisible;
public:
    SwBlink();
//STRIP001 	~SwBlink();

//STRIP001 	DECL_LINK( Blinker, Timer * );

//STRIP001     void Insert( const Point& rPoint, const SwLinePortion* pPor,
//STRIP001                  const SwTxtFrm *pTxtFrm, USHORT nDir );
//STRIP001 	void Replace( const SwLinePortion* pOld, const SwLinePortion* pNew );
//STRIP001 	void Delete( const SwLinePortion* pPor );
//STRIP001 	void FrmDelete( const SwRootFrm* pRoot );
//STRIP001 	inline BOOL IsVisible() const { return bVisible ; }
};

// Blink-Manager, globale Variable, in Blink.Cxx angelegt
extern SwBlink *pBlink;


} //namespace binfilter
#endif

