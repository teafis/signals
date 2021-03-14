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

#ifndef TF_SIGNAL_TYPE_BASE_H
#define TF_SIGNAL_TYPE_BASE_H

#include "data_reader.h"
#include "data_writer.h"

#include "signal_def.h"
#include "gen_signal_def.h"

#include "signal_time.h"

#include "signal_base_parameters.h"

#include <chrono>

namespace efis_signals
{

enum class SignalSourceType
{
    None = 0,
    Transmitted = 1,
    Received = 2
};

class SignalTypeBase
{
public:
    SignalTypeBase(const SignalDef& signal) :
        signal_def(signal),
        source_type(SignalSourceType::Received),
        updated_time(0)
    {
        // Set Base Parameters
        parameters.cat_id = signal_def.category_id;
        parameters.sub_id = signal_def.sub_id;
    }

    virtual bool serialize(DataWriter&) const
    {
        return is_transmit();
    }

    virtual bool deserialize(DataReader&)
    {
        return is_receive();
    }

    bool update_base(const SignalBaseParameters& other)
    {
        // Ensure that the ID of the signal matches
        const bool id_matches =
                other.cat_id == parameters.cat_id &&
                other.sub_id == parameters.sub_id;

        // Allow replacement if the new priority is higher than the existing priority
        const bool replace_higher_priority = other.priority > parameters.priority;

        // Allow replacement if the parameter is from the same device and the timestamp has increased
        const bool replace_higher_timestamp =
                other.from_device == parameters.from_device &&
                other.timestamp >= parameters.timestamp;

        // Allow replacement if any of the priority, timestamp is okay, or the current signal
        // is not valid
        const bool can_replace =
                !is_valid() ||
                replace_higher_priority ||
                replace_higher_timestamp;

        // Check if we can update the base parameters
        if (is_receive() && id_matches && can_replace)
        {
            parameters.from_device = other.from_device;
            parameters.priority = other.priority;
            parameters.timestamp = other.timestamp;
            set_updated_time_to_now();
            return true;
        }
        else
        {
            return false;
        }
    }

    const SignalDef& get_signal_def() const
    {
        return signal_def;
    }

    bool is_valid() const
    {
        // TODO - Document

        return
            (parameters.priority & 0x80) > 0 &&
            (get_millis() - updated_time) <= signal_def.timeout_millis;
    }

    virtual size_t size() const
    {
        return 0;
    }

    void set_updated_time_to_now()
    {
        updated_time = get_millis();
        if (is_transmit())
        {
            parameters.timestamp = get_millis();
        }
    }

    void set_source_type(const SignalSourceType type)
    {
        source_type = type;
    }

    bool set_priority(const uint8_t priority)
    {
        if (is_transmit())
        {
            parameters.priority = priority;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool set_from_device(const uint8_t from_device)
    {
        if (is_transmit())
        {
            parameters.from_device = from_device;
            return true;
        }
        else
        {
            return false;
        }
    }

    const SignalBaseParameters& get_parameters() const
    {
        return parameters;
    }

protected:
    bool is_receive() const
    {
        return source_type == SignalSourceType::Received;
    }

    bool is_transmit() const
    {
        return source_type == SignalSourceType::Transmitted;
    }

protected:
    SignalDef signal_def;

    SignalBaseParameters parameters;

    SignalSourceType source_type;

private:
    efis_signals::timestamp_t updated_time;
};

}

#endif // TF_SIGNAL_TYPE_BASE_H
