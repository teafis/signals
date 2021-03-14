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

#include "signal_type_data.h"

using namespace efis_signals;

SignalTypeData::SignalTypeData(
        const SignalDef& signal,
        const data_size_t size) :
    SignalTypeBase(signal),
    data_array_size(size),
    data_array(nullptr)
{
    // Define the data array
    data_array = new data_t[data_array_size];
    for (data_size_t i = 0; i < data_array_size; ++i)
    {
        data_array[i] = 0;
    }
}

SignalTypeData::SignalTypeData(const SignalTypeData& other) :
    SignalTypeBase(other),
    data_array_size(other.data_array_size),
    data_array(nullptr)

{
    // Define the data array
    data_array = new data_t[data_array_size];
    for (data_size_t i = 0; i < data_array_size; ++i)
    {
        data_array[i] = other.data_array[i];
    }
}

SignalTypeData& SignalTypeData::operator=(const SignalTypeData& other)
{
    // Check for self-assignment
    if (this == &other)
    {
        return *this;
    }

    // Allocate new data size if required
    if (data_array_size != other.data_array_size)
    {
        data_array_size = other.data_array_size;

        if (data_array != nullptr)
        {
            delete[] data_array;
        }

        data_array = new data_t[data_array_size];
    }

    // Copy data values
    for (data_size_t i = 0; i < data_array_size; ++i)
    {
        data_array[i] = other.data_array[i];
    }

    // Return the provided pointer
    return *this;
}

bool SignalTypeData::set_value(
        const data_size_t index,
        const data_t value)
{
    if (is_transmit() && index < data_array_size)
    {
        data_array[index] = value;
        set_updated_time_to_now();
        return true;
    }
    else
    {
        return false;
    }
}

bool SignalTypeData::get_value(
        const data_size_t index,
        data_t& value) const
{
    if (index < data_array_size)
    {
        value = data_array[index];
        return true;
    }
    else
    {
        return false;
    }
}

SignalTypeData::data_size_t SignalTypeData::data_size() const
{
    return data_array_size;
}

bool SignalTypeData::serialize(DataWriter& writer) const
{
    bool success =
            SignalTypeBase::serialize(writer) &&
            writer.add_uint(data_array_size);

    for (data_size_t i = 0; i < data_array_size; ++i)
    {
        success &= writer.add_ubyte(data_array[i]);
    }

    return success;
}

bool SignalTypeData::deserialize(DataReader& reader)
{
    data_size_t new_size;
    bool success =
            SignalTypeBase::deserialize(reader) &&
            reader.read_uint(new_size);

    if (success && new_size == data_array_size)
    {
        for (data_size_t i = 0; i < data_array_size; ++i)
        {
            success &= reader.read_ubyte(data_array[i]);
        }

        return success;
    }
    else
    {
        return false;
    }
}

size_t SignalTypeData::packet_size() const
{
    return SignalTypeBase::packet_size() + 4 + data_array_size;
}

SignalTypeData::~SignalTypeData()
{
    if (data_array != nullptr)
    {
        delete[] data_array;
        data_array = nullptr;
    }
}
