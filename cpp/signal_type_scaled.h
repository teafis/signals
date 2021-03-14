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

#ifndef SIGNAL_TYPE_FIXED_H
#define SIGNAL_TYPE_FIXED_H

#include "signal_type_base.h"

#include "data_type_scaled.h"

// TODO - Documentation
// TODO - Split into CPP file

namespace efis_signals
{

class SignalTypeScaled : public SignalTypeBase
{
public:
    SignalTypeScaled(const SignalDef& signal, const double resolution) :
        SignalTypeBase(signal),
        data(resolution)
    {
        // Empty Constructor
    }

    bool set_value(const double input)
    {
        if (is_transmit())
        {
            data.set_value(input);
            set_updated_time_to_now();
            return true;
        }
        else
        {
            return false;
        }
    }

    double get_value() const
    {
        return data.get_value();
    }

    const DataTypeScaled& get_data_value() const
    {
        return data;
    }

    virtual bool serialize(DataWriter& writer) const override
    {
        return
                SignalTypeBase::serialize(writer) &&
                writer.add_uint(data.get_raw_value());
    }

    virtual bool deserialize(DataReader& reader) override
    {
        uint32_t raw_value = 0;
        const bool success =
                SignalTypeBase::deserialize(reader) &&
                reader.read_uint(raw_value);

        if (success)
        {
            data.set_raw_value(raw_value);
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual size_t size() const override
    {
        return SignalTypeBase::size() + 4;
    }

protected:
    DataTypeScaled data;
};

}

#endif // SIGNAL_TYPE_FIXED_H
