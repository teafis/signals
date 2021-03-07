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
// Creation Date: 2021-03-07 05:11:00 UTC

#include "signal_database.h"
#include "signal_type_base.h"
#include "signal_type_fixed.h"
#include "gen_signal_id.h"

using namespace efis_signals;

void SignalDatabase::init_signals()
{
    static SignalTypeBase signal_null(SIGNAL_ID_NULL);
    signal_array[SIGNAL_ID_NULL.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_null);

    static SignalTypeFixed signal_gps_latitude(SIGNAL_ID_GPS_LATITUDE, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_ID_GPS_LATITUDE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_gps_latitude);

    static SignalTypeFixed signal_gps_longitude(SIGNAL_ID_GPS_LONGITUDE, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_ID_GPS_LONGITUDE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_gps_longitude);

    static SignalTypeFixed signal_altitude_msl(SIGNAL_ID_ALTITUDE_MSL, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_ID_ALTITUDE_MSL.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_altitude_msl);

    static SignalTypeFixed signal_altitude_agl(SIGNAL_ID_ALTITUDE_AGL, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_ID_ALTITUDE_AGL.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_altitude_agl);

    static SignalTypeFixed signal_altitude_rate(SIGNAL_ID_ALTITUDE_RATE, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_ID_ALTITUDE_RATE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_altitude_rate);

    static SignalTypeFixed signal_heading_true(SIGNAL_ID_HEADING_TRUE, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_ID_HEADING_TRUE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_heading_true);

    static SignalTypeFixed signal_heading_mag(SIGNAL_ID_HEADING_MAG, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_ID_HEADING_MAG.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_heading_mag);

    static SignalTypeFixed signal_ground_track(SIGNAL_ID_GROUND_TRACK, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_ID_GROUND_TRACK.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_ground_track);

    static SignalTypeFixed signal_magnetic_variation(SIGNAL_ID_MAGNETIC_VARIATION, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_ID_MAGNETIC_VARIATION.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_magnetic_variation);

    static SignalTypeFixed signal_att_pitch(SIGNAL_ID_ATT_PITCH, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_ID_ATT_PITCH.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_att_pitch);

    static SignalTypeFixed signal_att_roll(SIGNAL_ID_ATT_ROLL, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_ID_ATT_ROLL.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_att_roll);

    static SignalTypeFixed signal_speed_ias(SIGNAL_ID_SPEED_IAS, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_ID_SPEED_IAS.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_speed_ias);

    static SignalTypeFixed signal_speed_gs(SIGNAL_ID_SPEED_GS, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_ID_SPEED_GS.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_speed_gs);

    static SignalTypeFixed signal_engine_rpm(SIGNAL_ID_ENGINE_RPM, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_ID_ENGINE_RPM.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_engine_rpm);

    static SignalTypeFixed signal_oil_pressure(SIGNAL_ID_OIL_PRESSURE, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_ID_OIL_PRESSURE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_oil_pressure);

    static SignalTypeFixed signal_oil_temperature(SIGNAL_ID_OIL_TEMPERATURE, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_ID_OIL_TEMPERATURE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_oil_temperature);
}
