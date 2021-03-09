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

#ifndef TF_SIGNAL_CRC16_H
#define TF_SIGNAL_CRC16_H

#include <cstdint>

namespace efis_signals
{

class CRC16
{
public:
    CRC16()
    {
        // Empty Constructor
    }

    uint16_t get_checksum(const uint8_t* data, uint32_t size)
    {
        // TODO - This
        (void)data;
        (void)size;
        return 0;
    }
};

}

#endif // TF_SIGNAL_CRC16_H
