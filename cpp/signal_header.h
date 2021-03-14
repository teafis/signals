// TeaFIS is a cockpit display for aircraft
// Copyright (C) 2021  Ian O'Rourke
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#ifndef TF_SIGNAL_HEADER_H
#define TF_SIGNAL_HEADER_H

#include <cstdint>

#include "data_writer.h"
#include "data_reader.h"

#include "signal_def.h"

namespace efis_signals
{

/**
 * @brief The SignalHeader struct defines common base-type signal
 * values across all signal types and provides the basic header
 * for signal types
 */
struct SignalHeader
{
    /**
     * @brief cat_id provides the category ID for the signal
     */
    uint8_t cat_id;

    /**
     * @brief sub_id provides the subcategory ID for the signal
     */
    uint8_t sub_id;

    /**
     * @brief priority provides the priority for the signal
     */
    uint8_t priority;

    /**
     * @brief from_device provides the sending device
     */
    uint8_t from_device;

    /**
     * @brief timestamp provides the sending timestamp
     */
    uint32_t timestamp;

    /**
     * @brief SignalHeader constructs an empty/invalid signal header
     */
    SignalHeader();

    /**
     * @brief write_header writes header parameters to the data writer
     * @param writer is the data writer to write data into
     * @return true if the header is written successfully
     */
    bool write_header(DataWriter& writer) const;

    /**
     * @brief read_header reads header parameters from a data reader
     * @param reader is the data reader to use in reading data
     * @return true if the header data is successfully read from
     */
    bool read_header(DataReader& reader);

    /**
     * @brief get_signal_def attempts to obtain the signal definition
     * @return the signal_def for the header, or the NULL signal if none is found
     */
    SignalDef get_signal_def() const;

    /**
     * @brief get_signal_def_check provides a checked signal definition instance
     * @param signal_def returns the signal definition
     * @return true if the signal definition is found
     */
    bool get_signal_def_check(SignalDef& signal_def) const;

    /**
     * @brief has_valid_def determines if the header has a valid signal definition
     * @return true if a signal definition exists for the current header parameters
     */
    bool has_valid_def() const;
};

}

#endif // TF_SIGNAL_HEADER_H
