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

#include "signal_database.h"

using namespace efis_signals;

SignalDatabase::SignalDatabase()
{
    for (size_t i = 0; i < size(); ++i)
    {
        signal_array[i] = nullptr;
    }

    init_signals();
}

SignalDatabase& SignalDatabase::get_instance()
{
    static SignalDatabase database;
    return database;
}

size_t SignalDatabase::size() const
{
    return SignalID::MAX_SIGNAL_COUNT;
}

bool SignalDatabase::update_packet(DataReader& reader)
{
    SignalTypeBase read_signal(SignalID(0, 0));
    if (reader.bytes_available() >= read_signal.size() && read_signal.deserialize(reader))
    {
        reader.reset();
        SignalTypeBase* signal_to_update = nullptr;

        if (!get_signal(read_signal.get_signal_id(), &signal_to_update))
        {
            return false;
        }
        else if (reader.bytes_available() < signal_to_update->size())
        {
            return false;
        }
        else if (!signal_to_update->can_update_base(read_signal))
        {
            return false;
        }
        else
        {
            return signal_to_update->deserialize(reader);
        }
    }
    else
    {
        return false;
    }
}

bool SignalDatabase::get_signal(
        const SignalID& signal_id,
        SignalTypeBase** signal) const
{
    const size_t signal_index = signal_id.signal_index();
    if (signal_index < size() && signal_array[signal_index] != nullptr)
    {
        *signal = signal_array[signal_index];
        return true;
    }
    else
    {
        return false;
    }
}

bool SignalDatabase::get_fixed_signal(
        const SignalID& signal_id,
        SignalTypeFixed** signal) const
{
    // Obtain the base signal
    SignalTypeBase* base;
    if (!get_signal(signal_id, &base))
    {
        return false;
    }

    // Attempt to convert to a fixed type
    *signal = dynamic_cast<SignalTypeFixed*>(base);
    return *signal != nullptr;
}
