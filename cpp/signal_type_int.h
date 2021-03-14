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

#ifndef TF_SIGNAL_TYPE_INT_H
#define TF_SIGNAL_TYPE_INT_H

#include "signal_type_base.h"

#include "data_type_scaled.h"

// TODO - Documentation
// TODO - Split into CPP file

namespace efis_signals
{

class SignalTypeInteger : public SignalTypeBase
{
public:
    SignalTypeInteger(const SignalDef& signal) :
        SignalTypeBase(signal)
    {
        // Empty Constructor
    }

    bool set_value(const uint32_t input)
    {
        if (is_transmit())
        {
            value = input;
            set_updated_time_to_now();
            return true;
        }
        else
        {
            return false;
        }
    }

    uint32_t get_value() const
    {
        return value;
    }

    virtual bool serialize(DataWriter& writer) const override
    {
        return
                SignalTypeBase::serialize(writer) &&
                writer.add_uint(value);
    }

    virtual bool deserialize(DataReader& reader) override
    {
        return
                SignalTypeBase::deserialize(reader) &&
                reader.read_uint(value);
    }

    virtual size_t size() const override
    {
        return SignalTypeBase::size() + 4;
    }

protected:
    uint32_t value;
};

}

#endif // TF_SIGNAL_TYPE_INT_H
