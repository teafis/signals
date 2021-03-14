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

#include "signal_header.h"

#include "gen_signal_def.h"

using namespace efis_signals;

SignalHeader::SignalHeader() :
    cat_id(0),
    sub_id(0),
    priority(0),
    from_device(0),
    timestamp(0)
{
    // Empty Constructor
}

bool SignalHeader::write_header(DataWriter& writer) const
{
    return
            writer.add_ubyte(from_device) &&
            writer.add_ubyte(priority) &&
            writer.add_ubyte(cat_id) &&
            writer.add_ubyte(sub_id) &&
            writer.add_uint(timestamp);
}

bool SignalHeader::read_header(DataReader& reader)
{
    return
            reader.read_ubyte(from_device) &&
            reader.read_ubyte(priority) &&
            reader.read_ubyte(cat_id) &&
            reader.read_ubyte(sub_id) &&
            reader.read_uint(timestamp);
}

SignalDef SignalHeader::get_signal_def() const
{
    SignalDef sig_def;
    if (get_signal_def_check(sig_def))
    {
        return sig_def;
    }
    else
    {
        return SIGNAL_DEF_NULL;
    }
}

bool SignalHeader::get_signal_def_check(SignalDef& signal_def) const
{
    return get_signal_for_cat_sub_id(
                cat_id,
                sub_id,
                signal_def);
}

bool SignalHeader::has_valid_def() const
{
    SignalDef sig_def;
    return get_signal_def_check(sig_def);
}
