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

#include "gen_signal_def.h"

using namespace efis_signals;

const uint32_t efis_signals::SIGNAL_LIST_VERSION_NUM = 1;

const SignalDef efis_signals::SIGNAL_DEF_NULL(0, 0, 1000);
const SignalDef efis_signals::SIGNAL_DEF_GPS_LATITUDE(10, 10, 1000);
const SignalDef efis_signals::SIGNAL_DEF_GPS_LONGITUDE(10, 11, 1000);
const SignalDef efis_signals::SIGNAL_DEF_ALTITUDE_MSL(10, 20, 1000);
const SignalDef efis_signals::SIGNAL_DEF_ALTITUDE_AGL(10, 21, 1000);
const SignalDef efis_signals::SIGNAL_DEF_ALTITUDE_RATE(10, 22, 1000);
const SignalDef efis_signals::SIGNAL_DEF_VERTICAL_SPEED(10, 23, 1000);
const SignalDef efis_signals::SIGNAL_DEF_HEADING_TRUE(10, 30, 1000);
const SignalDef efis_signals::SIGNAL_DEF_HEADING_MAG(10, 31, 1000);
const SignalDef efis_signals::SIGNAL_DEF_GROUND_TRACK(10, 32, 1000);
const SignalDef efis_signals::SIGNAL_DEF_MAGNETIC_VARIATION(10, 33, 1000);
const SignalDef efis_signals::SIGNAL_DEF_ATT_PITCH(10, 40, 1000);
const SignalDef efis_signals::SIGNAL_DEF_ATT_ROLL(10, 41, 1000);
const SignalDef efis_signals::SIGNAL_DEF_SPEED_IAS(10, 50, 1000);
const SignalDef efis_signals::SIGNAL_DEF_SPEED_GS(10, 51, 1000);
const SignalDef efis_signals::SIGNAL_DEF_ENGINE_RPM(20, 10, 1000);
const SignalDef efis_signals::SIGNAL_DEF_OIL_PRESSURE(20, 20, 1000);
const SignalDef efis_signals::SIGNAL_DEF_OIL_TEMPERATURE(20, 21, 1000);

bool efis_signals::get_signal_def_for_name(const std::string& name, SignalDef& signal_def)
{
    if (name == "null")
    {
        signal_def = SIGNAL_DEF_NULL;
        return true;
    }
    else if (name == "gps_latitude")
    {
        signal_def = SIGNAL_DEF_GPS_LATITUDE;
        return true;
    }
    else if (name == "gps_longitude")
    {
        signal_def = SIGNAL_DEF_GPS_LONGITUDE;
        return true;
    }
    else if (name == "altitude_msl")
    {
        signal_def = SIGNAL_DEF_ALTITUDE_MSL;
        return true;
    }
    else if (name == "altitude_agl")
    {
        signal_def = SIGNAL_DEF_ALTITUDE_AGL;
        return true;
    }
    else if (name == "altitude_rate")
    {
        signal_def = SIGNAL_DEF_ALTITUDE_RATE;
        return true;
    }
    else if (name == "vertical_speed")
    {
        signal_def = SIGNAL_DEF_VERTICAL_SPEED;
        return true;
    }
    else if (name == "heading_true")
    {
        signal_def = SIGNAL_DEF_HEADING_TRUE;
        return true;
    }
    else if (name == "heading_mag")
    {
        signal_def = SIGNAL_DEF_HEADING_MAG;
        return true;
    }
    else if (name == "ground_track")
    {
        signal_def = SIGNAL_DEF_GROUND_TRACK;
        return true;
    }
    else if (name == "magnetic_variation")
    {
        signal_def = SIGNAL_DEF_MAGNETIC_VARIATION;
        return true;
    }
    else if (name == "att_pitch")
    {
        signal_def = SIGNAL_DEF_ATT_PITCH;
        return true;
    }
    else if (name == "att_roll")
    {
        signal_def = SIGNAL_DEF_ATT_ROLL;
        return true;
    }
    else if (name == "speed_ias")
    {
        signal_def = SIGNAL_DEF_SPEED_IAS;
        return true;
    }
    else if (name == "speed_gs")
    {
        signal_def = SIGNAL_DEF_SPEED_GS;
        return true;
    }
    else if (name == "engine_rpm")
    {
        signal_def = SIGNAL_DEF_ENGINE_RPM;
        return true;
    }
    else if (name == "oil_pressure")
    {
        signal_def = SIGNAL_DEF_OIL_PRESSURE;
        return true;
    }
    else if (name == "oil_temperature")
    {
        signal_def = SIGNAL_DEF_OIL_TEMPERATURE;
        return true;
    }
    else
    {
        return false;
    }
}

