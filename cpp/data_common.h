// TeaFIS is a cockpit display for aircraft
// Copyright (C) 2020  Ian O'Rourke
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

#ifndef EFIS_SIGNALS_COMMON_H
#define EFIS_SIGNALS_COMMON_H

#include <cstdint>

namespace efis_signals
{

/**
 * @brief The NetworkPacketReader class defines the reader for parsing
 * information from a network packet buffer
 */
class DataReader
{
public:
    /**
     * @brief NetworkPacketReader initializes the NetworkPacketReader with
     * an empty buffer
     */
    DataReader();

    /**
     * @brief read_byte reads a single uint8_t from the current buffer
     * @param val stores the byte value if read sucessfully
     * @return true if the byte is read
     */
    bool read_ubyte(uint8_t& val);

    /**
     * @brief read_short reads a single uint16_t from the current buffer
     * @param val stores the short if read successfully
     * @return true if the short is successfully read
     */
    bool read_ushort(uint16_t& val);

    /**
     * @brief read_int reads a single uint32_t from the current buffer
     * @param val stores the int if read successfully
     * @return true if the short is successfully read
     */
    bool read_uint(uint32_t& val);

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

/**
 * @brief The NetworkPacketCreator class defines a utility to be used in
 * creating a packet within a buffer
 */
class DataWriter
{
public:
    /**
     * @brief NetworkPacketCreator creates an empty data writer
     */
    DataWriter();

    /**
     * @brief add_byte adds a byte to the buffer
     * @param val is the byte to add
     * @return true if the byte was able to be successfully added
     */
    bool add_ubyte(const uint8_t val);

    /**
     * @brief add_short adds a short to the buffer
     * @param val is the short to add
     * @return true if the short was able to be successfully added
     */
    bool add_ushort(const uint16_t val);

    /**
     * @brief add_short adds an int to the buffer
     * @param val is the int to add
     * @return true if the int was able to be successfully added
     */
    bool add_uint(const uint32_t val);

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

#endif
