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

#include "data_common.h"

#ifdef __linux__
#include <arpa/inet.h>
#elif WIN32
#include <winsock2.h>
#endif

namespace efis_signals
{

DataReader::DataReader() :
    buffer(nullptr),
    size(0),
    current(0)
{
    // Empty Constructor
}

bool DataReader::read_ubyte(uint8_t& val)
{
    if (bytes_available() >= 1)
    {
        val = buffer[current];
        current += 1;
        return true;
    }
    else
    {
        return false;
    }
}

bool DataReader::read_ushort(uint16_t& val)
{
    uint8_t vals[2];

    if (read_ubyte(vals[0]) && read_ubyte(vals[1]))
    {
        const uint16_t* ptr = reinterpret_cast<uint16_t*>(vals);
        val = ntohs(*ptr);
        return true;
    }
    else
    {
        return false;
    }
}

bool DataReader::read_uint(uint32_t& val)
{
    uint8_t vals[4];

    if (read_ubyte(vals[0]) &&
            read_ubyte(vals[1]) &&
            read_ubyte(vals[2]) &&
            read_ubyte(vals[3]))
    {
        const uint32_t* ptr = reinterpret_cast<uint32_t*>(vals);
        val = ntohl(*ptr);
        return true;
    }
    else
    {
        return false;
    }
}

size_t DataReader::bytes_available() const
{
    return size - current;
}

void DataReader::set_buffer(
        const uint8_t* const buffer,
        const size_t size)
{
    this->buffer = buffer;
    this->size = size;
    reset();
}

void DataReader::reset()
{
    current = 0;
}

DataWriter::DataWriter() :
    current(0),
    size(0),
    buffer(nullptr)
{
    // Empty Constructor
}

bool DataWriter::add_ubyte(const uint8_t val)
{
    if (current < size && buffer != nullptr)
    {
        buffer[current] = val;
        current += 1;
        return true;
    }
    else
    {
        return false;
    }
}

bool DataWriter::add_ushort(const uint16_t val)
{
    const uint16_t network = htons(val);
    const uint8_t* buffer = reinterpret_cast<const uint8_t*>(&network);
    return
        add_ubyte(buffer[0]) &&
        add_ubyte(buffer[1]);
}

bool DataWriter::add_uint(const uint32_t val)
{
    const uint32_t network = htonl(val);
    const uint8_t* buffer = reinterpret_cast<const uint8_t*>(&network);
    return
        add_ubyte(buffer[0]) &&
        add_ubyte(buffer[1]) &&
        add_ubyte(buffer[2]) &&
        add_ubyte(buffer[3]);
}

void DataWriter::reset()
{
    current = 0;
}

size_t DataWriter::bytes_available() const
{
    if (current < size)
    {
        return size - current;
    }
    else
    {
        return 0;
    }
}

void DataWriter::set_buffer(
        uint8_t *const buffer,
        const size_t size)
{
    this->buffer = buffer;
    this->size = size;
    reset();
}

const uint8_t* DataWriter::get_buffer() const
{
    return buffer;
}

}
