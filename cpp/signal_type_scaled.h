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

#ifndef SIGNAL_TYPE_FIXED_H
#define SIGNAL_TYPE_FIXED_H

#include "signal_type_base.h"

#include "data_type_scaled.h"

// TODO - Documentation
// TODO - Split into CPP file

namespace efis_signals
{

/**
 * @brief The SignalTypeScaled class provides a signal type
 * to hold a floating point value scaled into a 4-byte integer
 * using 2's complement
 */
class SignalTypeScaled : public SignalTypeBase
{
public:
    /**
     * @brief SignalTypeScaled constructs the scaled data type
     * @param signal is the signal definition to use
     * @param resolution is the resolution of the scaled data
     */
    SignalTypeScaled(
            const SignalDef& signal,
            const double resolution);

    /**
     * @brief set_value sets the scaled data value (Tx only)
     * @param input is the new value to set
     * @return true if the value can be set
     */
    bool set_value(const double input);

    /**
     * @brief get_value provides the current scaled value
     * @return the signal value
     */
    double get_value() const;

    /**
     * @brief get_data_value provides the underlying scaled data type
     * @return the underlying scaled data type
     */
    const DataTypeScaled& get_data_value() const;

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
     * @brief data provides the underlying data value
     */
    DataTypeScaled value;
};

}

#endif // SIGNAL_TYPE_FIXED_H
