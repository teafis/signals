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

#include "signal_type_base.h"

using namespace efis_signals;

SignalTypeBase::SignalTypeBase(const SignalDef& signal) :
    source_type(SignalSourceType::Received),
    updated_time(0)
{
    // Set Base Parameters
    header.cat_id = signal.category_id;
    header.sub_id = signal.sub_id;
}

bool SignalTypeBase::serialize(DataWriter&) const
{
    return is_transmit();
}

bool SignalTypeBase::deserialize(DataReader&)
{
    return is_receive();
}

bool SignalTypeBase::update_header(const SignalHeader& other)
{
    // Ensure that the ID of the signal matches
    const bool id_matches =
            other.cat_id == header.cat_id &&
            other.sub_id == header.sub_id;

    // Allow replacement if the new priority is higher than the existing priority
    const bool replace_higher_priority = other.priority > header.priority;

    // Allow replacement if the parameter is from the same device and the timestamp has increased
    const bool replace_higher_timestamp =
            other.from_device == header.from_device &&
            other.timestamp >= header.timestamp;

    // Allow replacement if any of the priority, timestamp is okay, or the current signal
    // is not valid
    const bool can_replace =
            !is_valid() ||
            replace_higher_priority ||
            replace_higher_timestamp;

    // Check if we can update the base parameters
    if (is_receive() && id_matches && can_replace)
    {
        header.from_device = other.from_device;
        header.priority = other.priority;
        header.timestamp = other.timestamp;
        set_updated_time_to_now();
        return true;
    }
    else
    {
        return false;
    }
}

bool SignalTypeBase::is_valid() const
{
    const bool priority_valid = (header.priority & 0x80) > 0;
    const bool timeout_valid = get_millis() - updated_time <= header.get_signal_def().timeout_millis;

    return priority_valid && timeout_valid;
}

size_t SignalTypeBase::packet_size() const
{
    return 0;
}

void SignalTypeBase::set_updated_time_to_now()
{
    const efis_signals::timestamp_t millis = get_millis();
    updated_time = millis;
    if (is_transmit())
    {
        header.timestamp = millis;
    }
}

void SignalTypeBase::set_source_type(const SignalSourceType type)
{
    source_type = type;
}

bool SignalTypeBase::set_priority(const uint8_t priority)
{
    if (is_transmit())
    {
        header.priority = priority;
        return true;
    }
    else
    {
        return false;
    }
}

bool SignalTypeBase::set_from_device(const uint8_t from_device)
{
    if (is_transmit())
    {
        header.from_device = from_device;
        return true;
    }
    else
    {
        return false;
    }
}

const SignalHeader& SignalTypeBase::get_header() const
{
    return header;
}

bool SignalTypeBase::is_receive() const
{
    return source_type == SignalSourceType::Received;
}

bool SignalTypeBase::is_transmit() const
{
    return source_type == SignalSourceType::Transmitted;
}
