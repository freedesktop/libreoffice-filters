/*************************************************************************
 *
 *  $RCSfile: sch_chtmode6.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 12:45:31 $
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

#include <bf_svx/eeitem.hxx>
//svdraw.hxx
#define _SDR_NOITEMS
#define _SDR_NOTOUCH
#define _SDR_NOTRANSFORM
//#define _SDR_NOOBJECTS
//#define _SDR_NOVIEWS ***

//#define SI_NOITEMS
//#define SI_NODRW
#define _SI_NOSBXCONTROLS
#define _SI_NOOTHERFORMS
#define _SI_NOCONTROL
#define _SI_NOSBXCONTROLS

#ifndef _XDEF_HXX
#include <bf_svx/xdef.hxx>
#endif

#ifndef _SV_MENU_HXX //autogen
// auto strip #include <vcl/menu.hxx>
// auto strip #include <bf_svx/svdattr.hxx>
#endif

// auto strip #include <bf_svx/svdattr.hxx>
// auto strip #ifndef _XTABLE_HXX
// auto strip #include <bf_svx/xtable.hxx>
// auto strip #endif
#ifndef _SCHATTR_HXX
#include "schattr.hxx"
#endif

#ifndef _SVX_CHRTITEM_HXX //autogen
#define ITEMID_DOUBLE			0
#define ITEMID_CHARTTEXTORDER	SCHATTR_TEXT_ORDER
#define ITEMID_CHARTTEXTORIENT	SCHATTR_TEXT_ORIENT
#define ITEMID_CHARTLEGENDPOS	SCHATTR_LEGEND_POS
#define ITEMID_CHARTDATADESCR	SCHATTR_DATADESCR_DESCR

#ifndef _SFXENUMITEM_HXX
#include <svtools/eitem.hxx>
#endif

// auto strip #include <bf_svx/chrtitem.hxx>
#endif

#define ITEMID_FONT 	   EE_CHAR_FONTINFO
#define ITEMID_COLOR	   EE_CHAR_COLOR
#define ITEMID_FONTHEIGHT  EE_CHAR_FONTHEIGHT
// auto strip #include <bf_svx/fontitem.hxx>
// auto strip #include <bf_svx/fhgtitem.hxx>
// auto strip #include <bf_svx/colritem.hxx>

#include <string.h> 			// memset

#ifndef _SVX_DIALOGS_HRC
#include <bf_svx/dialogs.hrc>
#endif

#ifndef _CHTMODEL_HXX
// auto strip #include <chtmodel.hxx>
// auto strip #include <globfunc.hxx>
#endif

#include "docshell.hxx"

// auto strip #include <bf_svx/svdpage.hxx>




// auto strip #ifndef _SFX_WHITER_HXX //autogen
// auto strip #include <svtools/whiter.hxx>
// auto strip #endif

#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* MapMode des Printers auf Seitengroesse einstellen
|*
\************************************************************************/

