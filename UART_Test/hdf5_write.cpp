/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the COPYING file, which can be found at the root of the source code       *
 * distribution tree, or in https://www.hdfgroup.org/licenses.               *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 *  This example writes a dataset to a new HDF5 file.
 */

#include <iostream>

#include <string>
#include "H5Cpp.h"
#include "hdf5_write.hpp"

using namespace H5;

const H5std_string FILE_NAME("SDS.h5");
const H5std_string DATASET_NAME("uint16_tArray");
const int          RANK = 1;
const int          DATA_SIZE = 6;

int hdf5_write(uint16_t data[DATA_SIZE])
{
    /*
     * Data initialization.
     */
    int i;

    // Try block to detect exceptions raised by any of the calls inside it
    try {
        /*
         * Turn off the auto-printing when failure occurs so that we can
         * handle the errors appropriately
         */
        Exception::dontPrint();

        /*
         * Create a new file using H5F_ACC_TRUNC access,
         * default file creation properties, and default file
         * access properties.
         */
        H5File file(FILE_NAME, H5F_ACC_TRUNC);

        /*
         * Define the size of the array and create the data space for fixed
         * size dataset.
         */
        hsize_t dimsf[1]; // dataset dimensions
        dimsf[0] = DATA_SIZE;
        DataSpace dataspace(RANK, dimsf);

        /*
         * Define datatype for the data in the file.
         * We will store little endian INT numbers.
         */
        IntType datatype(PredType::NATIVE_UINT16);
        datatype.setOrder(H5T_ORDER_LE);

        /*
         * Create a new dataset within the file using defined dataspace and
         * datatype and default dataset creation properties.
         */
        DataSet dataset = file.createDataSet(DATASET_NAME, datatype, dataspace);

        /*
         * Write the data to the dataset using default memory space, file
         * space, and transfer properties.
         */
        dataset.write(data, PredType::NATIVE_UINT16);
    } // end of try block

    // catch failure caused by the H5File operations
    catch (FileIException error) {
        error.printErrorStack();
        return -1;
    }

    // catch failure caused by the DataSet operations
    catch (DataSetIException error) {
        error.printErrorStack();
        return -1;
    }

    // catch failure caused by the DataSpace operations
    catch (DataSpaceIException error) {
        error.printErrorStack();
        return -1;
    }

    // catch failure caused by the DataSpace operations
    catch (DataTypeIException error) {
        error.printErrorStack();
        return -1;
    }

    return 0; // successfully terminated
}
