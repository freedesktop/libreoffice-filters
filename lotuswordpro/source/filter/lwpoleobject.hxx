/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
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
 *  The Initial Developer of the Original Code is: IBM Corporation
 *
 *  Copyright: 2008 by IBM Corporation
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
/**
 * @file
 *  For LWP filter architecture prototype - OLE object
 */
/*************************************************************************
 * Change History
 Feb 2005		 	Created
 ************************************************************************/
#ifndef _LWPOLEOBJECT_HXX_
#define _LWPOLEOBJECT_HXX_

#include "lwpobj.hxx"
#include "lwpobjhdr.hxx"
#include "lwpobjid.hxx"
#include "lwpstory.hxx"
#include "tools/gen.hxx"
/*
#include <so3/svstor.hxx>
#include <so3/outplace.hxx>
#include <so3/ipobj.hxx>
#include <so3/factory.hxx>
*/
#include <svx/svdoole2.hxx>
#include <svx/svdpage.hxx>
#include <sfx2/objsh.hxx>
#include <sot/storinfo.hxx>


typedef struct tagAFID_CACHE
{
    unsigned long LinkedFileSize;				/* 0 if not linked */
    unsigned long LinkedFileTime;				/* 0 if not linked */
    long Width;								/* -1 if not present */
    long Height;								/* -1 if not present */
} AFID_CACHE,  * PAFID_CACHE;

/* Maximum string sizes - includes space for null terminator */
#define AFID_MAX_FILE_FORMAT_SIZE                	80
#define AFID_MAX_CONTEXT_FORMAT_SIZE             	80

// OLE defined maximum
#define MAX_STREAMORSTORAGENAME		32
/**
 * @descr
 * super class of LwpOleObject and LwpGraphicObject
 */
class LwpGraphicOleObject : public LwpContent
{
public:
    LwpGraphicOleObject(LwpObjectHeader& objHdr, LwpSvStream* pStrm);
    virtual void Read();
    virtual void GetGrafScaledSize(double& fWidth, double& fHeight);
    virtual void GetGrafOrgSize(double& rWidth, double& rHeight);
protected:
    LwpObjectID m_pPrevObj;
    LwpObjectID m_pNextObj;

    rtl::OUString m_strStyleName;
};

class LwpFrameLayout;
/**
 * @descr
 * class to read and parse VO_OLEOBJECT object
 */
class LwpOleObject : public LwpGraphicOleObject
{
public:
    LwpOleObject(LwpObjectHeader& objHdr, LwpSvStream* pStrm);
    ~LwpOleObject(){};
    virtual void Read();
    virtual void Parse(IXFStream* pOutputStream);
    virtual void XFConvert(XFContentContainer * pCont);
    virtual void RegisterStyle();
    void GetGrafOrgSize(double& rWidth, double& rHeight) ;
private:
    void GetChildStorageName(char *pObjName);
    Rectangle GetOLEObjectSize( SotStorage * pStor ) const;

    sal_uInt16 cPersistentFlags;

    Rectangle m_SizeRect;
};

/**
*  Added by  for SODC_2667,03/20/2006
*  Read the OLE Object stream and get the info of the OLE picture
*/
#include <tools/stream.hxx>
#include <vcl/gdimtf.hxx>
#include <vcl/bitmap.hxx>
#include <vcl/outdev.hxx>
class LwpOlePres
{
    ULONG	nFormat;
    USHORT	nAspect;
    Bitmap *		pBmp;
    GDIMetaFile *	pMtf;

    UINT32  nAdvFlags;
    INT32 	nJobLen;
    BYTE *	pJob;
    Size	aSize;		// Groesse in 100TH_MM
public:
    LwpOlePres( ULONG nF )
        : nFormat( nF )
        , pBmp( NULL )
        , pMtf( NULL )
        , nAdvFlags( 0x2 ) // in Dokument gefunden
        , nJobLen( 0 )
        , pJob( NULL )
    {}
    ~LwpOlePres()
    {
        delete [] pJob;
        delete pBmp;
        delete pMtf;
    }
    void	SetMtf( const GDIMetaFile & rMtf )
    {
        if( pMtf )
            delete pMtf;
        pMtf = new GDIMetaFile( rMtf );
    }
    Bitmap *GetBitmap() const { return pBmp; }
    GDIMetaFile *GetMetaFile() const { return pMtf; }
    ULONG	GetFormat() const { return nFormat; }
    void	SetAspect( USHORT nAsp ) { nAspect = nAsp; }
    ULONG	GetAdviseFlags() const { return nAdvFlags; }
    void	SetAdviseFlags( ULONG nAdv ) { nAdvFlags = nAdv; }
    void	SetSize( const Size & rSize ) { aSize = rSize; }
    Size GetSize() const { return aSize; } //Add by , 10/26/2005
    /// return FALSE => unknown format
    BOOL 	Read( SvStream & rStm );
    void 	Write( SvStream & rStm );
};
//End by


#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
