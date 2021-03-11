import typing

from .codegen_file import CodegenSingle, CodegenInterface, CodegenFile
from .signal_def_base import SignalDefinitionBase
from .signal_list import SignalList


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
        return 'TF_{:s}_H'.format(self._gen_base_name().upper())

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


class CodegenCppIfMatchFunction:
    """
    Defines the CodeGen instance of a for an If-Else matching function
    """

    def __init__(
            self,
            name: str,
            namespace: typing.Union[str, None],
            result: str,
            parameters: typing.List[str],
            if_callable: typing.Callable[[SignalDefinitionBase], typing.Tuple[str, typing.List[str]]],
            default: typing.List[str],
            description: typing.List[str]):
        """
        Initializes the codegen if-match C++ function
        :param name: the function name
        :param namespace: the namespace of the function
        :param result: the resulting type of the function
        :param parameters: the parameters for the function
        :param if_callable: the if-else callable to provide the conditional expression and the statements if true
        :param default: the default "else" result
        :param description: the function description
        """
        self.name = name
        self.namespace = namespace
        self.result = result
        self.parameters = parameters
        self.if_callable = if_callable
        self.default = default
        self.description = description

    def _function_signature(self, with_namespace: bool):
        """
        Provides the C++ function signature in
        :param with_namespace: determines whether to include the namespace, if provided
        :return: the function signature
        """
        # Determine the namespace string if needed
        if with_namespace and self.namespace is not None and len(self.namespace) > 0:
            namespace_part = '{:s}::'.format(self.namespace)
        else:
            namespace_part = ''

        # Construct and return the signature
        return '{0:s} {1:s}{2:s}({3:s})'.format(
            self.result,
            namespace_part,
            self.name,
            ', '.join(self.parameters))

    def codegen_for_header(self) -> CodegenInterface:
        """
        Generates the function section for the header
        :return: the interface section for the C++ header
        """
        def header_printer(*_) -> typing.List[str]:
            """
            Provides the function declaration and description
            :param _:
            :return: returns the header file function declaration
            """
            result_list = list()
            result_list.extend([s.replace('<NAME>', self.name) for s in self.description])
            result_list.append('{:s};'.format(self._function_signature(with_namespace=False)))
            return result_list

        return CodegenSingle(printer=header_printer)

    def section_for_source(self) -> CodegenInterface:
        """
        Generates the function section for the source
        :return: the interface section for the C++ source
        """
        def source_printer(signal_list: SignalList) -> typing.List[str]:
            """
            Provides the function definition
            :param signal_list: the signal list to generate against
            :return: the function definition
            """
            # Initiate and open up the function
            result_list = list()
            result_list.append('{:s}'.format(self._function_signature(with_namespace=True)))
            result_list.append('{')

            # Create an add-with-indent function to make it easier to maintain consistent indentation
            def add_with_indent(val: str, indent: int = 0):
                result_list.append('{:s}{:s}'.format(
                    ''.join(['    '] * indent),
                    val))

            # Loop through the signal list for each definition
            for i, signal_def in enumerate(signal_list.definitions.values()):
                # Determine the conditional and resulting callable expressions
                conditional, statement = self.if_callable(signal_def)

                # Add the if statement
                add_with_indent(
                    '{:s} ({:s})'.format(
                        'if' if i == 0 else 'else if',
                        conditional),
                    1)

                # Open up the if block
                add_with_indent('{', 1)

                # Add each statement within with the proper indentation
                for s in statement:
                    add_with_indent(s, 2)

                # Close the if block
                add_with_indent('}', 1)

            # Check if a default parameter is required
            if len(self.default) > 0:
                # Add the else block and open
                add_with_indent('else', 1)
                add_with_indent('{', 1)

                # Add each statement with proper indentation
                for s in self.default:
                    add_with_indent(s, 2)

                # Close the else block
                add_with_indent('}', 1)

            # Close the function
            result_list.append('}')

            # Return the function definition
            return result_list

        return CodegenSingle(printer=source_printer)
