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

from .codegen_type import CodeGenType

from .signal_def_base import SignalDefinitionBase
from .signal_def_fixed import SignalDefinitionFixed


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
            def signal_id_name(signal: SignalDefinitionBase) -> str:
                return 'SIGNAL_ID_{:s}'.format(signal.name.upper())

            def signal_var_name(signal: SignalDefinitionBase) -> str:
                return 'signal_{:s}'.format(signal.name.lower())

            # Define the generated SignalID header class instance
            def signal_id_hdr_printer(_, signal: SignalDefinitionBase) -> typing.List[str]:
                return [
                    'extern const SignalID {0:s};'.format(
                        signal_id_name(signal=signal))
                ]

            def empty_printer(*_) -> typing.List[str]:
                return list()

            signal_id_hdr = codegen_file.CodegenFileCppHeader(base_name='signal_id')
            signal_id_hdr.add_section(section=codegen_file.CodegenSection(signal_printer=signal_id_hdr_printer))

            def get_find_func_sig(with_namespace: bool) -> str:
                return 'bool {:s}get_signal_id_for_name(const std::string& name, SignalID& signal)'.format(
                    '{:s}::'.format(codegen_file.CodegenFileCpp.NAMESPACE_NAME) if with_namespace else '')

            signal_id_hdr_func_sect = codegen_file.CodegenSection(signal_printer=empty_printer)
            signal_id_hdr_func_sect.init_list = ['{:s};'.format(get_find_func_sig(with_namespace=False))]
            signal_id_hdr.add_section(section=signal_id_hdr_func_sect)

            signal_id_hdr.add_include_file('signal_id.h')
            signal_id_hdr.add_include_file('string', system=True)

            # Define the generated SignalID source class instance
            def signal_id_src_printer(_, signal: SignalDefinitionBase) -> typing.List[str]:
                return [
                    'const SignalID {0:s}::{1:s}({2:d}, {3:d});'.format(
                        codegen_file.CodegenFileCpp.NAMESPACE_NAME,
                        signal_id_name(signal=signal),
                        signal.cat_id,
                        signal.sub_id)
                    ]

            signal_id_src = codegen_file.CodegenFileCppSource(base_name='signal_id')
            signal_id_src.add_section(section=codegen_file.CodegenSection(signal_printer=signal_id_src_printer))

            def signal_id_src_func_printer(index: int, signal: SignalDefinitionBase) -> typing.List[str]:
                if index == 0:
                    if_val = 'if'
                else:
                    if_val = 'else if'

                return [
                    '{0:s} (name == "{1:s}")'.format(if_val, signal.name),
                    '{',
                    '    signal = {0:s};'.format(signal_id_name(signal)),
                    '    return true;',
                    '}'
                ]

            signal_id_src_func_sec = codegen_file.CodegenSection(signal_printer=signal_id_src_func_printer, indent=1, add_printer_item_separation=False)
            signal_id_src_func_sec.init_list = [
                '{:s}'.format(get_find_func_sig(with_namespace=True)),
                '{'
            ]

            signal_id_src_func_sec.end_indent_list = [
                'else',
                '{',
                '    return false;',
                '}'
            ]
            signal_id_src_func_sec.end_list = ['}']
            signal_id_src.add_section(signal_id_src_func_sec)

            signal_id_src.add_include_file('gen_signal_id.h')

            # Define the generated Signal Database source class instance
            def signal_db_src_printer(_, signal: SignalDefinitionBase) -> typing.List[str]:
                # Define the return list
                src_list = list()

                # Define the type of the signal based on the definition type
                constructor_args = [signal_id_name(signal=signal)]

                if isinstance(signal, SignalDefinitionFixed):
                    signal_type = 'SignalTypeFixed'
                    constructor_args.append('{:.24e}'.format(signal.resolution))
                elif type(signal) == SignalDefinitionBase:
                    signal_type = 'SignalTypeBase'
                else:
                    raise NotImplementedError()

                # Add parameters to the list
                src_list.append('static {0:s} {1:s}({2:});'.format(
                    signal_type,
                    signal_var_name(signal=signal),
                    ', '.join(constructor_args)))
                src_list.append('signal_array[{0:s}.signal_index()] = dynamic_cast<SignalTypeBase*>(&{1:});'.format(
                        signal_id_name(signal=signal),
                        signal_var_name(signal=signal)))

                # Add indentation and return
                return src_list

            signal_db_src = codegen_file.CodegenFileCppSource(base_name='signal_database')

            signal_db_src_sec = codegen_file.CodegenSection(
                signal_printer=signal_db_src_printer,
                indent=1)
            signal_db_src_sec.init_list = [
                'void SignalDatabase::init_signals()',
                '{'
            ]
            signal_db_src_sec.end_list = [
                '}',
                ''
            ]

            signal_db_src.add_section(section=signal_db_src_sec)

            signal_db_src.add_include_file('signal_database.h')
            signal_db_src.add_include_file('signal_type_base.h')
            signal_db_src.add_include_file('signal_type_fixed.h')
            signal_db_src.add_include_file('gen_signal_id.h')

            # Run the code generation for each individual file
            for codegen in [signal_id_hdr, signal_id_src, signal_db_src]:
                codegen.generate_signal_list(
                    target_dir=target_dir,
                    signal_list=self)
        else:
            raise NotImplementedError()

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
            elif sig_type == 'fixed':
                sig_type_obj = SignalDefinitionFixed
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
