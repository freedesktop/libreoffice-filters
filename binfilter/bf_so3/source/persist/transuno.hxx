/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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

#ifndef _TRANSUNO_HXX
#define _TRANSUNO_HXX

#ifndef _RTL_USTRING_
#include <rtl/ustring.h>
#endif

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/uno/XInterface.hpp>
#include <com/sun/star/beans/Property.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/ucb/PropertyValueInfo.hpp>
#include <com/sun/star/ucb/XContent.hpp>
#include <com/sun/star/ucb/XCommandProcessor.hpp>
#include <com/sun/star/sdbc/XRow.hpp>

using com::sun::star::beans::PropertyValue;
using com::sun::star::beans::Property;
using com::sun::star::ucb::XContent;
using com::sun::star::ucb::XCommandProcessor;

namespace binfilter {

/*========================================================================
 *
 * SvBindingTransport_Impl interface.
 *
 *======================================================================*/
class SvBindingTransport_Impl
{
public:
    /** getProcessServiceFactory.
     */
    static com::sun::star::uno::Reference<com::sun::star::uno::XInterface>
    getProcessServiceFactory (void);

    /** createContent.
     */
    static com::sun::star::uno::Reference<XContent>
    createContent (
        const rtl::OUString &rUrl);

    /** getProperties.
     */
    static com::sun::star::uno::Any
    getProperties (
        const com::sun::star::uno::Reference<XCommandProcessor> &rxProc,
        const com::sun::star::uno::Sequence<Property>           &rxProp);

    /** setProperties.
     */
    static void setProperties (
        const com::sun::star::uno::Reference<XCommandProcessor> &rxProc,
        const com::sun::star::uno::Sequence<PropertyValue>           &rxProp);
};

/*========================================================================
 *
 * The End.
 *
 *======================================================================*/

}

#endif /* !_TRANSUNO_HXX */

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
