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

SignalDefinition provides the overall signal definition parameters for a generic
signal type within the TeaFIS project
"""


class SignalDefinition:
    """
    Class to maintain the definition for a signal type
    """

    def __init__(
            self,
            cat_id: int,
            sub_id: int,
            name: str,
            unit: str,
            sig_type: str,
            timeout_millisecond: int):
        """
        Creates a signal definition for the provided input parameters
        :param cat_id: the category ID for the signal
        :param sub_id: the signal ID for the signal
        :param unit: the unit associated with the signal
        :param sig_type: the signal type
        :param timeout_millisecond: the number of milliseconds until timeout for the signal
        """
        self.cat_id = cat_id
        self.sub_id = sub_id
        self.name = name
        self.unit = unit
        self.sig_type = sig_type
        self.timeout_millisecond = timeout_millisecond

    def generate_cpp_code(self) -> str:
        """
        Generates C++ Code for the given packet type
        :return: C++ code for the current signal type
        """
        raise NotImplementedError()

    @staticmethod
    def from_csv_line(line: str) -> 'SignalDefinition':
        """
        Provides a signal definition from a single comma-separated line of the signal list, in the form
          CategoryID,SubID,Name,Units,Type,TimeoutMillisecond
        :param line: the line to extract the signal definition from
        :return: the signal definition for the values found in the line
        """
        # Split the input line by commas
        words = [word.strip() for word in line.split(',')]

        # Ensure that there is the expected number of parameters
        if len(words) != 7:
            raise ValueError('Invalid number of parameters found in the line, expecting 6, got {:d}'.format(len(words)))

        # Extract the signal parameters
        cat_id = int(words[0])
        sub_id = int(words[1])
        name = words[2]
        unit = words[3]
        sig_type = words[4]
        timeout_millisecond = int(words[5])

        if words[6] == 'semi2deg':
            resolution = 180.0 / 2**31
        else:
            resolution = float(words[6])

        # Return the signal type based on the provided definition
        if sig_type == 'fixed':
            from .signal_type_fixed import SignalFixedDefinition
            return SignalFixedDefinition(
                cat_id=cat_id,
                sub_id=sub_id,
                name=name,
                unit=unit,
                sig_type=sig_type,
                timeout_millisecond=timeout_millisecond,
                resolution=resolution)
        else:
            raise RuntimeError('Signal type {:s} is not yet supported'.format(sig_type))
