/*************************************************************************
 *
 *    OpenOffice.org - a multi-platform office productivity suite
 *
 *    Author:
 *      Fridrich Strba  <fridrich.strba@bluewin.ch>
 *      Thorsten Behrens <tbehrens@novell.com>
 *
 *      Copyright (C) 2008, Novell Inc.
 *
 *   The Contents of this file are made available subject to
 *   the terms of GNU Lesser General Public License Version 3.
 *
 ************************************************************************/

#ifndef INCLUDED_PARSERFRAGMENTS_HXX
#define INCLUDED_PARSERFRAGMENTS_HXX

#include <sal/config.h>
#include <vector>
#include <string>

namespace basegfx
{
    class B2DHomMatrix;
    class B2DRange;
}
namespace svgi
{
    struct ARGBColor;

    /// Parse given string for one of the SVG color grammars
    bool parseColor( const char* sColor, ARGBColor& rColor );
    bool parseOpacity( const char* sOpacity, ARGBColor& rColor );

    /// Parse given string for one of the SVG transformation grammars
    bool parseTransform( const char* sTransform, basegfx::B2DHomMatrix& rTransform );

    /// Parse given string for the viewBox attribute
    bool parseViewBox( const char* sViewbox, basegfx::B2DRange& rRect );

    /// Parse given string for a list of double values, comma-delimited
    bool parseDashArray( const char* sDashArray, std::vector<double>& rOutputVector );

    /// Parse given string for the xlink attribute
    bool parseXlinkHref( const char* xlink, std::string& data );

} // namespace svgi

#endif
