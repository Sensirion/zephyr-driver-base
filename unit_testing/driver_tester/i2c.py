# -*- coding: utf-8 -*-


"""Sensirion i2c"""

import logging
from typing import Iterable

from . import sensirion_common_wrap as wrapped

log = logging.getLogger(__name__)

def generate_crc(input_data: Iterable[int], count: int) -> int:
    data = wrapped.byte_array(len(input_data))
    for i, x in enumerate(input_data):  # this is not efficient that we need it only for testing and convenience
        data[i] = x
    return wrapped.sensirion_i2c_generate_crc(data, count)

def check_crc(input_data: Iterable[int], count: int, checksum: int) -> int:
    data = wrapped.byte_array(len(input_data))
    for i, x in enumerate(input_data):  # this is not efficient that we need it only for testing and convenience
        data[i] = x
    return wrapped.sensirion_i2c_check_crc(data, count, checksum)
