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

#include "signal_type_int.h"

using namespace efis_signals;

SignalTypeInteger::SignalTypeInteger(const SignalDef& signal) :
    SignalTypeBase(signal)
{
    // Empty Constructor
}

bool SignalTypeInteger::set_value(const uint32_t input)
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

uint32_t SignalTypeInteger::get_value() const
{
    return value;
}

bool SignalTypeInteger::serialize(DataWriter& writer) const
{
    return
            SignalTypeBase::serialize(writer) &&
            writer.add_uint(value);
}

bool SignalTypeInteger::deserialize(DataReader& reader)
{
    return
            SignalTypeBase::deserialize(reader) &&
            reader.read_uint(value);
}

size_t SignalTypeInteger::packet_size() const
{
    return SignalTypeBase::packet_size() + 4;
}
