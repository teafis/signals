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

#ifndef TF_SIGNALS_DATA_WRITER_H
#define TF_SIGNALS_DATA_WRITER_H

#include <cstddef>
#include <cstdint>

#include "data_type_scaled.h"

namespace efis_signals
{

/**
 * @brief The DataWriter class defines a utility to be used in
 * creating a packet within a buffer
 */
class DataWriter
{
public:
    /**
     * @brief DataWriter creates an empty data writer
     */
    DataWriter();

    /**
     * @brief add_ubyte adds a byte to the buffer
     * @param val is the byte to add
     * @return true if the byte was able to be successfully added
     */
    bool add_ubyte(const uint8_t val);

    /**
     * @brief add_ushort adds a short to the buffer
     * @param val is the short to add
     * @return true if the short was able to be successfully added
     */
    bool add_ushort(const uint16_t val);

    /**
     * @brief add_uint adds an int to the buffer
     * @param val is the int to add
     * @return true if the int was able to be successfully added
     */
    bool add_uint(const uint32_t val);

    /**
     * @brief add_scaled adds a scaled data to the buffer
     * @param val is the scaled data to add
     * @return true if the scaled was able to be successfully added
     */
    bool add_scaled(const DataTypeScaled& val);

    /**
     * @brief reset resets the current buffer pointer index to the start of the buffer
     */
    void reset();

    /**
     * @brief bytes_available determines the number of bytes available
     * @return the number of free bytes available that can be written to in the buffer
     */
    size_t bytes_available() const;

    /**
     * @brief set_buffer sets or resets buffer information
     * @param buffer is the buffer where data can be written
     * @param size is the overall size of the buffer
     */
    void set_buffer(
            uint8_t* const buffer,
            const size_t size);

    /**
     * @brief get_buffer provides the current buffer pointer
     * @return the current buffer pointer
     */
    const uint8_t* get_buffer() const;

protected:
    /**
     * @brief current is the current index that will be written to on the next
     * write. For example, if the current is zero, add_ubyte() will write
     * data to index zero and then increment current
     */
    size_t current;

    /**
     * @brief size is the maximum size of the buffer
     */
    size_t size;

    /**
     * @brief buffer is the buffer of data to be used
     */
    uint8_t* buffer;
};

}

#endif // DATA_WRITER_H
