/*************************************************************************
 *
 *  $RCSfile: sw_authfld.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:24:26 $
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

#define _SVSTDARR_STRINGSDTOR
#define _SVSTDARR_USHORTS
#define _SVSTDARR_LONGS
#define _SVSTDARR_ULONGS

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

// auto strip #include <svtools/svstdarr.hxx>
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
// auto strip #ifndef _SVX_LANGITEM_HXX
// auto strip #include <bf_svx/langitem.hxx>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUES_HPP_
// auto strip #include <com/sun/star/beans/PropertyValues.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
// auto strip #include <com/sun/star/lang/Locale.hpp>
// auto strip #endif

// auto strip #ifndef _SWTYPES_HXX
// auto strip #include <swtypes.hxx>
// auto strip #endif
#ifndef _AUTHFLD_HXX
#include <authfld.hxx>
#endif
// auto strip #ifndef _EXPFLD_HXX
// auto strip #include <expfld.hxx>
// auto strip #endif

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
// auto strip #ifndef _CNTFRM_HXX
// auto strip #include <cntfrm.hxx>
// auto strip #endif 
// auto strip #ifndef _TOX_HXX
// auto strip #include <tox.hxx>
// auto strip #endif
// auto strip #ifndef _TXMSRT_HXX
// auto strip #include <txmsrt.hxx>
// auto strip #endif
#ifndef _DOCTXM_HXX
#include <doctxm.hxx>
#endif
// auto strip #ifndef _FMTFLD_HXX
// auto strip #include <fmtfld.hxx>
// auto strip #endif
// auto strip #ifndef _TXTFLD_HXX
// auto strip #include <txtfld.hxx>
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif
#ifndef _UNOPRNMS_HXX
#include <unoprnms.hxx>
#endif 
namespace binfilter {

extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr ); //STRIP008

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::lang;
using namespace ::rtl;

#define C2U(cChar) ::rtl::OUString::createFromAscii(cChar)

typedef SwAuthEntry* SwAuthEntryPtr;
SV_DECL_PTRARR_DEL( SwAuthDataArr, SwAuthEntryPtr, 5, 5 )
SV_IMPL_PTRARR( SwAuthDataArr, SwAuthEntryPtr )


typedef SwTOXSortKey* TOXSortKeyPtr;
SV_DECL_PTRARR_DEL( SortKeyArr, TOXSortKeyPtr, 5, 5 )
SV_IMPL_PTRARR( SortKeyArr, TOXSortKeyPtr )


/* -----------------16.09.99 11:53-------------------

 --------------------------------------------------*/
 SwAuthEntry::SwAuthEntry(const SwAuthEntry& rCopy)
    : nRefCount(0)
 {
    for(USHORT i = 0; i < AUTH_FIELD_END; i++)
        aAuthFields[i] = rCopy.aAuthFields[i];
 }
// --------------------------------------------------------
BOOL    SwAuthEntry::operator==(const SwAuthEntry& rComp)
{
    for(USHORT i = 0; i < AUTH_FIELD_END; i++)
        if(aAuthFields[i] != rComp.aAuthFields[i])
            return FALSE;
    return TRUE;
}
// --------------------------------------------------------
BOOL    SwAuthEntry::GetFirstAuthorField(USHORT& nPos, String& rToFill)const
{
    BOOL bRet = FALSE;
        for(USHORT i = 0; i < AUTH_FIELD_END; i++)
            if(aAuthFields[i].Len())
            {
                rToFill = aAuthFields[i];
                nPos = i;
                bRet = TRUE;
                break;
            }
    return bRet;
}
// --------------------------------------------------------
BOOL    SwAuthEntry::GetNextAuthorField(USHORT& nPos, String& rToFill)const
{
    BOOL bRet = FALSE;
    if(AUTH_FIELD_END > ++nPos)
    {
        for(USHORT i = nPos; i < AUTH_FIELD_END; i++)
            if(aAuthFields[i].Len())
            {
                rToFill = aAuthFields[i];
                nPos = i;
                bRet = TRUE;
                break;
            }
    }
    return bRet;
}

// --------------------------------------------------------

/* -----------------14.09.99 16:15-------------------

 --------------------------------------------------*/