/*N*/ void ChartModel::AdjustPrinter()
/*N*/ {
/*N*/ 	SchChartDocShell* pDocSh = (SchChartDocShell*) pDocShell;
/*N*/ 
/*N*/ 	if (!pDocSh)
/*N*/ 	{
/*?*/ 		pDocSh = PTR_CAST(SchChartDocShell, SfxObjectShell::Current());
/*N*/ 	}
/*N*/ 
/*N*/ 	if (pDocSh)
/*N*/ 	{
/*N*/ 		SfxPrinter* pPrinter = pDocSh->GetPrinter();
/*N*/ 
/*N*/ 		if (pPrinter && pPrinter->IsValid())
/*N*/ 		{
/*N*/ 			MapMode aOldMap = pPrinter->GetMapMode();
/*N*/ 			MapMode aMap(aOldMap);
/*N*/ 			aMap.SetMapUnit(MAP_100TH_MM);
/*N*/ 			aMap.SetScaleX(Fraction(1,1));
/*N*/ 			aMap.SetScaleY(Fraction(1,1));
/*N*/ 			pPrinter->SetMapMode(aMap);
/*N*/ 			Size aPrintSize = pPrinter->GetOutputSize();
/*N*/ 
/*N*/ 			SdrPage* pPage = GetPage( 0 );
/*N*/ 			DBG_ASSERT( pPage, "Invalid Page!" );
/*N*/ 
/*N*/ 			Size aPageSize( 0, 0 );
/*N*/ 			long nPageWidth = 0,
/*N*/ 				nPageHeight = 0;
/*N*/ 
/*N*/ 			if( pPage )
/*N*/ 			{
/*N*/ 				aPageSize = pPage->GetSize();
/*N*/ 				nPageWidth = aPageSize.Width();
/*N*/ 				nPageHeight = aPageSize.Height();
/*N*/ 			}
/*N*/ 
/*N*/ 			const long nPrintWidth = aPrintSize.Width();
/*N*/ 			const long nPrintHeight= aPrintSize.Height();
/*N*/ 
/*N*/ 			if( nPageHeight > 0 &&
/*N*/ 				nPageWidth  > 0 &&
/*N*/ 				nPrintHeight > 0 &&
/*N*/ 				nPrintWidth  > 0 )
/*N*/ 			{
/*N*/ 				// landscape mode
/*N*/ 				if( pPrinter->GetOrientation() == ORIENTATION_LANDSCAPE )
/*N*/ 				{
/*?*/ 					double fVert  = (double)nPrintWidth  / (double)nPageWidth;
/*?*/ 					double fHorz  = (double)nPrintHeight / (double)nPageHeight;
/*?*/ 					BOOL   bVert;
/*?*/ 
/*?*/ 					// bestimmung, welche richtung das hauptgewicht der skalierung hat. dazu werden
/*?*/ 					// papier- und seitengroesse verglichen und nach der richtung mit der geringeren
/*?*/ 					// abweichung (1:1) wird die skalierung bestimmt.
/*?*/ 					// bVert bestimmt nachfolgend die einpassung in das papier, je nachdem, ob das
/*?*/ 					// chart im hochformat oder quer ausgerichtet (nicht gedruckt !) ist.
/*?*/ 					//
/*?*/ 					if (fHorz < 1.0)
/*?*/ 						if (fVert < 1.0)
/*?*/ 						{
/*?*/ 							// wird in jede richtung vergroessert
/*?*/ 							bVert = fHorz < fVert;
/*?*/ 							Fraction aFract = bVert
/*?*/ 								? Fraction( nPrintWidth, nPageWidth )
/*?*/ 								: Fraction( nPrintHeight,nPageHeight );
/*?*/ 
/*?*/ 							aMap.SetScaleX(aFract);
/*?*/ 							aMap.SetScaleY(aFract);
/*?*/ 						}
/*?*/ 						else
/*?*/ 						{
/*?*/ 							// horizontal verkleinert, vertikal vergroessert
/*?*/ 							bVert = (fVert - 1.0) < (1.0 - fHorz);
/*?*/ 							Fraction aFract = bVert
/*?*/ 								? Fraction( nPrintWidth, nPageWidth )
/*?*/ 								: Fraction( nPrintHeight,nPageHeight );
/*?*/ 
/*?*/ 							aMap.SetScaleX(aFract);
/*?*/ 							aMap.SetScaleY(aFract);
/*?*/ 						}
/*?*/ 					else if (fVert < 1.0)
/*?*/ 					{
/*?*/ 						// vertikal verkleinert, horizontal vergroessert
/*?*/ 						bVert = (1.0 - fVert) < (fHorz - 1.0);//TEST2
/*?*/ 						Fraction aFract = bVert
/*?*/ 							? Fraction( nPrintWidth, nPageWidth )
/*?*/ 							: Fraction( nPrintHeight,nPageHeight );
/*?*/ 
/*?*/ 						aMap.SetScaleX(aFract);
/*?*/ 						aMap.SetScaleY(aFract);
/*?*/ 					}
/*?*/ 					else
/*?*/ 					{
/*?*/ 						// wird in jede richtung verkleinert
/*?*/ 						bVert = fVert < fHorz;
/*?*/ 						Fraction aFract = bVert
/*?*/ 							? Fraction( nPrintWidth, nPageWidth )
/*?*/ 							: Fraction( nPrintHeight,nPageHeight );
/*?*/ 
/*?*/ 						aMap.SetScaleX(aFract);
/*?*/ 						aMap.SetScaleY(aFract);
/*?*/ 					}
/*?*/ 
/*?*/ 					if (bVert)
/*?*/ 					{
/*?*/ 						Fraction aYFract = aMap.GetScaleY ();//TEST1,2
/*?*/ 
/*?*/ 						aMap.SetOrigin(Point(0, (aPrintSize.Height () - aPageSize.Height () * aYFract.GetNumerator () / aYFract.GetDenominator ()) /
/*?*/ 											 2 * aYFract.GetDenominator () / aYFract.GetNumerator ()));
/*?*/ 					}
/*?*/ 					else
/*?*/ 					{
/*?*/ 						Fraction aXFract = aMap.GetScaleX ();
/*?*/ 
/*?*/ 						aMap.SetOrigin(Point((aPrintSize.Width () - aPageSize.Width () * aXFract.GetNumerator () / aXFract.GetDenominator ()) /
/*?*/ 											 2 * aXFract.GetDenominator () / aXFract.GetNumerator (), 0));
/*?*/ 					}
/*?*/ 				}
/*N*/ 				// portrait mode
/*N*/ 				else
/*N*/ 				{
/*N*/ 					double fHorz  = (double)nPrintWidth  / (double)nPageWidth;
/*N*/ 					double fVert  = (double)nPrintHeight / (double)nPageHeight;
/*N*/ 					BOOL   bHorz;
/*N*/ 
/*N*/ 					if (fHorz < 1.0)
/*N*/ 						if (fVert < 1.0)
/*N*/ 						{
/*?*/ 							bHorz = fVert < fHorz;
/*?*/ 							Fraction aFract = bHorz
/*?*/ 								? Fraction( nPrintWidth, nPageWidth )
/*?*/ 								: Fraction( nPrintHeight, nPageHeight );
/*?*/ 
/*?*/ 							aMap.SetScaleX(aFract);
/*?*/ 							aMap.SetScaleY(aFract);
/*N*/ 						}
/*N*/ 						else
/*N*/ 						{
/*?*/ 							bHorz = (1.0 - fHorz) < (fVert - 1.0);
/*?*/ 							Fraction aFract = bHorz
/*?*/ 								? Fraction( nPrintWidth, nPageWidth)
/*?*/ 								: Fraction( nPrintHeight, nPageHeight);
/*?*/ 
/*?*/ 							aMap.SetScaleX(aFract);
/*?*/ 							aMap.SetScaleY(aFract);
/*N*/ 						}
/*N*/ 					else if (fVert < 1.0)
/*N*/ 					{
/*?*/ 						bHorz = (fHorz - 1.0) < (1.0 - fVert);
/*?*/ 						Fraction aFract = bHorz
/*?*/ 							? Fraction( nPrintWidth, nPageWidth)
/*?*/ 							: Fraction( nPrintHeight, nPageHeight);
/*?*/ 
/*?*/ 						aMap.SetScaleX(aFract);
/*?*/ 						aMap.SetScaleY(aFract);
/*?*/ 					}
/*N*/ 					else
/*N*/ 					{
/*N*/ 						bHorz = (fHorz < fVert);
/*N*/ 						Fraction aFract = bHorz
/*N*/ 							? Fraction( nPrintWidth, nPageWidth )
/*N*/ 							: Fraction( nPrintHeight, nPageHeight );
/*N*/ 
/*N*/ 						aMap.SetScaleX(aFract);
/*N*/ 						aMap.SetScaleY(aFract);
/*N*/ 					}
/*N*/ 
/*N*/ 					if (bHorz)
/*N*/ 					{
/*N*/ 						Fraction aYFract = aMap.GetScaleY ();
/*N*/ 
/*N*/ 						aMap.SetOrigin(Point(0, (aPrintSize.Height () - aPageSize.Height () * aYFract.GetNumerator () / aYFract.GetDenominator ()) /
/*N*/ 											 2 * aYFract.GetDenominator () / aYFract.GetNumerator ()));
/*N*/ 					}
/*N*/ 					else
/*N*/ 					{
/*?*/ 						Fraction aXFract = aMap.GetScaleX ();
/*?*/ 
/*?*/ 						aMap.SetOrigin(Point((aPrintSize.Width () - aPageSize.Width () * aXFract.GetNumerator () / aXFract.GetDenominator ()) /
/*?*/ 											 2 * aXFract.GetDenominator () / aXFract.GetNumerator (), 0));
/*N*/ 					}
/*N*/ 				}
/*N*/ 			}
/*N*/ 			
/*N*/ 			pPrinter->SetMapMode(aMap);
/*N*/ 		}
/*N*/ 	}
/*N*/ }



}
