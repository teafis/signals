"""
AnalogSignal defines the analog signal type
"""

from .signal_definition import SignalDefinition


class AnalogSignalDefinition(SignalDefinition):
    """
    Class to maintain the definition for an analog signal type
    """
    def __init__(
            self,
            cat_id: int,
            sub_id: int,
            name: str,
            unit: str,
            sig_type: str,
            timeout_msec: int,
            resolution: float):
        """
        Creates a signal definition for the provided input parameters
        :param cat_id: the category ID for the signal
        :param sub_id: the signal ID for the signal
        :param unit: the unit associated with the signal
        :param sig_type: the signal type
        :param timeout_msec: the number of milliseconds until timeout for the signal
        :param resolution: the resolution to multiply network data by to get the engineering data
        """
        super().__init__(cat_id, sub_id, name, unit, sig_type, timeout_msec)
        self.resolution = resolution

