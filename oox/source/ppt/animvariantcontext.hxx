/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: animvariantcontext.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-01-17 08:06:00 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2007 by Sun Microsystems, Inc.
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



#ifndef OOX_PPT_ANIMVARIANTCONTEXT
#define OOX_PPT_ANIMVERIANTCONTEXT


#include <com/sun/star/uno/Any.hxx>

#include "oox/core/context.hxx"
#include "oox/core/fragmenthandler.hxx"
#include "oox/drawingml/color.hxx"

namespace oox { namespace ppt {

    /** context CT_TLAnimVariant */
    class AnimVariantContext
        : public ::oox::core::Context
    {
    public:
        AnimVariantContext( const ::oox::core::FragmentHandlerRef & xHandler, ::sal_Int32 aElement, ::com::sun::star::uno::Any & aValue );
        ~AnimVariantContext( ) throw( );
        virtual void SAL_CALL endFastElement( sal_Int32 /*aElement*/ ) throw ( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken, const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& xAttribs ) throw ( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );
        
    private:
        ::sal_Int32 mnElement;
        ::com::sun::star::uno::Any& maValue;
        ::oox::drawingml::Color		maColor;
    };

} }


#endif
