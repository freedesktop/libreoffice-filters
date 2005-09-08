/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_ParseContext.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 05:39:40 $
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
#ifndef SVX_QUERYDESIGNCONTEXT_HXX
#include "ParseContext.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
// auto strip #ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
// auto strip #include <svtools/syslocale.hxx>
// auto strip #endif
#ifndef _SVX_FMRESIDS_HRC
#include "fmresids.hrc"
#endif
#include "dialmgr.hxx"
#ifndef _SV_SVAPP_HXX 
#include <vcl/svapp.hxx>
#endif
#ifndef _VOS_MUTEX_HXX_ 
#include <vos/mutex.hxx>
#endif

#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif

namespace binfilter {


using namespace svxform;
using namespace ::connectivity;
//==========================================================================
//= OSystemParseContext
//==========================================================================
/*N*/ DBG_NAME(OSystemParseContext)
//-----------------------------------------------------------------------------
/*N*/ OSystemParseContext::OSystemParseContext() : IParseContext()
/*N*/ {
/*N*/ 	DBG_CTOR(OSystemParseContext,NULL);
/*N*/ 	vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/ 	m_aSQLInternationals = ByteString(SVX_RES(RID_STR_SVT_SQL_INTERNATIONAL),RTL_TEXTENCODING_ASCII_US);
/*N*/ }

//-----------------------------------------------------------------------------
/*?*/ OSystemParseContext::~OSystemParseContext()
/*?*/ {
/*?*/ 	DBG_DTOR(OSystemParseContext,NULL);
/*?*/ }

//-----------------------------------------------------------------------------
/*?*/ ::com::sun::star::lang::Locale OSystemParseContext::getPreferredLocale( ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); ::com::sun::star::lang::Locale alocal; return alocal;//STRIP001 
/*?*/ //STRIP001 	return SvtSysLocale().GetLocaleData().getLocale();
/*?*/ }

//-----------------------------------------------------------------------------
/*?*/ ::rtl::OUString OSystemParseContext::getErrorMessage(ErrorCode _eCode) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); String astring; return astring;//STRIP001 
//STRIP001 	String aMsg;
//STRIP001 	vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 	switch (_eCode)
//STRIP001 	{
//STRIP001 		case ERROR_GENERAL:					aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_ERROR); break;
//STRIP001 		case ERROR_GENERAL_HINT:			aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_ERROR_BEFORE); break;
//STRIP001 		case ERROR_VALUE_NO_LIKE:			aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_VALUE_NO_LIKE); break;
//STRIP001 		case ERROR_FIELD_NO_LIKE:			aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_FIELD_NO_LIKE); break;
//STRIP001 		case ERROR_INVALID_COMPARE:			aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_CRIT_NO_COMPARE); break;
//STRIP001 		case ERROR_INVALID_INT_COMPARE:		aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_INT_NO_VALID); break;
//STRIP001 		case ERROR_INVALID_STRING_COMPARE:	aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_NO_NUM); break;
//STRIP001 		case ERROR_INVALID_DATE_COMPARE:	aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_ACCESS_DAT_NO_VALID); break;
//STRIP001 		case ERROR_INVALID_REAL_COMPARE:	aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_REAL_NO_VALID); break;
//STRIP001 		case ERROR_INVALID_TABLE:			aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_TABLE); break;
//STRIP001 		case ERROR_INVALID_COLUMN:			aMsg = SVX_RES(RID_STR_SVT_SQL_SYNTAX_COLUMN); break;
//STRIP001 	}
//STRIP001 	return aMsg;
/*?*/ }

//-----------------------------------------------------------------------------
/*?*/ ::rtl::OString OSystemParseContext::getIntlKeywordAscii(InternationalKeyCode _eKey) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); ByteString aKeyword; return aKeyword;//STRIP001 
//STRIP001 	ByteString aKeyword;
//STRIP001 	switch (_eKey)
//STRIP001 	{
//STRIP001 		case KEY_LIKE:		aKeyword = m_aSQLInternationals.GetToken(0); break;
//STRIP001 		case KEY_NOT:		aKeyword = m_aSQLInternationals.GetToken(1); break;
//STRIP001 		case KEY_NULL:		aKeyword = m_aSQLInternationals.GetToken(2); break;
//STRIP001 		case KEY_TRUE:		aKeyword = m_aSQLInternationals.GetToken(3); break;
//STRIP001 		case KEY_FALSE:		aKeyword = m_aSQLInternationals.GetToken(4); break;
//STRIP001 		case KEY_IS:		aKeyword = m_aSQLInternationals.GetToken(5); break;
//STRIP001 		case KEY_BETWEEN:	aKeyword = m_aSQLInternationals.GetToken(6); break;
//STRIP001 		case KEY_OR:		aKeyword = m_aSQLInternationals.GetToken(7); break;
//STRIP001 		case KEY_AND:		aKeyword = m_aSQLInternationals.GetToken(8); break;
//STRIP001 		case KEY_AVG:		aKeyword = m_aSQLInternationals.GetToken(9); break;
//STRIP001 		case KEY_COUNT:		aKeyword = m_aSQLInternationals.GetToken(10); break;
//STRIP001 		case KEY_MAX:		aKeyword = m_aSQLInternationals.GetToken(11); break;
//STRIP001 		case KEY_MIN:		aKeyword = m_aSQLInternationals.GetToken(12); break;
//STRIP001 		case KEY_SUM:		aKeyword = m_aSQLInternationals.GetToken(13); break;
//STRIP001 	}
//STRIP001 	return aKeyword;
/*?*/ }

