"""
Generates C++ Files for Provided Packets
"""

import pathlib

from signal_generator.signal_list import SignalList
from signal_generator.codegen_type import CodeGenType
from signal_generator.codegen_cpp import generate_cpp_code


def generate_code(
        signal_list: SignalList,
        target: CodeGenType,
        target_dir: pathlib.Path) -> None:
    """
    Generates the SignalList code associated with the provided code generation target type in the target directory
    :param signal_list: the signal list to use in code generation
    :param target: the code generation target type to use
    :param target_dir: the target directory to place generated source files within
    """
    if not target_dir.exists() or not target_dir.is_dir():
        raise ValueError('Target directory must be an existing file')

    if target == CodeGenType.CPP:
        generate_cpp_code(
            target_dir=target_dir,
            signal_list=signal_list)
    else:
        raise NotImplementedError()


def main():
    signal_file = pathlib.Path('signal_list.json')
    signal_list = SignalList.from_json(file=signal_file)
    generate_code(
        signal_list=signal_list,
        target=CodeGenType.CPP,
        target_dir=pathlib.Path(__file__).parent / 'cpp')


if __name__ == '__main__':
    main()
