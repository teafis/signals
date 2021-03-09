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

/**
 * @brief The CRC16 class provides a CRC16 implementation for networking
 */
class CRC16
{
public:
    /**
     * @brief CRC16 constructs and generates parameters required for CRC generation
     */
    CRC16()
    {
        // Empty Constructor
    }

    /**
     * @brief compute provides the CRC-16 checksum for the provided data
     * @param data the data to check
     * @param size the size of the data to read
     * @return the associated CRC-16 for the data
     */
    uint16_t compute(const uint8_t* data, uint32_t size)
    {
        // TODO - This
        (void)data;
        (void)size;
        return 0;
    }
};

}

#endif // TF_SIGNAL_CRC16_H
