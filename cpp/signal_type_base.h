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

#ifndef SIGNAL_TYPE_BASE_H
#define SIGNAL_TYPE_BASE_H

#include "data_common.h"

#include "signal_id.h"

namespace efis_signals
{

class SignalTypeBase
{
public:
    SignalTypeBase(const SignalID& signal) :
        from_device(0),
        priority(0),
        category_id(signal.category_id),
        signal_id(signal.sub_id),
        timestamp(0)
    {

    }

    virtual bool serialize(DataWriter& writer) const
    {
        return
                writer.add_ubyte(from_device) &&
                writer.add_ubyte(priority) &&
                writer.add_ubyte(category_id) &&
                writer.add_ubyte(signal_id) &&
                writer.add_uint(timestamp);
    }

    virtual bool deserialize(DataReader& reader)
    {
        // Determine if each of the parameters could be read successfully
        const bool success =
                reader.read_ubyte(from_device) &&
                reader.read_ubyte(priority) &&
                reader.read_ubyte(category_id) &&
                reader.read_ubyte(signal_id) &&
                reader.read_uint(timestamp);

        // TODO: Update timestamp here
        return success;
    }

    bool read_base(DataReader& reader)
    {
        return
                reader.read_ubyte(from_device) &&
                reader.read_ubyte(priority) &&
                reader.read_ubyte(category_id) &&
                reader.read_ubyte(signal_id) &&
                reader.read_uint(timestamp);
    }

    bool can_update_base(const SignalTypeBase& other) const
    {
        return
                category_id == other.category_id &&
                signal_id == other.signal_id &&
                (
                    timed_out() ||
                    other.priority > priority ||
                    (other.from_device == from_device && other.timestamp > timestamp));
    }

    SignalID get_signal_id() const
    {
        return SignalID(
                    category_id,
                    signal_id);
    }

    bool timed_out() const
    {
        return false;
    }

    bool is_valid() const
    {
        return false;
    }

    virtual size_t size() const
    {
        return 8;
    }

protected:
    uint8_t from_device;
    uint8_t priority;
    uint8_t category_id;
    uint8_t signal_id;
    uint32_t timestamp;
};

}

#endif // SIGNAL_TYPE_BASE_H
