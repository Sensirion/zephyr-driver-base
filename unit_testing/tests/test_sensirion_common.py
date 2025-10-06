# -*- coding: utf-8 -*-
import pytest

import driver_tester.i2c as i2c
import driver_tester.common as common


@pytest.mark.parametrize("data, expected", [
    ((0, 0), 0),
    ((0, 1), 1),
    ((1, 0), 256)])
def test_bytes_to_int16(data, expected):
    assert expected == common.byte_sequence_to_uint16(data)


@pytest.mark.parametrize("data, expected", [
    (0, (0, 0)),
    (1, (0, 1)),
    (256, (1, 0))])
def test_uint16_to_bytes(data, expected):
    assert expected == tuple(common.uint16_to_byte_sequence(data))

@pytest.mark.parametrize("data, count, expected", [
    ([190, 239], 2, 146),
    ([83, 135], 2, 166),
    ([254, 237], 2, 121)])
def test_generate_crc(data, count, expected):
    assert expected == i2c.generate_crc(data, count)

@pytest.mark.parametrize("data, count, checksum, expected", [
    ([190, 239], 2, 146, 0),
    ([83, 135], 2, 111, 1)])
def test_check_crc(data, count, checksum, expected):
    assert expected == i2c.check_crc(data, count, checksum)
