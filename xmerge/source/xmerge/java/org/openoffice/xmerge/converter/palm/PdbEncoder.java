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

package org.openoffice.xmerge.converter.palm;

import java.io.OutputStream;
import java.io.BufferedOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Date;

/**
 *  <p>Provides functionality to encode a <code>PalmDB</code> object
 *  into a PDB formatted file given a file <code>OutputStream</code>.
 *  This class is only used by the <code>PalmDB</code> object.</p>
 *
 *  <p>One needs to create one <code>PdbEncoder</code> object per
 *  <code>PalmDB</code> object to be encoded.  This class keeps
 *  the PDB header data and functionality in the <code>PdbHeader</code>
 *  class.</p>
 *
 *  <p>Sample usage:</p>
 *
 *  <blockquote><pre><code>
 *     PdbEncoder encoder = new PdbEncoder(palmDB, "STRW", "data");
 *     encoder.write(new FileOutputStream("sample.pdb"));
 *  </code></pre></blockquote>
 *
 *  @author  Herbie Ong
 *  @see     PalmDB
 *  @see     Record
 */
public final class PdbEncoder {

    /**  PDB header. */
    private PdbHeader header = null;

    /**  the PalmDB object. */
    private PalmDB db = null;

    /**
     *  The pattern for unique_id=0x00BABE(start).
     */
    private final static int START_UNIQUE_ID = 0x00BABE;


    /**
     *  Constructor.
     *
     *  @param   db       The <code>PalmDB</code> to be encoded.
     */
    public PdbEncoder(PalmDB db) {

        header = new PdbHeader();
    header.version = db.getVersion();

        header.attribute = db.getAttribute();

        this.db = db;

        header.pdbName = db.getPDBNameBytes();
        header.creatorID = db.getCreatorID();
        header.typeID = db.getTypeID();

        // set the following dates to current date
        Date date = new Date();
        header.creationDate = (date.getTime() / 1000) + PdbUtil.TIME_DIFF;
        header.modificationDate = header.creationDate;

        header.numRecords = db.getRecordCount();
    }


    /**
     *  <p>Write out a PDB into the given <code>OutputStream</code>.</p>
     *
     *  <p>First, write out the header data by using the
     *  <code>PdbHeader</code> <code>write</code> method. Next,
     *  calculate the RecordList section and write it out.
     *  Lastly, write out the bytes corresponding to each
     *  <code>Record</code>.</p>
     *
     *  <p>The RecordList section contains a list of
     *  <code>Record</code> index info, where each <code>Record</code>
     *  index info contains:</p>
     *
     *  <p><ul>
     *  <li>4 bytes local offset of the <code>Record</code> from the
     *      top of the PDB.</li>
     *  <li>1 byte of <code>Record</code> attribute.</li>
     *  <li>3 bytes unique <code>Record</code> ID.</li>
     *  </ul></p>
     *
     *  <p>There should be a total of <code>header.numRecords</code>
     *  of <code>Record</code> index info</p>.
     *
     *  @param  os  <code>OutputStream</code> to write out PDB. 
     *
     *  @throws  IOException  If I/O error occurs.
     */
    public void write(OutputStream os) throws IOException {

        BufferedOutputStream bos = new BufferedOutputStream(os);
        DataOutputStream dos = new DataOutputStream(bos);

        // write out the PDB header
        header.write(dos);

        if (header.numRecords > 0) {

            // compute for recOffset[]

            int recOffset[] = new int[header.numRecords];
            byte recAttr[] = new byte[header.numRecords];

            // first recOffset will be at PdbUtil.HEADER_SIZE + all the
            // record indices (@ 8 bytes each)
            recOffset[0] = PdbUtil.HEADER_SIZE + (header.numRecords * 8);

            int lastIndex = header.numRecords - 1;

            for (int i = 0; i < lastIndex; i++) {

                Record rec = db.getRecord(i);
                int size = rec.getSize();
                recAttr[i] = rec.getAttributes();

                recOffset[i+1] = recOffset[i] + size;
            }

            // grab the last record's attribute.

            Record lastRec = db.getRecord(lastIndex);
            recAttr[lastIndex] = lastRec.getAttributes();


            int uid = START_UNIQUE_ID;

            for (int i = 0; i < header.numRecords; i++) {

                // write out each record offset
                dos.writeInt(recOffset[i]);

                // write out record attribute (recAttr) and
                // unique ID (uid) in 4 bytes (int) chunk.
                // unique ID's have to be unique, thus
                // increment each time.
                int attr = (((int) recAttr[i]) << 24 );
                attr |= uid;
                dos.writeInt(attr);
                uid++;
            }

            // write out the raw records

            for (int i = 0; i < header.numRecords; i++) {

                Record rec = db.getRecord(i);
                byte bytes[] = rec.getBytes();
                dos.write(bytes);
            }

        } else {

            // placeholder bytes if there are no records in the list.
            dos.writeShort(0);
        }

        dos.flush();
    }
}

