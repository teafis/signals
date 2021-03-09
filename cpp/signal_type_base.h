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

#include "data_common.h"

#include "signal_def.h"

#include <chrono>

namespace efis_signals
{

class SignalTypeBase
{
public:
    SignalTypeBase(const SignalDef& signal) :
        signal_def(signal),
        from_device(0),
        priority(0),
        timestamp(0)
    {
        start_time = std::chrono::high_resolution_clock::now();
        updated_time = std::chrono::high_resolution_clock::time_point::min();
    }

    virtual bool serialize(DataWriter& writer) const
    {
        return
                writer.add_ubyte(from_device) &&
                writer.add_ubyte(priority) &&
                writer.add_ubyte(signal_def.category_id) &&
                writer.add_ubyte(signal_def.sub_id) &&
                writer.add_uint(timestamp);
    }

    virtual bool deserialize(DataReader& reader)
    {
        uint8_t temp;

        // Determine if each of the parameters could be read successfully
        const bool success =
                reader.read_ubyte(from_device) &&
                reader.read_ubyte(priority) &&
                reader.read_ubyte(temp) &&
                reader.read_ubyte(temp) &&
                reader.read_uint(timestamp);

        // TODO: Update timestamp here
        return success;
    }

    bool read_base(DataReader& reader)
    {
        uint8_t temp;
        return
                reader.read_ubyte(from_device) &&
                reader.read_ubyte(priority) &&
                reader.read_ubyte(temp) &&
                reader.read_ubyte(temp) &&
                reader.read_uint(timestamp);
    }

    bool can_update_base(const SignalTypeBase& other) const
    {
        return
                signal_def == other.signal_def &&
                (
                    timed_out() ||
                    other.priority > priority ||
                    (other.from_device == from_device && other.timestamp > timestamp));
    }

    const SignalDef& get_signal_def() const
    {
        return signal_def;
    }

    bool timed_out() const
    {
        return false;
    }

    bool is_valid() const
    {
        // TODO - Document

        const auto period = std::chrono::high_resolution_clock::period();
        return
            (priority & 0x80) > 0 &&
            updated_time > start_time &&
            (updated_time - start_time).count() * period.num / period.den / 1000 < signal_def.timeout_millis;
    }

    virtual size_t size() const
    {
        return 8;
    }

    void set_timestamp(const uint32_t time)
    {
        timestamp = time;
    }

    void set_from_device(const uint8_t device)
    {
        from_device = device;
    }

    void update_time()
    {

    }

protected:
    SignalDef signal_def;

    uint8_t from_device;
    uint8_t priority;

    uint32_t timestamp;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> updated_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

}

#endif // TF_SIGNAL_TYPE_BASE_H
