/************************************************************************
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
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

package org.openoffice.xmerge.merger.merge;

import org.w3c.dom.Element;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.NamedNodeMap;

import org.openoffice.xmerge.ConverterCapabilities;
import org.openoffice.xmerge.MergeException;
import org.openoffice.xmerge.merger.MergeAlgorithm;
import org.openoffice.xmerge.merger.NodeMergeAlgorithm;
import org.openoffice.xmerge.merger.Iterator;
import org.openoffice.xmerge.merger.Difference;
import org.openoffice.xmerge.util.XmlUtil;

/**
 * This is an implementation of the <code>MergeAlgorithm</code> interface.
 * This class will merge two <code>Document</code> classes.  It utilizes the
 * appropriate class which implements {@link
 * org.openoffice.xmerge.merger.NodeMergeAlgorithm
 * NodeMergeAlgorithm} to perform the merge.
 *
 * @author smak
 */
public class DocumentMerge implements MergeAlgorithm {

    private NodeMergeAlgorithm subDocumentMerge = null;

    /**  The capabilities of this converter. */
    protected ConverterCapabilities cc_;


    /**
     *  Constructor
     *
     *  @param  cc     The <code>ConverterCapabilities</code>.
     *  @param  merge  The <code>NodeMergeAlgorithm</code>.
     */
    public DocumentMerge(ConverterCapabilities cc, NodeMergeAlgorithm merge) {
        cc_ = cc;
        subDocumentMerge = merge;
    }


    public void applyDifference(Iterator orgSeq, Iterator modSeq,
                            Difference[] differences) throws MergeException {


        // a quick test whether the differences array is in ascending order
        int currentPosition = -1;
        boolean haveDeleteOperation = false;

        for (int i = 0; i < differences.length; i++) {
            if (differences[i].getOrgPosition() > currentPosition) {
                currentPosition = differences[i].getOrgPosition();
                if (differences[i].getOperation() == Difference.DELETE) {
                    haveDeleteOperation = true;
                } else  {
                    haveDeleteOperation = false;
                }
            } else if (differences[i].getOrgPosition() == currentPosition) {
                if (differences[i].getOperation() == Difference.DELETE) {
                    haveDeleteOperation = true;
                } else if (differences[i].getOperation() == Difference.ADD &&
                            haveDeleteOperation == true) {
                    throw new MergeException(
                         "Differences array is not sorted. Delete before Add");
                }
            } else {
               throw new MergeException("Differences array need to be sorted.");
            }
        }

        // reset sequence counters
        orgSeq.start();
        int orgSeqCounter = 0;

        modSeq.start();
        int modSeqCounter = 0;

        // check for each diff unit in the diff array to apply the diff
        for (int i = 0; i < differences.length; i++) {

            Difference currentDiff = differences[i];

            int operation = currentDiff.getOperation();

            Object currentElement;

            switch (operation) {

            case Difference.DELETE:
                // loop through the original sequence up to the expected
                // position. note that we use delta (see above comment)
                // also. we will just continue the counter without reset it.
                for (;
                     orgSeqCounter < currentDiff.getOrgPosition();
                     orgSeqCounter++, orgSeq.next()) {
                    // empty
                }

                // remove the Node. note that it will NOT affect the
                // iterator sequence as ParaNodeIterator is a static one.
                removeNode((Node)(orgSeq.currentElement()));

                break;

            // if it's an add operation, then get content from original seq
            case Difference.ADD:
                // loop through the modified sequence up to the expected
                // position to get the content. As we don't need to modify
                // the sequence. we don't need to use delta to do adjustment.
                for (;
                     modSeqCounter < currentDiff.getModPosition();
                     modSeqCounter++, modSeq.next()) {
                    // empty
                }

                currentElement = orgSeq.currentElement();

                for (;
                     orgSeqCounter < currentDiff.getOrgPosition();
                     orgSeqCounter++, currentElement = orgSeq.next()) {
                    // empty
                }

                if (orgSeqCounter > orgSeq.elementCount() - 1) {
                    // append the element to the end of the original sequence
                    appendNode((Node)(orgSeq.currentElement()),
                               (Node)(modSeq.currentElement()));
                } else {
                    // insert the element BEFORE the current element
                    insertNode((Node)(orgSeq.currentElement()),
                               (Node)(modSeq.currentElement()));
                }

                break;

            case Difference.CHANGE:
                for (;
                     modSeqCounter < currentDiff.getModPosition();
                     modSeqCounter++, modSeq.next()) {
                    // empty
                }

                currentElement = orgSeq.currentElement();

                for (;
                     orgSeqCounter < currentDiff.getOrgPosition();
                     orgSeqCounter++, currentElement = orgSeq.next()) {
                    // empty
                }

                if (subDocumentMerge == null) {
                    // use a simple replace if no row merge algorithm supply
                    replaceElement((Element)orgSeq.currentElement(),
                                   (Element)modSeq.currentElement());
                } else {
                    subDocumentMerge.merge((Element)orgSeq.currentElement(),
                                         (Element)modSeq.currentElement());

                }
                break;

            default:
                break;
            }
        }
    }


    /** 
     *  Removes the specified <code>Node</code>.
     *
     *  @param  node  <code>Node</code> to remove.
     */
    protected void removeNode(Node node) {

        Node parent = node.getParentNode();
        parent.removeChild(node);
    }

    /**
     *  Appends <code>Node</code> after the specified <code>Node</code>.
     *
     *  @param  oldNode  <code>Node</code> to append after.
     *  @param  newNode  <code>Node</code> to append.
     */
    protected void appendNode(Node oldNode, Node newNode) {
        Node clonedNode = XmlUtil.deepClone(oldNode, newNode);
        Node parent = oldNode.getParentNode();
        parent.appendChild(clonedNode);
    }


    /**
     *  Insert <code>Node</code> before the specified <code>Node</code>.
     *
     *  @param  oldNode  <code>Node</code> to insert before.
     *  @param  newNode  <code>Node</code> to insert.
     */
    protected void insertNode(Node oldNode, Node newNode) {
        Node clonedNode = XmlUtil.deepClone(oldNode, newNode);
        Node parent = oldNode.getParentNode();
        parent.insertBefore(clonedNode, oldNode);
    }


    /**
     *  Replace <code>Element</code>.
     *
     *  @param  currElem  <code>Element</code> to be replaced.
     *  @param  newElem   <code>Element</code> to replace.
     */
    protected void replaceElement(Element currElem, Element newElem) {

        Node clonedNode = XmlUtil.deepClone(currElem, newElem);
        Node parent = currElem.getParentNode();
        parent.replaceChild(clonedNode, currElem);
    }
}