SwAuthorityFieldType::SwAuthorityFieldType(SwDoc* pDoc)
    : SwFieldType( RES_AUTHORITY ),
    m_pDoc(pDoc),
    m_pDataArr(new SwAuthDataArr ),
    m_pSequArr(new SvLongs(5, 5)),
    m_pSortKeyArr(new SortKeyArr(3, 3)),
    m_bSortByDocument(TRUE),
    m_bIsSequence(FALSE),
    m_cPrefix('['),
    m_cSuffix(']'),
    m_eLanguage((LanguageType)GetAppLanguage())
{
}

SwAuthorityFieldType::SwAuthorityFieldType( const SwAuthorityFieldType& rFType)
    : SwFieldType( RES_AUTHORITY ),
    m_pDataArr(new SwAuthDataArr ),
    m_pSequArr(new SvLongs(5, 5)),
    m_pSortKeyArr(new SortKeyArr(3, 3)),
    m_bSortByDocument(rFType.m_bSortByDocument),
    m_bIsSequence(rFType.m_bIsSequence),
    m_cPrefix(rFType.m_cPrefix),
    m_cSuffix(rFType.m_cSuffix),
    m_eLanguage(rFType.m_eLanguage),
    m_sSortAlgorithm(rFType.m_sSortAlgorithm)
{
    for(USHORT i = 0; i < rFType.m_pSortKeyArr->Count(); i++)
        m_pSortKeyArr->Insert((*rFType.m_pSortKeyArr)[i], i);
}

/* -----------------17.09.99 13:52-------------------

 --------------------------------------------------*/
SwAuthorityFieldType::~SwAuthorityFieldType()
{
//  DBG_ASSERT(!m_pDataArr->Count(), "Array is not empty")
    m_pSortKeyArr->DeleteAndDestroy(0, m_pSortKeyArr->Count());
    delete m_pSortKeyArr;
    delete m_pSequArr;
    delete m_pDataArr;
}
/*-- 14.09.99 16:22:09---------------------------------------------------

  -----------------------------------------------------------------------*/
SwFieldType*    SwAuthorityFieldType::Copy()  const
{
    return new SwAuthorityFieldType(m_pDoc);
}
/* -----------------17.09.99 13:43-------------------

 --------------------------------------------------*/
void    SwAuthorityFieldType::RemoveField(long nHandle)
{
#ifdef DBG_UTIL
    BOOL bRemoved = FALSE;
#endif
    for(USHORT j = 0; j < m_pDataArr->Count(); j++)
    {
        SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
        long nRet = (long)(void*)pTemp;
        if(nRet == nHandle)
        {
#ifdef DBG_UTIL
            bRemoved = TRUE;
#endif
            pTemp->RemoveRef();
            if(!pTemp->GetRefCount())
            {
                m_pDataArr->DeleteAndDestroy(j, 1);
                //re-generate positions of the fields
                DelSequenceArray();
            }
            break;
        }
    }
#ifdef DBG_UTIL
    DBG_ASSERT(bRemoved, "Field unknown" )
#endif
}
/* -----------------17.09.99 13:43-------------------

 --------------------------------------------------*/
long    SwAuthorityFieldType::AddField(const String& rFieldContents)
{
    long nRet = 0;
    SwAuthEntry* pEntry = new SwAuthEntry;
    for( USHORT i = 0; i < AUTH_FIELD_END; ++i )
        pEntry->SetAuthorField( (ToxAuthorityField)i,
                        rFieldContents.GetToken( i, TOX_STYLE_DELIMITER ));

    for(USHORT j = 0; j < m_pDataArr->Count() && pEntry; j++)
    {
        SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
        if(*pTemp == *pEntry)
        {
            DELETEZ(pEntry);
            nRet = (long)(void*)pTemp;
            pTemp->AddRef();
        }
    }
    //if it is a new Entry - insert
    if(pEntry)
    {
        nRet = (long)(void*)pEntry;
        pEntry->AddRef();
        m_pDataArr->Insert(pEntry, m_pDataArr->Count());
        //re-generate positions of the fields
        DelSequenceArray();
    }
    return nRet;
}
/* -----------------17.09.99 14:18-------------------

 --------------------------------------------------*/
BOOL SwAuthorityFieldType::AddField(long nHandle)
{
    BOOL bRet = FALSE;
    for( USHORT j = 0; j < m_pDataArr->Count(); j++ )
    {
        SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
        long nTmp = (long)(void*)pTemp;
        if( nTmp == nHandle )
        {
            bRet = TRUE;
            pTemp->AddRef();
            //re-generate positions of the fields
            DelSequenceArray();
            break;
        }
    }
    DBG_ASSERT(bRet, "::AddField(long) failed");
    return bRet;
}
/* -----------------17.09.99 14:52-------------------

 --------------------------------------------------*/
