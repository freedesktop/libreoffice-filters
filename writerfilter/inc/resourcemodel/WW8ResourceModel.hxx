/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: WW8ResourceModel.hxx,v $
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

#ifndef INCLUDED_WW8_EVENT_HANDLER_HXX
#define INCLUDED_WW8_EVENT_HANDLER_HXX

#include <string>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <sal/types.h>
#include <com/sun/star/uno/Any.hxx>
#include <WriterFilterDllApi.hxx>
#include <resourcemodel/OutputWithDepth.hxx>
/**
   @file WW8ResourceModel.hxx

   The classes in this file define the interfaces for the resource
   model of the DocTokenizer:

   @image html doctok.png

   A resource is a set of events that describe an object. A resource
   is only an abstract concept. It is not instanciated to a class.

   A reference to a resource represents the object that the resource
   describes. The reference can be resolved thereby generating the
   events of the resource.

   A handler receives the events generated by resolving a
   reference. There are several types of handlers each accepting their
   specific set of events.

   References always have a parameter determining the kind of handler
   they send the events they generate to. The set of events generated
   by resolving the reference is a subset of the events received by
   the handler.
*/


typedef sal_uInt32 Id;

namespace writerfilter {
using namespace ::com::sun::star;
using namespace ::std;

/** 
    Reference to an resource that generates events and sends them to a
    handler.

    The reference can be resolved, i.e. the resource generates its
    events. The events must be suitable for the handler type given by
    the template parameter.

    @attention The parameter of the template does not determine the
    type of the reference's target. It determines the type of the handler!

    Example:
    
    A Word document can be represented as a stream of events. Event
    types in a Word document are text, properties, tables, starts and
    ends of groups. These can be handled by a stream handler (@see
    Stream). Thus a reference to a Word document is resolved by
    sending these events to a stream handler.
*/

template <class T>
class WRITERFILTER_DLLPUBLIC Reference
{
public:
    /** 
        Pointer to reference

        @attention The ownership of a reference is transfered when
        the reference is passed.
    */
    typedef boost::shared_ptr< Reference<T> > Pointer_t;

    virtual ~Reference() {}

    /**
       Resolves the reference.

       The events of the references target resource are generated and
       send to a handler.

       @param rHandler         handler which receives the events
     */
    virtual void resolve(T & rHandler) = 0;

    /**
       Returns the type of the reference aka the name of the access class.
     */
    virtual string getType() const = 0;
};

class Value;
class Sprm;

/**
   Handler for properties.
 */
class WRITERFILTER_DLLPUBLIC Properties
{
public:
    /**
       Receives an attribute.

       @param name     name of the attribute
       @param val      value of the attribute
     */
    virtual void attribute(Id name, Value & val) = 0;

    /**
       Receives a SPRM.

       @param  sprm      the SPRM received
    */
    virtual void sprm(Sprm & sprm) = 0;
    
};

/**
   Handler for tables.
 */
class WRITERFILTER_DLLPUBLIC Table
{
public:
    /**
       Receives an entry of the table.

       @param pos     position of the entry in the table
       @param ref     reference to properties of the entry
     */
    virtual void entry(int pos, writerfilter::Reference<Properties>::Pointer_t ref) = 0;    
};

/**
   Handler for binary objects.
 */
class WRITERFILTER_DLLPUBLIC BinaryObj
{
public:
    /**
       Receives binary data of the object.

       @param buf     pointer to buffer containing the data
       @param len     size of buffer
       @param ref     reference to properties of binary object
     */
    virtual void data(const sal_uInt8* buf, size_t len,
                      writerfilter::Reference<Properties>::Pointer_t ref) = 0;
};

/**
   Handler for a stream.
 */
class WRITERFILTER_DLLPUBLIC Stream
{
public:
    /**
       Pointer to this stream.
     */
    typedef boost::shared_ptr<Stream> Pointer_t;

    /**
       Receives start mark for group with the same section properties.
     */
    virtual void startSectionGroup() = 0;
    
    /**
       Receives end mark for group with the same section properties.
    */
    virtual void endSectionGroup() = 0;

    /**
       Receives start mark for group with the same paragraph properties.
     */
    virtual void startParagraphGroup() = 0;

    /**
       Receives end mark for group with the same paragraph properties.
     */
    virtual void endParagraphGroup() = 0;

    /**
       Receives start mark for group with the same character properties.
     */
    virtual void startCharacterGroup() = 0;

    /**
       Receives end mark for group with the same character properties.
     */
    virtual void endCharacterGroup() = 0;

