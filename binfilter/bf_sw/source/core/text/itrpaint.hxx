/*************************************************************************
 *
 *  $RCSfile: itrpaint.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:51:09 $
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
#ifndef _ITRPAINT_HXX
#define _ITRPAINT_HXX

#include "itrtxt.hxx"
namespace binfilter {

class SwSaveClip;          // SwTxtPainter
class SwMultiPortion;

/*************************************************************************
 *                      class SwTxtPainter
 *************************************************************************/

class SwTxtPainter : public SwTxtCursor
{
    sal_Bool bPaintDrop;

//STRIP001 	SwLinePortion *CalcPaintOfst( const SwRect &rPaint );
//STRIP001     void CheckSpecialUnderline( const SwLinePortion* pPor,
//STRIP001                                 long nAdjustBaseLine = 0 );
protected:
    void CtorInit( SwTxtFrm *pFrm, SwTxtPaintInfo *pInf );
    inline SwTxtPainter() { }
public:
    inline SwTxtPainter( SwTxtFrm *pFrm, SwTxtPaintInfo *pInf )
           { CtorInit( pFrm, pInf ); }
//STRIP001 	void DrawTextLine( const SwRect &rPaint, SwSaveClip &rClip,
//STRIP001 					   const sal_Bool bUnderSz );
//STRIP001 	void PaintDropPortion();
//STRIP001 #ifdef BIDI
    // if PaintMultiPortion is called recursively, we have to pass the
    // surrounding SwBidiPortion
//STRIP001     void PaintMultiPortion( const SwRect &rPaint, SwMultiPortion& rMulti,
//STRIP001                             const SwMultiPortion* pEnvPor = 0 );
//STRIP001 #else
//STRIP001 	void PaintMultiPortion( const SwRect &rPaint, SwMultiPortion& rMulti );
//STRIP001 #endif
    inline void SetPaintDrop( const sal_Bool bNew ) { bPaintDrop = bNew; }
    inline IsPaintDrop() const { return bPaintDrop; }
    inline SwTxtPaintInfo &GetInfo()
        { return (SwTxtPaintInfo&)SwTxtIter::GetInfo(); }
    inline const SwTxtPaintInfo &GetInfo() const
        { return (const SwTxtPaintInfo&)SwTxtIter::GetInfo(); }
};



} //namespace binfilter
#endif
