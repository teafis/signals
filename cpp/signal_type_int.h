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

#ifndef TF_SIGNAL_TYPE_INT_H
#define TF_SIGNAL_TYPE_INT_H

#include "signal_type_base.h"

namespace efis_signals
{

/**
 * @brief The SignalTypeInteger class provides a signal type
 * to hold a 4-byte unsigned integer value
 */
class SignalTypeInteger : public SignalTypeBase
{
public:
    /**
     * @brief SignalTypeInteger constructs the integer signal
     * @param signal is the signal definition to use
     */
    SignalTypeInteger(const SignalDef& signal);

    /**
     * @brief set_value sets the integer value (Tx only)
     * @param input is the new value to set
     * @return true if the value can be set
     */
    bool set_value(const uint32_t input);

    /**
     * @brief get_value provides the integer value
     * @return the signal value
     */
    uint32_t get_value() const;

    /**
     * @brief serialize writes signal (Tx only)
     * @param writer is the data to write to
     * @return true if able to be written
     */
    virtual bool serialize(DataWriter& writer) const override;

    /**
     * @brief deserialize reads the signal from the reader (Rx only)
     * @param reader is the data to read from
     * @return true if able to be read
     */
    virtual bool deserialize(DataReader& reader) override;

    /**
     * @brief size provides the size of the packet, not including the header
     * @return the packet size
     */
    virtual size_t packet_size() const override;

protected:
    /**
     * @brief value is the underlying data value
     */
    uint32_t value;
};

}

#endif // TF_SIGNAL_TYPE_INT_H
