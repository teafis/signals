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

#ifndef TF_SIGNAL_TYPE_DATA_H
#define TF_SIGNAL_TYPE_DATA_H

#include "signal_type_base.h"

namespace efis_signals
{

// TODO - Replace with VarArray?

/**
 * @brief The SignalTypeData class provides a signal type for
 * an array of byte values
 */
class SignalTypeData : public SignalTypeBase
{
public:
    // Define common types
    using data_size_t = uint32_t;
    using data_t = uint8_t;

    /**
     * @brief SignalTypeData constructs the data array signal
     * @param signal is the signal definition to use
     * @param size is the base size of the data
     */
    SignalTypeData(
            const SignalDef& signal,
            const data_size_t size);

    /**
     * @brief SignalTypeData is a copy constructor for the data values
     * @param other is the other SignalTypeData to construct from
     */
    SignalTypeData(const SignalTypeData& other);

    /**
     * @brief operator = is the assignment operator for the data type singal
     * @param other is the other SignalTypeData to assign from
     * @return the original instance updated to be equal to the other value
     */
    SignalTypeData& operator=(const SignalTypeData& other);

    /**
     * @brief set_value sets the array index to the given value (Tx only)
     * @param index is the array index to set
     * @param value is the value to set
     * @return true if the value was successfully set
     */
    bool set_value(
            const data_size_t index,
            const data_t value);

    /**
     * @brief get_value gets the array index and assigns to the value provided
     * @param index is the array index to get
     * @param value is the assigned to the current data value
     * @return true if the value can be gotten
     */
    bool get_value(
            const data_size_t index,
            data_t& value) const;

    /**
     * @brief data_size provides the size of the data array
     * @return the array size
     */
    data_size_t data_size() const;

    /**
     * @brief serialize writes signal value to the array (Tx only)
     * @param writer is the data to write to
     * @return true if able to be written
     */
    virtual bool serialize(DataWriter& writer) const override;

    /**
     * @brief deserialize reads signal from the reader (Rx only)
     * @param reader is the data to read from
     * @return true if able to be read
     */
    virtual bool deserialize(DataReader& reader) override;

    /**
     * @brief size provides the size of the packet, not including the header
     * @return the packet size
     */
    virtual size_t packet_size() const override;

    /**
     * @brief ~SignalTypeData provides the destructor for the data array
     */
    virtual ~SignalTypeData();

protected:
    /**
     * @brief data_array_size provides the size of the data array
     */
    data_size_t data_array_size;

    /**
     * @brief data_array provides the actual data values for the array
     */
    data_t* data_array;
};

}

#endif // TF_SIGNAL_TYPE_DATA_H
