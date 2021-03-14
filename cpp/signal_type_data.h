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

#ifndef TF_SIGNAL_TYPE_DATA_H
#define TF_SIGNAL_TYPE_DATA_H

#include "signal_type_base.h"

namespace efis_signals
{

// TODO - Replace with VarArray?

// TODO - Documentation
// TODO - Split into CPP file

class SignalTypeData : public SignalTypeBase
{
public:
    using data_size_t = uint32_t;
    using data_t = uint8_t;

    SignalTypeData(
            const SignalDef& signal,
            const data_size_t size) :
        SignalTypeBase(signal),
        data_size(size),
        data(nullptr)
    {
        // Define the data array
        data = new data_t[data_size];
        for (data_size_t i = 0; i < data_size; ++i)
        {
            data[i] = 0;
        }
    }

    SignalTypeData(const SignalTypeData& other) :
        SignalTypeBase(other),
        data_size(other.data_size),
        data(nullptr)

    {
        // Define the data array
        data = new data_t[data_size];
        for (data_size_t i = 0; i < data_size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    SignalTypeData& operator=(const SignalTypeData& other)
    {
        // Check for self-assignment
        if (this == &other)
        {
            return *this;
        }

        // Allocate new data size if required
        if (data_size != other.data_size)
        {
            data_size = other.data_size;

            if (data != nullptr)
            {
                delete[] data;
            }

            data = new data_t[data_size];
        }

        // Copy data values
        for (data_size_t i = 0; i < data_size; ++i)
        {
            data[i] = other.data[i];
        }

        // Return the provided pointer
        return *this;
    }

    bool set_value(const data_size_t index, const data_t value)
    {
        if (is_transmit() && index < data_size)
        {
            data[index] = value;
            set_updated_time_to_now();
            return true;
        }
        else
        {
            return false;
        }
    }

    bool get_value(const data_size_t index, data_t& value) const
    {
        if (index < data_size)
        {
            value = data[index];
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual bool serialize(DataWriter& writer) const override
    {
        bool success =
                SignalTypeBase::serialize(writer) &&
                writer.add_uint(data_size);

        for (data_size_t i = 0; i < data_size; ++i)
        {
            success &= writer.add_ubyte(data[i]);
        }

        return success;
    }

    virtual bool deserialize(DataReader& reader) override
    {
        data_size_t new_size;
        bool success =
                SignalTypeBase::deserialize(reader) &&
                reader.read_uint(new_size);

        if (success && new_size == data_size)
        {
            for (data_size_t i = 0; i < data_size; ++i)
            {
                success &= reader.read_ubyte(data[i]);
            }

            return success;
        }
        else
        {
            return false;
        }
    }

    virtual size_t size() const override
    {
        return SignalTypeBase::size() + 4 + data_size;
    }

    virtual ~SignalTypeData()
    {
        if (data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }

protected:
    data_size_t data_size;
    data_t* data;
};

}

#endif // TF_SIGNAL_TYPE_DATA_H
