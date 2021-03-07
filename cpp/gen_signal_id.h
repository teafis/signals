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

// This file is auto-generated
// Creation Date: 2021-03-07 17:22:04 UTC

#include "signal_id.h"
#include <string>

#ifndef GEN_SIGNAL_ID_H
#define GEN_SIGNAL_ID_H

namespace efis_signals
{

/**
 * @brief SIGNAL_ID_NULL is the signal for the empty signal for temporary use
 */
extern const SignalID SIGNAL_ID_NULL;

/**
 * @brief SIGNAL_ID_GPS_LATITUDE is the signal for the GPS latitude of the aircraft
 */
extern const SignalID SIGNAL_ID_GPS_LATITUDE;

/**
 * @brief SIGNAL_ID_GPS_LONGITUDE is the signal for the GPS longitude of the aircraft
 */
extern const SignalID SIGNAL_ID_GPS_LONGITUDE;

/**
 * @brief SIGNAL_ID_ALTITUDE_MSL is the signal for the MSL altitude of the aircraft
 */
extern const SignalID SIGNAL_ID_ALTITUDE_MSL;

/**
 * @brief SIGNAL_ID_ALTITUDE_AGL is the signal for the AGL altitude of the aircraft
 */
extern const SignalID SIGNAL_ID_ALTITUDE_AGL;

/**
 * @brief SIGNAL_ID_ALTITUDE_RATE is the signal for the altitude rate of the aircraft
 */
extern const SignalID SIGNAL_ID_ALTITUDE_RATE;

/**
 * @brief SIGNAL_ID_VERTICAL_SPEED is the signal for the vertical speed of the aircraft
 */
extern const SignalID SIGNAL_ID_VERTICAL_SPEED;

/**
 * @brief SIGNAL_ID_HEADING_TRUE is the signal for the true heading of the aircraft
 */
extern const SignalID SIGNAL_ID_HEADING_TRUE;

/**
 * @brief SIGNAL_ID_HEADING_MAG is the signal for the magnetic heading of the aircraft
 */
extern const SignalID SIGNAL_ID_HEADING_MAG;

/**
 * @brief SIGNAL_ID_GROUND_TRACK is the signal for the ground track of the aircraft
 */
extern const SignalID SIGNAL_ID_GROUND_TRACK;

/**
 * @brief SIGNAL_ID_MAGNETIC_VARIATION is the signal for the current magnetic variation
 */
extern const SignalID SIGNAL_ID_MAGNETIC_VARIATION;

/**
 * @brief SIGNAL_ID_ATT_PITCH is the signal for the pitch attitude angle of the aircraft
 */
extern const SignalID SIGNAL_ID_ATT_PITCH;

/**
 * @brief SIGNAL_ID_ATT_ROLL is the signal for the roll attitude angle of the aircraft
 */
extern const SignalID SIGNAL_ID_ATT_ROLL;

/**
 * @brief SIGNAL_ID_SPEED_IAS is the signal for the indicated airspeed of the aircraft
 */
extern const SignalID SIGNAL_ID_SPEED_IAS;

/**
 * @brief SIGNAL_ID_SPEED_GS is the signal for the ground speed of the aircraft
 */
extern const SignalID SIGNAL_ID_SPEED_GS;

/**
 * @brief SIGNAL_ID_ENGINE_RPM is the signal for the RPM of the engine
 */
extern const SignalID SIGNAL_ID_ENGINE_RPM;

/**
 * @brief SIGNAL_ID_OIL_PRESSURE is the signal for the oil pressure for the engine
 */
extern const SignalID SIGNAL_ID_OIL_PRESSURE;

/**
 * @brief SIGNAL_ID_OIL_TEMPERATURE is the signal for the oil temperature for the engine
 */
extern const SignalID SIGNAL_ID_OIL_TEMPERATURE;

/**
 * @brief get_signal_id_for_name provides the signal ID for the provided name
 * @param name is the name of the signal to find
 * @param signal provides the resulting signal ID if found
 * @return true if a signal for the given name is found
 */
bool get_signal_id_for_name(const std::string& name, SignalID& signal);

/**
 * @brief get_signal_name_for_id provides the name of the signal
 * @param signal_id is the signal ID to try to find a name for
 * @param name provides the name of the signal if found
 * @return true if a name for the given signal is found
 */
bool get_signal_name_for_id(const SignalID& signal_id, std::string name);

}

#endif // GEN_SIGNAL_ID_H