const SwAuthEntry*  SwAuthorityFieldType::GetEntryByHandle(long nHandle) const
{
    const SwAuthEntry* pRet = 0;
    for(USHORT j = 0; j < m_pDataArr->Count(); j++)
    {
        const SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
        long nTmp = (long)(void*)pTemp;
        if( nTmp == nHandle )
        {
            pRet = pTemp;
            break;
        }
    }
    ASSERT( pRet, "invalid Handle" );
    return pRet;
}
/* -----------------21.09.99 13:34-------------------

 --------------------------------------------------*/
void SwAuthorityFieldType::GetAllEntryIdentifiers(
                SvStringsDtor& rToFill )const
{
    for(USHORT j = 0; j < m_pDataArr->Count(); j++)
    {
        SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
        rToFill.Insert( new String( pTemp->GetAuthorField(
                    AUTH_FIELD_IDENTIFIER )), rToFill.Count() );
    }
}
/* -----------------21.09.99 13:34-------------------

 --------------------------------------------------*/
const SwAuthEntry*  SwAuthorityFieldType::GetEntryByIdentifier(
                                const String& rIdentifier)const
{
    const SwAuthEntry* pRet = 0;
    for( USHORT j = 0; j < m_pDataArr->Count(); ++j )
    {
        const SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
        if( rIdentifier == pTemp->GetAuthorField( AUTH_FIELD_IDENTIFIER ))
        {
            pRet = pTemp;
            break;
        }
    }
    return pRet;
}
/* -----------------------------21.12.99 13:20--------------------------------

 ---------------------------------------------------------------------------*/
void SwAuthorityFieldType::ChangeEntryContent(const SwAuthEntry* pNewEntry)
{
    for( USHORT j = 0; j < m_pDataArr->Count(); ++j )
    {
        SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
        if(pTemp->GetAuthorField(AUTH_FIELD_IDENTIFIER) ==
                    pNewEntry->GetAuthorField(AUTH_FIELD_IDENTIFIER))
        {
            for(USHORT i = 0; i < AUTH_FIELD_END; i++)
                pTemp->SetAuthorField((ToxAuthorityField) i,
                    pNewEntry->GetAuthorField((ToxAuthorityField)i));
            break;
        }
    }
}
/*-- 11.10.99 08:49:22---------------------------------------------------
    Description: 	appends a new entry (if new) and returns the array position

  -----------------------------------------------------------------------*/
USHORT  SwAuthorityFieldType::AppendField( const SwAuthEntry& rInsert )
{
    USHORT nRet = 0;
    for( nRet = 0; nRet < m_pDataArr->Count(); ++nRet )
    {
        SwAuthEntry* pTemp = m_pDataArr->GetObject( nRet );
        if( *pTemp == rInsert )
        {
            break;
            //ref count unchanged
        }
    }

    //if it is a new Entry - insert
    if( nRet == m_pDataArr->Count() )
        m_pDataArr->Insert( new SwAuthEntry( rInsert ), nRet );

    return nRet;
}

/*-- 11.10.99 08:49:23---------------------------------------------------

  -----------------------------------------------------------------------*/
void SwAuthorityFieldType::MergeFieldType( const SwAuthorityFieldType& rNew,
                                            SvUShorts& rMap )
{
    DBG_ASSERT( !rMap.Count(), "array not empty!")
    for( USHORT i = 0; i < rNew.m_pDataArr->Count(); ++i )
    {
        USHORT  nNewPos = AppendField(*rNew.m_pDataArr->GetObject(i));
        rMap.Insert(nNewPos, i);
    }
}

/*-- 11.10.99 08:49:23---------------------------------------------------
    Description: 	After import is done some of the array members may have a

  -----------------------------------------------------------------------*/
void SwAuthorityFieldType::RemoveUnusedFields()
{
    for( USHORT j = m_pDataArr->Count(); j; )
    {
        SwAuthEntry* pTemp = m_pDataArr->GetObject( --j );
        if( !pTemp->GetRefCount() )
        {
            m_pDataArr->Remove( j );
            delete pTemp;
        }
    }
    DelSequenceArray();
}

