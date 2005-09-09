/************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: TokenFactory.java,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:09:10 $
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


package org.openoffice.xmerge.converter.xml.sxc.pexcel.records.formula;

import java.io.*;
import java.util.Vector;
import java.util.Enumeration;

import org.openoffice.xmerge.util.Debug;

/**
 * This is the Factory class responsible for creating a <code>Token</code>. 
 * It has three methods for returning three different types of Tokens
 * (Operator, Operand and Function).  
 * This utility class is used by either the <code>FormulaParser</code> or the
 * <code>FormulaDecoder</code>. 
 */
public class TokenFactory {
    
    private OperatorLookup operatorLookup;
    private OperandLookup operandLookup;
    private FunctionLookup fl;
   
    /**
     * Default Constructor
     */
    public TokenFactory() {
        operatorLookup = new OperatorLookup();
        operandLookup = new OperandLookup();
        fl = new FunctionLookup();
    }

    /**
     * The Factory method for creating function Tokens
     * 
     * @return The created <code>Token</code>
     */
    public Token getFunctionToken(String s, int args) {
        Token t = null;
        // We will have to fix this later to include fixed function tokens
        // Also will need to handle errors where functions names are incorrect???
        Debug.log(Debug.TRACE,"TokenFactory creating function Token : " + s);
        try {
            t = new Token(s, ParseToken.TOKEN_FUNCTION_VARIABLE, fl.getIDFromString(s), args);
        } catch (UnsupportedFunctionException eFn) {
                
            Debug.log(Debug.ERROR, eFn.getMessage());
        }
        return t;
    }
        
    /**
     * The Factory method for creating operator Tokens
     *
     * @return The created <code>Token</code>
     */
    public Token getOperatorToken(String s, int args) {
    
        Token t = null;
                
        Debug.log(Debug.TRACE,"TokenFactory creating operator Token : " + s);
        try  {
            if(args==1) {
                if(s.equals("+")) {
                    t = new Token(s, ParseToken.TOKEN_OPERATOR, operatorLookup.getIDFromString("UNARY_PLUS"), args);
                } else if (s.equals("-")) {
                    t = new Token(s, ParseToken.TOKEN_OPERATOR, operatorLookup.getIDFromString("UNARY_MINUS"), args);
                } else {
                    t = new Token(s, ParseToken.TOKEN_OPERATOR, operatorLookup.getIDFromString(s), args);
                }
            } else {
                t = new Token(s, ParseToken.TOKEN_OPERATOR, operatorLookup.getIDFromString(s), args);
            }
        } catch (UnsupportedFunctionException eFn) {
            Debug.log(Debug.ERROR, eFn.getMessage());
        } 
        return t;
    }

    /**
     * The Factory method for creating Operand Tokens
     *
     * @return The created <code>Token</code>
     */
    public Token getOperandToken(String s, String type) {
        Token t = null;
        
        Debug.log(Debug.TRACE,"TokenFactory creating operand (" + type + ") Token : " + s);
        try {
            t = new Token(s, ParseToken.TOKEN_OPERAND, operandLookup.getIDFromString(type), 0);
        } catch (UnsupportedFunctionException eFn) {
            Debug.log(Debug.ERROR, eFn.getMessage());
        } 

        return t;
    }
}
