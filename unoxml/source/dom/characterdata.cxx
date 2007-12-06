/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: characterdata.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: vg $ $Date: 2007-12-06 10:58:40 $
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

#include <com/sun/star/xml/dom/events/XDocumentEvent.hpp>
#include "characterdata.hxx"
#include "../events/mutationevent.hxx"

namespace DOM
{

    CCharacterData::CCharacterData()
    {}

    void CCharacterData::_dispatchEvent(const OUString& prevValue, const OUString& newValue)
    {
        Reference< XDocumentEvent > docevent(getOwnerDocument(), UNO_QUERY);
        Reference< XMutationEvent > event(docevent->createEvent(
            OUString::createFromAscii("DOMCharacterDataModified")), UNO_QUERY);
        event->initMutationEvent(
                OUString::createFromAscii("DOMCharacterDataModified"),
                sal_True, sal_False, Reference< XNode >(),
                prevValue, newValue, OUString(), (AttrChangeType)0 );
        dispatchEvent(Reference< XEvent >(event, UNO_QUERY));
        dispatchSubtreeModified();
    }

    void CCharacterData::init_characterdata(const xmlNodePtr aNodePtr)
    {
        init_node(aNodePtr);
    }

    /**
    Append the string to the end of the character data of the node.
    */
    void SAL_CALL CCharacterData::appendData(const OUString& arg)
        throw (RuntimeException, DOMException)
    {
        if (m_aNodePtr != NULL)
        {
            OUString oldValue((char*)m_aNodePtr->content, strlen((char*)m_aNodePtr->content), RTL_TEXTENCODING_UTF8);
            xmlNodeAddContent(m_aNodePtr, (const xmlChar*)(OUStringToOString(arg, RTL_TEXTENCODING_UTF8).getStr()));
            OUString newValue((char*)m_aNodePtr->content, strlen((char*)m_aNodePtr->content), RTL_TEXTENCODING_UTF8);
            _dispatchEvent(oldValue, newValue);
        }
    }

    /**
    Remove a range of 16-bit units from the node.
    */
    void SAL_CALL CCharacterData::deleteData(sal_Int32 offset, sal_Int32 count)
        throw (RuntimeException, DOMException)
    {
        if (m_aNodePtr != NULL)
        {
            // get current data
            OString aData((const sal_Char*)xmlNodeGetContent(m_aNodePtr));
            OUString tmp(aData, aData.getLength(), RTL_TEXTENCODING_UTF8);
            if (offset > tmp.getLength() || offset < 0 || count < 0) {
                DOMException e;
                e.Code = DOMExceptionType_INDEX_SIZE_ERR;
                throw e;
            }
            if ((offset+count) > tmp.getLength())
                count = tmp.getLength() - offset;

            OUString tmp2 = tmp.copy(0, offset);
            tmp2 += tmp.copy(offset+count, tmp.getLength() - (offset+count));
            OUString oldValue((char*)m_aNodePtr->content, strlen((char*)m_aNodePtr->content), RTL_TEXTENCODING_UTF8);
            xmlNodeSetContent(m_aNodePtr, (const xmlChar*)(OUStringToOString(tmp2, RTL_TEXTENCODING_UTF8).getStr()));
            OUString newValue((char*)m_aNodePtr->content, strlen((char*)m_aNodePtr->content), RTL_TEXTENCODING_UTF8);
            _dispatchEvent(oldValue, newValue);

        }
    }


    /**
    Return the character data of the node that implements this interface.
    */
    OUString SAL_CALL CCharacterData::getData() throw (RuntimeException)
    {
        OUString aData;
        if (m_aNodePtr != NULL)
        {
            OSL_ENSURE(m_aNodePtr->content, "character data node with NULL content, please inform lars.oppermann@sun.com!");
            if (m_aNodePtr->content != NULL)
            {
                aData = OUString((const sal_Char*)m_aNodePtr->content, strlen((const sal_Char*)m_aNodePtr->content),  RTL_TEXTENCODING_UTF8);
            }
        }
        return aData;
    }

    /**
    The number of 16-bit units that are available through data and the
    substringData method below.
    */
    sal_Int32 CCharacterData::getLength() throw (RuntimeException)
    {
        sal_Int32 length = 0;
        if (m_aNodePtr != NULL)
        {
             OUString aData((const sal_Char*)m_aNodePtr->content, strlen((const sal_Char*)m_aNodePtr->content),  RTL_TEXTENCODING_UTF8);
             length = aData.getLength();
        }
        return length;
    }