/*-- 11.10.99 08:49:24---------------------------------------------------

  -----------------------------------------------------------------------*/
long    SwAuthorityFieldType::GetHandle(USHORT nPos)
{
    long nRet = 0;
    if( nPos < m_pDataArr->Count() )
    {
        SwAuthEntry* pTemp = m_pDataArr->GetObject(nPos);
        nRet = (long)(void*)pTemp;
    }
    return nRet;
}
/* -----------------20.10.99 13:38-------------------

 --------------------------------------------------*/
USHORT  SwAuthorityFieldType::GetPosition(long nHandle)
{
    USHORT j = 0;
    for( ; j < m_pDataArr->Count(); ++j )
    {
        const SwAuthEntry* pTemp = m_pDataArr->GetObject(j);
        long nTmp = (long)(void*)pTemp;
        if( nTmp == nHandle )
            break;
    }
    if( j == m_pDataArr->Count() )
        j = USHRT_MAX;

    ASSERT( USHRT_MAX != j, "handle not found" );
    return j;
}

/*-- 11.10.99 08:51:03---------------------------------------------------

  -----------------------------------------------------------------------*/
USHORT  SwAuthorityFieldType::GetEntryCount() const
{
    return m_pDataArr->Count();
}
/*-- 11.10.99 08:51:03---------------------------------------------------

  -----------------------------------------------------------------------*/
const SwAuthEntry*  SwAuthorityFieldType::GetEntryByPosition(USHORT nPos) const
{
    if(nPos < m_pDataArr->Count())
        return m_pDataArr->GetObject(nPos);
    DBG_ERROR("wrong index")
    return 0;
}
/* -----------------19.10.99 13:46-------------------

 --------------------------------------------------*/
