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

#ifndef TF_SIGNAL_DATABASE_H
#define TF_SIGNAL_DATABASE_H

#include <cstdint>

#include "signal_type_base.h"
#include "signal_type_scaled.h"
#include "signal_def.h"

#include "crc16.h"

namespace efis_signals
{

class SignalDatabase
{
private:
    SignalDatabase();

public:
    static SignalDatabase& get_instance();

    bool get_signal(
            const SignalDef& signal_def,
            SignalTypeBase** signal) const;

    bool get_scaled_signal(
            const SignalDef& signal_def,
            SignalTypeScaled** signal) const;

    size_t size() const;

    bool update_packet(DataReader& reader);

    bool write_packet(DataWriter& write);

protected:
    void init_signals();

protected:
    SignalTypeBase* signal_array[SignalDef::MAX_SIGNAL_COUNT];

    CRC16 crc;
};

}

#endif // TF_SIGNAL_DATABASE_H
