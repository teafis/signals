"""
Generates C++ Files for Provided Packets
"""

import pathlib

from signal_generator.signal_list import SignalList
from signal_generator.codegen_type import CodeGenType


def main():
    signal_file = pathlib.Path('signal_list.json')
    signal_list = SignalList.from_json(file=signal_file)
    signal_list.generate_code(
        target=CodeGenType.CPP,
        target_dir=pathlib.Path(__file__).parent / 'cpp')


if __name__ == '__main__':
    main()