//STRIP001 USHORT  SwAuthorityFieldType::GetSequencePos(long nHandle)
//STRIP001 {
//STRIP001     //find the field in a sorted array of handles,
//STRIP001 #ifdef DBG_UTIL
//STRIP001     sal_Bool bCurrentFieldWithoutTextNode = sal_False;
//STRIP001 #endif
//STRIP001     if(m_pSequArr->Count() && m_pSequArr->Count() != m_pDataArr->Count())
//STRIP001         DelSequenceArray();
//STRIP001     if(!m_pSequArr->Count())
//STRIP001     {
//STRIP001         SwTOXSortTabBases aSortArr;
//STRIP001         SwClientIter aIter( *this );
//STRIP001 
//STRIP001         SwTOXInternational aIntl(m_eLanguage, 0, m_sSortAlgorithm);
//STRIP001 
//STRIP001         for( SwFmtFld* pFmtFld = (SwFmtFld*)aIter.First( TYPE(SwFmtFld) );
//STRIP001                                 pFmtFld; pFmtFld = (SwFmtFld*)aIter.Next() )
//STRIP001         {
//STRIP001             SwAuthorityField* pAFld = (SwAuthorityField*)pFmtFld->GetFld();
//STRIP001             const SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
//STRIP001          if(!pTxtFld || !pTxtFld->GetpTxtNode())
//STRIP001             {
//STRIP001 #ifdef DBG_UTIL
//STRIP001                 if(nHandle == pAFld->GetHandle())
//STRIP001                     bCurrentFieldWithoutTextNode = sal_True;
//STRIP001 #endif
//STRIP001                 continue;
//STRIP001             }
//STRIP001             const SwTxtNode& rFldTxtNode = pTxtFld->GetTxtNode();
//STRIP001             SwPosition aFldPos(rFldTxtNode);
//STRIP001             SwDoc& rDoc = *(SwDoc*)rFldTxtNode.GetDoc();
//STRIP001             SwCntntFrm *pFrm = rFldTxtNode.GetFrm();
//STRIP001             const SwTxtNode* pTxtNode = 0;
//STRIP001             if(pFrm && !pFrm->IsInDocBody())
//STRIP001                 pTxtNode = GetBodyTxtNode( rDoc, aFldPos, *pFrm );
//STRIP001             //if no text node could be found or the field is in the document 
//STRIP001             //body the directly available text node will be used
//STRIP001             if(!pTxtNode)
//STRIP001                 pTxtNode = &rFldTxtNode;
//STRIP001             ULONG nPos = pTxtNode->GetIndex();
//STRIP001             if( pTxtNode->GetTxt().Len() && pTxtNode->GetFrm() &&
//STRIP001                 pTxtNode->GetNodes().IsDocNodes() )
//STRIP001             {
//STRIP001                 SwTOXAuthority* pNew = new SwTOXAuthority( *pTxtNode,
//STRIP001                                                             *pFmtFld, aIntl );
//STRIP001 
//STRIP001                 for(short i = 0; i < aSortArr.Count(); ++i)
//STRIP001                 {
//STRIP001                     SwTOXSortTabBase* pOld = aSortArr[i];
//STRIP001                     if(*pOld == *pNew)
//STRIP001                     {
//STRIP001                         //only the first occurence in the document
//STRIP001                         //has to be in the array
//STRIP001                         if(*pOld < *pNew)
//STRIP001                             DELETEZ(pNew);
//STRIP001                         else // remove the old content
//STRIP001                             aSortArr.DeleteAndDestroy( i, 1 );
//STRIP001                         break;
//STRIP001                     }
//STRIP001                 }
//STRIP001                 //if it still exists - insert at the correct position
//STRIP001                 if(pNew)
//STRIP001                 {
//STRIP001                     for(short j = 0; j < aSortArr.Count(); ++j)
//STRIP001                     {
//STRIP001                         SwTOXSortTabBase* pOld = aSortArr[j];
//STRIP001                         if(*pNew < *pOld)
//STRIP001                             break;
//STRIP001                     }
//STRIP001                     aSortArr.Insert(pNew, j );
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001 
//STRIP001         for(USHORT i = 0; i < aSortArr.Count(); i++)
//STRIP001         {
//STRIP001             const SwTOXSortTabBase& rBase = *aSortArr[i];
//STRIP001             SwFmtFld& rFmtFld = ((SwTOXAuthority&)rBase).GetFldFmt();
//STRIP001             SwAuthorityField* pAFld = (SwAuthorityField*)rFmtFld.GetFld();
//STRIP001             m_pSequArr->Insert(pAFld->GetHandle(), i);
//STRIP001         }
//STRIP001         aSortArr.DeleteAndDestroy(0, aSortArr.Count());
//STRIP001     }
//STRIP001     //find nHandle
//STRIP001     USHORT nRet = 0;
//STRIP001     for(USHORT i = 0; i < m_pSequArr->Count(); i++)
//STRIP001     {
//STRIP001         if((*m_pSequArr)[i] == nHandle)
//STRIP001         {
//STRIP001             nRet = i + 1;
//STRIP001             break;
//STRIP001         }
//STRIP001     }
//STRIP001     ASSERT(bCurrentFieldWithoutTextNode || nRet, "Handle not found")
//STRIP001     return nRet;
//STRIP001 }
/* -----------------------------15.11.00 17:33--------------------------------

 ---------------------------------------------------------------------------*/
BOOL    SwAuthorityFieldType::QueryValue( Any& rVal, BYTE nMId ) const
{
    nMId &= ~CONVERT_TWIPS;
    switch( nMId )
    {
    case FIELD_PROP_PAR1:
    case FIELD_PROP_PAR2:
        {
            OUString sVal;
            sal_Unicode uRet = FIELD_PROP_PAR1 == nMId ? m_cPrefix : m_cSuffix;
            if(uRet)
                sVal = OUString(uRet);
            rVal <<= sVal;
        }
        break;
    case FIELD_PROP_PAR3:
        rVal <<= OUString(GetSortAlgorithm());
        break;

    case FIELD_PROP_BOOL1:
    case FIELD_PROP_BOOL2:
        {
            sal_Bool bVal = FIELD_PROP_BOOL1 == nMId ? m_bIsSequence: m_bSortByDocument;
            rVal.setValue(&bVal, ::getBooleanCppuType());
        }
        break;

    case FIELD_PROP_LOCALE:
        rVal <<= SvxCreateLocale(GetLanguage());
        break;

    case FIELD_PROP_PROP_SEQ:
        {
            Sequence<PropertyValues> aRet(m_pSortKeyArr->Count());
            PropertyValues* pValues = aRet.getArray();
            OUString sProp1( C2U(SW_PROP_NAME_STR(UNO_NAME_SORT_KEY)) ),
                     sProp2( C2U(SW_PROP_NAME_STR(UNO_NAME_IS_SORT_ASCENDING)));
            for(sal_uInt16 i = 0; i < m_pSortKeyArr->Count(); i++)
            {
                const SwTOXSortKey* pKey = (*m_pSortKeyArr)[i];
                pValues[i].realloc(2);
                PropertyValue* pValue = pValues[i].getArray();
                pValue[0].Name = sProp1;
                pValue[0].Value <<= sal_Int16(pKey->eField);
                pValue[1].Name = sProp2;
                pValue[1].Value.setValue(&pKey->bSortAscending, ::getBooleanCppuType());
            }
            rVal <<= aRet;
        }
        break;
    default:
        DBG_ERROR("illegal property");
    }
    return TRUE;
}
/* -----------------------------15.11.00 17:33--------------------------------

 ---------------------------------------------------------------------------*/
