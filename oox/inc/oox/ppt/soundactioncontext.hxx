/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: soundactioncontext.hxx,v $
 * $Revision: 1.4 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/


#ifndef OOX_PPT_SOUNDACTIONCONTEXT
#define OOX_PPT_SOUNDACTIONCONTEXT

#include "oox/core/contexthandler.hxx"

namespace oox { class PropertyMap; }

namespace oox { namespace ppt {

class SoundActionContext : public ::oox::core::ContextHandler
{
public:
    SoundActionContext( ::oox::core::ContextHandler& rParent, PropertyMap & aProperties ) throw();
    virtual ~SoundActionContext() throw();

    virtual void SAL_CALL endFastElement( sal_Int32 aElement ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 Element, const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& Attribs ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

private:
    PropertyMap&                    maSlideProperties;
    bool                              mbHasStartSound;
    bool                              mbLoopSound;
    bool                              mbStopSound;
    ::rtl::OUString                   msEmbedded;
    ::rtl::OUString                   msLink;
    ::rtl::OUString                   msSndName;
};

} }



#endif
