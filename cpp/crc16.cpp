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

#include "crc16.h"

efis_signals::CRC16::CRC16()
{
    // Empty Constructor
}

uint16_t efis_signals::CRC16::compute(
        const uint8_t* data,
        uint32_t size) const
{
    // TODO - Provide implementation
    (void)data;
    (void)size;
    return 0;
}
