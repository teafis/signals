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

Codegen File provides information pertaining to common functionality
between code generation files
"""

import pathlib
import typing

from .signal_def_base import SignalDefinitionBase
from .signal_list import SignalList

SignalPrinterCallable = typing.Callable[[int, SignalDefinitionBase], typing.List[str]]


class CodegenSection:
    """
    CodegenSection defines a section of code generation for a particular signal parameter
    """

    def __init__(self, signal_printer: SignalPrinterCallable, indent: int = 0, add_printer_item_separation: bool = True):
        self.indent = max(indent, 0)
        self.signal_printer = signal_printer
        self.item_separation = add_printer_item_separation

        self.init_list = list()
        self.end_list = list()

        self.init_indent_list = list()
        self.end_indent_list = list()

    def generate_for_signal_list(self, signal_list: SignalList) -> typing.List[str]:
        total_list = list()
        total_list.extend(self.init_list)

        def update_for_indent(input_list: typing.List[str]) -> typing.List[str]:
            if self.indent > 0:
                indent_str = '    ' * self.indent
                return ['{:s}{:s}'.format(indent_str, s) for s in input_list]
            else:
                return input_list

        total_list.extend(update_for_indent(self.init_indent_list))

        for i, signal in enumerate(signal_list.definitions.values()):
            # Determine the text to write for the signal
            signal_lines = update_for_indent(self.signal_printer(i, signal))

            # Add spacing if the number of signal lines is sufficient
            if i > 0 and len(signal_lines) > 1 and self.item_separation:
                total_list.append('')

            # Write the signal lines
            total_list.extend(signal_lines)

        total_list.extend(update_for_indent(self.end_indent_list))

        total_list.extend(self.end_list)

        return total_list


class CodegenFile:
    """
    CodegenFile defines the base code generation instance file and basic interface
    """

    def __init__(self, base_name: str):
        """
        Initializes the instance with a base name that will be used to generate parameter items and a signal printer
        function to be called for each signal in the list
        :param base_name: the base name of the generated file (signal_id or signal_database, for example)
        """
        # Save variables and initialize the list
        self.lines = list()
        self.base_name = base_name

        # Define sections
        self.sections: typing.List['CodegenSection'] = list()

    def add_section(self, section: 'CodegenSection') -> None:
        """
        Adds a code generation section to parameters to be output
        :param section: the section to add
        """
        self.sections.append(section)

    def _gen_base_name(self) -> str:
        """
        Defines the base source file name for generation
        :return: the generated base file name
        """
        return 'gen_{:s}'.format(self.base_name)

    def _print_init(self) -> None:
        """
        Interface instance to write initialization parameters to the source file
        """
        pass

    def _print_end(self) -> None:
        """
        Interface instance to write ending parameters to the source file
        By default will add an empty line if not already present
        """
        if len(self.lines) == 0 or len(self.lines[-1]) > 0:
            self.lines.append('')

    def clear(self) -> None:
        """
        Clears any text currently within the list
        """
        self.lines = list()

    @staticmethod
    def _date_string() -> str:
        """
        Provides a date string associated with the current UTC time
        :return: a string for the current UTC date and time
        """
        import datetime
        return datetime.datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S')

    def _gen_file_name(self) -> str:
        """
        An interface to provide the generated file's name
        :return: the filename to write the file to
        """
        raise NotImplementedError()

    def generate_code(
            self,
            target_dir: pathlib.Path,
            signal_list: SignalList) -> None:
        """
        Generates and writes the file from the provided signal list
        :param target_dir: the target directory to write to
        :param signal_list: the signal list to use
        """
        # Clear the text if values have already been written
        if len(self.lines) > 0:
            self.clear()

        # Write initial text to the file
        self._print_init()

        # Loop through each signal to add to the list
        for i, sec in enumerate(self.sections):
            # Add an empty line if needed
            if i > 0:
                self.lines.append('')

            # Determine the string list for the section
            section_lines = sec.generate_for_signal_list(signal_list=signal_list)

            # Add the section lines to the list
            self.lines.extend(section_lines)

        # Write final text to the output buffer
        self._print_end()

        # Strip any ending whitespace
        self.lines = [line.rstrip() for line in self.lines]

        # Write the file
        with (target_dir / self._gen_file_name()).open('w') as f:
            f.write('\n'.join(self.lines))


class CodegenFileCpp(CodegenFile):
    """
    Class instance for a Codegen file for the C++ language
    """

    def __init__(self, base_name: str, namespace: str):
        """
        Initializes the instance with a base name that will be used to generate parameter items and a signal printer
        function to be called for each signal in the list
        :param base_name: the base name of the generated file (signal_id or signal_database, for example)
        :param namespace: the namespace to associate with the current code generation file
        """
        super().__init__(base_name=base_name)
        self.includes = list()
        self.namespace = namespace

    def add_include_file(self, file: str, system: bool = False) -> None:
        """
        Adds a file to the list of preprocessor includes to use
        :param file: the file to include
        :param system: determines if the file is a system file
        """
        if not system:
            self.includes.append('#include "{:s}"'.format(file))
        else:
            self.includes.append('#include <{:s}>'.format(file))

    def _gen_file_name(self) -> str:
        """
        An interface to provide the generated file's name
        :return: the filename to write the file to
        """
        raise NotImplementedError()

    def has_namespace(self) -> bool:
        """
        Determines if a namespace is associated with the current generator
        :return: True if a namespace is provided
        """
        return len(self.namespace) > 0

    def _print_init(self) -> None:
        """
        Interface instance to write initialization parameters to the source file
        Prints header information and include directory information
        """
        super()._print_init()
        self.lines.extend([
            '// TeaFIS is a cockpit display for aircraft',
            '// Copyright (C) 2021  Ian O\'Rourke',
            '//',
            '// This program is free software; you can redistribute it and/or modify',
            '// it under the terms of the GNU General Public License as published by',
            '// the Free Software Foundation; either version 2 of the License, or',
            '// (at your option) any later version.',
            '//',
            '// This program is distributed in the hope that it will be useful,',
            '// but WITHOUT ANY WARRANTY; without even the implied warranty of',
            '// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the',
            '// GNU General Public License for more details.',
            '//',
            '// You should have received a copy of the GNU General Public License along',
            '// with this program; if not, write to the Free Software Foundation, Inc.,',
            '// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.',
            '',
            '// This file is auto-generated',
            '// Creation Date: {0:s} UTC'.format(self._date_string()),
            ''
            ])
        if len(self.includes) > 0:
            self.lines.extend(self.includes)
            self.lines.append('')


class CodegenFileCppHeader(CodegenFileCpp):
    """
    Class instance for a Codegen header file for the C++ language
    """

    def __init__(self, base_name: str, namespace: str = ''):
        """
        Initializes the instance with a base name that will be used to generate parameter items and a signal printer
        function to be called for each signal in the list
        :param base_name: the base name of the generated file (signal_id or signal_database, for example)
        :param namespace: the namespace to associate with the current code generation file
        """
        super().__init__(base_name=base_name, namespace=namespace)

    def _header_guard(self) -> str:
        """
        Provides the name of the header guard for the header file
        :return: the header guard string
        """
        return '{:s}_H'.format(self._gen_base_name().upper())

    def _gen_file_name(self) -> str:
        """
        Provides the file name to write
        :return: the file name to write the generated file to
        """
        return '{:s}.h'.format(self._gen_base_name())

    def _print_init(self) -> None:
        """
        Adds additional parameters to the write buffer for the header guard and the namespace name
        """
        super()._print_init()
        self.lines.extend([
            '#ifndef {:s}'.format(self._header_guard()),
            '#define {:s}'.format(self._header_guard()),
            ''])

        if self.has_namespace():
            self.lines.extend([
                'namespace {:s}'.format(self.namespace),
                '{',
                ''])

    def _print_end(self) -> None:
        """
        Adds additional parameters to the write buffer for ending parameter values
        """
        if self.has_namespace():
            self.lines.extend(['', '}'])

        self.lines.extend([
            '',
            '#endif // {:s}'.format(self._header_guard()),
            ''])

        super()._print_end()


class CodegenFileCppSource(CodegenFileCpp):
    """
    Class instance for a Codegen source file for the C++ language
    """

    def __init__(self, base_name: str, namespace: str = ''):
        """
        Initializes the instance with a base name that will be used to generate parameter items and a signal printer
        function to be called for each signal in the list
        :param base_name: the base name of the generated file (signal_id or signal_database, for example)
        :param namespace: the namespace to associate with the current code generation file
        """
        super().__init__(base_name=base_name, namespace=namespace)

    def _gen_file_name(self) -> str:
        """
        Provides the file name to write
        :return: the file name to write the generated file to
        """
        return '{:s}.cpp'.format(self._gen_base_name())

    def _print_init(self) -> None:
        """
        Adds additional parameters to the write buffer for the header guard and the namespace name
        """
        super()._print_init()
        if self.has_namespace():
            self.lines.append('using namespace {:s};'.format(self.namespace))
            self.lines.append('')
