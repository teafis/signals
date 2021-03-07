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

#ifndef SIGNAL_BASE_H
#define SIGNAL_BASE_H

#include "data_common.h"

#include "signal_id.h"

namespace efis_signals
{

class BaseSignal
{
public:
    BaseSignal(const SignalID& signal) :
        from_device(0),
        priority(0),
        category_id(signal.category_id),
        signal_id(signal.signal_id),
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
        // Create a temporary variables to use in determining deserialization
        // parameters and ability
        uint8_t pkt_from_device;
        uint8_t pkt_priority;
        uint8_t pkt_category_id;
        uint8_t pkt_signal_id;
        uint32_t pkt_timestamp;

        // Determine if each of the parameters could be read successfully
        const bool success =
                reader.read_ubyte(pkt_from_device) &&
                reader.read_ubyte(pkt_priority) &&
                reader.read_ubyte(pkt_category_id) &&
                reader.read_ubyte(pkt_signal_id) &&
                reader.read_uint(pkt_timestamp);

        // Fail if parameters did not read correctly
        if (!success)
        {
            return false;
        }
        // Fail if either the category or signal ID do not match the expected
        else if (pkt_category_id != category_id || pkt_signal_id != signal_id)
        {
            return false;
        }
        // If we are timed out, then we can update the parameters to accept a new packet
        else if (timed_out())
        {
            from_device = pkt_from_device;
            priority = pkt_priority;
            timestamp = pkt_timestamp;
            return true;
        }
        // Check if the priority is greater than the current priority
        else if (pkt_priority > priority)
        {
            return true;
        }
        // If the packet originates from the same device, check the timestamps
        else if (pkt_from_device == from_device)
        {
            return pkt_timestamp >= timestamp;
        }
        // Otherwise return false;
        else
        {
            return false;
        }
    }

    bool timed_out() const
    {
        return false;
    }

    virtual size_t packet_size() const
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

#endif // SIGNAL_BASE_H
