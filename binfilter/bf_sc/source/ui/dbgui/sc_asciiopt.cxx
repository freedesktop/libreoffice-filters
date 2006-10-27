/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_asciiopt.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 15:43:09 $
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

#ifdef PCH
#endif

#pragma hdrstop

#include "asciiopt.hxx"
#include "asciiopt.hrc"

#ifndef _RTL_TENCINFO_H
#include <rtl/tencinfo.h>
#endif
namespace binfilter {


// ============================================================================

//! TODO make dynamic
#ifdef WIN
const sal_Int32 ASCIIDLG_MAXROWS                = 10000;
#else
const sal_Int32 ASCIIDLG_MAXROWS                = 32000;
#endif

static const sal_Char __FAR_DATA pStrFix[] = "FIX";
static const sal_Char __FAR_DATA pStrMrg[] = "MRG";


// ============================================================================

/*N*/ ScAsciiOptions::ScAsciiOptions() :
/*N*/ 	bFixedLen		( FALSE ),
/*N*/ 	aFieldSeps		( ';' ),
/*N*/ 	bMergeFieldSeps	( FALSE ),
/*N*/ 	cTextSep		( 34 ),
/*N*/ 	eCharSet		( gsl_getSystemTextEncoding() ),
/*N*/ 	bCharSetSystem	( FALSE ),
/*N*/ 	nStartRow		( 1 ),
/*N*/ 	nInfoCount		( 0 ),
/*N*/     pColStart       ( NULL ),
/*N*/ 	pColFormat		( NULL )
/*N*/ {
/*N*/ }


/*N*/ ScAsciiOptions::ScAsciiOptions(const ScAsciiOptions& rOpt) :
/*N*/ 	bFixedLen		( rOpt.bFixedLen ),
/*N*/ 	aFieldSeps		( rOpt.aFieldSeps ),
/*N*/ 	bMergeFieldSeps	( rOpt.bMergeFieldSeps ),
/*N*/ 	cTextSep		( rOpt.cTextSep ),
/*N*/ 	eCharSet		( rOpt.eCharSet ),
/*N*/ 	bCharSetSystem	( rOpt.bCharSetSystem ),
/*N*/ 	nStartRow		( rOpt.nStartRow ),
/*N*/ 	nInfoCount		( rOpt.nInfoCount )
/*N*/ {
/*N*/ 	if (nInfoCount)
/*N*/ 	{
/*N*/ 		pColStart = new xub_StrLen[nInfoCount];
/*N*/ 		pColFormat = new BYTE[nInfoCount];
/*N*/ 		for (USHORT i=0; i<nInfoCount; i++)
/*N*/ 		{
/*N*/ 			pColStart[i] = rOpt.pColStart[i];
/*N*/ 			pColFormat[i] = rOpt.pColFormat[i];
/*N*/ 		}
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		pColStart = NULL;
/*N*/ 		pColFormat = NULL;
/*N*/ 	}
/*N*/ }


/*N*/ ScAsciiOptions::~ScAsciiOptions()
/*N*/ {
/*N*/ 	delete[] pColStart;
/*N*/ 	delete[] pColFormat;
/*N*/ }









//
//	Der Options-String darf kein Semikolon mehr enthalten (wegen Pickliste)
//	darum ab Version 336 Komma stattdessen
//


/*N*/ void ScAsciiOptions::ReadFromString( const String& rString )
/*N*/ {
/*N*/ 	xub_StrLen nCount = rString.GetTokenCount(',');
/*N*/ 	String aToken;
/*N*/ 	xub_StrLen nSub;
/*N*/ 	xub_StrLen i;
/*N*/ 
/*N*/ 		//
/*N*/ 		//	Feld-Trenner
/*N*/ 		//
/*N*/ 
/*N*/ 	if ( nCount >= 1 )
/*N*/ 	{
/*N*/ 		bFixedLen = bMergeFieldSeps = FALSE;
/*N*/ 		aFieldSeps.Erase();
/*N*/ 
/*N*/ 		aToken = rString.GetToken(0,',');
/*N*/ 		if ( aToken.EqualsAscii(pStrFix) )
/*N*/ 			bFixedLen = TRUE;
/*N*/ 		nSub = aToken.GetTokenCount('/');
/*N*/ 		for ( i=0; i<nSub; i++ )
/*N*/ 		{
/*N*/ 			String aCode = aToken.GetToken( i, '/' );
/*N*/ 			if ( aCode.EqualsAscii(pStrMrg) )
/*N*/ 				bMergeFieldSeps = TRUE;
/*N*/ 			else
/*N*/ 			{
/*N*/ 				sal_Int32 nVal = aCode.ToInt32();
/*N*/ 				if ( nVal )
/*N*/ 					aFieldSeps += (sal_Unicode) nVal;
/*N*/ 			}
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 		//
/*N*/ 		//	Text-Trenner
/*N*/ 		//
/*N*/ 
/*N*/ 	if ( nCount >= 2 )
/*N*/ 	{
/*N*/ 		aToken = rString.GetToken(1,',');
/*N*/ 		sal_Int32 nVal = aToken.ToInt32();
/*N*/ 		cTextSep = (sal_Unicode) nVal;
/*N*/ 	}
/*N*/ 
/*N*/ 		//
/*N*/ 		//	Zeichensatz
/*N*/ 		//
/*N*/ 
/*N*/ 	if ( nCount >= 3 )
/*N*/ 	{
/*N*/ 		aToken = rString.GetToken(2,',');
/*N*/ 		eCharSet = ScGlobal::GetCharsetValue( aToken );
/*N*/ 	}
/*N*/ 
/*N*/ 		//
/*N*/ 		//	Startzeile
/*N*/ 		//
/*N*/ 
/*N*/ 	if ( nCount >= 4 )
/*N*/ 	{
/*N*/ 		aToken = rString.GetToken(3,',');
/*N*/ 		nStartRow = aToken.ToInt32();
/*N*/ 	}
/*N*/ 
/*N*/ 		//
/*N*/ 		//	Spalten-Infos
/*N*/ 		//
/*N*/ 
/*N*/ 	if ( nCount >= 5 )
/*N*/ 	{
/*N*/ 		delete[] pColStart;
/*N*/ 		delete[] pColFormat;
/*N*/ 
/*N*/ 		aToken = rString.GetToken(4,',');
/*N*/ 		nSub = aToken.GetTokenCount('/');
/*N*/ 		nInfoCount = nSub / 2;
/*N*/ 		if (nInfoCount)
/*N*/ 		{
/*N*/ 			pColStart = new xub_StrLen[nInfoCount];
/*N*/ 			pColFormat = new BYTE[nInfoCount];
/*N*/ 			for (USHORT nInfo=0; nInfo<nInfoCount; nInfo++)
/*N*/ 			{
/*N*/ 				pColStart[nInfo]  = (xub_StrLen) aToken.GetToken( 2*nInfo, '/' ).ToInt32();
/*N*/ 				pColFormat[nInfo] = (BYTE) aToken.GetToken( 2*nInfo+1, '/' ).ToInt32();
/*N*/ 			}
/*N*/ 		}
/*N*/ 		else
/*N*/ 		{
/*N*/ 			pColStart = NULL;
/*N*/ 			pColFormat = NULL;
/*N*/ 		}
/*N*/ 	}
/*N*/ }


/*N*/ String ScAsciiOptions::WriteToString() const
/*N*/ {
/*N*/ 	String aOutStr;
/*N*/ 
/*N*/ 		//
/*N*/ 		//	Feld-Trenner
/*N*/ 		//
/*N*/ 
/*N*/ 	if ( bFixedLen )
/*N*/ 		aOutStr.AppendAscii(pStrFix);
/*N*/ 	else if ( !aFieldSeps.Len() )
/*N*/ 		aOutStr += '0';
/*N*/ 	else
/*N*/ 	{
/*N*/ 		xub_StrLen nLen = aFieldSeps.Len();
/*N*/ 		for (xub_StrLen i=0; i<nLen; i++)
/*N*/ 		{
/*N*/ 			if (i)
/*N*/ 				aOutStr += '/';
/*N*/ 			aOutStr += String::CreateFromInt32(aFieldSeps.GetChar(i));
/*N*/ 		}
/*N*/ 		if ( bMergeFieldSeps )
/*N*/ 		{
/*N*/ 			aOutStr += '/';
/*N*/ 			aOutStr.AppendAscii(pStrMrg);
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	aOutStr += ',';					// Token-Ende
/*N*/ 
/*N*/ 		//
/*N*/ 		//	Text-Trenner
/*N*/ 		//
/*N*/ 
/*N*/ 	aOutStr += String::CreateFromInt32(cTextSep);
/*N*/ 	aOutStr += ',';					// Token-Ende
/*N*/ 
/*N*/ 		//
/*N*/ 		//	Zeichensatz
/*N*/ 		//
/*N*/ 
/*N*/ 	if ( bCharSetSystem )			// force "SYSTEM"
/*N*/ 		aOutStr += ScGlobal::GetCharsetString( RTL_TEXTENCODING_DONTKNOW );
/*N*/ 	else
/*N*/ 		aOutStr += ScGlobal::GetCharsetString( eCharSet );
/*N*/ 	aOutStr += ',';					// Token-Ende
/*N*/ 
/*N*/ 		//
/*N*/ 		//	Startzeile
/*N*/ 		//
/*N*/ 
/*N*/ 	aOutStr += String::CreateFromInt32(nStartRow);
/*N*/ 	aOutStr += ',';					// Token-Ende
/*N*/ 
/*N*/ 		//
/*N*/ 		//	Spalten-Infos
/*N*/ 		//
/*N*/ 
/*N*/ 	DBG_ASSERT( !nInfoCount || (pColStart && pColFormat), "0-Zeiger in ScAsciiOptions" );
/*N*/ 	for (USHORT nInfo=0; nInfo<nInfoCount; nInfo++)
/*N*/ 	{
/*N*/ 		if (nInfo)
/*N*/ 			aOutStr += '/';
/*N*/ 		aOutStr += String::CreateFromInt32(pColStart[nInfo]);
/*N*/ 		aOutStr += '/';
/*N*/ 		aOutStr += String::CreateFromInt32(pColFormat[nInfo]);
/*N*/ 	}
/*N*/ 
/*N*/ 	return aOutStr;
/*N*/ }

#if 0
//	Code, um die Spalten-Liste aus einem Excel-kompatiblen String zu erzeugen:
//	(im Moment nicht benutzt)

#endif


// ============================================================================

void lcl_FillCombo( ComboBox& rCombo, const String& rList, sal_Unicode cSelect )
{
    DBG_BF_ASSERT(0, "STRIP"); //STRIP001 xub_StrLen i;
}

sal_Unicode lcl_CharFromCombo( ComboBox& rCombo, const String& rList )
{
    sal_Unicode c = 0;
    DBG_BF_ASSERT(0, "STRIP"); //STRIP001 String aStr = rCombo.GetText();
    return c;
}


// ----------------------------------------------------------------------------










// ----------------------------------------------------------------------------








}
