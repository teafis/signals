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

#ifndef SIGNAL_DATABASE_H
#define SIGNAL_DATABASE_H

#include <cstdint>

#include "signal_type_base.h"
#include "signal_type_fixed.h"
#include "signal_id.h"

namespace efis_signals
{

class SignalDatabase
{
private:
    SignalDatabase();

public:
    static SignalDatabase& get_instance();

    bool get_signal(
            const SignalID& signal_id,
            SignalTypeBase** signal) const;

    bool get_fixed_signal(
            const SignalID& signal_id,
            SignalTypeFixed** signal) const;

    size_t size() const;

    bool update_packet(DataReader& reader);

protected:
    void init_signals();

protected:
    SignalTypeBase* signal_array[SignalID::MAX_SIGNAL_COUNT];
};

}

#endif // SIGNAL_DATABASE_H