    /**
    Insert a string at the specified 16-bit unit offset.
    */
    void SAL_CALL CCharacterData::insertData(sal_Int32 offset, const OUString& arg)
        throw (RuntimeException, DOMException)
    {
        if (m_aNodePtr != NULL)
        {
            // get current data
            OString aData((const sal_Char*)xmlNodeGetContent(m_aNodePtr));
            OUString tmp(aData, aData.getLength(), RTL_TEXTENCODING_UTF8);
            if (offset > tmp.getLength() || offset < 0) {
                DOMException e;
                e.Code = DOMExceptionType_INDEX_SIZE_ERR;
                throw e;
            }

            OUString tmp2 = tmp.copy(0, offset);
            tmp2 += arg;
            tmp2 += tmp.copy(offset, tmp.getLength() - offset);
            OUString oldValue((char*)m_aNodePtr->content, strlen((char*)m_aNodePtr->content), RTL_TEXTENCODING_UTF8);
            xmlNodeSetContent(m_aNodePtr, (const xmlChar*)(OUStringToOString(tmp2, RTL_TEXTENCODING_UTF8).getStr()));
            OUString newValue((char*)m_aNodePtr->content, strlen((char*)m_aNodePtr->content), RTL_TEXTENCODING_UTF8);
            _dispatchEvent(oldValue, newValue);

        }
    }


    /**
    Replace the characters starting at the specified 16-bit unit offset 
    with the specified string.
    */
    void SAL_CALL CCharacterData::replaceData(sal_Int32 offset, sal_Int32 count, const OUString& arg)
        throw (RuntimeException, DOMException)
    {
        if (m_aNodePtr != NULL)
        {
            // get current data
            OString aData((const sal_Char*)xmlNodeGetContent(m_aNodePtr));
            OUString tmp(aData, aData.getLength(), RTL_TEXTENCODING_UTF8);
            if (offset > tmp.getLength() || offset < 0 || count < 0){
                DOMException e;
                e.Code = DOMExceptionType_INDEX_SIZE_ERR;
                throw e;
            }
            if ((offset+count) > tmp.getLength())
                count = tmp.getLength() - offset;

            OUString tmp2 = tmp.copy(0, offset);
            tmp2 += arg;
            tmp2 += tmp.copy(offset+count, tmp.getLength() - (offset+count));
            OUString oldValue((char*)m_aNodePtr->content, strlen((char*)m_aNodePtr->content), RTL_TEXTENCODING_UTF8);
            xmlNodeSetContent(m_aNodePtr, (const xmlChar*)(OUStringToOString(tmp2, RTL_TEXTENCODING_UTF8).getStr()));
            OUString newValue((char*)m_aNodePtr->content, strlen((char*)m_aNodePtr->content), RTL_TEXTENCODING_UTF8);
            _dispatchEvent(oldValue, newValue);
        }
    }

    /**
    Set the character data of the node that implements this interface.
    */
    void SAL_CALL CCharacterData::setData(const OUString& data)
        throw (RuntimeException, DOMException)
    {
        if (m_aNodePtr != NULL)
        {
            OUString oldValue((char*)m_aNodePtr->content, strlen((char*)m_aNodePtr->content), RTL_TEXTENCODING_UTF8);
            xmlNodeSetContent(m_aNodePtr, (const xmlChar*)(OUStringToOString(data, RTL_TEXTENCODING_UTF8).getStr()));
            OUString newValue((char*)m_aNodePtr->content, strlen((char*)m_aNodePtr->content), RTL_TEXTENCODING_UTF8);
            _dispatchEvent(oldValue, newValue);

        }
    }

    /**
    Extracts a range of data from the node.
    */
    OUString SAL_CALL CCharacterData::subStringData(sal_Int32 offset, sal_Int32 count)
        throw (RuntimeException, DOMException)
    {
        OUString aStr;
        if (m_aNodePtr != NULL)
        {
            // get current data
            OString aData((const sal_Char*)xmlNodeGetContent(m_aNodePtr));
            OUString tmp(aData, aData.getLength(), RTL_TEXTENCODING_UTF8);
            if (offset > tmp.getLength() || offset < 0 || count < 0) {
                DOMException e;
                e.Code = DOMExceptionType_INDEX_SIZE_ERR;
                throw e;
            }
            aStr = tmp.copy(offset, count);
        }
        return aStr;
    }


} // namspace DOM

