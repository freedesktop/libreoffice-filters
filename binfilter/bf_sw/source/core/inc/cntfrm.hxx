/*************************************************************************
 *
 *  $RCSfile: cntfrm.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:49 $
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
#ifndef _CNTFRM_HXX
#define _CNTFRM_HXX

#include "frame.hxx"
#include "flowfrm.hxx"
#include "cshtyp.hxx"
namespace binfilter {

class SwLayoutFrm;
class SwPageFrm;
class SwCntntNode;
struct SwCrsrMoveState;
class SwBorderAttrs;
class SwAttrSetChg;

//Implementiert in cntfrm.cxx, wird von cntfrm.cxx und crsrsh.cxx angezogen
extern BOOL GetFrmInPage( const SwCntntFrm*, SwWhichPage, SwPosPage, SwPaM* );

class SwCntntFrm: public SwFrm, public SwFlowFrm
{
    friend void MakeNxt( SwFrm *pFrm, SwFrm *pNxt );	//ruft MakePrtArea

    BOOL _WouldFit( SwTwips nSpace, SwLayoutFrm *pNewUpper, BOOL bTstMove );
    virtual void MakeAll();

    void _UpdateAttr( SfxPoolItem*, SfxPoolItem*, BYTE &,
                      SwAttrSetChg *pa = 0, SwAttrSetChg *pb = 0 );

    virtual BOOL ShouldBwdMoved( SwLayoutFrm *pNewUpper, BOOL, BOOL& );

protected:

    BOOL MakePrtArea( const SwBorderAttrs & );

    virtual void Modify( SfxPoolItem*, SfxPoolItem* );
    virtual SwTwips ShrinkFrm( SwTwips, SZPTR
                               BOOL bTst = FALSE, BOOL bInfo = FALSE );
    virtual SwTwips GrowFrm  ( SwTwips, SZPTR
                               BOOL bTst = FALSE, BOOL bInfo = FALSE );

    SwCntntFrm( SwCntntNode * const );

public:
    virtual ~SwCntntFrm();
    TYPEINFO();	//bereits in Basisklassen drin

    virtual void Cut();
    virtual void Paste( SwFrm* pParent, SwFrm* pSibling = 0 );

    inline 		 SwCntntNode *GetNode();
    inline const SwCntntNode *GetNode() const;
                 USHORT 	  GetSectionLevel();

    inline const SwCntntFrm *GetFollow() const;
    inline		 SwCntntFrm *GetFollow();

        //Layoutabhaengiges Cursortravelling
//STRIP001 	virtual BOOL	LeftMargin( SwPaM * ) const;
//STRIP001 	virtual BOOL	RightMargin( SwPaM *, BOOL bAPI = FALSE ) const;
//STRIP001 	virtual BOOL	UnitUp( SwPaM *, const SwTwips nOffset = 0,
//STRIP001 							BOOL bSetInReadOnly = FALSE ) const;
//STRIP001 	virtual BOOL	UnitDown( SwPaM *, const SwTwips nOffset = 0,
//STRIP001 							BOOL bSetInReadOnly = FALSE ) const;
    inline	BOOL	StartNextPage( SwPaM * ) const;
    inline	BOOL	StartPrevPage( SwPaM * ) const;
    inline	BOOL	StartCurrPage( SwPaM * ) const;
    inline	BOOL	EndCurrPage( SwPaM * ) const;
    inline	BOOL	EndNextPage( SwPaM * ) const;
    inline	BOOL	EndPrevPage( SwPaM * ) const;

    //nMaxHeight liefert die benoetigte Hoehe,
    //bSplit sagt, obj der Absatz gesplittet werden muss.
    virtual BOOL WouldFit( SwTwips &nMaxHeight, BOOL &bSplit );

//STRIP001 	BOOL MoveFtnCntFwd( BOOL, SwFtnBossFrm* );//von MoveFwd gerufen bei Ftn-Inhalt
};

inline SwCntntNode *SwCntntFrm::GetNode()
{
    return (SwCntntNode*)GetDep();
}
inline const SwCntntNode *SwCntntFrm::GetNode() const
{
    return (SwCntntNode*)GetDep();
}

inline const SwCntntFrm *SwCntntFrm::GetFollow() const
{
    return (const SwCntntFrm*)SwFlowFrm::GetFollow();
}
inline SwCntntFrm *SwCntntFrm::GetFollow()
{
    return (SwCntntFrm*)SwFlowFrm::GetFollow();
}

} //namespace binfilter
#endif
