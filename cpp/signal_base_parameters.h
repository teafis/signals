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

#ifndef TF_SIGNAL_BASE_PARAMETERS_H
#define TF_SIGNAL_BASE_PARAMETERS_H

#include <cstdint>

#include "data_writer.h"
#include "data_reader.h"

#include "signal_def.h"

namespace efis_signals
{

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
                writer.add_uint(timestamp);
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

}

#endif // TF_SIGNAL_BASE_PARAMETERS_H
