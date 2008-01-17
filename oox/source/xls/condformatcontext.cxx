/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: condformatcontext.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-01-17 08:06:08 $
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

#include "oox/xls/condformatcontext.hxx"

using ::rtl::OUString;

namespace oox {
namespace xls {

// ============================================================================

OoxCondFormatContext::OoxCondFormatContext( const OoxWorksheetFragmentBase& rFragment ) :
    OoxWorksheetContextBase( rFragment )
{
}

// oox.xls.OoxContextHelper interface -----------------------------------------

bool OoxCondFormatContext::onCanCreateContext( sal_Int32 nElement ) const
{
    switch( getCurrentContext() )
    {
        case XLS_TOKEN( conditionalFormatting ):
            return  (nElement == XLS_TOKEN( cfRule ));
        case XLS_TOKEN( cfRule ):
            return  (nElement == XLS_TOKEN( formula ));
    }
    return false;
}

void OoxCondFormatContext::onStartElement( const AttributeList& rAttribs )
{
    switch( getCurrentContext() )
    {
        case XLS_TOKEN( conditionalFormatting ):
            mxCondFmt = getCondFormats().importConditionalFormatting( rAttribs );
        break;
        case XLS_TOKEN( cfRule ):
            if( mxCondFmt.get() ) mxRule = mxCondFmt->importCfRule( rAttribs );
        break;
    }
}

void OoxCondFormatContext::onEndElement( const OUString& rChars )
{
    switch( getCurrentContext() )
    {
        case XLS_TOKEN( formula ):
            if( mxCondFmt.get() && mxRule.get() ) mxRule->appendFormula( rChars );
        break;
    }
}

bool OoxCondFormatContext::onCanCreateRecordContext( sal_Int32 nRecId )
{
    switch( getCurrentContext() )
    {
        case OOBIN_ID_CONDFORMATTING:
            return  (nRecId == OOBIN_ID_CFRULE);
    }
    return false;
}

void OoxCondFormatContext::onStartRecord( RecordInputStream& rStrm )
{
    switch( getCurrentContext() )
    {
        case OOBIN_ID_CONDFORMATTING:
            mxCondFmt = getCondFormats().importCondFormatting( rStrm );
        break;
        case OOBIN_ID_CFRULE:
            if( mxCondFmt.get() ) mxCondFmt->importCfRule( rStrm );
        break;
    }
}

// ============================================================================

} // namespace xls
} // namespace oox

