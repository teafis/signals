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

#ifndef TF_SIGNALS_DATA_SCALED_H
#define TF_SIGNALS_DATA_SCALED_H

#include <cstdint>
#include <limits>

namespace efis_signals
{

/**
 * @brief The DataTypeScaled class provides a scaled data type for
 * transmitting a floating point number of the network consistently
 * between devices with potentially different floating point
 * implementations within a four-byte datatype
 */
class DataTypeScaled
{
public:
    /**
     * @brief DataTypeScaled constructs the scaled type with the provided resolution
     * @param resolution
     */
    DataTypeScaled(const double resolution) :
        resolution(resolution),
        value(0.0)
    {
        // Empty Constructor
    }

    /**
     * @brief set_value sets the stored flaoting point value. If the value is
     * above or below the maximum allowed value, it will be saturated at
     * the respective limit
     * @param input the value to set
     */
    void set_value(const double input)
    {
        if (input > max_value())
        {
            value = max_value();
        }
        else if (input < min_value())
        {
            value = min_value();
        }
        else
        {
            value = input;
        }
    }

    /**
     * @brief get_value provides the current value associated with the type
     * @return the floating point scaled value
     */
    double get_value() const
    {
        return value;
    }

    /**
     * @brief set_raw_value sets the data type with a raw value
     * @param raw is the raw value to set
     */
    void set_raw_value(const uint32_t raw)
    {
        value = static_cast<double>(static_cast<int32_t>(raw)) * resolution;
    }

    /**
     * @brief get_raw_value gets the underlying raw data type for the signal
     * @return the raw byte interpretation of the scaled data type
     */
    uint32_t get_raw_value() const
    {
        return static_cast<uint32_t>(static_cast<int32_t>(value / resolution));
    }

    /**
     * @brief max_value provides the maximum possible value for the type
     * @return the maximum value possible with the provided resolution
     */
    double max_value() const
    {
        return std::numeric_limits<int32_t>::max() * resolution;
    }

    /**
     * @brief min_value provides the minimum possible value for the type
     * @return the minimum value possible with the provided resolution
     */
    double min_value() const
    {
        return std::numeric_limits<int32_t>::min() * resolution;
    }

    /**
     * @brief get_resolution provides the data resolution
     * @return the resolution setting for the scaled type
     */
    double get_resolution() const;

protected:
    /**
     * @brief resolution stores the resolution of the scaled type
     */
    double resolution;

    /**
     * @brief value is the underlying data type value for the signal
     */
    double value;
};

}

#endif // TF_SIGNALS_DATA_SCALED_H