BOOL    SwAuthorityFieldType::PutValue( const Any& rAny, BYTE nMId )
{
    nMId &= ~CONVERT_TWIPS;
    sal_Bool bRet = TRUE;
    String sTmp;
    switch( nMId )
    {
    case FIELD_PROP_PAR1:
    case FIELD_PROP_PAR2:
    {
        ::binfilter::GetString( rAny, sTmp );
        sal_Unicode uSet = sTmp.GetChar(0);
        if( FIELD_PROP_PAR1 == nMId )
            m_cPrefix = uSet;
        else
            m_cSuffix = uSet;
    }
    break;
    case FIELD_PROP_PAR3:
        SetSortAlgorithm( ::binfilter::GetString( rAny, sTmp ));
        break;

    case FIELD_PROP_BOOL1:
        m_bIsSequence = *(sal_Bool*)rAny.getValue();
        break;
    case FIELD_PROP_BOOL2:
        m_bSortByDocument = *(sal_Bool*)rAny.getValue();
        break;

    case FIELD_PROP_LOCALE:
        {
            Locale aLocale;
            if( 0 != (bRet = rAny >>= aLocale ))
                SetLanguage( SvxLocaleToLanguage( aLocale ));
        }
        break;

    case FIELD_PROP_PROP_SEQ:
        {
            Sequence<PropertyValues> aSeq;
            if( 0 != (bRet = rAny >>= aSeq) )
            {
                m_pSortKeyArr->DeleteAndDestroy(0, m_pSortKeyArr->Count());
                const PropertyValues* pValues = aSeq.getConstArray();
                for(sal_Int32 i = 0; i < aSeq.getLength() && i < USHRT_MAX / 4; i++)
                {
                    const PropertyValue* pValue = pValues[i].getConstArray();
                    SwTOXSortKey* pSortKey = new SwTOXSortKey;
                    for(sal_Int32 j = 0; j < pValues[i].getLength(); j++)
                    {
                        if(pValue[j].Name.equalsAsciiL(SW_PROP_NAME(UNO_NAME_SORT_KEY)))
                        {
                            sal_Int16 nVal = -1; pValue[j].Value >>= nVal;
                            if(nVal >= 0 && nVal < AUTH_FIELD_END)
                                pSortKey->eField = (ToxAuthorityField) nVal;
                            else
                                bRet = FALSE;
                        }
                        else if(pValue[j].Name.equalsAsciiL(SW_PROP_NAME(UNO_NAME_IS_SORT_ASCENDING)))
                        {
                            pSortKey->bSortAscending = *(sal_Bool*)pValue[j].Value.getValue();
                        }
                    }
                    m_pSortKeyArr->Insert(pSortKey, m_pSortKeyArr->Count());
                }
            }
        }
        break;
    default:
        DBG_ERROR("illegal property");
    }
    return bRet;
}
/* -----------------19.10.99 13:25-------------------

 --------------------------------------------------*/
void SwAuthorityFieldType::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew )
{
    //re-generate positions of the fields
    DelSequenceArray();
    SwModify::Modify( pOld, pNew );
}
/* -----------------20.10.99 13:38-------------------

 --------------------------------------------------*/
USHORT SwAuthorityFieldType::GetSortKeyCount() const
{
    return m_pSortKeyArr->Count();
}
/* -----------------20.10.99 13:38-------------------

 --------------------------------------------------*/
const SwTOXSortKey*  SwAuthorityFieldType::GetSortKey(USHORT nIdx) const
{
    SwTOXSortKey* pRet = 0;
    if(m_pSortKeyArr->Count() > nIdx)
        pRet = (*m_pSortKeyArr)[nIdx];
    DBG_ASSERT(pRet, "Sort key not found")
    return pRet;
}
/* -----------------20.10.99 13:38-------------------

 --------------------------------------------------*/
