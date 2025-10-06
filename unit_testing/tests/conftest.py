#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import division, print_function

import pathlib

import pytest

package_root = pathlib.Path(__file__).parent


@pytest.fixture
def test_data_path() -> pathlib.Path:
    data_path = package_root / 'test_data'
    data_path.mkdir(parents=True, exist_ok=True)
    return data_path.absolute()
