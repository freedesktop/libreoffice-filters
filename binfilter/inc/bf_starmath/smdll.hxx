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
#ifndef SMDLL_HXX
#define SMDLL_HXX

#include <bf_svtools/bf_solar.h>

#define SMDLL	1

#include <bf_starmath/smdll0.hxx>
#include <tools/resid.hxx>
#include <bf_sfx2/sfxdefs.hxx>
namespace binfilter {

class SmData;
class SfxMedium;
class SfxFilter;

class SmDLL
{
    static BOOL bInitialized;
public:
    SmDLL();
    ~SmDLL();

    static void Init();
    static void LibInit();
    static void Exit();
    static void LibExit();

    static ULONG DetectFilter( SfxMedium& rMedium, const SfxFilter **ppFilter,
                               SfxFilterFlags nMust, SfxFilterFlags nDont );
};

#ifdef SMDLL
class SmResId : public ResId
{
public:
    SmResId(USHORT nId) :
        ResId(nId, *SM_MOD()->GetResMgr())
    {
    }
};
#endif

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
