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
from .codegen_file import CodegenSection, CodegenSingle
from .codegen_cpp_utils import CodegenCppIfMatchFunction, CodegenFileCppHeader, CodegenFileCppSource
from .signal_def_base import SignalDefinitionBase
from .signal_def_scaled import SignalDefinitionScaled


def _get_namespace_name() -> str:
    """
    Provides the default namespace for the code generation
    :return: the default namespace
    """
    return 'efis_signals'


def _get_signal_version_name() -> str:
    """
    Defines the variable name to use for the signal version variable name
    :return: the signal version variable name
    """
    return 'SIGNAL_LIST_VERSION_NUM'


def _signal_def_name(signal: SignalDefinitionBase) -> str:
    """
    Provides a signal ID variable name
    :param signal: the signal to generate the name for
    :return: the associated variable name
    """
    return 'SIGNAL_DEF_{:s}'.format(signal.name.upper())


def _signal_var_name(signal: SignalDefinitionBase) -> str:
    """
    Provides a signal definition variable name
    :param signal: the signal to generate the name for
    :return: the associated variable name
    """
    return 'signal_{:s}'.format(signal.name.lower())


def _func_signal_def_for_name_callable(signal: SignalDefinitionBase) -> typing.Tuple[str, typing.List[str]]:
    """
    # TODO
    :param signal:
    :return:
    """
    conditional = 'name == "{:s}"'.format(signal.name)
    statements = [
        'signal_def = {:s};'.format(_signal_def_name(signal)),
        'return true;'
    ]
    return conditional, statements


def _func_signal_name_for_def_callable(signal: SignalDefinitionBase) -> typing.Tuple[str, typing.List[str]]:
    """
    TODO
    :param signal:
    :return:
    """
    conditional = 'signal_def == {:s}'.format(_signal_def_name(signal))
    statements = [
        'name = "{:s}";'.format(signal.name),
        'return true;'
    ]
    return conditional, statements


def _func_signal_name_for_cat_sub_id_callable(signal: SignalDefinitionBase) -> typing.Tuple[str, typing.List[str]]:
    """
    TODO
    :param signal:
    :return:
    """
    conditional = 'cat_id == {:d} && sub_id == {:d}'.format(signal.cat_id, signal.sub_id)
    statements = [
        'signal_def = {:s};'.format(_signal_def_name(signal)),
        'return true;'
    ]
    return conditional, statements


FUNC_SIGNAL_DEF_FOR_NAME = CodegenCppIfMatchFunction(
    name='get_signal_def_for_name',
    namespace=_get_namespace_name(),
    result='bool',
    parameters=['const std::string& name', 'SignalDef& signal_def'],
    if_callable=_func_signal_def_for_name_callable,
    default=['return false;'],
    description=[
        '/**',
        ' * @brief <NAME> provides the signal definition for the provided name',
        ' * @param name is the name of the signal to find',
        ' * @param signal provides the resulting signal definition if found',
        ' * @return true if a signal for the given name is found',
        ' */'])

FUNC_SIGNAL_NAME_FOR_DEF = CodegenCppIfMatchFunction(
    name='get_signal_name_for_def',
    namespace=_get_namespace_name(),
    result='bool',
    parameters=['const SignalDef& signal_def', 'std::string name'],
    if_callable=_func_signal_name_for_def_callable,
    default=['return false;'],
    description=[
        '/**',
        ' * @brief <NAME> provides the name of the signal',
        ' * @param signal_def is the signal definition to try to find a name for',
        ' * @param name provides the name of the signal if found',
        ' * @return true if a name for the given signal is found',
        ' */'])


FUNC_SIGNAL_DEF_FOR_CAT_SUB_ID = CodegenCppIfMatchFunction(
    name='get_signal_for_cat_sub_id',
    namespace=_get_namespace_name(),
    result='bool',
    parameters=['const uint8_t cat_id', 'const uint8_t sub_id', 'SignalDef& signal_def'],
    if_callable=_func_signal_name_for_cat_sub_id_callable,
    default=['return false;'],
    description=[
        '/**',
        ' * @brief <NAME> provides the name of the signal',
        ' * @param cat_id is the category ID of the signal to search for',
        ' * @param sub_id is the subcategory ID of the signal to search for',
        ' * @param signal_def provides the signal definition if found',
        ' * @return true if a name for the given signal is found',
        ' */'])


