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
// Creation Date: 2021-03-07 17:08:58 UTC

#include "signal_id.h"
#include <string>

#ifndef GEN_SIGNAL_ID_H
#define GEN_SIGNAL_ID_H

namespace efis_signals
{

extern const SignalID SIGNAL_ID_NULL;
extern const SignalID SIGNAL_ID_GPS_LATITUDE;
extern const SignalID SIGNAL_ID_GPS_LONGITUDE;
extern const SignalID SIGNAL_ID_ALTITUDE_MSL;
extern const SignalID SIGNAL_ID_ALTITUDE_AGL;
extern const SignalID SIGNAL_ID_ALTITUDE_RATE;
extern const SignalID SIGNAL_ID_HEADING_TRUE;
extern const SignalID SIGNAL_ID_HEADING_MAG;
extern const SignalID SIGNAL_ID_GROUND_TRACK;
extern const SignalID SIGNAL_ID_MAGNETIC_VARIATION;
extern const SignalID SIGNAL_ID_ATT_PITCH;
extern const SignalID SIGNAL_ID_ATT_ROLL;
extern const SignalID SIGNAL_ID_SPEED_IAS;
extern const SignalID SIGNAL_ID_SPEED_GS;
extern const SignalID SIGNAL_ID_ENGINE_RPM;
extern const SignalID SIGNAL_ID_OIL_PRESSURE;
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
