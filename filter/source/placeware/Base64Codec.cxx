/*************************************************************************
 *
 *  $RCSfile: Base64Codec.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: cl $ $Date: 2002-09-25 10:24:35 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): Martin Gallwey (gallwey@sun.com)
 *
 *
 ************************************************************************/

#ifndef _BASE64_CODEC_HXX
#include "Base64Codec.hxx"
#endif
#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif
#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif
using namespace rtl;
using namespace osl;
using namespace com::sun::star;

const
  sal_Char aBase64EncodeTable[] =
    { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };

const
  sal_uInt8 aBase64DecodeTable[]  =
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0-15

      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 16-31

      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62,  0,  0,  0, 63, // 32-47
//                                                +               /

     52, 53, 54, 55, 56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0, // 48-63
//    0   1   2   3   4   5   6   7   8   9               =

      0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, // 64-79
//        A   B   C   D   E   F   G   H   I   J   K   L   M   N   O

     15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,  0,  0,  0,  0, // 80-95
//    P   Q   R   S   T   U   V   W   X   Y   Z

      0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, // 96-111
//        a   b   c   d   e   f   g   h   i   j   k   l   m   n   o

     41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,  0,  0,  0,  0,  0, // 112-127
//    p   q   r   s   t   u   v   w   x   y   z

      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};


void ThreeByteToFourByte (const sal_uInt8* pBuffer, const sal_Int32 nStart, const sal_Int32 nFullLen, rtl::OUStringBuffer& sBuffer)
{
    sal_Int32 nLen(nFullLen - nStart);
    if (nLen > 3)
        nLen = 3;
    if (nLen == 0)
    {
        sBuffer.setLength(0);
        return;
    }

    sal_Int32 nBinaer;
    switch (nLen)
    {
        case 1:
        {
            nBinaer = ((sal_uInt8)pBuffer[nStart + 0]) << 16;
        }
        break;
        case 2:
        {
            nBinaer = (((sal_uInt8)pBuffer[nStart + 0]) << 16) +
                    (((sal_uInt8)pBuffer[nStart + 1]) <<  8);
        }
        break;
        default:
        {
            nBinaer = (((sal_uInt8)pBuffer[nStart + 0]) << 16) +
                    (((sal_uInt8)pBuffer[nStart + 1]) <<  8) +
                    ((sal_uInt8)pBuffer[nStart + 2]);
        }
        break;
    }

    sBuffer.appendAscii("====");

    sal_uInt8 nIndex ((nBinaer & 0xFC0000) >> 18);
    sBuffer.setCharAt(0, aBase64EncodeTable [nIndex]);

    nIndex = (nBinaer & 0x3F000) >> 12;
    sBuffer.setCharAt(1, aBase64EncodeTable [nIndex]);
    if (nLen == 1)
        return;

    nIndex = (nBinaer & 0xFC0) >> 6;
    sBuffer.setCharAt(2, aBase64EncodeTable [nIndex]);
    if (nLen == 2)
        return;

    nIndex = (nBinaer & 0x3F);
    sBuffer.setCharAt(3, aBase64EncodeTable [nIndex]);
}

void Base64Codec::encodeBase64(rtl::OUStringBuffer& aStrBuffer, const uno::Sequence < sal_Int8 >& aPass)
{
    sal_Int32 i(0);
    sal_Int32 nBufferLength(aPass.getLength());
    const sal_Int8* pBuffer = aPass.getConstArray();
    while (i < nBufferLength)
    {
        rtl::OUStringBuffer sBuffer;
        ThreeByteToFourByte ((const sal_uInt8*)pBuffer, i, nBufferLength, sBuffer);
        aStrBuffer.append(sBuffer);
        i += 3;
    }
}

const rtl::OUString s2equal(RTL_CONSTASCII_USTRINGPARAM("=="));
const rtl::OUString s1equal(RTL_CONSTASCII_USTRINGPARAM("="));

void FourByteToThreeByte (sal_uInt8* pBuffer, sal_Int32& nLength, const sal_Int32 nStart, const rtl::OUString& sString)
{
    nLength = 0;
    sal_Int32 nLen (sString.getLength());

    if (nLen != 4)
    {
        OSL_DEBUG_ONLY(  "wrong length");
        return;
    }


    if (sString.indexOf(s2equal) == 2)
        nLength = 1;
    else if (sString.indexOf(s1equal) == 3)
        nLength = 2;
    else
        nLength = 3;

    sal_Int32 nBinaer ((aBase64DecodeTable [sString [0]] << 18) +
            (aBase64DecodeTable [sString [1]] << 12) +
            (aBase64DecodeTable [sString [2]] <<  6) +
            (aBase64DecodeTable [sString [3]]));

    sal_uInt8 OneByte ((nBinaer & 0xFF0000) >> 16);
    pBuffer[nStart + 0] = (sal_uInt8)OneByte;

    if (nLength == 1)
        return;

    OneByte = (nBinaer & 0xFF00) >> 8;
    pBuffer[nStart + 1] = (sal_uInt8)OneByte;

    if (nLength == 2)
        return;

    OneByte = nBinaer & 0xFF;
    pBuffer[nStart + 2] = (sal_uInt8)OneByte;
}

void Base64Codec::decodeBase64(uno::Sequence< sal_uInt8 >& aBuffer, const rtl::OUString& sBuffer)
{
    sal_Int32 nFirstLength((sBuffer.getLength() / 4) * 3);
    sal_uInt8* pBuffer = new sal_uInt8[nFirstLength];
    sal_Int32 nSecondLength(0);
    sal_Int32 nLength(0);
    sal_Int32 i = 0;
    sal_Int32 k = 0;
    while (i < sBuffer.getLength())
    {
        FourByteToThreeByte (pBuffer, nLength, k, sBuffer.copy(i, 4));
        nSecondLength += nLength;
        nLength = 0;
        i += 4;
        k += 3;
    }
    aBuffer = uno::Sequence<sal_uInt8>(pBuffer, nSecondLength);
    delete[] pBuffer;
}