void SwAuthorityFieldType::SetSortKeys(USHORT nKeyCount, SwTOXSortKey aKeys[])
{
    m_pSortKeyArr->DeleteAndDestroy(0, m_pSortKeyArr->Count());
    USHORT nArrIdx = 0;
    for(USHORT i = 0; i < nKeyCount; i++)
        if(aKeys[i].eField < AUTH_FIELD_END)
            m_pSortKeyArr->Insert(new SwTOXSortKey(aKeys[i]), nArrIdx++);
}

/* -----------------14.09.99 16:15-------------------

 --------------------------------------------------*/
SwAuthorityField::SwAuthorityField( SwAuthorityFieldType* pType,
                                    const String& rFieldContents )
    : SwField(pType)
{
    nHandle = pType->AddField( rFieldContents );
}
/* -----------------17.09.99 14:24-------------------

 --------------------------------------------------*/
SwAuthorityField::SwAuthorityField( SwAuthorityFieldType* pType,
                                                long nSetHandle )
    : SwField( pType ),
    nHandle( nSetHandle )
{
    pType->AddField( nHandle );
}
/* -----------------15.09.99 15:00-------------------

 --------------------------------------------------*/
SwAuthorityField::~SwAuthorityField()
{
    ((SwAuthorityFieldType* )GetTyp())->RemoveField(nHandle);
}
/*-- 14.09.99 16:20:59---------------------------------------------------

  -----------------------------------------------------------------------*/
String  SwAuthorityField::Expand() const
{
    DBG_ERROR("STRIP" ) return String();
//STRIP001     SwAuthorityFieldType* pAuthType = (SwAuthorityFieldType*)GetTyp();
//STRIP001     String sRet;
//STRIP001     if(pAuthType->GetPrefix())
//STRIP001         sRet.Assign(pAuthType->GetPrefix());
//STRIP001 
//STRIP001     if( pAuthType->IsSequence() )
//STRIP001     {
//STRIP001         sRet += String::CreateFromInt32( pAuthType->GetSequencePos( nHandle ));
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         const SwAuthEntry* pEntry = pAuthType->GetEntryByHandle(nHandle);
//STRIP001         //TODO: Expand to: identifier, number sequence, ...
//STRIP001         if(pEntry)
//STRIP001             sRet += pEntry->GetAuthorField(AUTH_FIELD_IDENTIFIER);
//STRIP001     }
//STRIP001     if(pAuthType->GetSuffix())
//STRIP001         sRet += pAuthType->GetSuffix();
//STRIP001     return sRet;
}
/*-- 14.09.99 16:21:00---------------------------------------------------

  -----------------------------------------------------------------------*/
SwField* SwAuthorityField::Copy() const
{
    SwAuthorityFieldType* pAuthType = (SwAuthorityFieldType*)GetTyp();
    return new SwAuthorityField(pAuthType, nHandle);
}
/* -----------------21.09.99 12:55-------------------

 --------------------------------------------------*/
const String&   SwAuthorityField::GetFieldText(ToxAuthorityField eField) const
{
    SwAuthorityFieldType* pAuthType = (SwAuthorityFieldType*)GetTyp();
    const SwAuthEntry* pEntry = pAuthType->GetEntryByHandle( nHandle );
    return pEntry->GetAuthorField( eField );
}
/* -----------------21.09.99 14:57-------------------

 --------------------------------------------------*/
void    SwAuthorityField::SetPar1(const String& rStr)
{
    SwAuthorityFieldType* pType = (SwAuthorityFieldType* )GetTyp();
    pType->RemoveField(nHandle);
    nHandle = pType->AddField(rStr);
}
/* -----------------11.10.99 09:43-------------------

 --------------------------------------------------*/
USHORT  SwAuthorityField::GetHandlePosition() const
{
    SwAuthorityFieldType* pAuthType = (SwAuthorityFieldType*)GetTyp();
    DBG_ASSERT(pAuthType, "no field type")
    return pAuthType->GetPosition(nHandle);
}
/* -----------------------------15.11.00 17:33--------------------------------

 ---------------------------------------------------------------------------*/
