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
#ifndef INCLUDED_DMAPPER_PROPERTYIDS_HXX
#define INCLUDED_DMAPPER_PROPERTYIDS_HXX

namespace rtl{ class OUString;}

namespace writerfilter {
namespace dmapper{
enum PropertyIds
{
        PROP_ID_START = 1
 /* 1*/ ,PROP_CHAR_WEIGHT = PROP_ID_START
 /* 2*/ ,PROP_CHAR_POSTURE
 /* 3*/ ,PROP_CHAR_STRIKEOUT
 /* 4*/ ,PROP_CHAR_CONTOURED
 /* 5*/ ,PROP_CHAR_SHADOWED
 /* 6*/ ,PROP_CHAR_CASE_MAP
 /* 7*/ ,PROP_CHAR_COLOR
 /* 8*/ ,PROP_CHAR_RELIEF
 /* 9*/ ,PROP_CHAR_UNDERLINE
 /*10*/ ,PROP_CHAR_WORD_MODE
 /*11*/ ,PROP_CHAR_ESCAPEMENT
 /*12*/ ,PROP_CHAR_ESCAPEMENT_HEIGHT
 /*13*/ ,PROP_CHAR_HEIGHT
 /*14*/ ,PROP_CHAR_HEIGHT_COMPLEX
 /*15*/ ,PROP_CHAR_LOCALE
 /*16*/ ,PROP_CHAR_LOCALE_ASIAN
 /*17*/ ,PROP_CHAR_WEIGHT_COMPLEX
 /*18*/ ,PROP_CHAR_POSTURE_COMPLEX
 /*19*/ ,PROP_CHAR_AUTO_KERNING
 /*20*/ ,PROP_CHAR_CHAR_KERNING
 /*21*/ ,PROP_CHAR_SCALE_WIDTH
 /*22*/ ,PROP_CHAR_LOCALE_COMPLEX
 /*23*/ ,PROP_CHAR_UNDERLINE_COLOR
/*24*/ , PROP_CHAR_UNDERLINE_HAS_COLOR
/*25*/ , PROP_CHAR_FONT_NAME
/*26*/ , PROP_CHAR_FONT_STYLE
/*27*/ , PROP_CHAR_FONT_FAMILY
/*28*/ , PROP_CHAR_FONT_CHAR_SET
/*29*/ , PROP_CHAR_FONT_PITCH
/*30*/ , PROP_CHAR_FONT_NAME_ASIAN
/*31*/ , PROP_CHAR_HEIGHT_ASIAN
/*32*/ , PROP_CHAR_FONT_STYLE_ASIAN
/*33*/ , PROP_CHAR_FONT_FAMILY_ASIAN
/*34*/ , PROP_CHAR_FONT_CHAR_SET_ASIAN
/*35*/ , PROP_CHAR_FONT_PITCH_ASIAN
/*36*/ , PROP_CHAR_FONT_NAME_COMPLEX
/*37*/ , PROP_CHAR_FONT_STYLE_COMPLEX
/*38*/ , PROP_CHAR_FONT_FAMILY_COMPLEX
/*39*/ , PROP_CHAR_FONT_CHAR_SET_COMPLEX
/*40*/ , PROP_CHAR_FONT_PITCH_COMPLEX
/*41*/ , PROP_CHAR_HIDDEN
/*42*/ , PROP_CHAR_WEIGHT_ASIAN
/*43*/ , PROP_CHAR_POSTURE_ASIAN
/*44*/ , PROP_PARA_STYLE_NAME
/*45*/ , PROP_CHAR_STYLE_NAME
/*46*/ , PROP_PARA_ADJUST
/*47*/ , PROP_PARA_LAST_LINE_ADJUST
/*48*/ , PROP_PARA_RIGHT_MARGIN
/*49*/ , PROP_PARA_LEFT_MARGIN
/*50*/ , PROP_PARA_FIRST_LINE_INDENT
/*51*/ , PROP_PARA_KEEP_TOGETHER
/*52*/ , PROP_PARA_TOP_MARGIN
/*53*/ , PROP_PARA_BOTTOM_MARGIN
/*54*/ , PROP_PARA_IS_HYPHENATION
/*55*/ , PROP_PARA_LINE_NUMBER_COUNT
/*56*/ , PROP_PARA_IS_HANGING_PUNCTUATION
/*57*/ , PROP_PARA_LINE_SPACING
/*58*/ , PROP_PARA_TAB_STOPS
/*59*/ , PROP_PARA_WIDOWS
/*60*/ , PROP_PARA_ORPHANS
/*61*/ , PROP_PARA_LINE_NUMBER_START_VALUE
/*62*/ , PROP_NUMBERING_LEVEL
/*63*/ , PROP_NUMBERING_RULES
/*64*/ , PROP_NUMBERING_TYPE
/*65*/ , PROP_START_WITH
/*66*/ , PROP_ADJUST
/*67*/ , PROP_PARENT_NUMBERING
/*68*/ , PROP_LEFT_MARGIN
/*69*/ , PROP_RIGHT_MARGIN
/*70*/ , PROP_TOP_MARGIN
/*71*/ , PROP_BOTTOM_MARGIN
/*72*/ , PROP_FIRST_LINE_OFFSET
/*73*/ , PROP_LEFT_BORDER
/*74*/ , PROP_RIGHT_BORDER
/*75*/ , PROP_TOP_BORDER
/*76*/ , PROP_BOTTOM_BORDER
/*77*/ , PROP_TABLE_BORDER
/*78*/ , PROP_LEFT_BORDER_DISTANCE
/*79*/ , PROP_RIGHT_BORDER_DISTANCE
/*80*/ , PROP_TOP_BORDER_DISTANCE
/*81*/ , PROP_BOTTOM_BORDER_DISTANCE
/*82*/ , PROP_CURRENT_PRESENTATION
/*83*/ , PROP_IS_FIXED
/*84*/ , PROP_SUB_TYPE
/*85*/ , PROP_FILE_FORMAT
/*86*/ , PROP_HYPER_LINK_U_R_L
/*87*/ , PROP_NUMBER_FORMAT
/*88*/ , PROP_NAME
/*89*/ , PROP_IS_INPUT
/*90*/ , PROP_HINT
/*91*/ , PROP_FULL_NAME
/*92*/ , PROP_KEYWORDS
/*93*/ , PROP_DESCRIPTION
/*94*/ , PROP_MACRO_NAME
/*95*/ , PROP_SUBJECT
/*96*/ , PROP_USER_DATA_TYPE
/*97*/ , PROP_TITLE
/*98*/ , PROP_CONTENT
/*99*/ , PROP_DATA_COLUMN_NAME
/*100*/, PROP_INPUT_STREAM
/*101*/, PROP_GRAPHIC
/*102*/, PROP_ANCHOR_TYPE
/*103*/ ,PROP_SIZE
/*104*/ ,PROP_HORI_ORIENT
/*105*/ ,PROP_HORI_ORIENT_POSITION
/*106*/ ,PROP_HORI_ORIENT_RELATION
/*107*/ ,PROP_VERT_ORIENT
/*108*/ ,PROP_VERT_ORIENT_POSITION
/*109*/ ,PROP_VERT_ORIENT_RELATION
/*110*/ ,PROP_GRAPHIC_CROP
/*111*/ ,PROP_SIZE100th_M_M
/*112*/ ,PROP_SIZE_PIXEL
/*113*/ ,PROP_SURROUND
/*114*/ ,PROP_SURROUND_CONTOUR
/*115*/ ,PROP_ADJUST_CONTRAST
/*116*/ ,PROP_ADJUST_LUMINANCE
/*117*/ ,PROP_GRAPHIC_COLOR_MODE
/*118*/ ,PROP_GAMMA
/*119*/ ,PROP_HORI_MIRRORED_ON_EVEN_PAGES
/*120*/ ,PROP_HORI_MIRRORED_ON_ODD_PAGES
/*121*/ ,PROP_VERT_MIRRORED
/*122*/ ,PROP_CONTOUR_OUTSIDE
/*123*/ ,PROP_CONTOUR_POLY_POLYGON
/*124*/ ,PROP_PAGE_TOGGLE
/*125*/ ,PROP_BACK_COLOR
/*126*/ ,PROP_ALTERNATIVE_TEXT
/*127*/ ,PROP_HEADER_TEXT_LEFT
/*128*/ ,PROP_HEADER_TEXT
/*129*/ ,PROP_HEADER_IS_SHARED
/*130*/ ,PROP_HEADER_IS_ON
/*131*/ ,PROP_FOOTER_TEXT_LEFT
/*132*/ ,PROP_FOOTER_TEXT
/*133*/ ,PROP_FOOTER_IS_SHARED
/*134*/ ,PROP_FOOTER_IS_ON
/*135*/ ,PROP_WIDTH
/*136*/ ,PROP_HEIGHT
/*137*/ ,PROP_SEPARATOR_LINE_IS_ON
/*138*/ ,PROP_TEXT_COLUMNS
/*139*/ ,PROP_AUTOMATIC_DISTANCE
/*140*/ ,PROP_IS_LANDSCAPE
/*141*/ ,PROP_PRINTER_PAPER_TRAY_INDEX
/*142*/ ,PROP_FIRST_PAGE
/*143*/ ,PROP_DEFAULT
/*144*/ ,PROP_PAGE_DESC_NAME
/*145*/ ,PROP_PAGE_NUMBER_OFFSET
/*146*/ ,PROP_BREAK_TYPE
/*147*/ ,PROP_FOOTER_IS_DYNAMIC_HEIGHT
/*148*/ ,PROP_FOOTER_DYNAMIC_SPACING
/*149*/ ,PROP_FOOTER_HEIGHT
/*150*/ ,PROP_FOOTER_BODY_DISTANCE
/*151*/ ,PROP_HEADER_IS_DYNAMIC_HEIGHT
/*152*/ ,PROP_HEADER_DYNAMIC_SPACING
/*153*/ ,PROP_HEADER_HEIGHT
/*154*/ ,PROP_HEADER_BODY_DISTANCE
/*155*/ ,PROP_WRITING_MODE
/*156*/ ,PROP_GRID_MODE
/*157*/ ,PROP_GRID_DISPLAY
/*158*/ ,PROP_GRID_PRINT
/*159*/ ,PROP_ADD_EXTERNAL_LEADING
/*160*/ ,PROP_GRID_LINES
/*161*/ ,PROP_GRID_BASE_HEIGHT
/*162*/ ,PROP_GRID_RUBY_HEIGHT
/*163*/ ,PROP_IS_ON
/*164*/ ,PROP_RESTART_AT_EACH_PAGE
/*165*/ ,PROP_COUNT_EMPTY_LINES
/*166*/ ,PROP_COUNT_LINES_IN_FRAMES
/*167*/ ,PROP_INTERVAL
/*168*/ ,PROP_DISTANCE
/*169*/ ,PROP_NUMBER_POSITION
/*170*/ ,PROP_LEVEL
/*171*/ ,PROP_LEVEL_PARAGRAPH_STYLES
/*172*/ ,PROP_LEVEL_FORMAT
/*173*/ ,PROP_TOKEN_TYPE
/*174*/ ,PROP_TOKEN_HYPERLINK_START
/*175*/ ,PROP_TOKEN_HYPERLINK_END
/*176*/ ,PROP_TOKEN_CHAPTER_INFO
/*177*/ ,PROP_CHAPTER_FORMAT
/*178*/ ,PROP_TOKEN_TEXT
/*179*/ ,PROP_TEXT
/*180*/ ,PROP_CREATE_FROM_OUTLINE
/*181*/ ,PROP_CREATE_FROM_MARKS
/*182*/ ,PROP_STANDARD
/*183*/ ,PROP_CHAR_BACK_COLOR
/*184*/ ,PROP_CHAR_EMPHASIS
/*185*/ ,PROP_CHAR_COMBINE_IS_ON
/*186*/ ,PROP_CHAR_COMBINE_PREFIX
/*187*/ ,PROP_CHAR_COMBINE_SUFFIX
/*188*/ ,PROP_CHAR_ROTATION
/*189*/ ,PROP_CHAR_ROTATION_IS_FIT_TO_LINE
/*190*/ ,PROP_CHAR_FLASH
/*191*/ ,PROP_IS_SPLIT_ALLOWED
/*192*/ ,META_PROP_VERTICAL_BORDER
/*193*/ ,META_PROP_HORIZONTAL_BORDER
/*194*/ ,PROP_HEADER_ROW_COUNT
/*195*/ ,PROP_IS_AUTO_HEIGHT
/*196*/ ,PROP_SIZE_TYPE
/*197*/ ,PROP_TABLE_COLUMN_SEPARATORS
/*198*/ ,META_PROP_TABLE_STYLE_NAME
/*199*/ ,PROP_REDLINE_AUTHOR
/*200*/ ,PROP_REDLINE_DATE_TIME
/*201*/ ,PROP_REDLINE_COMMENT
/*202*/ ,PROP_REDLINE_TYPE
/*203*/ ,PROP_REDLINE_SUCCESSOR_DATA
/*204*/ ,PROP_REDLINE_IDENTIFIER
/*205*/ ,PROP_SIZE_PROTECTED
/*206*/ ,PROP_POSITION_PROTECTED
/*207*/ ,PROP_OPAQUE
/*208*/ ,PROP_VERTICAL_MERGE
/*209*/ ,PROP_BULLET_CHAR
/*210*/ ,PROP_BULLET_FONT_NAME
/*211*/ ,PROP_PARA_BACK_COLOR
/*212*/ ,PROP_TABS_RELATIVE_TO_INDENT
/*213*/ ,PROP_PREFIX
/*214*/ ,PROP_SUFFIX
/*215*/ ,PROP_CREATE_FROM_LEVEL_PARAGRAPH_STYLES
/*216*/ ,PROP_DROP_CAP_FORMAT
/*217*/ , PROP_REFERENCE_FIELD_PART
/*218*/ ,PROP_SOURCE_NAME
/*219*/ ,PROP_REFERENCE_FIELD_SOURCE
/*220*/ ,PROP_WIDTH_TYPE
/*221*/ ,PROP_TEXT_RANGE
/*222*/ ,PROP_SERVICE_CHAR_STYLE
/*223*/ ,PROP_SERVICE_PARA_STYLE
/*224*/ ,PROP_CHARACTER_STYLES
/*225*/ ,PROP_PARAGRAPH_STYLES
/*226*/ ,PROP_TABLE_BORDER_DISTANCES
/*227*/ ,META_PROP_CELL_MAR_TOP
/*228*/ ,META_PROP_CELL_MAR_BOTTOM
/*229*/ ,META_PROP_CELL_MAR_LEFT
/*230*/ ,META_PROP_CELL_MAR_RIGHT
/*231*/ ,PROP_START_AT
/*232*/ ,PROP_ADD_PARA_TABLE_SPACING
/*233*/ ,PROP_CHAR_PROP_HEIGHT
/*234*/ ,PROP_CHAR_PROP_HEIGHT_ASIAN
/*235*/ ,PROP_CHAR_PROP_HEIGHT_COMPLEX
/*236*/ ,PROP_FORMAT
/*237*/ ,PROP_INSERT
/*238*/ ,PROP_DELETE
/*239*/ ,PROP_STREAM_NAME
/*240*/ ,PROP_BITMAP
/*241*/ ,PROP_IS_DATE
/*242*/ ,PROP_TAB_STOP_DISTANCE
/*243*/ ,PROP_CNF_STYLE
/*244*/ ,PROP_INDENT_AT
/*245*/ ,PROP_FIRST_LINE_INDENT
/*246*/ ,PROP_NUMBERING_STYLE_NAME
/*247*/ ,PROP_OUTLINE_LEVEL
/*248*/ ,PROP_LISTTAB_STOP_POSITION
/*249*/ ,PROP_POSITION_AND_SPACE_MODE
/*250*/ ,PROP_HEADING_STYLE_NAME
/*251*/ ,PROP_PARA_SPLIT
/*252*/ ,PROP_HELP
/*253*/ ,PROP_FRM_DIRECTION
};
struct PropertyNameSupplier_Impl;
class PropertyNameSupplier
{
    PropertyNameSupplier_Impl* m_pImpl;
public:
    PropertyNameSupplier();
    ~PropertyNameSupplier();
    const rtl::OUString& GetName( PropertyIds eId ) const;

    static PropertyNameSupplier& GetPropertyNameSupplier();
};
} //namespace dmapper
} // namespace writerfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
