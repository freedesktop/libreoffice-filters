/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: timenodelistcontext.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-01-17 08:06:01 $
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

#include "oox/ppt/timenodelistcontext.hxx"

#include "comphelper/anytostring.hxx"
#include "cppuhelper/exc_hlp.hxx"
#include <comphelper/processfactory.hxx>
#include <osl/diagnose.h>
#include <rtl/math.hxx>

#include <com/sun/star/animations/XTimeContainer.hpp>
#include <com/sun/star/animations/XAnimationNode.hpp>
#include <com/sun/star/animations/XAnimateColor.hpp>
#include <com/sun/star/animations/XAnimateSet.hpp>
#include <com/sun/star/animations/XAnimateTransform.hpp>
#include <com/sun/star/animations/AnimationTransformType.hpp>
#include <com/sun/star/animations/AnimationCalcMode.hpp>
#include <com/sun/star/animations/AnimationColorSpace.hpp>
#include <com/sun/star/animations/AnimationNodeType.hpp>
#include <com/sun/star/animations/XCommand.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/presentation/EffectCommands.hpp>
#include <com/sun/star/beans/NamedValue.hpp>

#include "oox/helper/attributelist.hxx"
#include "oox/core/namespaces.hxx"
#include "oox/drawingml/drawingmltypes.hxx"
#include "oox/drawingml/colorchoicecontext.hxx"
#include "oox/ppt/slidetransition.hxx"
#include "tokens.hxx"

#include "animvariantcontext.hxx"
#include "commonbehaviorcontext.hxx"
#include "conditioncontext.hxx"
#include "commontimenodecontext.hxx"
#include "timeanimvaluecontext.hxx"
#include "animationtypes.hxx"

using namespace ::oox::core;
using namespace ::oox::drawingml;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::animations;
using namespace ::com::sun::star::presentation;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::awt;
using ::com::sun::star::beans::NamedValue;

using ::rtl::OUString;

namespace oox { namespace ppt {

    struct AnimColor
    {
        AnimColor(sal_Int16 cs, sal_Int32 o, sal_Int32 t, sal_Int32 th )
            : colorSpace( cs ), one( o ), two( t ), three( th )
            {
            }

        sal_Int32 get()
            {
                sal_Int32 nColor;

                switch( colorSpace )
                {
                case AnimationColorSpace::HSL:
                    nColor = ( ( ( one * 128 ) / 360 ) & 0xff ) << 16
                        | ( ( ( two * 128 ) / 1000 ) & 0xff ) << 8
                        | ( ( ( three * 128 ) / 1000 )  & 0xff );
                    break;
                case AnimationColorSpace::RGB:
                    nColor = ( ( ( one * 128 ) / 1000 ) & 0xff ) << 16
                        | ( ( ( two * 128 ) / 1000 ) & 0xff ) << 8
                        | ( ( ( three * 128 ) / 1000 )  & 0xff );
                    break;
                default:
                    nColor = 0;
                    break;
                }
                return  nColor;
            }

        sal_Int16 colorSpace;
        sal_Int32 one;
        sal_Int32 two;
        sal_Int32 three;
    };


    /** CT_TLMediaNodeAudio
            CT_TLMediaNodeVideo */
    class MediaNodeContext
        : public TimeNodeContext
    {
    public:
        MediaNodeContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement,
                                            const Reference< XFastAttributeList >& xAttribs,
                                            const TimeNodePtr & pNode )
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
                , mbIsNarration( false )
                , mbFullScrn( false )
            {
                AttributeList attribs( xAttribs );

                switch( aElement )
                {
                case NMSP_PPT|XML_audio:
                    mbIsNarration = attribs.getBool( XML_isNarration, false );
                    break;
                case NMSP_PPT|XML_video:
                    mbFullScrn = attribs.getBool( XML_fullScrn, false );
                    break;
                default:
                    break;
                }
            }

