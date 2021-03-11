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

SignalListCallable = typing.Callable[[SignalList], typing.List[str]]
SignalPrinterCallable = typing.Callable[[int, SignalList, SignalDefinitionBase], typing.List[str]]


class CodegenInterface:
    """
    Generic interface for code generation parameters
    """

    def generate_for_signal_list(self, signal_list: SignalList) -> typing.List[str]:
        """
        Generates the code for the given signal list
        :param signal_list: the signal list to generate code for
        :return: a list of lines within the generated code
        """
        raise NotImplementedError()


class CodegenSingle(CodegenInterface):
    """
    Interface to provide a single list of code generation for the provided signal list
    """

    def __init__(self, printer: SignalListCallable):
        """
        Instantiates the single codegen parameter
        :param printer:
        """
        self.printer = printer

    def generate_for_signal_list(self, signal_list: SignalList) -> typing.List[str]:
        """
        Generates the code for the given signal list
        :param signal_list: the signal list to generate code for
        :return: a list of lines within the generated code
        """
        return self.printer(signal_list)


class CodegenSection(CodegenInterface):
    """
    CodegenSection defines a section of code generation for a particular signal parameter
    """

    def __init__(
            self,
            signal_printer: typing.Union[SignalPrinterCallable, None],
            add_printer_item_separation: bool = True):
        """
        Initializes the codegen section with the provided signal parameters
        :param signal_printer: is the signal printer to use
        :param add_printer_item_separation: determines whether to add separation to items
        in the looped section
        """
        # Save parameters
        self.signal_printer = signal_printer
        self.item_separation = add_printer_item_separation

        # Update the signal printer if none
        if self.signal_printer is None:
            def _empty_printer(*_, **__) -> typing.List[str]:
                """
                Provides a printer to perform no additions for each signal parameter
                :param _: variable argument input to be ignored
                :return: an empty list
                """
                return list()
            self.signal_printer = _empty_printer

        # Initialize the init/end list not added to indentations
        def _empty_bookend_printer(*_) -> typing.List[str]:
            return list()

        self.init_callable: SignalListCallable = _empty_bookend_printer
        self.end_callable: SignalListCallable = _empty_bookend_printer

    def generate_for_signal_list(self, signal_list: SignalList) -> typing.List[str]:
        """
        Generates the code for the given signal list
        :param signal_list: the signal list to generate code for
        :return: a list of lines within the generated code
        """
        # Define the initial list and add any initial parameters
        total_list = list()
        total_list.extend(self.init_callable(signal_list))

        # Loop through each signal
        for i, signal in enumerate(signal_list.definitions.values()):
            # Determine the text to write for the signal
            signal_lines = self.signal_printer(i, signal_list, signal)

            # Add spacing if the number of signal lines is sufficient
            if i > 0 and len(signal_lines) > 1 and self.item_separation:
                total_list.append('')

            # Write the signal lines
            total_list.extend(signal_lines)

        # Add the ending init and ending function
        total_list.extend(self.end_callable(signal_list))

        # Return the results
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
        self.sections: typing.List['CodegenInterface'] = list()

    def add_section(self, section: 'CodegenInterface') -> None:
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
