# -*- coding: utf-8 -*-


"""Sensirion common"""

import logging
from typing import Iterable

from . import sensirion_common_wrap as wrapped

log = logging.getLogger(__name__)


def byte_sequence_to_uint16(byte_sequence: Iterable[int]) -> int:
    data = wrapped.byte_array(len(byte_sequence))
    for i, x in enumerate(byte_sequence):  # this is not efficient that we need it only for testing and convenience
        data[i] = x
    return wrapped.sensirion_common_bytes_to_int16_t(data)


def uint16_to_byte_sequence(value: int) -> bytes:
    result = wrapped.byte_array(2)
    wrapped.sensirion_common_uint16_t_to_bytes(value, result)
    print(result)
    return bytes([result[0], result[1]])