        virtual void SAL_CALL endFastElement( sal_Int32 aElement )
            throw ( SAXException, RuntimeException)
            {
                if( aElement == ( NMSP_PPT|XML_audio ) )
                {
                    // TODO deal with mbIsNarration
                }
                else if( aElement == ( NMSP_PPT|XML_video ) )
                {
                    // TODO deal with mbFullScrn
                }
            }

        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken,
                                                                                                                                                            const Reference< XFastAttributeList >& xAttribs )
            throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_cBhvr:
                    xRet.set( new CommonBehaviorContext ( getHandler(), xAttribs, mpNode ) );
                    break;
                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }

    private:
        bool mbIsNarration;
        bool mbFullScrn;
    };


    /** CT_TLSetBehavior
     */
    class SetTimeNodeContext
        : public TimeNodeContext
    {
    public:
        SetTimeNodeContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement,
                                                const Reference< XFastAttributeList >& xAttribs,
                                                const TimeNodePtr & pNode )
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
            {

            }

        ~SetTimeNodeContext() throw ()
            {
                if( maTo.hasValue() )
                {
                    // TODO
                    // HACK !!! discard and refactor
                    OUString aString;
                    if( maTo >>= aString )
                    {
                        OSL_TRACE( "Magic conversion %s", OUSTRING_TO_CSTR( aString ) );
                        maTo = makeAny( aString.equalsAscii( "visible" ) ? sal_True : sal_False );
                        if( !maTo.has<sal_Bool>() )
                            OSL_TRACE( "conversion failed" );			
                    }
                    mpNode->setTo( maTo );
                }
                
            }

        virtual void SAL_CALL endFastElement( sal_Int32 /*aElement*/ )
            throw ( SAXException, RuntimeException)
            {
            }


        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken,
                                                                                                                                                            const Reference< XFastAttributeList >& xAttribs )
            throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_cBhvr:
                    xRet.set( new CommonBehaviorContext ( getHandler(), xAttribs, mpNode ) );
                    break;
                case NMSP_PPT|XML_to:
                    // CT_TLAnimVariant
                    xRet.set( new AnimVariantContext( getHandler(), aElementToken, maTo ) );
                    break;
                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }
    private:
        Any  maTo;
    };

    /** CT_TLCommandBehavior
     */
    class CmdTimeNodeContext
        : public TimeNodeContext
    {
    public:
        CmdTimeNodeContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement,
                                                const Reference< XFastAttributeList >& xAttribs,
                                                const TimeNodePtr & pNode )
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
                , maType(0)
            {
                switch ( aElement )
                {
                case NMSP_PPT|XML_cmd:
                    msCommand = xAttribs->getOptionalValue( XML_cmd );
                    maType = xAttribs->getOptionalValueToken( XML_type, 0 );
                    break;
                default:
                    break;
                }
            }

        ~CmdTimeNodeContext() throw ()
            {
            }

        virtual void SAL_CALL endFastElement( sal_Int32 aElement )
            throw ( SAXException, RuntimeException)
            {
                if( aElement == ( NMSP_PPT|XML_cmd ) )
                {
                    try {
                        // see sd/source/filter/ppt/pptinanimations.cxx
                        // in AnimationImporter::importCommandContainer()
                        // REFACTOR?
                        // a good chunk of this code has been copied verbatim *sigh*
                        sal_Int16 nCommand = EffectCommands::CUSTOM;
                        NamedValue aParamValue;

                        switch( maType )
                        {
                        case XML_verb:
                            aParamValue.Name = OUString(RTL_CONSTASCII_USTRINGPARAM("Verb"));
                            // TODO make sure msCommand has what we want
                            aParamValue.Value <<= msCommand.toInt32();
                            nCommand = EffectCommands::VERB;
                            break;
                        case XML_evt:
                        case XML_call:
                            if( msCommand.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "onstopaudio" ) ) )
                            {
                                nCommand = EffectCommands::STOPAUDIO;
                            }
                            else if( msCommand.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM("play") ) )
                            {
                                nCommand = EffectCommands::PLAY;
                            }
                            else if( msCommand.compareToAscii( RTL_CONSTASCII_STRINGPARAM("playFrom") ) == 0 )
                            {
                                const OUString aMediaTime( msCommand.copy( 9, msCommand.getLength() - 10 ) );
                                rtl_math_ConversionStatus eStatus;
                                double fMediaTime = ::rtl::math::stringToDouble( aMediaTime, (sal_Unicode)('.'), (sal_Unicode)(','), &eStatus, NULL );
                                if( eStatus == rtl_math_ConversionStatus_Ok )
                                {
                                    aParamValue.Name = CREATE_OUSTRING("MediaTime");
                                    aParamValue.Value <<= fMediaTime;
                                }
                                nCommand = EffectCommands::PLAY;
                            }
                            else if( msCommand.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM("togglePause") ) )
                            {
                                nCommand = EffectCommands::TOGGLEPAUSE;
                            }
                            else if( msCommand.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM("stop") ) )
                            {
                                nCommand = EffectCommands::STOP;
                            }
                            break;
                        }
                        mpNode->getNodeProperties()[ NP_COMMAND ] = makeAny((sal_Int16)nCommand);
                        if( nCommand == EffectCommands::CUSTOM )
                        {
                            OSL_TRACE("OOX: CmdTimeNodeContext::endFastElement(), unknown command!");
                            aParamValue.Name = CREATE_OUSTRING("UserDefined");
                            aParamValue.Value <<= msCommand;
                        }
                        if( aParamValue.Value.hasValue() )
                        {
                            Sequence< NamedValue > aParamSeq( &aParamValue, 1 );
                            mpNode->getNodeProperties()[ NP_PARAMETER ] = makeAny( aParamSeq );
                        }
                    }
                    catch( RuntimeException& )
                    {
                        OSL_TRACE( "OOX: Exception in CmdTimeNodeContext::endFastElement()" );
                    }
                }
            }


        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken,
                                                                                                                                                            const Reference< XFastAttributeList >& xAttribs )
            throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_cBhvr:
                    xRet.set( new CommonBehaviorContext ( getHandler(), xAttribs, mpNode ) );
                    break;
                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }

    private:
        OUString msCommand;
        sal_Int32 maType;
    };


    /** CT_TLTimeNodeSequence
     */
    class SequenceTimeNodeContext
        : public TimeNodeContext
    {
    public:
        SequenceTimeNodeContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement,
                                                                 const Reference< XFastAttributeList >& xAttribs,
                                                                 const TimeNodePtr & pNode )
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
                , mnNextAc(0)
                , mnPrevAc(0)
            {
                AttributeList attribs(xAttribs);
                mbConcurrent = attribs.getBool( XML_concurrent, false );
                // ST_TLNextActionType { none, seek }
                mnNextAc = xAttribs->getOptionalValueToken( XML_nextAc, 0 );
                // ST_TLPreviousActionType { none, skipTimed }				
                mnPrevAc = xAttribs->getOptionalValueToken( XML_prevAc, 0 );
            }

        ~SequenceTimeNodeContext() throw()
            {
            }


        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken, 
                                                                                                                                                            const Reference< XFastAttributeList >& xAttribs ) 
            throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_cTn:
                    xRet.set( new CommonTimeNodeContext( getHandler(), aElementToken, xAttribs, mpNode ) );
                    break;
                case NMSP_PPT|XML_nextCondLst:
                    xRet.set( new CondListContext( getHandler(), aElementToken, xAttribs, mpNode, 
                                                   mpNode->getNextCondition() ) );
                    break;
                case NMSP_PPT|XML_prevCondLst:
                    xRet.set( new CondListContext( getHandler(), aElementToken, xAttribs, mpNode, 
                                                   mpNode->getPrevCondition() ) );
                    break;
                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }
    private:
        bool mbConcurrent;
        sal_Int32 mnNextAc, mnPrevAc;
    };


    /** CT_TLTimeNodeParallel
     *  CT_TLTimeNodeExclusive
     */
    class ParallelExclTimeNodeContext
        : public TimeNodeContext
    {
    public:
        ParallelExclTimeNodeContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement,
                                                                 const Reference< XFastAttributeList >& xAttribs,
                                                                 const TimeNodePtr & pNode )
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
            {
            }

        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken, 
                                                                                                                                                            const Reference< XFastAttributeList >& xAttribs ) 
            throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_cTn:
                    xRet.set( new CommonTimeNodeContext( getHandler(), aElementToken, xAttribs, mpNode ) );
                    break;
                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }

    protected:

    };


    /** CT_TLAnimateColorBehavior */
    class AnimColorContext
        : public TimeNodeContext
    {
    public:
        AnimColorContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement, 
                                            const Reference< XFastAttributeList >& xAttribs, 
                                             const TimeNodePtr & pNode ) throw()
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
                // ST_TLAnimateColorSpace ( XML_rgb, XML_hsl }
            , mnColorSpace( xAttribs->getOptionalValueToken( XML_clrSpc, 0 ) )
                // ST_TLAnimateColorDirection { XML_cw, XML_ccw }
            , mnDir( xAttribs->getOptionalValueToken( XML_dir, 0 ) )
            , mbHasByColor( false )
            , m_byColor( AnimationColorSpace::RGB, 0, 0, 0)
            {
            }
        ~AnimColorContext() throw()
            {
            }

        virtual void SAL_CALL endFastElement( sal_Int32 aElement ) throw ( SAXException, RuntimeException)
            {
                //xParentNode
                if( aElement == mnElement )
                {
                    NodePropertyMap & pProps(mpNode->getNodeProperties());
                    pProps[ NP_DIRECTION ] = makeAny( mnDir == XML_cw );
                    pProps[ NP_COLORINTERPOLATION ] = makeAny( mnColorSpace == XML_hsl ? AnimationColorSpace::HSL : AnimationColorSpace::RGB );
                    if( maToClr.isUsed() )
                    {
                        mpNode->setTo( Any( maToClr.getColor( *getHandler()->getFilter().get() ) ) );
                    }
                    if( maFromClr.isUsed() )
                    {
                        mpNode->setFrom( Any( maFromClr.getColor( *getHandler()->getFilter().get() ) ) );
                    }
                    if( mbHasByColor )
                    {
                        mpNode->setBy( Any ( m_byColor.get() ) );
                    }

                }
            }


        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken, const Reference< XFastAttributeList >& xAttribs ) throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_hsl:
                    // CT_TLByHslColorTransform
                {
                    if( mbHasByColor )
                    {
                        m_byColor.colorSpace = AnimationColorSpace::HSL;
                        m_byColor.one = xAttribs->getOptionalValue( XML_h ).toInt32( );
                        m_byColor.two = xAttribs->getOptionalValue( XML_s ).toInt32( );
                        m_byColor.three = xAttribs->getOptionalValue( XML_l ).toInt32( );
                    }
                    xRet.set(this);
                    break;
                }
                case NMSP_PPT|XML_rgb:
                {
                    if( mbHasByColor )
                    {
                        // CT_TLByRgbColorTransform
                        m_byColor.colorSpace = AnimationColorSpace::RGB;
                        m_byColor.one = xAttribs->getOptionalValue( XML_r ).toInt32();
                        m_byColor.two = xAttribs->getOptionalValue( XML_g ).toInt32();
                        m_byColor.three = xAttribs->getOptionalValue( XML_b ).toInt32();
                    }
                    xRet.set(this);
                    break;
                }
                case NMSP_PPT|XML_by:
                    // CT_TLByAnimateColorTransform
                    mbHasByColor = true;
                    xRet.set(this);
                    break;
                case NMSP_PPT|XML_cBhvr:
                    xRet.set( new CommonBehaviorContext ( getHandler(), xAttribs, mpNode ) );
                    break;
                case NMSP_PPT|XML_to:
                    // CT_Color
                    xRet.set( new colorChoiceContext( getHandler(), maToClr ) );
                    break;
                case NMSP_PPT|XML_from:
                    // CT_Color
                    xRet.set( new colorChoiceContext( getHandler(), maFromClr ) );
                    break;

                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }


    private:
        sal_Int32 mnColorSpace;
        sal_Int32 mnDir;
        bool mbHasByColor;
        AnimColor m_byColor;
        oox::drawingml::Color maToClr;
        oox::drawingml::Color maFromClr;
    };


    /** CT_TLAnimateBehavior */
    class AnimContext
        : public TimeNodeContext
    {
    public:
        AnimContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement,
                                 const Reference< XFastAttributeList >& xAttribs,
                                  const TimeNodePtr & pNode ) throw()
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
            {
                NodePropertyMap & aProps( pNode->getNodeProperties() );
                sal_Int32 nCalcMode = xAttribs->getOptionalValueToken( XML_calcmode, 0 );
                if(nCalcMode) 
                {
                    sal_Int16 nEnum = 0;
                    switch(nCalcMode) 
                    {
                    case XML_discrete:
                        nEnum = AnimationCalcMode::DISCRETE;
                        break;
                    case XML_lin:
                        nEnum = AnimationCalcMode::LINEAR;
                        break;
                    case XML_fmla:
                    default:
                        // TODO what value is good ?
                        nEnum = AnimationCalcMode::DISCRETE;
                        break;
                    }
                    aProps[ NP_CALCMODE ] = makeAny(nEnum);
                }
                OUString aStr;
                aStr = xAttribs->getOptionalValue( XML_from );				
                if( aStr.getLength() ) 
                {
                    pNode->setFrom( makeAny( aStr ) );
                }
                aStr = xAttribs->getOptionalValue( XML_by );
                if( aStr.getLength() ) 
                {
                    pNode->setBy( makeAny( aStr ) );
                }
                aStr = xAttribs->getOptionalValue( XML_to );
                if( aStr.getLength() ) 
                {
                    pNode->setTo( makeAny( aStr ) );
                }
                mnValueType = xAttribs->getOptionalValueToken( XML_valueType, 0 );
            }


        ~AnimContext() throw ()
            {
                ::std::list< TimeAnimationValue >::iterator iter, end;
                int nKeyTimes = maTavList.size();
                if( nKeyTimes > 0)
                {
                    int i;
                    Sequence< double > aKeyTimes( nKeyTimes );
                    Sequence< Any > aValues( nKeyTimes );
                    
                    NodePropertyMap & aProps( mpNode->getNodeProperties() );
                    end = maTavList.end();
                    for(iter = maTavList.begin(), i=0; iter != end; iter++,i++)
                    {
                        // TODO what to do if it is Timing_INFINITE ?
                        Any aTime = GetTimeAnimateValueTime( iter->msTime );
                        aTime >>= aKeyTimes[i];
                        aValues[i] = iter->maValue;

                        OUString aTest;
                        iter->maValue >>= aTest;
                        if( aTest.getLength() != 0 )
                        {
                            aValues[i] = iter->maValue;
                        }
                        else 
                        {
                            aProps[ NP_FORMULA ] <<= iter->msFormula;
                        }
                    }
                    aProps[ NP_VALUES ] <<= aValues;
                    aProps[ NP_KEYTIMES ] <<= aKeyTimes;
                }
            }


        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken, const Reference< XFastAttributeList >& xAttribs ) throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_cBhvr:
                    xRet.set( new CommonBehaviorContext ( getHandler(), xAttribs, mpNode ) );
                    break;
                case NMSP_PPT|XML_tavLst:
                    xRet.set( new TimeAnimValueListContext ( getHandler(), xAttribs, maTavList ) );
                    break;
                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }
    private:
        sal_Int32              mnValueType;
        TimeAnimationValueList maTavList;
    };


    /** CT_TLAnimateScaleBehavior */
    class AnimScaleContext
        : public TimeNodeContext
    {
    public:
        AnimScaleContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement,
                                            const Reference< XFastAttributeList >& xAttribs,
                                            const TimeNodePtr & pNode ) throw()
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
                , mbZoomContents( false )
            {
                AttributeList attribs( xAttribs );
                // TODO what to do with mbZoomContents
                mbZoomContents = attribs.getBool( XML_zoomContents, false );
                pNode->getNodeProperties()[ NP_TRANSFORMTYPE ] 
                    = makeAny((sal_Int16)AnimationTransformType::SCALE);
            }

        ~AnimScaleContext( ) throw( )
            {
            }

        virtual void SAL_CALL endFastElement( sal_Int32 aElement ) throw ( SAXException, RuntimeException)
            {
                if( aElement == mnElement )
                {
                    if( maTo.hasValue() )
                    {
                        mpNode->setTo( maTo );
                    }
                    if( maBy.hasValue() )
                    {
                        mpNode->setBy( maBy );
                    }
                    if( maFrom.hasValue() )
                    {
                        mpNode->setFrom( maFrom );
                    }
                }
            }

        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken, 
                                                                                                                                                            const Reference< XFastAttributeList >& xAttribs ) 
            throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_cBhvr:
                    xRet.set( new CommonBehaviorContext ( getHandler(), xAttribs, mpNode ) );
                    break;
                case NMSP_PPT|XML_to:
                {
                    // CT_TLPoint
                    Point p = GetPointPercent( xAttribs );
                    maTo <<= p.X;
                    maTo <<= p.Y;
                    break;
                }
                case NMSP_PPT|XML_from:
                {
                    // CT_TLPoint
                    Point p = GetPointPercent( xAttribs );
                    maFrom <<= p.X;
                    maFrom <<= p.Y;
                    break;
                }
                case NMSP_PPT|XML_by:
                {
                    // CT_TLPoint
                    Point p = GetPointPercent( xAttribs );
                    maBy <<= p.X;
                    maBy <<= p.Y;
                    break;
                }
                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }
    private:
        Any maBy;
        Any maFrom;
        Any maTo;
        bool mbZoomContents;
    };


    /** CT_TLAnimateRotationBehavior */
    class AnimRotContext
        : public TimeNodeContext
    {
    public:
        AnimRotContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement,
                                        const Reference< XFastAttributeList >& xAttribs,
                                         const TimeNodePtr & pNode ) throw()
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
            {
                AttributeList attribs( xAttribs );

                pNode->getNodeProperties()[ NP_TRANSFORMTYPE ] 
                    = makeAny((sal_Int16)AnimationTransformType::ROTATE);
                // TODO make sure the units are OK
                if(attribs.hasAttribute( XML_by ) ) 
                {
                    sal_Int32 nBy = attribs.getInteger( XML_by, 0 );
                    pNode->setBy( makeAny( nBy ) );
                }
                if(attribs.hasAttribute( XML_from ) )
                {
                    sal_Int32 nFrom = attribs.getInteger( XML_from, 0 );
                    pNode->setFrom( makeAny( nFrom ) );
                }
                if(attribs.hasAttribute( XML_to ) )
                {
                    sal_Int32 nTo = attribs.getInteger( XML_to, 0 );
                    pNode->setTo( makeAny( nTo ) );
                }
            }

        ~AnimRotContext( ) throw( )
            {
            }

        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken, const Reference< XFastAttributeList >& xAttribs ) throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_cBhvr:
                    xRet.set( new CommonBehaviorContext ( getHandler(), xAttribs, mpNode ) );
                    break;
                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }
    };



    /** CT_TLAnimateMotionBehavior */
    class AnimMotionContext
        : public TimeNodeContext
    {
    public:
        AnimMotionContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement,
                                             const Reference< XFastAttributeList >& xAttribs,
                                              const TimeNodePtr & pNode ) throw()
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
            {
                pNode->getNodeProperties()[ NP_TRANSFORMTYPE ] 
                    = makeAny((sal_Int16)AnimationTransformType::TRANSLATE);
                
                AttributeList attribs( xAttribs );
                // ST_TLAnimateMotionBehaviorOrigin { parent, layour }
                sal_Int32 nOrigin = xAttribs->getOptionalValueToken( XML_origin, 0 );
                if( nOrigin != 0 )
                {
                    switch(nOrigin)
                    {
                    case XML_layout:
                    case XML_parent:
                        break;
                    }
                    // TODO
                }
                
                OUString aStr = xAttribs->getOptionalValue( XML_path );
                aStr = aStr.replace( 'E', ' ' );
                aStr = aStr.trim();
                pNode->getNodeProperties()[ NP_PATH ] = makeAny(aStr);

                // ST_TLAnimateMotionPathEditMode{ fixed, relative }
                mnPathEditMode = xAttribs->getOptionalValueToken( XML_pathEditMode, 0 );
                msPtsTypes = xAttribs->getOptionalValue( XML_ptsTypes );
                mnAngle = attribs.getInteger( XML_rAng, 0 );
                // TODO make sure the units are right. Likely not.
            }

        ~AnimMotionContext( ) throw()
            {
            }


        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken, 
                                                                                                                                                            const Reference< XFastAttributeList >& xAttribs ) 
            throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_cBhvr:
                    xRet.set( new CommonBehaviorContext ( getHandler(), xAttribs, mpNode ) );
                    break;
                case NMSP_PPT|XML_to:
                {
                    // CT_TLPoint
                    Point p = GetPointPercent( xAttribs );
                    Any rAny;
                    rAny <<= p.X;
                    rAny <<= p.Y;
                    mpNode->setTo( rAny );
                    break;
                }
                case NMSP_PPT|XML_from:
                {
                    // CT_TLPoint
                    Point p = GetPointPercent( xAttribs );
                    Any rAny;
                    rAny <<= p.X;
                    rAny <<= p.Y;
                    mpNode->setFrom( rAny );
                    break;
                }
                case NMSP_PPT|XML_by:
                {
                    // CT_TLPoint
                    Point p = GetPointPercent( xAttribs );
                    Any rAny;
                    rAny <<= p.X;
                    rAny <<= p.Y;
                    mpNode->setBy( rAny );
                    break;
                }
                case NMSP_PPT|XML_rCtr:
                {
                    // CT_TLPoint
                    Point p = GetPointPercent( xAttribs );
                    // TODO push
                    break;
                }
                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }
    private:
        OUString msPtsTypes;
        sal_Int32 mnPathEditMode;
        sal_Int32 mnAngle;
    };


    /** CT_TLAnimateEffectBehavior */
    class AnimEffectContext
        : public TimeNodeContext
    {
    public:
        AnimEffectContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement,
                                             const Reference< XFastAttributeList >& xAttribs,
                                             const TimeNodePtr & pNode ) throw()
            : TimeNodeContext( xHandler, aElement, xAttribs, pNode )
            {
                sal_Int32 nDir = xAttribs->getOptionalValueToken( XML_transition, 0 );
                OUString sFilter = xAttribs->getOptionalValue( XML_filter );
                // TODO
//				OUString sPrList = xAttribs->getOptionalValue( XML_prLst );

                if( sFilter.getLength() ) 
                {
                    SlideTransition aFilter( sFilter );
                    aFilter.setMode( nDir == XML_out ? false : true );
                    pNode->setTransitionFilter( aFilter );
                }
            }


        ~AnimEffectContext( ) throw()
            {
            }


        virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElementToken, const Reference< XFastAttributeList >& xAttribs ) throw ( SAXException, RuntimeException )
            {
                Reference< XFastContextHandler > xRet;

                switch ( aElementToken )
                {
                case NMSP_PPT|XML_cBhvr:
                    xRet.set( new CommonBehaviorContext ( getHandler(), xAttribs, mpNode ) );
                    break;
                case NMSP_PPT|XML_progress:
                    xRet.set( new AnimVariantContext( getHandler(), aElementToken, maProgress ) );
                    // TODO handle it.
                    break;
                default:
                    break;
                }

                if( !xRet.is() )
                    xRet.set( this );

                return xRet;
            }
    private:
        Any maProgress;
        OUString msFilter;
        OUString msPrList;
    };



    TimeNodeContext * TimeNodeContext::makeContext( const FragmentHandlerRef& xHandler, sal_Int32  aElement, 
                                                                                                    const Reference< XFastAttributeList >& xAttribs,
                                                                                                    const TimeNodePtr & pNode )
    {
        TimeNodeContext *pCtx = NULL;
        switch( aElement )
        {
        case NMSP_PPT|XML_animClr:
            pCtx = new AnimColorContext( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_par:
            pCtx = new ParallelExclTimeNodeContext( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_seq:
            pCtx = new SequenceTimeNodeContext( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_excl:
            pCtx = new ParallelExclTimeNodeContext( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_anim:
            pCtx = new AnimContext ( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_animEffect:
            pCtx = new AnimEffectContext( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_animMotion:
            pCtx = new AnimMotionContext( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_animRot:
            pCtx = new AnimRotContext( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_animScale:
            pCtx = new AnimScaleContext( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_cmd:
            pCtx = new CmdTimeNodeContext( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_set:
            pCtx = new SetTimeNodeContext( xHandler, aElement, xAttribs, pNode );
            break;
        case NMSP_PPT|XML_audio:
        case NMSP_PPT|XML_video:
            pCtx = new MediaNodeContext( xHandler, aElement, xAttribs, pNode );
            break;
        default:
            break;
        }
        return pCtx;
    }


    TimeNodeContext::TimeNodeContext( const FragmentHandlerRef& xHandler, sal_Int32 aElement, 
                                                                            const Reference< XFastAttributeList >& /*xAttribs*/, 
                                                                            const TimeNodePtr & pNode ) throw()
        : Context( xHandler )
        , mnElement( aElement )
        , mpNode( pNode )
    {
    }


    TimeNodeContext::~TimeNodeContext( ) throw()
    {

    }


    TimeNodeListContext::TimeNodeListContext( const FragmentHandlerRef& xHandler, TimeNodePtrList & aList )
        throw()
        : Context( xHandler )
            , maList( aList )
    {
    }


    TimeNodeListContext::~TimeNodeListContext( ) throw()
    {
    }


    Reference< XFastContextHandler > SAL_CALL TimeNodeListContext::createFastChildContext( ::sal_Int32 aElementToken, const Reference< XFastAttributeList >& xAttribs ) throw (SAXException, RuntimeException)
    {
        Reference< XFastContextHandler > xRet;

        sal_Int16 nNodeType;

        switch( aElementToken )
        {
        case NMSP_PPT|XML_par:
            nNodeType = AnimationNodeType::PAR;
            break;
        case NMSP_PPT|XML_seq:
            nNodeType = AnimationNodeType::SEQ;
            break;
        case NMSP_PPT|XML_excl:
            // TODO pick the right type. We choose parallel for now as
            // there does not seem to be an "Exclusive"
            nNodeType = AnimationNodeType::PAR;
            break;
        case NMSP_PPT|XML_anim:
            nNodeType = AnimationNodeType::ANIMATE;
            break;
        case NMSP_PPT|XML_animClr:
            nNodeType = AnimationNodeType::ANIMATECOLOR;
            break;
        case NMSP_PPT|XML_animEffect:
            nNodeType = AnimationNodeType::TRANSITIONFILTER;
            break;
        case NMSP_PPT|XML_animMotion:
            nNodeType = AnimationNodeType::ANIMATEMOTION;
            break;
        case NMSP_PPT|XML_animRot:
        case NMSP_PPT|XML_animScale:
            nNodeType = AnimationNodeType::ANIMATETRANSFORM;
            break;
        case NMSP_PPT|XML_cmd:
            nNodeType = AnimationNodeType::COMMAND;
            break;
        case NMSP_PPT|XML_set:
            nNodeType = AnimationNodeType::SET;
            break;
        case NMSP_PPT|XML_audio:
            nNodeType = AnimationNodeType::AUDIO;
            break;
        case NMSP_PPT|XML_video:
            nNodeType = AnimationNodeType::AUDIO;
            OSL_TRACE( "OOX: video requested, gave Audio instead" );
            break;

        default:
            nNodeType = AnimationNodeType::CUSTOM;
            OSL_TRACE( "OOX: uhandled token %x", aElementToken );
            break;
        }

        TimeNodePtr pNode(new TimeNode(nNodeType));
        maList.push_back( pNode );
        Context * pContext = TimeNodeContext::makeContext( getHandler(), aElementToken, xAttribs, pNode );
        xRet.set( ( pContext != NULL ? pContext : this ) );

        if( !xRet.is() )
            xRet.set(this);

        return xRet;
    }


} }