//-----------------------------------------------------------------------------
//STRIP001 static sal_Unicode lcl_getSeparatorChar( const String& _rSeparator, sal_Unicode _nFallback )
//STRIP001 {
//STRIP001 	DBG_ASSERT( 0 < _rSeparator.Len(), "::lcl_getSeparatorChar: invalid decimal separator!" );
//STRIP001 
//STRIP001 	sal_Unicode nReturn( _nFallback );
//STRIP001 	if ( _rSeparator.Len() )
//STRIP001 		nReturn = static_cast< sal_Char >( _rSeparator.GetBuffer( )[0] );
//STRIP001 	return nReturn;
//STRIP001 }

//-----------------------------------------------------------------------------
//STRIP001 sal_Unicode OSystemParseContext::getNumDecimalSep( ) const
//STRIP001 {
//STRIP001 	return lcl_getSeparatorChar( SvtSysLocale().GetLocaleData().getNumDecimalSep(), '.' );
//STRIP001 }

//-----------------------------------------------------------------------------
//STRIP001 sal_Unicode OSystemParseContext::getNumThousandSep( ) const
//STRIP001 {
//STRIP001 	return lcl_getSeparatorChar( SvtSysLocale().GetLocaleData().getNumThousandSep(), ',' );
//STRIP001 }
// -----------------------------------------------------------------------------
/*?*/ IParseContext::InternationalKeyCode OSystemParseContext::getIntlKeyCode(const ::rtl::OString& rToken) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return KEY_NONE;//STRIP001 
//STRIP001 	static IParseContext::InternationalKeyCode Intl_TokenID[] =
//STRIP001 	{
//STRIP001 		KEY_LIKE, KEY_NOT, KEY_NULL, KEY_TRUE,
//STRIP001 		KEY_FALSE, KEY_IS, KEY_BETWEEN, KEY_OR,
//STRIP001 		KEY_AND, KEY_AVG, KEY_COUNT, KEY_MAX,
//STRIP001 		KEY_MIN, KEY_SUM
//STRIP001 	};
//STRIP001 
//STRIP001 	sal_uInt32 nCount = sizeof Intl_TokenID / sizeof Intl_TokenID[0];
//STRIP001 	for (sal_uInt32 i = 0; i < nCount; i++)
//STRIP001 	{
//STRIP001 		::rtl::OString aKey = getIntlKeywordAscii(Intl_TokenID[i]);
//STRIP001 		if (rToken.equalsIgnoreAsciiCase(aKey))
//STRIP001 			return Intl_TokenID[i];
//STRIP001 	}														    
//STRIP001 
//STRIP001 	return KEY_NONE;
/*?*/ }


// =============================================================================
// =============================================================================
namespace
{
    // -----------------------------------------------------------------------------
/*N*/ 	::osl::Mutex& getSafteyMutex()
/*N*/ 	{
/*N*/ 		static ::osl::Mutex s_aSafety;
/*N*/ 		return s_aSafety;
/*N*/ 	}
    // -----------------------------------------------------------------------------
/*N*/ 	oslInterlockedCount& getCounter()
/*N*/ 	{
/*N*/ 		static oslInterlockedCount s_nCounter;
/*N*/ 		return s_nCounter;
/*N*/ 	}
    // -----------------------------------------------------------------------------
/*N*/ 	OSystemParseContext* getSharedContext(OSystemParseContext* _pContext = NULL,sal_Bool _bSet = sal_False)
/*N*/ 	{
/*N*/ 		static OSystemParseContext* s_pSharedContext = NULL;
/*N*/ 		if ( _pContext && !s_pSharedContext || _bSet )
/*N*/ 			s_pSharedContext = _pContext;
/*N*/ 		return s_pSharedContext;
    }
    // -----------------------------------------------------------------------------
}
// -----------------------------------------------------------------------------
/*N*/ OParseContextClient::OParseContextClient()
/*N*/ {
/*N*/ 	::osl::MutexGuard aGuard( getSafteyMutex() );
/*N*/ 	if ( 1 == osl_incrementInterlockedCount( &getCounter() ) )
/*N*/ 	{	// first instance
/*N*/ 		getSharedContext( new OSystemParseContext );
/*N*/ 	}
/*N*/ }

// -----------------------------------------------------------------------------
/*N*/ OParseContextClient::~OParseContextClient()
/*N*/ {
/*N*/ 	{
/*N*/ 		::osl::MutexGuard aGuard( getSafteyMutex() );
/*N*/ 		if ( 0 == osl_decrementInterlockedCount( &getCounter() ) )
/*N*/ 			delete getSharedContext(NULL,sal_True);
/*N*/ 	}
/*N*/ }
// -----------------------------------------------------------------------------
/*N*/ const OSystemParseContext* OParseContextClient::getParseContext() const 
/*N*/ { DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001 
//STRIP001 	return getSharedContext(); 
/*N*/ }
// -----------------------------------------------------------------------------





}
