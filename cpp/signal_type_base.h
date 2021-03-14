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

#ifndef TF_SIGNAL_TYPE_BASE_H
#define TF_SIGNAL_TYPE_BASE_H

#include "data_reader.h"
#include "data_writer.h"

#include "signal_def.h"
#include "gen_signal_def.h"

#include "signal_time.h"

#include "signal_header.h"

#include <chrono>

namespace efis_signals
{

/**
 * @brief The SignalSourceType enum provides signal source
 * type information for a given signal, including transmit
 * and receive
 */
enum class SignalSourceType
{
    None = 0,
    Transmitted = 1,
    Received = 2
};

/**
 * @brief The SignalTypeBase class provides the base class
 * for all signal types to be used
 */
class SignalTypeBase
{
public:
    /**
     * @brief SignalTypeBase defines the base signal class
     * @param signal is the signal definition to construct
     * the signal with
     */
    SignalTypeBase(const SignalDef& signal);

    /**
     * @brief serialize writes data information to the writer,
     * not including the header (Tx only)
     * @return true if the data is able to be written
     */
    virtual bool serialize(DataWriter&) const;

    /**
     * @brief deserialize reads data from the data reader,
     * not including the header (Rx only)
     * @return true if the dta is able to be written
     */
    virtual bool deserialize(DataReader&);

    /**
     * @brief update_header attempts to update the signal header
     * from the other header provided (presumably read from the
     * network). The header may only be updated if the category
     * and sub ID's match, and the update rules state that
     * the current header may be updated (e.g., the signal is
     * currently invalid, the new timestamp is greater than the
     * last signal's timestamp, or the other header has a higher
     * priority). (Rx only)
     *
     * Note that updates may only occur if the signal is a
     * receiving signal
     * @param other is the other header to use to update.
     * @return true if the header was successfully updated
     */
    bool update_header(const SignalHeader& other);

    /**
     * @brief is_valid determines if the signal is valid, based on
     * timeout and priority validity parameters
     * @return true if the signal is valid
     */
    bool is_valid() const;

    /**
     * @brief size determines the size of the data packet, not including
     * the header
     * @return packet size in bytes
     */
    virtual size_t packet_size() const;

    /**
     * @brief set_updated_time_to_now updates the last updated time
     * to the current time value. If Tx, will also update the header
     * updated timestamp to the current timestamp
     */
    void set_updated_time_to_now();

    /**
     * @brief set_source_type updates the signal's source type
     * @param type is the type to update the signal to
     */
    void set_source_type(const SignalSourceType type);

    /**
     * @brief set_priority attempts to set the priority of the signal (Tx only)
     * @param priority is the new priority to set
     * @return true if the priority was successfully set
     */
    bool set_priority(const uint8_t priority);

    /**
     * @brief set_from_device attempts to set the from_device of the signal (Tx only)
     * @param from_device is the new from_device to set
     * @return true if the from_deivce was successfully set
     */
    bool set_from_device(const uint8_t from_device);

    /**
     * @brief get_header provides the current header
     * @return the signal header
     */
    const SignalHeader& get_header() const;

protected:
    /**
     * @brief is_receive determines if the signal is receive
     * @return true if the signal is Rx
     */
    bool is_receive() const;

    /**
     * @brief is_transmit determines if the signal is transmit
     * @return true if the signal is Tx
     */
    bool is_transmit() const;

protected:
    /**
     * @brief header provides the base header information
     */
    SignalHeader header;

    /**
     * @brief source_type provides the signal source tyep
     */
    SignalSourceType source_type;

private:
    /**
     * @brief updated_time defines the last time that the signal has been updated
     */
    efis_signals::timestamp_t updated_time;
};

}

#endif // TF_SIGNAL_TYPE_BASE_H
