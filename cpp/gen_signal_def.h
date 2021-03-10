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
// Creation Date: 2021-03-10 19:04:03 UTC

#include "signal_def.h"
#include <string>

#ifndef TF_GEN_SIGNAL_DEF_H
#define TF_GEN_SIGNAL_DEF_H

namespace efis_signals
{

extern const uint32_t SIGNAL_VERSION_NUM;

/**
 * @brief SIGNAL_DEF_NULL is the signal for the empty signal for temporary use
 */
extern const SignalDef SIGNAL_DEF_NULL;

/**
 * @brief SIGNAL_DEF_GPS_LATITUDE is the signal for the GPS latitude of the aircraft
 */
extern const SignalDef SIGNAL_DEF_GPS_LATITUDE;

/**
 * @brief SIGNAL_DEF_GPS_LONGITUDE is the signal for the GPS longitude of the aircraft
 */
extern const SignalDef SIGNAL_DEF_GPS_LONGITUDE;

/**
 * @brief SIGNAL_DEF_ALTITUDE_MSL is the signal for the MSL altitude of the aircraft
 */
extern const SignalDef SIGNAL_DEF_ALTITUDE_MSL;

/**
 * @brief SIGNAL_DEF_ALTITUDE_AGL is the signal for the AGL altitude of the aircraft
 */
extern const SignalDef SIGNAL_DEF_ALTITUDE_AGL;

/**
 * @brief SIGNAL_DEF_ALTITUDE_RATE is the signal for the altitude rate of the aircraft
 */
extern const SignalDef SIGNAL_DEF_ALTITUDE_RATE;

/**
 * @brief SIGNAL_DEF_VERTICAL_SPEED is the signal for the vertical speed of the aircraft
 */
extern const SignalDef SIGNAL_DEF_VERTICAL_SPEED;

/**
 * @brief SIGNAL_DEF_HEADING_TRUE is the signal for the true heading of the aircraft
 */
extern const SignalDef SIGNAL_DEF_HEADING_TRUE;

/**
 * @brief SIGNAL_DEF_HEADING_MAG is the signal for the magnetic heading of the aircraft
 */
extern const SignalDef SIGNAL_DEF_HEADING_MAG;

/**
 * @brief SIGNAL_DEF_GROUND_TRACK is the signal for the ground track of the aircraft
 */
extern const SignalDef SIGNAL_DEF_GROUND_TRACK;

/**
 * @brief SIGNAL_DEF_MAGNETIC_VARIATION is the signal for the current magnetic variation
 */
extern const SignalDef SIGNAL_DEF_MAGNETIC_VARIATION;

/**
 * @brief SIGNAL_DEF_ATT_PITCH is the signal for the pitch attitude angle of the aircraft
 */
extern const SignalDef SIGNAL_DEF_ATT_PITCH;

/**
 * @brief SIGNAL_DEF_ATT_ROLL is the signal for the roll attitude angle of the aircraft
 */
extern const SignalDef SIGNAL_DEF_ATT_ROLL;

/**
 * @brief SIGNAL_DEF_SPEED_IAS is the signal for the indicated airspeed of the aircraft
 */
extern const SignalDef SIGNAL_DEF_SPEED_IAS;

/**
 * @brief SIGNAL_DEF_SPEED_GS is the signal for the ground speed of the aircraft
 */
extern const SignalDef SIGNAL_DEF_SPEED_GS;

/**
 * @brief SIGNAL_DEF_ENGINE_RPM is the signal for the RPM of the engine
 */
extern const SignalDef SIGNAL_DEF_ENGINE_RPM;

/**
 * @brief SIGNAL_DEF_OIL_PRESSURE is the signal for the oil pressure for the engine
 */
extern const SignalDef SIGNAL_DEF_OIL_PRESSURE;

/**
 * @brief SIGNAL_DEF_OIL_TEMPERATURE is the signal for the oil temperature for the engine
 */
extern const SignalDef SIGNAL_DEF_OIL_TEMPERATURE;

/**
 * @brief get_signal_def_for_name provides the signal definition for the provided name
 * @param name is the name of the signal to find
 * @param signal provides the resulting signal definition if found
 * @return true if a signal for the given name is found
 */
bool get_signal_def_for_name(const std::string& name, SignalDef& signal);

/**
 * @brief get_signal_name_for_def provides the name of the signal
 * @param signal_def is the signal definition to try to find a name for
 * @param name provides the name of the signal if found
 * @return true if a name for the given signal is found
 */
bool get_signal_name_for_def(const SignalDef& signal_def, std::string name);

/**
 * @brief get_signal_for_cat_sub_id provides the name of the signal
 * @param cat_id is the category ID of the signal to search for
 * @param sub_id is the subcategory ID of the signal to search for
 * @param signal_def provides the signal definition if found
 * @return true if a name for the given signal is found
 */
bool get_signal_for_cat_sub_id(const uint8_t cat_id, const uint8_t sub_id, SignalDef& signal_def);

}

#endif // TF_GEN_SIGNAL_DEF_H
