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

import typing

JSON_DICT_TYPE = typing.Dict[str, typing.Union[str, float, int]]


class SignalDefinitionBase:
    """
    Class to maintain the definition for a signal type
    """

    def __init__(
            self,
            cat_id: int,
            sub_id: int,
            name: str,
            description: str,
            timeout_millisecond: int):
        """
        Creates a signal definition for the provided input parameters
        :param cat_id: the category ID for the signal
        :param sub_id: the signal ID for the signal
        :param name: the name of the signal
        :param description: the description for the signal
        :param timeout_millisecond: the number of milliseconds until timeout for the signal
        """
        self.cat_id = cat_id
        self.sub_id = sub_id
        self.name = name
        self.description = description
        self.timeout_millisecond = timeout_millisecond

    @staticmethod
    def _get_base_args(sig_def: JSON_DICT_TYPE) -> JSON_DICT_TYPE:
        """
        Parses and returns a dictionary of the base arguments for a signal
        :param sig_def: the JSON dictionary definition for the signal
        :return: common input arguments for the dictionary signal
        """
        return {
            'cat_id': int(sig_def['cat_id']),
            'sub_id': int(sig_def['sub_id']),
            'name': sig_def['name'],
            'description': sig_def['description'],
            'timeout_millisecond': int(sig_def['timeout'])
        }

    @staticmethod
    def from_json_def(sig_def: JSON_DICT_TYPE) -> 'SignalDefinitionBase':
        """
        Provides a signal definition from a single comma-separated line of the signal list, in the form
          CategoryID,SubID,Name,Units,Type,TimeoutMillisecond
        :param sig_def: the JSON dictionary definition for the signal
        :return: the signal definition for the values found in the line
        """
        return SignalDefinitionBase(**SignalDefinitionBase._get_base_args(sig_def=sig_def))
