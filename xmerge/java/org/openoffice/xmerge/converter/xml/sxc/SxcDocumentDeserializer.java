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

package org.openoffice.xmerge.converter.xml.sxc;

import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;

import java.io.IOException;

import org.openoffice.xmerge.Document;
import org.openoffice.xmerge.ConvertData;
import org.openoffice.xmerge.ConvertException;
import org.openoffice.xmerge.DocumentDeserializer;
import org.openoffice.xmerge.converter.xml.OfficeConstants;
import org.openoffice.xmerge.converter.xml.sxc.SxcDocument;
import org.openoffice.xmerge.util.Debug;

/**
 *  <p>General spreadsheet implementation of <code>DocumentDeserializer</code>
 *  for the {@link
 *  org.openoffice.xmerge.converter.xml.sxc.SxcPluginFactory
 *  SxcPluginFactory}.  Used with SXC <code>Document</code> objects.</p>
 *
 *  <p>The <code>deserialize</code> method uses a <code>DocDecoder</code>
 *  to read the device spreadsheet format into a <code>String</code>
 *  object, then it calls <code>buildDocument</code> to create a
 *  <code>SxcDocument</code> object from it.</p>
 *
 *  @author      Paul Rank
 *  @author      Mark Murnane
 */
public abstract class SxcDocumentDeserializer implements OfficeConstants,
    DocumentDeserializer {

    /**
     *  A <code>SpreadsheetDecoder</code> object for decoding from
     *  device formats.
     */
    private SpreadsheetDecoder decoder = null;

    /**  A w3c <code>Document</code>. */
    private org.w3c.dom.Document doc = null;

    /**  An <code>ConvertData</code> object assigned to this object. */
    private ConvertData cd = null;


    /**
     *  Constructor.
     *
     *  @param  cd  <code>ConvertData</code> consisting of a
     *              device content object.
     */
    public SxcDocumentDeserializer(ConvertData cd) {
        this.cd = cd;
    }


    /** 
     *  This abstract method will be implemented by concrete subclasses
     *  and will return an application-specific Decoder.
     *
     *  @param  workbook  The WorkBook to read.
     *  @param  password  The WorkBook password.
     *
     *  @return  The appropriate <code>SpreadSheetDecoder</code>.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    public abstract SpreadsheetDecoder createDecoder(String workbook, String[] worksheetNames, String password)
        throws IOException;

    
    /**
     *  <p>This method will return the name of the WorkBook from the
     *  <code>ConvertData</code>.  Allows for situations where the
     *  WorkBook name differs from the Device Content name.</p>
     *
     *  <p>Implemented in the Deserializer as the Decoder's constructor requires
     *  a name.</p>
     *
     *  @param  cd  The <code>ConvertData</code> containing the Device 
     *              content.
     *
     *  @return  The WorkBook name.
     */
    protected abstract String getWorkbookName(ConvertData cd) throws IOException;

    
    /**
     *  This method will return the name of the WorkSheet from the
     *  <code>ConvertData</code>.
     *
     *  @param  cd  The <code>ConvertData</code> containing the Device
     *              content.
     *
     *  @return  The WorkSheet names.
     */
    protected abstract String[] getWorksheetNames(ConvertData cd) throws IOException;
    
    
    /**
     *  <p>Method to convert a set of &quot;Device&quot;
     *  <code>Document</code> objects into a <code>SxcDocument</code>
     *  object and returns it as a <code>Document</code>.</p>
     *
     *  <p>This method is not thread safe for performance reasons.
     *  This method should not be called from within two threads.
     *  It would be best to call this method only once per object
     *  instance.</p>
     *
     *  @return  document  An <code>SxcDocument</code> consisting
     *                     of the data converted from the input
     *                     stream.
     *
     *  @throws  ConvertException  If any conversion error occurs.
     *  @throws  IOException       If any I/O error occurs.
     */
    public Document deserialize() throws ConvertException,
        IOException {

        // Get the name of the WorkBook from the ConvertData.
        String[] worksheetNames = getWorksheetNames(cd);
        String workbookName = getWorkbookName(cd);

        // Create a document
        SxcDocument sxcDoc = new SxcDocument(workbookName);
        sxcDoc.initContentDOM();

        doc = sxcDoc.getContentDOM();

        // Little fact for the curious reader: workbookName should
        // be the name of the StarCalc file minus the file extension suffix.

        // Create a Decoder to decode the DeviceContent to a spreadsheet document
        // TODO - we aren't using a password in StarCalc, so we can
        // use any value for password here.  If StarCalc XML supports
        // passwords in the future, we should try to get the correct
        // password value here.
        //
        decoder = createDecoder(workbookName, worksheetNames, "password");

        Debug.log(Debug.TRACE, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
        Debug.log(Debug.TRACE, "<DEBUGLOG>");

        decoder.addDeviceContent(cd);
        decode();

        Debug.log(Debug.TRACE, "</DEBUGLOG>");

        return sxcDoc;
    }


    /**
     *  Outer level method used to decode a WorkBook
     *  into a <code>Document</code>.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    protected void decode() throws IOException {

         // Get number of worksheets
        int numSheets = decoder.getNumberOfSheets();

        for (int i = 0; i < numSheets; i++) {

            // Set the decoder to the correct worksheet
            decoder.setWorksheet(i);

            //  Traverse to the office:body element.
            //  There should only be one.
            NodeList list = doc.getElementsByTagName(TAG_OFFICE_BODY);

            int len = list.getLength();

            if (len > 0) {

                Node node = list.item(0);

                // Process the spreadsheet
                processTable(node);
            }
        }
    }


    /**
     *  This method process a WorkSheet and generates a portion
     *  of the <code>Document</code>.  A spreadsheet is represented
     *  as a table Node in StarOffice XML format.
     *
     *  @param  root  The root <code>Node</code> of the
     *                <code>Document</code> we are building.  This
     *                <code>Node</code> should be a TAG_OFFICE_BODY
     *                tag.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    protected void processTable(Node root) throws IOException {

        Debug.log(Debug.TRACE, "<TABLE>");

        // Create an element node for the table
        Element tableElement = (Element) doc.createElement(TAG_TABLE);

        // Get the sheet name
        String sheetName = decoder.getSheetName();

        // Set the table name attribute
        tableElement.setAttribute(ATTRIBUTE_TABLE_NAME, sheetName);

        // TODO - style currently hardcoded - get real value
        // Set table style-name attribute
        tableElement.setAttribute(ATTRIBUTE_TABLE_STYLE_NAME, "Default");

        // Append the table element to the root node
        root.appendChild(tableElement);

        Debug.log(Debug.TRACE, "<SheetName>");
        Debug.log(Debug.TRACE, sheetName);
        Debug.log(Debug.TRACE, "</SheetName>");

        // Get each cell and add to doc
        processCells(tableElement);

        Debug.log(Debug.TRACE, "</TABLE>");
    }


    /**
     *  <p>This method process the cells in a <code>Document</code>
     *  and generates a portion of the <code>Document</code>.</p>
     *
     *  <p>This method assumes that records are sorted by
     *  row and then column.</p>
     *
     *  @param  root  The <code>Node</code> of the <code>Document</code>
     *                we are building that we will append our cell
     *                <code>Node</code> objects.  This <code>Node</code>
     *                should be a TAG_TABLE tag.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    protected void processCells(Node root) throws IOException {

        // The current row element
        Element rowElement = null;

        // The current cell element
        Element cellElement = null;

        // The row number - we may not have any rows (empty sheet)
        // so set to zero.
        int row = 0;

        // The column number - This is the expected column number of
        // the next cell we are reading.
        int col = 1;

        // The number of columns in the spreadsheet
        int lastColumn = decoder.getNumberOfColumns();


        // Loop over all cells in the spreadsheet
        while (decoder.goToNextCell()) {

            // Get the row number
            int newRow = decoder.getRowNumber();

            // Is the cell in a new row, or part of the current row?
            if (newRow != row) {

                // Make sure that all the cells in the previous row
                // have been entered.
                if (col <= lastColumn && rowElement != null) {
                    int numSkippedCells = lastColumn - col + 1;
                    addEmptyCells(numSkippedCells, rowElement);
                }

                // log an end row - if we already have a row
                if (row != 0) {
                    Debug.log(Debug.TRACE, "</tr>");
                }

                // How far is the new row from the last row?
                int deltaRows = newRow - row;

                // Check if we have skipped any rows
                if (deltaRows > 1) {
                    // Add in empty rows
                    addEmptyRows(deltaRows-1, root, lastColumn);
                }

                // Re-initialize column (since we are in a new row)
                col = 1;

                // Create an element node for the new row
                rowElement = (Element) doc.createElement(TAG_TABLE_ROW);

                // TODO - style currently hardcoded - get real value
                // Set row style-name attribute
                rowElement.setAttribute(ATTRIBUTE_TABLE_STYLE_NAME,
                                        "Default");

                // Append the row element to the root node
                root.appendChild(rowElement);

                // Update row number
                row = newRow;

                Debug.log(Debug.TRACE, "<tr>");
            }

            // Get the column number of the current cell
            int newCol = decoder.getColNumber();

            // Check to see if some columns were skipped
            if (newCol != col) {

                // How many columns have we skipped?
                int numColsSkipped = newCol - col;

                addEmptyCells(numColsSkipped, rowElement);

                // Update the column number to account for the
                // skipped cells
                col = newCol;
            }

            // Lets start dealing with the cell data
            Debug.log(Debug.TRACE, "<td>");

            // Get the cell's contents
            String cellContents = decoder.getCellContents();

            // Get the type of the data in the cell
            String cellType = decoder.getCellDataType();

            // Create an element node for the cell
            cellElement = (Element) doc.createElement(TAG_TABLE_CELL);

            // TODO - style currently hardcoded - get real value
            // Set cell style-name attribute
            cellElement.setAttribute(ATTRIBUTE_TABLE_STYLE_NAME, "Default");

            // Store the cell data into the appropriate attributes
            processCellData(cellElement, cellType, cellContents);

            // Append the cell element to the row node
            rowElement.appendChild(cellElement);

            // Append the cellContents as a text node
            Element textElement = (Element) doc.createElement(TAG_PARAGRAPH);
            cellElement.appendChild(textElement);
            textElement.appendChild(doc.createTextNode(cellContents));

            Debug.log(Debug.TRACE, cellContents);
            Debug.log(Debug.TRACE, "</td>");

            // Increment to the column number of the next expected cell
            col++;
        }

        // Make sure that the last row is padded correctly
        if (col <= lastColumn && rowElement != null) {
            int numSkippedCells = lastColumn - col + 1;
            addEmptyCells(numSkippedCells, rowElement);
        }

        if (row != 0) {

            // The sheet does have rows, so write out a /tr
            Debug.log(Debug.TRACE, "</tr>");
        }
    }


    /**
     *  This method will add empty rows to the <code>Document</code>.
     *  It is called when the conversion process encounters
     *  a row (or rows) that do not contain any data in its cells.
     *
     *  @param  numEmptyRows   The number of empty rows that we 
     *                         need to add to the <code>Document</code>.
     *  @param  root           The <code>Node</code> of the
     *                         <code>Document</code> we are building
     *                         that we will append our empty row
     *                         <code>Node</code> objects.  This
     *                         <code>Node</code> should be a TAG_TABLE
     *                         tag.
     *  @param  numEmptyCells  The number of empty cells in the
     *                         empty row.
     */
    protected void addEmptyRows(int numEmptyRows, Node root, int numEmptyCells) {

        // Create an element node for the row
        Element rowElement = (Element) doc.createElement(TAG_TABLE_ROW);

        // TODO - style currently hardcoded - get real value
        // Set row style-name attribute
        rowElement.setAttribute(ATTRIBUTE_TABLE_STYLE_NAME, "Default");

        // Set cell number-rows-repeated attribute
        rowElement.setAttribute(ATTRIBUTE_TABLE_NUM_ROWS_REPEATED,
                                Integer.toString(numEmptyRows));

        // Append the row element to the root node
        root.appendChild(rowElement);

        // Open Office requires the empty row to have an empty cell (or cells)
        addEmptyCells(numEmptyCells, rowElement);

        // Write empty rows to the log
        for (int i = 0;  i < numEmptyRows; i++) {
            Debug.log(Debug.TRACE, "<tr />");
        }

    }


    /**
     *  This method will add empty cells to the <code>Document</code>.
     *  It is called when the conversion process encounters a row
     *  that contains some cells without data.
     *
     *  @param   numColsSkipped  The number of empty cells
     *                           that we need to add to the
     *                           current row.
     *  @param   row             The <code>Node</code> of the
     *                           <code>Document</code> we
     *                           are building that we will 
     *                           append our empty cell
     *                           <code>Node</code> objects.
     *                           This <code>Node</code> should
     *                           be a TAG_TABLE_ROW tag.
     */
    protected void addEmptyCells(int numColsSkipped, Node row) {

        // Create an empty cellElement
        Element cellElement = (Element) doc.createElement(TAG_TABLE_CELL);

        // TODO - style currently hardcoded - get real value
        // Set cell style-name attribute
        cellElement.setAttribute(ATTRIBUTE_TABLE_STYLE_NAME, "Default");

        // If we skipped more than 1 cell, we must set the
        // appropriate attribute
        if (numColsSkipped > 1) {

            // Set cell number-columns-repeated attribute
            cellElement.setAttribute(ATTRIBUTE_TABLE_NUM_COLUMNS_REPEATED,
                                     Integer.toString(numColsSkipped));
        }

        // Append the empty cell element to the row node
        row.appendChild(cellElement);

        // Write empty cells to the log
        for (int i = 0;  i < numColsSkipped; i++) {
            Debug.log(Debug.TRACE, "<td />");
        }
    }


    /**
     *  This method process the data in a cell and sets
     *  the appropriate attributes on the cell <code>Element</code>.
     *
     *  @param   cellElement  A TAG_TABLE_CELL <code>Element</code>
     *                        that we will be adding attributes to 
     *                        based on the type of data in the cell.
     *  @param   type         The type of data contained in the cell.
     *  @param   contents     The contents of the data contained in
     *                        the cell.
     */
    protected void processCellData(Element cellElement, String type,
                                 String contents) {

        // Set cell value-type attribute
        cellElement.setAttribute(ATTRIBUTE_TABLE_VALUE_TYPE, type);

        // Does the cell contain a formula?
        if (contents.startsWith("=")) {

            cellElement.setAttribute(ATTRIBUTE_TABLE_FORMULA,
                                     parseFormula(contents));

            // String data does not require any additional attributes
        } else if (!type.equals(CELLTYPE_STRING)) {

            if (type.equals(CELLTYPE_TIME)) {

                // Data returned in StarOffice XML format, so store in
                // attribute
                cellElement.setAttribute(ATTRIBUTE_TABLE_TIME_VALUE,
                                         contents);

            } else if (type.equals(CELLTYPE_DATE)) {

                // Data returned in StarOffice XML format, so store in
                // attribute
                cellElement.setAttribute(ATTRIBUTE_TABLE_DATE_VALUE,
                                         contents);

            } else if (type.equals(CELLTYPE_BOOLEAN)) {

                // StarOffice XML format requires stored boolean value 
                // to be in lower case
                cellElement.setAttribute(ATTRIBUTE_TABLE_BOOLEAN_VALUE,
                                         contents.toLowerCase());

            } else if (type.equals(CELLTYPE_CURRENCY)) {
                // TODO - StarOffice XML format requires a correct style to
                // display currencies correctly.  Need to implement styles.
                // TODO - USD is for US currencies.  Need to pick up
                // the correct currency location from the source file.
                cellElement.setAttribute(ATTRIBUTE_TABLE_CURRENCY, "USD");

                // Data comes stripped of currency symbols
                cellElement.setAttribute(ATTRIBUTE_TABLE_VALUE, contents);

            } else if (type.equals(CELLTYPE_PERCENT)) {
                // Data comes stripped of percent signs
                cellElement.setAttribute(ATTRIBUTE_TABLE_VALUE, contents);

            } else {
                // Remaining data types use table-value attribute

                cellElement.setAttribute(ATTRIBUTE_TABLE_VALUE, contents);
            }
        }
    }


    /**
     *  <p>This method takes a formula and parses it into
     *  StarOffice XML formula format.</p>
     *
     *  <p>Many spreadsheets use ',' as a separator.
     *  StarOffice XML format uses ';' as a separator instead.</p>
     *
     *  <p>Many spreadsheets use '!' as a separator when refencing 
     *  a cell in a different sheet.</p>
     *
     *  <blockquote>
     *  Example: =sheet1!A1
     *  </blockquote>
     *
     *  <p>StarOffice XML format uses '.' as a separator instead.</p>
     *
     *  <blockquote>
     *  Example: =sheet1.A1
     *  </blockquote>
     *
     *  @param  formula  A formula string.
     *
     *  @return  A StarOffice XML format formula string.
     */
    protected String parseFormula(String formula) {

        formula = formula.replace(',', ';');
        formula = formula.replace('!', '.');

        return formula;
    }
}

