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

#include <chrono>

namespace efis_signals
{

enum class SignalSourceType
{
    None = 0,
    Transmitted = 1,
    Received = 2
};

struct SignalBaseParameters
{
    uint8_t cat_id;
    uint8_t sub_id;
    uint8_t priority;
    uint8_t from_device;
    uint32_t timestamp;

    SignalBaseParameters() :
        cat_id(0),
        sub_id(0),
        priority(0),
        from_device(0),
        timestamp(0)
    {
        // Empty Constructor
    }

    bool write_base(DataWriter& writer) const
    {
        return
                writer.add_ubyte(from_device) &&
                writer.add_ubyte(priority) &&
                writer.add_ubyte(cat_id) &&
                writer.add_ubyte(sub_id) &&
                writer.add_ubyte(timestamp);
    }

    bool read_base(DataReader& reader)
    {
        return
                reader.read_ubyte(from_device) &&
                reader.read_ubyte(priority) &&
                reader.read_ubyte(cat_id) &&
                reader.read_ubyte(sub_id) &&
                reader.read_uint(timestamp);
    }

    bool get_signal_def(SignalDef& signal_def)
    {
        return get_signal_for_cat_sub_id(
                    cat_id,
                    sub_id,
                    signal_def);
    }
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

    bool can_update_base(const SignalBaseParameters& other) const
    {
        return
                is_receive() &&
                other.cat_id == parameters.cat_id &&
                other.sub_id == parameters.sub_id &&
                (
                    !is_valid() ||
                    other.priority > parameters.priority ||
                    (other.from_device == parameters.from_device && other.timestamp >= parameters.timestamp));
    }

    bool update_base(const SignalBaseParameters& other)
    {
        if (is_receive())
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
