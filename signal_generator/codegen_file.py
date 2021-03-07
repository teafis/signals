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

from .signal_definition import SignalDefinition
from .signal_list import SignalList

SignalPrinterCallable = typing.Callable[[SignalDefinition], typing.List[str]]


class CodegenFile:
    """
    CodegenFile defines the base code generation instance file and basic interface
    """

    def __init__(
            self,
            base_name: str,
            signal_printer: SignalPrinterCallable):
        """
        Initializes the instance with a base name that will be used to generate parameter items and a signal printer
        function to be called for each signal in the list
        :param base_name: the base name of the generated file (signal_id or signal_database, for example)
        :param signal_printer: the function to call to determine what to write for each signal file
        """
        # Save variables and initialize the list
        self.lines = list()
        self.signal_printer = signal_printer
        self.base_name = base_name

        # Define an empty "extra" function to include in source parameters and save
        def print_empty() -> typing.List[str]:
            return list()

        self.print_init_extra: typing.Callable[[], typing.List[str]] = print_empty
        self.print_end_extra: typing.Callable[[], typing.List[str]] = print_empty

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

    def generate_signal_list(
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
        self.lines.extend(self.print_init_extra())

        # Loop through each signal to add to the list
        for i, s in enumerate(signal_list.definitions.values()):
            # Determine the text to write for the signal
            signal_lines = self.signal_printer(s)

            # Add spacing if the number of signal lines is sufficient
            if i > 0 and len(signal_lines) > 1:
                self.lines.append('')

            # Write the signal lines
            self.lines.extend(signal_lines)

        # Write final text to the output buffer
        self.lines.extend(self.print_end_extra())
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

    # Define the default namespace name for C++
    NAMESPACE_NAME = 'efis_signals'

    def __init__(
            self,
            base_name: str,
            signal_printer: SignalPrinterCallable):
        """
        Initializes the instance with a base name that will be used to generate parameter items and a signal printer
        function to be called for each signal in the list
        :param base_name: the base name of the generated file (signal_id or signal_database, for example)
        :param signal_printer: the function to call to determine what to write for each signal file
        """
        super().__init__(
            base_name=base_name,
            signal_printer=signal_printer)
        self.includes = list()

    def add_include_file(self, file: str) -> None:
        """
        Adds a file to the list of preprocessor includes to use
        :param file: the file to include
        """
        self.includes.append(file)

    def _gen_file_name(self) -> str:
        """
        An interface to provide the generated file's name
        :return: the filename to write the file to
        """
        raise NotImplementedError()

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
            self.lines.extend(['#include "{:s}"'.format(f) for f in self.includes])
            self.lines.append('')


class CodegenFileCppHeader(CodegenFileCpp):
    """
    Class instance for a Codegen header file for the C++ language
    """

    def __init__(
            self,
            base_name: str,
            signal_printer: SignalPrinterCallable):
        """
        Initializes the instance with a base name that will be used to generate parameter items and a signal printer
        function to be called for each signal in the list
        :param base_name: the base name of the generated file (signal_id or signal_database, for example)
        :param signal_printer: the function to call to determine what to write for each signal file
        """
        super().__init__(
            base_name=base_name,
            signal_printer=signal_printer)

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
            '',
            'namespace {:s}'.format(self.NAMESPACE_NAME),
            '{',
            ''
            ])

    def _print_end(self) -> None:
        """
        Adds additional parameters to the write buffer for ending parameter values
        """
        self.lines.extend([
            '',
            '}',
            '',
            '#endif // {:s}'.format(self._header_guard()),
            ''
        ])
        super()._print_end()


class CodegenFileCppSource(CodegenFileCpp):
    """
    Class instance for a Codegen source file for the C++ language
    """

    def __init__(
            self,
            base_name: str,
            signal_printer: SignalPrinterCallable):
        """
        Initializes the instance with a base name that will be used to generate parameter items and a signal printer
        function to be called for each signal in the list
        :param base_name: the base name of the generated file (signal_id or signal_database, for example)
        :param signal_printer: the function to call to determine what to write for each signal file
        """
        super().__init__(
            base_name=base_name,
            signal_printer=signal_printer)

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
        self.lines.append('using namespace {:s};'.format(self.NAMESPACE_NAME))
        self.lines.append('')
