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

#ifndef TF_SIGNALS_READER_H
#define TF_SIGNALS_READER_H

#include <cstddef>
#include <cstdint>

#include "data_type_scaled.h"

namespace efis_signals
{

/**
 * @brief The DataReader class defines the reader for parsing
 * information from a network packet buffer
 */
class DataReader
{
public:
    /**
     * @brief DataReader initializes the NetworkPacketReader with
     * an empty buffer
     */
    DataReader();

    /**
     * @brief read_ubyte reads a single uint8_t from the current buffer
     * @param val stores the byte value if read sucessfully
     * @return true if the byte is read
     */
    bool read_ubyte(uint8_t& val);

    /**
     * @brief read_ushort reads a single uint16_t from the current buffer
     * @param val stores the short if read successfully
     * @return true if the short is successfully read
     */
    bool read_ushort(uint16_t& val);

    /**
     * @brief read_uint reads a single uint32_t from the current buffer
     * @param val stores the int if read successfully
     * @return true if the int is successfully read
     */
    bool read_uint(uint32_t& val);

    /**
     * @brief read_scaled reads a single scaled data from the current buffer
     * @param val stores the scaled data if read successfully
     * @return true if the scaled data is successfully read
     */
    bool read_scaled(DataTypeScaled& val);

    /**
     * @brief bytes_available determines the number of bytes available to read
     * @return the number of bytes available to read in the buffer
     */
    size_t bytes_available() const;

    /**
     * @brief set_buffer sets or resets buffer information
     * @param buffer is the buffer of data to be parsed
     * @param size is the overall size of the buffer
     */
    void set_buffer(
            const uint8_t* const buffer,
            const size_t size);

    /**
     * @brief reset resets the current buffer index to the start of the buffer
     */
    void reset();

private:
    /**
     * @brief buffer defines the buffer to read
     */
    const uint8_t* buffer;

    /**
     * @brief size defines the maximum size of the buffer
     */
    size_t size;

    /**
     * @brief current provides the current index to be read within the buffer
     */
    size_t current;
};

}

#endif // TF_SIGNALS_READER_H
