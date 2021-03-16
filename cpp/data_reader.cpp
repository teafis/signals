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

#include "data_reader.h"

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#else
#include <arpa/inet.h>
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
    uint8_t vals[2] = {};

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
    uint8_t vals[4] = {};

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

bool DataReader::read_scaled(DataTypeScaled& val)
{
    uint32_t temp;
    bool success = read_uint(temp);

    if (success)
    {
        val.set_raw_value(temp);
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

}
