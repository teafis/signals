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

#include "signal_database.h"
#include "signal_type_base.h"
#include "signal_type_scaled.h"
#include "gen_signal_def.h"

using namespace efis_signals;

void SignalDatabase::init_signals()
{
    static SignalTypeBase signal_null(SIGNAL_DEF_NULL);
    signal_array[SIGNAL_DEF_NULL.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_null);

    static SignalTypeScaled signal_gps_latitude(SIGNAL_DEF_GPS_LATITUDE, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_DEF_GPS_LATITUDE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_gps_latitude);

    static SignalTypeScaled signal_gps_longitude(SIGNAL_DEF_GPS_LONGITUDE, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_DEF_GPS_LONGITUDE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_gps_longitude);

    static SignalTypeScaled signal_altitude_msl(SIGNAL_DEF_ALTITUDE_MSL, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_DEF_ALTITUDE_MSL.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_altitude_msl);

    static SignalTypeScaled signal_altitude_agl(SIGNAL_DEF_ALTITUDE_AGL, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_DEF_ALTITUDE_AGL.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_altitude_agl);

    static SignalTypeScaled signal_altitude_rate(SIGNAL_DEF_ALTITUDE_RATE, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_DEF_ALTITUDE_RATE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_altitude_rate);

    static SignalTypeScaled signal_vertical_speed(SIGNAL_DEF_VERTICAL_SPEED, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_DEF_VERTICAL_SPEED.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_vertical_speed);

    static SignalTypeScaled signal_heading_true(SIGNAL_DEF_HEADING_TRUE, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_DEF_HEADING_TRUE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_heading_true);

    static SignalTypeScaled signal_heading_mag(SIGNAL_DEF_HEADING_MAG, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_DEF_HEADING_MAG.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_heading_mag);

    static SignalTypeScaled signal_ground_track(SIGNAL_DEF_GROUND_TRACK, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_DEF_GROUND_TRACK.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_ground_track);

    static SignalTypeScaled signal_magnetic_variation(SIGNAL_DEF_MAGNETIC_VARIATION, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_DEF_MAGNETIC_VARIATION.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_magnetic_variation);

    static SignalTypeScaled signal_att_pitch(SIGNAL_DEF_ATT_PITCH, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_DEF_ATT_PITCH.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_att_pitch);

    static SignalTypeScaled signal_att_roll(SIGNAL_DEF_ATT_ROLL, 8.381903171539306640625000e-08);
    signal_array[SIGNAL_DEF_ATT_ROLL.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_att_roll);

    static SignalTypeScaled signal_speed_ias(SIGNAL_DEF_SPEED_IAS, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_DEF_SPEED_IAS.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_speed_ias);

    static SignalTypeScaled signal_speed_gs(SIGNAL_DEF_SPEED_GS, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_DEF_SPEED_GS.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_speed_gs);

    static SignalTypeScaled signal_engine_rpm(SIGNAL_DEF_ENGINE_RPM, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_DEF_ENGINE_RPM.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_engine_rpm);

    static SignalTypeScaled signal_oil_pressure(SIGNAL_DEF_OIL_PRESSURE, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_DEF_OIL_PRESSURE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_oil_pressure);

    static SignalTypeScaled signal_oil_temperature(SIGNAL_DEF_OIL_TEMPERATURE, 1.000000000000000020816682e-02);
    signal_array[SIGNAL_DEF_OIL_TEMPERATURE.signal_index()] = dynamic_cast<SignalTypeBase*>(&signal_oil_temperature);
}
