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

#include "signal_def.h"

using namespace efis_signals;

SignalDef::SignalDef() :
    category_id(0),
    sub_id(0)
{
    // Empty constructor
}

SignalDef::SignalDef(
        const uint8_t category_id,
        const uint8_t sub_id,
        const uint32_t timeout_millis) :
    category_id(category_id),
    sub_id(sub_id),
    timeout_millis(timeout_millis)
{
    // Empty Constructor
}

bool SignalDef::operator==(const SignalDef& other) const
{
    return
            category_id == other.category_id &&
            sub_id == other.sub_id;
}

size_t SignalDef::signal_index() const
{
    return (static_cast<size_t>(category_id) << 8) | sub_id;
}
