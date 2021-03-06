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

from .signal_definition import SignalDefinition


class SignalFixedDefinition(SignalDefinition):
    """
    Class to maintain the definition for an analog signal type
    """

    def __init__(
            self,
            cat_id: int,
            sub_id: int,
            name: str,
            unit: str,
            sig_type: str,
            timeout_msec: int,
            resolution: float):
        """
        Creates a signal definition for the provided input parameters
        :param cat_id: the category ID for the signal
        :param sub_id: the signal ID for the signal
        :param unit: the unit associated with the signal
        :param sig_type: the signal type
        :param timeout_msec: the number of milliseconds until timeout for the signal
        :param resolution: the resolution to multiply network data by to get the engineering data
        """
        super().__init__(cat_id, sub_id, name, unit, sig_type, timeout_msec)
        self.resolution = resolution

    def generate_cpp_code(self) -> str:
        """
        Generates C++ Code for the given packet type
        :return: C++ code for the current signal type
        """
        raise NotImplementedError()