bool efis_signals::get_signal_name_for_def(const SignalDef& signal_def, std::string name)
{
    if (signal_def == SIGNAL_DEF_NULL)
    {
        name = "null";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_GPS_LATITUDE)
    {
        name = "gps_latitude";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_GPS_LONGITUDE)
    {
        name = "gps_longitude";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_ALTITUDE_MSL)
    {
        name = "altitude_msl";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_ALTITUDE_AGL)
    {
        name = "altitude_agl";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_ALTITUDE_RATE)
    {
        name = "altitude_rate";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_VERTICAL_SPEED)
    {
        name = "vertical_speed";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_HEADING_TRUE)
    {
        name = "heading_true";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_HEADING_MAG)
    {
        name = "heading_mag";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_GROUND_TRACK)
    {
        name = "ground_track";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_MAGNETIC_VARIATION)
    {
        name = "magnetic_variation";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_ATT_PITCH)
    {
        name = "att_pitch";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_ATT_ROLL)
    {
        name = "att_roll";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_SPEED_IAS)
    {
        name = "speed_ias";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_SPEED_GS)
    {
        name = "speed_gs";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_ENGINE_RPM)
    {
        name = "engine_rpm";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_OIL_PRESSURE)
    {
        name = "oil_pressure";
        return true;
    }
    else if (signal_def == SIGNAL_DEF_OIL_TEMPERATURE)
    {
        name = "oil_temperature";
        return true;
    }
    else
    {
        return false;
    }
}

bool efis_signals::get_signal_for_cat_sub_id(const uint8_t cat_id, const uint8_t sub_id, SignalDef& signal_def)
{
    if (cat_id == 0 && sub_id == 0)
    {
        signal_def = SIGNAL_DEF_NULL;
        return true;
    }
    else if (cat_id == 10 && sub_id == 10)
    {
        signal_def = SIGNAL_DEF_GPS_LATITUDE;
        return true;
    }
    else if (cat_id == 10 && sub_id == 11)
    {
        signal_def = SIGNAL_DEF_GPS_LONGITUDE;
        return true;
    }
    else if (cat_id == 10 && sub_id == 20)
    {
        signal_def = SIGNAL_DEF_ALTITUDE_MSL;
        return true;
    }
    else if (cat_id == 10 && sub_id == 21)
    {
        signal_def = SIGNAL_DEF_ALTITUDE_AGL;
        return true;
    }
    else if (cat_id == 10 && sub_id == 22)
    {
        signal_def = SIGNAL_DEF_ALTITUDE_RATE;
        return true;
    }
    else if (cat_id == 10 && sub_id == 23)
    {
        signal_def = SIGNAL_DEF_VERTICAL_SPEED;
        return true;
    }
    else if (cat_id == 10 && sub_id == 30)
    {
        signal_def = SIGNAL_DEF_HEADING_TRUE;
        return true;
    }
    else if (cat_id == 10 && sub_id == 31)
    {
        signal_def = SIGNAL_DEF_HEADING_MAG;
        return true;
    }
    else if (cat_id == 10 && sub_id == 32)
    {
        signal_def = SIGNAL_DEF_GROUND_TRACK;
        return true;
    }
    else if (cat_id == 10 && sub_id == 33)
    {
        signal_def = SIGNAL_DEF_MAGNETIC_VARIATION;
        return true;
    }
    else if (cat_id == 10 && sub_id == 40)
    {
        signal_def = SIGNAL_DEF_ATT_PITCH;
        return true;
    }
    else if (cat_id == 10 && sub_id == 41)
    {
        signal_def = SIGNAL_DEF_ATT_ROLL;
        return true;
    }
    else if (cat_id == 10 && sub_id == 50)
    {
        signal_def = SIGNAL_DEF_SPEED_IAS;
        return true;
    }
    else if (cat_id == 10 && sub_id == 51)
    {
        signal_def = SIGNAL_DEF_SPEED_GS;
        return true;
    }
    else if (cat_id == 20 && sub_id == 10)
    {
        signal_def = SIGNAL_DEF_ENGINE_RPM;
        return true;
    }
    else if (cat_id == 20 && sub_id == 20)
    {
        signal_def = SIGNAL_DEF_OIL_PRESSURE;
        return true;
    }
    else if (cat_id == 20 && sub_id == 21)
    {
        signal_def = SIGNAL_DEF_OIL_TEMPERATURE;
        return true;
    }
    else
    {
        return false;
    }
}
