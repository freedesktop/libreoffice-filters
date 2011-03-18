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

#include "oox/drawingml/textcharacterproperties.hxx"
#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/awt/FontSlant.hpp>
#include <com/sun/star/awt/FontWeight.hpp>
#include "oox/helper/helper.hxx"
#include "oox/helper/propertyset.hxx"
#include "oox/core/xmlfilterbase.hxx"
#include "oox/drawingml/drawingmltypes.hxx"
#include "oox/token/tokens.hxx"

using ::rtl::OUString;
using ::oox::core::XmlFilterBase;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;

namespace oox {
namespace drawingml {

// ============================================================================

void TextCharacterProperties::assignUsed( const TextCharacterProperties& rSourceProps )
{
    // overwrite all properties exisiting in rSourceProps
    maHyperlinkPropertyMap.insert( rSourceProps.maHyperlinkPropertyMap.begin(), rSourceProps.maHyperlinkPropertyMap.end() );
    maLatinFont.assignIfUsed( rSourceProps.maLatinFont );
    maAsianFont.assignIfUsed( rSourceProps.maAsianFont );
    maComplexFont.assignIfUsed( rSourceProps.maComplexFont );
    maSymbolFont.assignIfUsed( rSourceProps.maSymbolFont );
    maCharColor.assignIfUsed( rSourceProps.maCharColor );
    maHighlightColor.assignIfUsed( rSourceProps.maHighlightColor );
    maUnderlineColor.assignIfUsed( rSourceProps.maUnderlineColor );
    moHeight.assignIfUsed( rSourceProps.moHeight );
    moSpacing.assignIfUsed( rSourceProps.moSpacing );
    moUnderline.assignIfUsed( rSourceProps.moUnderline );
    moStrikeout.assignIfUsed( rSourceProps.moStrikeout );
    moCaseMap.assignIfUsed( rSourceProps.moCaseMap );
    moBold.assignIfUsed( rSourceProps.moBold );
    moItalic.assignIfUsed( rSourceProps.moItalic );
    moUnderlineLineFollowText.assignIfUsed( rSourceProps.moUnderlineLineFollowText );
    moUnderlineFillFollowText.assignIfUsed( rSourceProps.moUnderlineFillFollowText );
}

    void TextCharacterProperties::pushToPropMap( PropertyMap& rPropMap, const XmlFilterBase& rFilter, bool bUseOptional ) const
{
    OUString aFontName;
    sal_Int16 nFontPitch = 0;
    sal_Int16 nFontFamily = 0;

    if( maLatinFont.getFontData( aFontName, nFontPitch, nFontFamily, rFilter ) )
    {
        rPropMap[ PROP_CharFontName ] <<= aFontName;
        rPropMap[ PROP_CharFontPitch ] <<= nFontPitch;
        rPropMap[ PROP_CharFontFamily ] <<= nFontFamily;
    }

    if( maAsianFont.getFontData( aFontName, nFontPitch, nFontFamily, rFilter ) )
    {
        rPropMap[ PROP_CharFontNameAsian ] <<= aFontName;
        rPropMap[ PROP_CharFontPitchAsian ] <<= nFontFamily;
        rPropMap[ PROP_CharFontFamilyAsian ] <<= nFontPitch;
    }

    if( maComplexFont.getFontData( aFontName, nFontPitch, nFontFamily, rFilter ) )
    {
        rPropMap[ PROP_CharFontNameComplex ] <<= aFontName;
        rPropMap[ PROP_CharFontPitchComplex ] <<= nFontPitch;
        rPropMap[ PROP_CharFontFamilyComplex ] <<= nFontFamily;
    }

    // symbolfont, will now be ... textrun.cxx ... ausgewertet !!!i#113673

    if( maCharColor.isUsed() )
        rPropMap[ PROP_CharColor ] <<= maCharColor.getColor( rFilter.getGraphicHelper() );

    if( moLang.has() && (moLang.get().getLength() > 0) )
    {
        lang::Locale aLocale;
        sal_Int32 nSepPos = moLang.get().indexOf( sal_Unicode( '-' ), 0 );
        if ( nSepPos >= 0 )
        {
            aLocale.Language = moLang.get().copy( 0, nSepPos );
            aLocale.Country = moLang.get().copy( nSepPos + 1 );
        }
        else
        {
            aLocale.Language = moLang.get();
        }
        rPropMap[ PROP_CharLocale ] <<= aLocale;
        rPropMap[ PROP_CharLocaleAsian ] <<= aLocale;
        rPropMap[ PROP_CharLocaleComplex ] <<= aLocale;
    }

    if( moHeight.has() )
    {
        float fHeight = GetFontHeight( moHeight.get() );
        rPropMap[ PROP_CharHeight ] <<= fHeight;
        rPropMap[ PROP_CharHeightAsian ] <<= fHeight;
        rPropMap[ PROP_CharHeightComplex ] <<= fHeight;
    }

    rPropMap[ PROP_CharKerning ] <<= (sal_Int16) GetTextSpacingPoint( moSpacing.get( 0 ) );

    rPropMap[ PROP_CharUnderline ] <<= GetFontUnderline( moUnderline.get( XML_none ) );
    rPropMap[ PROP_CharStrikeout ] <<= GetFontStrikeout( moStrikeout.get( XML_noStrike ) );
    rPropMap[ PROP_CharCaseMap ] <<= GetCaseMap( moCaseMap.get( XML_none ) );

    if( !bUseOptional || moBold.has() ) {
        float fWeight = moBold.get( false ) ? awt::FontWeight::BOLD : awt::FontWeight::NORMAL;
        rPropMap[ PROP_CharWeight ] <<= fWeight;
        rPropMap[ PROP_CharWeightAsian ] <<= fWeight;
        rPropMap[ PROP_CharWeightComplex ] <<= fWeight;
    }

    if( !bUseOptional || moItalic.has() ) {
        awt::FontSlant eSlant = moItalic.get( false ) ? awt::FontSlant_ITALIC : awt::FontSlant_NONE;
        rPropMap[ PROP_CharPosture ] <<= eSlant;
        rPropMap[ PROP_CharPostureAsian ] <<= eSlant;
        rPropMap[ PROP_CharPostureComplex ] <<= eSlant;
    }

    bool bUnderlineFillFollowText = moUnderlineFillFollowText.get( false );
    if( moUnderline.has() && maUnderlineColor.isUsed() && !bUnderlineFillFollowText )
    {
        rPropMap[ PROP_CharUnderlineHasColor ] <<= true;
        rPropMap[ PROP_CharUnderlineColor ] <<= maUnderlineColor.getColor( rFilter.getGraphicHelper() );
    }
}

    void TextCharacterProperties::pushToPropSet( PropertySet& rPropSet, const XmlFilterBase& rFilter, bool bUseOptional ) const
{
    PropertyMap aPropMap;
    pushToPropMap( aPropMap, rFilter, bUseOptional );
    rPropSet.setProperties( aPropMap );
}

float TextCharacterProperties::getCharHeightPoints( float fDefault ) const
{
    return moHeight.has() ? GetFontHeight( moHeight.get() ) : fDefault;
}

// ============================================================================

} // namespace drawingml
} // namespace oox

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
