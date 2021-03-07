"""
TeaFIS is a cockpit display for aircraft
Copyright (C) 2021  Ian O'Rourke

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

SignalFixed defines the fixed-resolution signal definition
"""

import typing

from .signal_def_base import SignalDefinitionBase


class SignalDefinitionFixed(SignalDefinitionBase):
    """
    Class to maintain the definition for an analog signal type
    """

    # Define the resolution map
    RESOLUTION_MAP = {
        'semi2deg': 180.0 / 2**31
    }

    def __init__(
            self,
            cat_id: int,
            sub_id: int,
            name: str,
            description: str,
            timeout_millisecond: int,
            units: str,
            resolution: float):
        """
        Creates a signal definition for the provided input parameters
        :param cat_id: the category ID for the signal
        :param sub_id: the signal ID for the signal
        :param name: the name of the signal
        :param description: the description for the signal
        :param timeout_millisecond: the number of milliseconds until timeout for the signal
        :param units: the unit associated with the signal
        :param resolution: the resolution to multiply network data by to get the engineering data
        """
        super().__init__(
            cat_id=cat_id,
            sub_id=sub_id,
            name=name,
            description=description,
            timeout_millisecond=timeout_millisecond)
        self.units = units
        self.resolution = resolution

    @staticmethod
    def from_json_def(sig_def: typing.Dict[str, typing.Union[str, float, int]]) -> 'SignalDefinitionBase':
        """
        Provides a signal definition from a single comma-separated line of the signal list, in the form
          CategoryID,SubID,Name,Units,Type,TimeoutMillisecond
        :param sig_def: the JSON dictionary definition for the signal
        :return: the signal definition for the values found in the line
        """
        resolution = sig_def['resolution']
        if isinstance(resolution, str):
            resolution = SignalDefinitionFixed.RESOLUTION_MAP[resolution]
        else:
            resolution = float(resolution)

        return SignalDefinitionFixed(
            units=sig_def['units'],
            resolution=resolution,
            **SignalDefinitionFixed._get_base_args(sig_def=sig_def))
