"""

"""

import pathlib
import typing

import os

from .signal_definition import SignalDefinition


class SignalList:
    """
    Class to maintain signals present within a signal list file
    """

    def __init__(
            self,
            version: int,
            definitions: typing.Dict[str, SignalDefinition]):
        """
        Initializes the signal list object from the provided input definitions
        :param version: the version of the signal list file
        :param definitions: the signal list definitions to use
        """
        self.version = version
        self.definitions = definitions

    def get_definition(self, name: str) -> SignalDefinition:
        """
        Provides the signal for a given signal name in the dictionary
        :param name: signal definition to get from the dictionary
        :return: signal definition for the signal if in the dictionary
        """
        if name in self.definitions:
            return self.definitions[name]
        else:
            raise ValueError('No signal with name "{:s}" found in list'.format(name))

    @staticmethod
    def from_file(file: typing.Union[os.PathLike, pathlib.Path]) -> 'SignalList':
        """
        Creates a signal list object from the data within the provided text file
        :param file: the file to read into the signal list
        """
        # Read file data
        with open(os.fspath(file), 'r') as f:
            data = f.read()

        # Generate the signal list
        return SignalList.from_csv(data=data)

    @staticmethod
    def from_csv(data: str) -> 'SignalList':
        """
        Creates a signal list object from a provided CSV text string
        :param data: the CSV data to read
        :return: the corresponding signal list object
        """
        # Create the definition list
        def_list = dict()
        version = None

        # Set a boolean to toggle the first line
        first_line = True

        # Iterate over all parameters in the signal list
        for line in [l for l in data.splitlines()]:
            # Ignore comment lines
            if list(line)[0] == '#':
                continue

            # Set the version number from the first line
            if first_line:
                version = int(line.replace(',', ''))
                first_line = False
            # Otherwise, read in the signals
            else:
                s_def = SignalDefinition.from_csv_line(line)

                if s_def.name in def_list:
                    raise ValueError('Cannot have to signals with the same definition in the signal list')
                else:
                    def_list[s_def.name] = s_def

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

