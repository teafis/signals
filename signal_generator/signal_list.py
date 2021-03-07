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

import pathlib
import typing

import os

from .codegen_type import CodeGenType
from .signal_definition import SignalDefinition
from .signal_type_fixed import SignalFixedDefinition


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

    def generate_code(
            self,
            target: CodeGenType,
            target_dir: pathlib.Path) -> None:
        """
        Generates the SignalList code associated with the provided code generation target type in the target directory
        :param target: the code generation target type to use
        :param target_dir: the target directory to place generated source files within
        """
        from . import codegen_file

        if not target_dir.exists() or not target_dir.is_dir():
            raise ValueError('Target directory must be an existing file')

        if target == CodeGenType.CPP:
            # Define common functions for different types of signal to provide variable names
            def signal_id_name(signal: SignalDefinition) -> str:
                return 'SIGNAL_ID_{:s}'.format(signal.name.upper())

            def signal_var_name(signal: SignalDefinition) -> str:
                return 'signal_{:s}'.format(signal.name.lower())

            # Define the generated SignalID header class instance
            def signal_id_hdr_printer(signal: SignalDefinition) -> typing.List[str]:
                return [
                    'extern const SignalID {0:s};'.format(
                        signal_id_name(signal=signal))
                ]

            signal_id_hdr = codegen_file.CodegenFileCppHeader(
                base_name='signal_id',
                signal_printer=signal_id_hdr_printer)
            signal_id_hdr.add_include_file('signal_id.h')

            # Define the generated SignalID source class instance
            def signal_id_src_printer(signal: SignalDefinition) -> typing.List[str]:
                return [
                    'const SignalID {0:s}::{1:s}({2:d}, {3:d});'.format(
                        codegen_file.CodegenFileCpp.NAMESPACE_NAME,
                        signal_id_name(signal=signal),
                        signal.cat_id,
                        signal.sub_id)
                    ]

            signal_id_src = codegen_file.CodegenFileCppSource(
                base_name='signal_id',
                signal_printer=signal_id_src_printer)
            signal_id_src.add_include_file('gen_signal_id.h')

            # Define the generated Signal Database source class instance
            def signal_db_src_printer(signal: SignalDefinition) -> typing.List[str]:
                if isinstance(signal, SignalFixedDefinition):
                    return ['    {:s}'.format(s) for s in [
                        'static SignalFixed {0:s}({1:s}, {2:.24e});'.format(
                            signal_var_name(signal=signal),
                            signal_id_name(signal=signal),
                            signal.resolution),
                        'signal_array[{0:s}.signal_index()] = dynamic_cast<BaseSignal*>(&{1:});'.format(
                            signal_id_name(signal=signal),
                            signal_var_name(signal=signal))
                        ]]
                else:
                    raise NotImplementedError()

            signal_db_src = codegen_file.CodegenFileCppSource(
                base_name='signal_database',
                signal_printer=signal_db_src_printer)
            signal_db_src.add_include_file('signal_database.h')
            signal_db_src.add_include_file('signal_fixed.h')
            signal_db_src.add_include_file('gen_signal_id.h')

            def signal_db_src_init_extra():
                return [
                    'void SignalDatabase::init_signals()',
                    '{'
                ]

            signal_db_src.print_init_extra = signal_db_src_init_extra

            def signal_db_src_end_extra():
                return [
                    '}',
                    ''
                ]

            signal_db_src.print_end_extra = signal_db_src_end_extra

            # Run the code generation for each individual file
            for codegen in [signal_id_hdr, signal_id_src, signal_db_src]:
                codegen.generate_signal_list(
                    target_dir=target_dir,
                    signal_list=self)
        else:
            raise NotImplementedError()

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
        for line in [line for line in data.splitlines()]:
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
