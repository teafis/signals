"""
Generates C++ Files for Provided Packets
"""

import pathlib

from signal_generator.signal_list import SignalList


def main():
    signal_file = pathlib.Path('signal_list.csv')
    signal_list = SignalList.from_file(file=signal_file)


if __name__ == '__main__':
    main()
