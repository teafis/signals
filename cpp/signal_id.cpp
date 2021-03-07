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

#include "signal_id.h"

using namespace efis_signals;

SignalID::SignalID() :
    category_id(0),
    signal_id(0)
{
    // Empty constructor
}

SignalID::SignalID(
        const uint8_t category_id,
        const uint8_t signal_id) :
    category_id(category_id),
    signal_id(signal_id)
{
    // Empty Constructor
}

bool SignalID::operator==(const SignalID& other) const
{
    return
            category_id == other.category_id &&
            signal_id == other.signal_id;
}

size_t SignalID::signal_index() const
{
    return (static_cast<size_t>(category_id) << 8) | signal_id;
}
