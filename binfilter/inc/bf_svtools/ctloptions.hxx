/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: ctloptions.hxx,v $
 * $Revision: 1.3 $
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
#ifndef _SVTOOLS_CTLOPTIONS_HXX
#define _SVTOOLS_CTLOPTIONS_HXX

#ifndef INCLUDED_SVTDLLAPI_H
#include "bf_svtools/svtdllapi.h"
#endif

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

#ifndef _SFXBRDCST_HXX
#include <bf_svtools/brdcst.hxx>
#endif
#ifndef _SFXLSTNER_HXX
#include <bf_svtools/lstner.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_OPTIONS_HXX
#include <bf_svtools/options.hxx>
#endif

namespace binfilter {

class SvtCTLOptions_Impl;

// class SvtCTLOptions --------------------------------------------------------

class  SvtCTLOptions:
    public Options, public SfxBroadcaster, public SfxListener
{
private:
    SvtCTLOptions_Impl*    m_pImp;

public:

    // bDontLoad is for referencing purposes only
    SvtCTLOptions( sal_Bool bDontLoad = sal_False );
    virtual ~SvtCTLOptions();

    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    void            SetCTLFontEnabled( sal_Bool _bEnabled );
    sal_Bool		IsCTLFontEnabled() const;

    void			SetCTLSequenceChecking( sal_Bool _bEnabled );
    sal_Bool		IsCTLSequenceChecking() const;

    void			SetCTLSequenceCheckingRestricted( sal_Bool _bEnable );
    sal_Bool		IsCTLSequenceCheckingRestricted( void ) const;

    void            SetCTLSequenceCheckingTypeAndReplace( sal_Bool _bEnable );
    sal_Bool        IsCTLSequenceCheckingTypeAndReplace() const;

    enum CursorMovement
    {
        MOVEMENT_LOGICAL = 0,
        MOVEMENT_VISUAL
    };
    void        	SetCTLCursorMovement( CursorMovement _eMovement );
    CursorMovement	GetCTLCursorMovement() const;

    enum TextNumerals
    {
        NUMERALS_ARABIC = 0,
        NUMERALS_HINDI,
        NUMERALS_SYSTEM
    };
    void        	SetCTLTextNumerals( TextNumerals _eNumerals );
    TextNumerals	GetCTLTextNumerals() const;

    enum EOption
    {
        E_CTLFONT,
        E_CTLSEQUENCECHECKING,
        E_CTLCURSORMOVEMENT,
        E_CTLTEXTNUMERALS,
        E_CTLSEQUENCECHECKINGRESTRICTED,
        E_CTLSEQUENCECHECKINGTYPEANDREPLACE
    };
    sal_Bool IsReadOnly(EOption eOption) const;
};

}

#endif // _SVTOOLS_CTLOPTIONS_HXX

