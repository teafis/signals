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

/**
 * @brief The SignalDatabase class provides an instance of a database object
 * to store and provide the latest signal data type parameters for different
 * signals, stored by a SignalDefinition object
 */
class SignalDatabase
{
private:
    /**
     * @brief SignalDatabase constructs the signal database object
     */
    SignalDatabase();

public:
    /**
     * @brief get_instance provides access to the singleton database object
     * @return the singleton database object
     */
    static SignalDatabase& get_instance();

    /**
     * @brief get_signal provides a signal of the provided definition, if available
     * @param signal_def is the signal definition to search for
     * @param signal stores the output location of the signal in memory if found
     * @return true if the signal is found
     */
    bool get_signal(
            const SignalDef& signal_def,
            SignalTypeBase** signal) const;

    /**
     * @brief get_scaled_signal provides the scaled signal definition, if available
     * @param signal_def is the signal definition to search for
     * @param signal stores the return signal value if found
     * @return true if the scalled signal is found
     */
    bool get_scaled_signal(
            const SignalDef& signal_def,
            SignalTypeScaled** signal) const;

    /**
     * @brief get_signal_type provides the signal of the provided type, if available
     * @param signal_def is the signal definition to search for
     * @param signal stores the return signal value if found. Must be an instance
     * of the SignalTypeBase class or a subclass
     * @return  true if the signal of the provided type is found
     */
    template <typename T>
    bool get_signal_type(
            const SignalDef& signal_def,
            T** signal) const
    {
        // Ensure that the provided type is an instance of the SignalTypeBase
        static_assert(
            std::is_base_of<SignalTypeBase, T>::value,
            "get_signal_type may only be called with instances of SignalTypeBase");

         // Obtain the base class signal
        SignalTypeBase* base;
        if (!get_signal(signal_def, &base))
        {
            return false;
        }
        else
        {
            // Try to convert the base class into the requested type
            *signal = dynamic_cast<T*>(base);
            return *signal != nullptr;
        }
    }

    /**
     * @brief size provides the overall size of the signal database
     * @return provides the number of signals available in the dictionary
     */
    size_t size() const;

    /**
     * @brief update_packet attempts to read the data contained in the reader
     * into the dictionary and update any stored values within
     * @param reader is the reader object containing the data to be read
     * into the dictionary
     * @return true if a signal was successfully read into the dictionary
     */
    bool read_data_into_dictionary(DataReader& reader);

    /**
     * @brief write_data_from_dictionary attempts to write the requested signal
     * from the dictionary into the data writer, using the current FROM device
     * and timestamp as the parameter values for the header
     * @param signal is the signal to write into the object
     * @param writer is the object to write the data into
     * @return true if the signal is successfully writen into the data writer
     */
    bool write_data_from_dictionary(
            const SignalDef& signal,
            DataWriter& writer) const;

protected:
    /**
     * @brief init_signals provides a function to initialize the signals within
     * the database
     */
    void init_signals();

protected:
    /**
     * @brief signal_array provides the storage for locations to the signals
     * stored within the database. The actual signals within the database
     * are memory-managed separately and may be done in either the stack
     * or the heap, depending on the usage. This array should be initialized
     * within the init_signals function.
     */
    SignalTypeBase* signal_array[SignalDef::MAX_SIGNAL_COUNT];

    /**
     * @brief crc provides an instance used to calculate the CRC of incoming and
     * outgoing signals
     */
    CRC16 crc;
};

}

#endif // TF_SIGNAL_DATABASE_H