def _generate_signal_def_hdr() -> CodegenFileCppHeader:
    """
    Provides the code generator required to generate the signal Def header file,
    for gen_signal_def.h
    :return: the associated C++ header code generator
    """
    # Define the generated Signal Definition header class instance
    def signal_def_extern_printer(_, __, signal: SignalDefinitionBase) -> typing.List[str]:
        return [
            '/**',
            ' * @brief {0:s} is the signal for the {1:s}'.format(
                _signal_def_name(signal=signal),
                signal.description),
            ' */',
            'extern const SignalDef {0:s};'.format(_signal_def_name(signal=signal))]

    # Define the signal ID printer
    codegen = CodegenFileCppHeader(
        base_name='signal_def',
        namespace=_get_namespace_name())

    # Add the signal list version value
    codegen.add_section(
        section=CodegenSingle(
            printer=lambda _: ['extern const uint32_t {:s};'.format(_get_signal_version_name())]))

    # Add the signal definition list printer
    codegen.add_section(section=CodegenSection(signal_printer=signal_def_extern_printer))

    # Add signal definition functions
    codegen.add_section(section=FUNC_SIGNAL_DEF_FOR_NAME.codegen_for_header())
    codegen.add_section(section=FUNC_SIGNAL_NAME_FOR_DEF.codegen_for_header())
    codegen.add_section(section=FUNC_SIGNAL_DEF_FOR_CAT_SUB_ID.codegen_for_header())

    # Add include parameters
    codegen.add_include_file('signal_def.h')
    codegen.add_include_file('string', system=True)

    # Return the code generator
    return codegen


def _generate_signal_def_src() -> CodegenFileCppSource:
    """
    Provides the code generator required to generate the signal ID source file,
    for gen_signal_def.cpp
    :return: the associated C++ source code generator
    """
    # Define the code generator and the associated constructor section
    codegen = CodegenFileCppSource(
        base_name='signal_def',
        namespace=_get_namespace_name())

    # Add the section for the signal version number
    codegen.add_section(
        section=CodegenSingle(
            printer=lambda signal_list: [
                'const uint32_t {0:s}::{1:s} = {2:d};'.format(
                    _get_namespace_name(),
                    _get_signal_version_name(),
                    signal_list.version)]))

    # Add the constructor section for the different signal definition constructors
    def signal_def_constructor_printer(_, __, signal: SignalDefinitionBase) -> typing.List[str]:
        return [
            'const SignalDef {0:s}::{1:s}({2:d}, {3:d}, {4:d});'.format(
                _get_namespace_name(),
                _signal_def_name(signal=signal),
                signal.cat_id,
                signal.sub_id,
                signal.timeout_milliseconds)]

    codegen.add_section(section=CodegenSection(signal_printer=signal_def_constructor_printer))

    # Add signal definition functions
    codegen.add_section(section=FUNC_SIGNAL_DEF_FOR_NAME.section_for_source())
    codegen.add_section(section=FUNC_SIGNAL_NAME_FOR_DEF.section_for_source())
    codegen.add_section(section=FUNC_SIGNAL_DEF_FOR_CAT_SUB_ID.section_for_source())

    # Add include parameters
    codegen.add_include_file('gen_signal_def.h')

    # Return the code generator
    return codegen


def _generate_signal_db_src() -> CodegenFileCppSource:
    """
    Provides the code generator required to generate the signal database file,
    for gen_signal_database.cpp
    :return: the associated C++ source code generator
    """
    # Define the codegen C++ file
    codegen = CodegenFileCppSource(
        base_name='signal_database',
        namespace=_get_namespace_name())

    # Define the function definition section
    def signal_static_func_printer(_, __, signal: SignalDefinitionBase) -> typing.List[str]:
        # Define the type of the signal based on the definition type
        constructor_args = [_signal_def_name(signal=signal)]

        if isinstance(signal, SignalDefinitionScaled):
            signal_type = 'SignalTypeScaled'
            constructor_args.append('{:.24e}'.format(signal.resolution))
        elif type(signal) == SignalDefinitionBase:
            signal_type = 'SignalTypeBase'
        else:
            raise NotImplementedError()

        # Add parameters to the list
        src_list = list()
        src_list.append('    static {0:s} {1:s}({2:});'.format(
            signal_type,
            _signal_var_name(signal=signal),
            ', '.join(constructor_args)))
        src_list.append('    signal_array[{0:s}.signal_index()] = dynamic_cast<SignalTypeBase*>(&{1:});'.format(
            _signal_def_name(signal=signal),
            _signal_var_name(signal=signal)))

        # Add indentation and return
        return src_list

    func_sec = CodegenSection(signal_printer=signal_static_func_printer)
    func_sec.init_callable = lambda _: [
        'void SignalDatabase::init_signals()',
        '{']
    func_sec.end_callable = lambda _: [
        '}',
        '']
    codegen.add_section(section=func_sec)

    # Add required include files
    codegen.add_include_file('signal_database.h')
    codegen.add_include_file('signal_type_base.h')
    codegen.add_include_file('signal_type_scaled.h')
    codegen.add_include_file('gen_signal_def.h')

    # Return the generator
    return codegen


def generate_cpp_code(signal_list: SignalList, target_dir: pathlib.Path) -> None:
    """
    Generates C++ Code for the provided signal list in the provided target directory
    :param signal_list: the signal list to generate code for
    :param target_dir: the target directory to put the generated code in
    """
    # Run the code generation for each individual file
    for codegen in (_generate_signal_def_hdr(), _generate_signal_def_src(), _generate_signal_db_src()):
        codegen.generate_code(
            target_dir=target_dir,
            signal_list=signal_list)
