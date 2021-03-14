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

#include "gen_signal_def.h"

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
    return SignalDef::MAX_SIGNAL_COUNT;
}

bool SignalDatabase::read_data_into_dictionary(DataReader& reader)
{
    SignalBaseParameters base_params;
    if (base_params.read_base(reader))
    {
        SignalTypeBase* signal_to_update = nullptr;
        SignalDef signal_def = SIGNAL_DEF_NULL;

        if (!base_params.get_signal_def(signal_def))
        {
            return false;
        }
        else if (!get_signal(signal_def, &signal_to_update))
        {
            return false;
        }
        else if (reader.bytes_available() < signal_to_update->size())
        {
            return false;
        }
        else if (!signal_to_update->update_base(base_params))
        {
            return false;
        }
        else if (signal_to_update->deserialize(reader))
        {
            signal_to_update->set_updated_time_to_now();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool SignalDatabase::write_data_from_dictionary(
        const SignalDef& signal,
        DataWriter& writer) const
{
    SignalTypeBase* base_signal = nullptr;
    if (!get_signal(signal, &base_signal))
    {
        return false;
    }
    else
    {
        return
                base_signal->get_parameters().write_base(writer) &&
                base_signal->serialize(writer);
    }
}

bool SignalDatabase::get_signal(
        const SignalDef& signal_def,
        SignalTypeBase** signal) const
{
    const size_t signal_index = signal_def.signal_index();
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

bool SignalDatabase::get_scaled_signal(
        const SignalDef& signal_def,
        SignalTypeScaled** signal) const
{
    return get_signal_type(
                signal_def,
                signal);
}
