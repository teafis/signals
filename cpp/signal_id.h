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

#ifndef SIGNAL_ID_H
#define SIGNAL_ID_H

#include <cstdint>
#include <cstddef>
#include <limits>

namespace efis_signals
{

/**
 * @brief The SignalID struct defines a signal identification
 * method to positively define signal types
 */
struct SignalID
{
    /**
     * @brief SignalID constructs a signal ID instance
     * @param category_id is the category ID for the associated signal
     * @param signal_id is the signal ID for the associated signal
     */
    SignalID(
            const uint8_t category_id,
            const uint8_t signal_id);

    /**
     * @brief category_id the category ID of the signal
     */
    uint8_t category_id;

    /**
     * @brief sub_id the signal sub-category ID
     */
    uint8_t signal_id;

    /**
     * @brief operator == defines an equality check between two SignalID objects
     * @param other is the other SignalID to compare against the current one
     * @return True if the two signals are equal; otherwise false
     */
    bool operator==(const SignalID& other) const;

    /**
     * @brief signal_index provides the
     * @return
     */
    size_t signal_index() const;

    /**
     * @brief MAX_SIGNAL_COUNT
     */
    static const size_t MAX_SIGNAL_COUNT = static_cast<size_t>(std::numeric_limits<uint16_t>::max()) + 1;

};

}

#endif // SIGNAL_ID_H
