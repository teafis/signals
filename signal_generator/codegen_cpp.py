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

Codegen Cpp Provides information responsible for generating C++
code for the associated signal parameters
"""

import pathlib
import typing

from .signal_list import SignalList
from .codegen_file import CodegenFileCppHeader, CodegenFileCppSource, CodegenSection
from .signal_def_base import SignalDefinitionBase
from .signal_def_fixed import SignalDefinitionFixed


def _get_namespace_name() -> str:
    """
    Provides the default namespace for the code generation
    :return: the default namespace
    """
    return 'efis_signals'


def _signal_id_name(signal: SignalDefinitionBase) -> str:
    """
    Provides a signal ID variable name
    :param signal: the signal to generate the name for
    :return: the associated variable name
    """
    return 'SIGNAL_ID_{:s}'.format(signal.name.upper())


def _signal_var_name(signal: SignalDefinitionBase) -> str:
    """
    Provides a signal definition variable name
    :param signal: the signal to generate the name for
    :return: the associated variable name
    """
    return 'signal_{:s}'.format(signal.name.lower())


def _empty_printer(*_) -> typing.List[str]:
    """
    Provides a printer to perform no additions for each signal parameter
    :param _: variable argument input to be ignored
    :return: an empty list
    """
    return list()


def _get_find_func_sig(with_namespace: bool) -> str:
    """
    Determines the function signature for the get_signal_id_for_name function
    :param with_namespace: determines if the namespace should be added
    :return: the associated function signature
    """
    if with_namespace:
        namespace_sec = '{:s}::'.format(_get_namespace_name())
    else:
        namespace_sec = ''

    return 'bool {:s}get_signal_id_for_name(const std::string& name, SignalID& signal)'.format(namespace_sec)


def _get_find_name_func_sig(with_namespace: bool) -> str:
    """
    Determines the function signature for the get_name_for_signal_id function
    :param with_namespace: determines if the namespace should be added
    :return: the associated function signature
    """
    if with_namespace:
        namespace_sec = '{:s}::'.format(_get_namespace_name())
    else:
        namespace_sec = ''

    return 'bool {:s}get_name_for_signal_id(const SignalID& signal_id, std::string name)'.format(namespace_sec)


def _generate_signal_id_hdr() -> CodegenFileCppHeader:
    """
    Provides the code generator required to generate the signal ID header file,
    for gen_signal_id.h
    :return: the associated C++ header code generator
    """
    # Define the generated SignalID header class instance
    def signal_id_extern_printer(_, signal: SignalDefinitionBase) -> typing.List[str]:
        return [
            'extern const SignalID {0:s};'.format(_signal_id_name(signal=signal))]

    # Define the signal ID printer
    codegen = CodegenFileCppHeader(
        base_name='signal_id',
        namespace=_get_namespace_name())
    codegen.add_section(section=CodegenSection(signal_printer=signal_id_extern_printer))

    # Add the section for the get-id by name function
    get_by_name_sig_sec = CodegenSection(signal_printer=_empty_printer)
    get_by_name_sig_sec.init_list = ['{:s};'.format(_get_find_func_sig(with_namespace=False))]
    codegen.add_section(section=get_by_name_sig_sec)

    # Add the section for the get-name function
    get_id_name_sig_sec = CodegenSection(signal_printer=_empty_printer)
    get_id_name_sig_sec.init_list = ['{:s};'.format(_get_find_name_func_sig(with_namespace=False))]
    codegen.add_section(section=get_id_name_sig_sec)

    # Add include parameters
    codegen.add_include_file('signal_id.h')
    codegen.add_include_file('string', system=True)

    # Return the code generator
    return codegen


def _generate_signal_id_src() -> CodegenFileCppSource:
    """
    Provides the code generator required to generate the signal ID source file,
    for gen_signal_id.cpp
    :return: the associated C++ source code generator
    """
    # Define the generated SignalID source class instance
    def signal_id_constructor_printer(_, signal: SignalDefinitionBase) -> typing.List[str]:
        return [
            'const SignalID {0:s}::{1:s}({2:d}, {3:d});'.format(
                _get_namespace_name(),
                _signal_id_name(signal=signal),
                signal.cat_id,
                signal.sub_id)
            ]

    # Define the code generator and the associated constructor section
    codegen = CodegenFileCppSource(
        base_name='signal_id',
        namespace=_get_namespace_name())
    codegen.add_section(section=CodegenSection(signal_printer=signal_id_constructor_printer))

    # Define and add the section for the get-id by name function
    def func_get_id_printer(index: int, signal: SignalDefinitionBase) -> typing.List[str]:
        if index == 0:
            if_val = 'if'
        else:
            if_val = 'else if'

        return [
            '{0:s} (name == "{1:s}")'.format(if_val, signal.name),
            '{',
            '    signal = {0:s};'.format(_signal_id_name(signal)),
            '    return true;',
            '}'
        ]

    func_get_id_sec = CodegenSection(
        signal_printer=func_get_id_printer,
        indent=1,
        add_printer_item_separation=False)
    func_get_id_sec.init_list = [
        '{:s}'.format(_get_find_func_sig(with_namespace=True)),
        '{']
    func_get_id_sec.end_indent_list = [
        'else',
        '{',
        '    return false;',
        '}']
    func_get_id_sec.end_list = ['}']
    codegen.add_section(func_get_id_sec)

    # Define and add the section for the get-name from ID  function
    def func_get_name_printer(index: int, signal: SignalDefinitionBase) -> typing.List[str]:
        if index == 0:
            if_val = 'if'
        else:
            if_val = 'else if'

        return [
            '{0:s} (signal_id == {1:})'.format(if_val, _signal_id_name(signal)),
            '{',
            '    name = "{0:s}";'.format(signal.name),
            '    return true;',
            '}'
        ]

    func_get_name_sec = CodegenSection(
        signal_printer=func_get_name_printer,
        indent=1,
        add_printer_item_separation=False)
    func_get_name_sec.init_list = [
        '{:s}'.format(_get_find_name_func_sig(with_namespace=True)),
        '{']
    func_get_name_sec.end_indent_list = [
        'else',
        '{',
        '    return false;',
        '}']
    func_get_name_sec.end_list = ['}']
    codegen.add_section(func_get_name_sec)

    # Add include parameters
    codegen.add_include_file('gen_signal_id.h')

    # Return the code generator
    return codegen


def _generate_signal_db_src() -> CodegenFileCppSource:
    """
    Provides the code generator required to generate the signal database file,
    for gen_signal_database.cpp
    :return: the associated C++ source code generator
    """
    # Define the generated Signal Database source class instance
    def signal_static_func_printer(_, signal: SignalDefinitionBase) -> typing.List[str]:
        # Define the return list
        src_list = list()

        # Define the type of the signal based on the definition type
        constructor_args = [_signal_id_name(signal=signal)]

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
            _signal_var_name(signal=signal),
            ', '.join(constructor_args)))
        src_list.append('signal_array[{0:s}.signal_index()] = dynamic_cast<SignalTypeBase*>(&{1:});'.format(
            _signal_id_name(signal=signal),
            _signal_var_name(signal=signal)))

        # Add indentation and return
        return src_list

    # Define the codegen C++ file
    codegen = CodegenFileCppSource(
        base_name='signal_database',
        namespace=_get_namespace_name())

    # Define the function definition section
    func_sec = CodegenSection(
        signal_printer=signal_static_func_printer,
        indent=1)
    func_sec.init_list = [
        'void SignalDatabase::init_signals()',
        '{']
    func_sec.end_list = [
        '}',
        '']
    codegen.add_section(section=func_sec)

    # Add required include files
    codegen.add_include_file('signal_database.h')
    codegen.add_include_file('signal_type_base.h')
    codegen.add_include_file('signal_type_fixed.h')
    codegen.add_include_file('gen_signal_id.h')

    # Return the generator
    return codegen


def generate_cpp_code(signal_list: SignalList, target_dir: pathlib.Path) -> None:
    """
    Generates C++ Code for the provided signal list in the provided target directory
    :param signal_list: the signal list to generate code for
    :param target_dir: the target directory to put the generated code in
    """
    # Run the code generation for each individual file
    for codegen in (_generate_signal_id_hdr(), _generate_signal_id_src(), _generate_signal_db_src()):
        codegen.generate_code(
            target_dir=target_dir,
            signal_list=signal_list)
