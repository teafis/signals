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

#ifndef SIGNAL_FIXED_H
#define SIGNAL_FIXED_H

#include "signal_base.h"

#include <cstdint>
#include <limits>

namespace efis_signals
{

class SignalFixed : public BaseSignal
{
public:
    SignalFixed(const SignalID& signal, const double resolution) :
        BaseSignal(signal),
        resolution(resolution),
        value(0.0)
    {

    }

    void set_value(const double input)
    {
        if (input > max_value())
        {
            value = max_value();
        }
        else if (input < min_value())
        {
            value = min_value();
        }
        else
        {
            value = input;
        }
    }

    double get_value() const
    {
        return value;
    }

    double max_value() const
    {
        return std::numeric_limits<int32_t>::max() * resolution;
    }

    double min_value() const
    {
        return std::numeric_limits<int32_t>::min() * resolution;
    }

    virtual bool serialize(DataWriter& writer) const override
    {
        return
                BaseSignal::serialize(writer) &&
                writer.add_uint(get_data_value());
    }

    virtual bool deserialize(DataReader& reader) override
    {
        uint32_t raw_value = 0;
        const bool success =
                BaseSignal::deserialize(reader) &&
                reader.read_uint(raw_value);

        if (success)
        {
            from_raw_value(raw_value);
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual size_t packet_size() const override
    {
        return BaseSignal::packet_size() + 4;
    }

protected:
    void from_raw_value(const uint32_t raw)
    {
        value = static_cast<double>(static_cast<int32_t>(raw)) * resolution;
    }

    uint32_t get_data_value() const
    {
        return static_cast<uint32_t>(static_cast<int32_t>(value / resolution));
    }

protected:
    double resolution;
    double value;
};

}

#endif // SIGNAL_FIXED_H