const char* aFieldNames[] =
{
    "Identifier",
    "BibiliographicType",
    "Address",
    "Annote",
    "Author",
    "Booktitle",
    "Chapter",
    "Edition",
    "Editor",
    "Howpublished",
    "Institution",
    "Journal",
    "Month",
    "Note",
    "Number",
    "Organizations",
    "Pages",
    "Publisher",
    "School",
    "Series",
    "Title",
    "Report_Type",
    "Volume",
    "Year",
    "URL",
    "Custom1",
    "Custom2",
    "Custom3",
    "Custom4",
    "Custom5",
    "ISBN"
};
/* -----------------------------16.11.00 12:27--------------------------------

 ---------------------------------------------------------------------------*/
BOOL    SwAuthorityField::QueryValue( Any& rAny, BYTE nMId ) const
{
    nMId &= ~CONVERT_TWIPS;
    if(!GetTyp())
        return FALSE;
    const SwAuthEntry* pAuthEntry = ((SwAuthorityFieldType*)GetTyp())->GetEntryByHandle(nHandle);
    if(!pAuthEntry)
        return FALSE;
    Sequence <PropertyValue> aRet(AUTH_FIELD_END);
    PropertyValue* pValues = aRet.getArray();
    for(sal_Int16 i = 0; i < AUTH_FIELD_END; i++)
    {
        pValues[i].Name = C2U(aFieldNames[i]);
        const String& rField = pAuthEntry->GetAuthorField((ToxAuthorityField) i);
        if(i == AUTH_FIELD_AUTHORITY_TYPE)
            pValues[i].Value <<= sal_Int16(rField.ToInt32());
        else
            pValues[i].Value <<= OUString(rField);
    }
    rAny <<= aRet;
    return FALSE;
}
/* -----------------------------15.11.00 17:33--------------------------------

 ---------------------------------------------------------------------------*/
sal_Int16 lcl_Find(const OUString& rFieldName)
{
    for(sal_Int16 i = 0; i < AUTH_FIELD_END; i++)
        if(!rFieldName.compareToAscii(aFieldNames[i]))
            return i;
    return -1;
}
//----------------------------------------------------------------------------
BOOL    SwAuthorityField::PutValue( const Any& rAny, BYTE nMId )
{
    nMId &= ~CONVERT_TWIPS;
    if(!GetTyp() || !((SwAuthorityFieldType*)GetTyp())->GetEntryByHandle(nHandle))
        return FALSE;

    Sequence <PropertyValue> aParam;
    if(!(rAny >>= aParam))
        return FALSE;

    String sToSet;
    sToSet.Fill(AUTH_FIELD_ISBN, TOX_STYLE_DELIMITER);
    const PropertyValue* pParam = aParam.getConstArray();
    for(sal_Int32 i = 0; i < aParam.getLength(); i++)
    {
        sal_Int16 nFound = lcl_Find(pParam[i].Name);
        if(nFound >= 0)
        {
            OUString sContent;
            if(AUTH_FIELD_AUTHORITY_TYPE == nFound)
            {
                sal_Int16 nVal;
                pParam[i].Value >>= nVal;
                sContent = OUString::valueOf((sal_Int32)nVal);
            }
            else
                pParam[i].Value >>= sContent;
            sToSet.SetToken(nFound, TOX_STYLE_DELIMITER, sContent);
        }
    }

    ((SwAuthorityFieldType*)GetTyp())->RemoveField(nHandle);
    nHandle = ((SwAuthorityFieldType*)GetTyp())->AddField(sToSet);

    return FALSE;
}
/* -----------------11.10.99 09:43-------------------

 --------------------------------------------------*/
SwFieldType* SwAuthorityField::ChgTyp( SwFieldType* pFldTyp )
{
    SwAuthorityFieldType* pSrcTyp = (SwAuthorityFieldType*)GetTyp(),
                        * pDstTyp = (SwAuthorityFieldType*)pFldTyp;
    if( pSrcTyp != pDstTyp )
    {

        const SwAuthEntry* pEntry = pSrcTyp->GetEntryByHandle( nHandle );
        USHORT nHdlPos = pDstTyp->AppendField( *pEntry );
        pSrcTyp->RemoveField( nHandle );
        nHandle = pDstTyp->GetHandle( nHdlPos );
        pDstTyp->AddField( nHandle );
        SwField::ChgTyp( pFldTyp );
    }
    return pSrcTyp;
}


}