    /**
       Receives 8-bit per character text.

       @param data  buffer containing the text
       @param len   number of characters in the text
     */
    virtual void text(const sal_uInt8 * data, size_t len) = 0;

    /**
       Receives 16-bit per character text.

       @param data    buffer containing the text
       @param len     number of characters in the text.
     */
    virtual void utext(const sal_uInt8 * data, size_t len) = 0;

    /**
       Receives properties of the current run of text.

       @param ref    reference to the properties
     */
    virtual void props(writerfilter::Reference<Properties>::Pointer_t ref) = 0;

    /**
       Receives table.

       @param name     name of the table
       @param ref      referecne to the table
     */
    virtual void table(Id name, 
                       writerfilter::Reference<Table>::Pointer_t ref) = 0;
    
    /** 
        Receives a substream.

        @param name    name of the substream
        @param ref     reference to the substream
    */
    virtual void substream(Id name, 
                           writerfilter::Reference<Stream>::Pointer_t ref) = 0;


    /**
       Debugging: Receives information about current point in stream.

       @param info     the information
     */
    virtual void info(const string & info) = 0;
};

/**
   A value.

   The methods of this class may throw exceptions if a certain aspect
   makes no sense for a certain value, e.g. the integer value of a
   string.
 */
class WRITERFILTER_DLLPUBLIC Value
{
public:
    /**
       Pointer to a value.
     */
    typedef auto_ptr<Value> Pointer_t;

    /**
       Returns integer representation of the value.
     */
    virtual int getInt() const = 0;

    /**
       Returns string representation of the value.
     */
    virtual ::rtl::OUString getString() const = 0;

    /**
       Returns representation of the value as uno::Any.
     */
    virtual uno::Any getAny() const = 0;

    /**
       Returns properties of this value.
     */
    virtual writerfilter::Reference<Properties>::Pointer_t getProperties() = 0;

    /**
       Returns stream of this value.
     */
    virtual writerfilter::Reference<Stream>::Pointer_t getStream() = 0;

    /**
       Returns binary object  of this value.
     */
    virtual writerfilter::Reference<BinaryObj>::Pointer_t getBinary() = 0;

    /**
       Returns string representation of this value.
     */
    virtual string toString() const = 0;
};

/**
   An SPRM.

 */
class WRITERFILTER_DLLPUBLIC Sprm
{
public:
    typedef auto_ptr<Sprm> Pointer_t;
    enum Kind { UNKNOWN, CHARACTER, PARAGRAPH, TABLE };
    /**
       Returns id of the SPRM.
     */
    virtual sal_uInt32 getId() const = 0;

    /**
       Returns value of the SPRM.
     */
    virtual Value::Pointer_t getValue() = 0;

    /**
       Returns reference to binary object contained in the SPRM.
     */
    virtual writerfilter::Reference<BinaryObj>::Pointer_t getBinary() = 0;

    /**
       Returns reference to stream associated with the SPRM.
     */
    virtual writerfilter::Reference<Stream>::Pointer_t getStream() = 0;

    /**
       Returns reference to properties contained in the SPRM.

     */
    virtual writerfilter::Reference<Properties>::Pointer_t getProps() = 0;

    /**
       Returns the kind of this SPRM.
    */
    virtual Kind getKind() = 0;

    /**
       Returns name of sprm.
    */
    virtual string getName() const = 0;

    /**
       Returns string repesentation of sprm.
     */
    virtual string toString() const = 0;
};

/**
   Creates handler for a stream.
*/
Stream::Pointer_t WRITERFILTER_DLLPUBLIC createStreamHandler();

    void WRITERFILTER_DLLPUBLIC analyzerIds();
    Stream::Pointer_t WRITERFILTER_DLLPUBLIC createAnalyzer();
    
    void WRITERFILTER_DLLPUBLIC logger(string prefix, string message);
    
    void WRITERFILTER_DLLPUBLIC dump(OutputWithDepth<string> & o, const char * name, writerfilter::Reference<Properties>::Pointer_t props);
    void WRITERFILTER_DLLPUBLIC dump(OutputWithDepth<string> & o, const char * name, sal_uInt32 n);
    void WRITERFILTER_DLLPUBLIC dump(OutputWithDepth<string> & /*o*/, const char * /*name*/, 
                                     const rtl::OUString & /*str*/); 
    void WRITERFILTER_DLLPUBLIC dump(OutputWithDepth<string> & o, const char * name, writerfilter::Reference<BinaryObj>::Pointer_t binary);
    
}


#endif // INCLUDED_WW8_EVENT_HANDLER_HXX
