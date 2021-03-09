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

SignalList provides basic information for reading and processing a signal list file and generating code
"""

import json
import os
import pathlib
import typing

from .signal_def_base import SignalDefinitionBase
from .signal_def_scaled import SignalDefinitionScaled


class SignalList:
    """
    Class to maintain signals present within a signal list file
    """

    def __init__(
            self,
            version: int,
            definitions: typing.Dict[str, SignalDefinitionBase]):
        """
        Initializes the signal list object from the provided input definitions
        :param version: the version of the signal list file
        :param definitions: the signal list definitions to use
        """
        self.version = version
        self.definitions: typing.Dict[str, SignalDefinitionBase] = definitions

    def get_definition(self, name: str) -> SignalDefinitionBase:
        """
        Provides the signal for a given signal name in the dictionary
        :param name: signal definition to get from the dictionary
        :return: signal definition for the signal if in the dictionary
        """
        if name in self.definitions:
            return self.definitions[name]
        else:
            raise ValueError('No signal with name "{:s}" found in list'.format(name))

    def get_sorted_definitions(self) -> typing.List[SignalDefinitionBase]:
        """
        Provides a list of the signal definitions, sorted by ID value
        :return: the signal definition list sorted by ID value
        """
        overall_list: typing.List[SignalDefinitionBase] = list(self.definitions.values())
        overall_list.sort(key=lambda x: x.cat_id * 256 + x.sub_id)
        return overall_list

    @staticmethod
    def from_json(file: typing.Union[pathlib.Path, os.PathLike]) -> 'SignalList':
        """
        Creates a signal list object from a provided JSON text string
        :param file: the file to read into the signal list
        :return: the corresponding signal list object
        """
        # Read the JSON data
        with open(os.fspath(file), 'r') as f:
            data = json.load(f)

        # Create the definition list
        def_list = dict()
        version = data['version']

        # Read in each signal
        for sig_def in data['signals']:
            # Extract the signal type
            sig_type = sig_def['type']

            # Switch based on the signal type
            if sig_type == 'base':
                sig_type_obj = SignalDefinitionBase
            elif sig_type == 'scaled':
                sig_type_obj = SignalDefinitionScaled
            else:
                raise ValueError('Signal type "{:s}" unknown'.format(sig_type))

            # Call the constructor and create the signal
            created_signal = sig_type_obj.from_json_def(sig_def=sig_def)

            # Check that the signal doesn't already exist in the database
            if created_signal.name in def_list:
                raise ValueError('Database contains two values for {:s}'.format(created_signal.name))
            else:
                def_list[created_signal.name] = created_signal

        # Run another check to make sure that no signals have duplicate ids
        for key_i in def_list.keys():
            for key_j in def_list.keys():
                if key_i == key_j:
                    continue
                else:
                    s1 = def_list[key_i]
                    s2 = def_list[key_j]

                    if s1.cat_id == s2.cat_id and s1.sub_id == s2.sub_id:
                        raise ValueError('Cannot have two signals with the same category and signal ids')

        # Check to ensure that the version is valid
        if version is None or not isinstance(version, int) or version <= 0:
            raise ValueError('Signal List version must be an integer > 0')

        # Otherwise, return the results
        return SignalList(
            version=version,
            definitions=def_list)
