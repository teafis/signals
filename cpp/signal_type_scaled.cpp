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

#include "signal_type_scaled.h"

using namespace efis_signals;

SignalTypeScaled::SignalTypeScaled(
        const SignalDef& signal,
        const double resolution) :
    SignalTypeBase(signal),
    value(resolution)
{
    // Empty Constructor
}

bool SignalTypeScaled::set_value(const double input)
{
    if (is_transmit())
    {
        value.set_value(input);
        set_updated_time_to_now();
        return true;
    }
    else
    {
        return false;
    }
}

double SignalTypeScaled::get_value() const
{
    return value.get_value();
}

const DataTypeScaled& SignalTypeScaled::get_data_value() const
{
    return value;
}

bool SignalTypeScaled::serialize(DataWriter& writer) const
{
    return
            SignalTypeBase::serialize(writer) &&
            writer.add_uint(value.get_raw_value());
}

bool SignalTypeScaled::deserialize(DataReader& reader)
{
    uint32_t raw_value = 0;
    const bool success =
            SignalTypeBase::deserialize(reader) &&
            reader.read_uint(raw_value);

    if (success)
    {
        value.set_raw_value(raw_value);
        return true;
    }
    else
    {
        return false;
    }
}

size_t SignalTypeScaled::packet_size() const
{
    return SignalTypeBase::packet_size() + 4;
}
