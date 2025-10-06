#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import absolute_import, division, print_function

import os
import re

from setuptools import setup, find_packages, Extension

################################
# Required developer input start
################################

# Python versions this package is compatible with
python_requires = '>=3.8,<4'

# Packages that this package imports. List everything apart from standard lib packages.
install_requires = [
    # <insert list of packages and versions here>
]

# Packages required for tests and docs
extras_require = {
    'test': [
        'sensirion-i2c-driver~=1.0.0',
        'hypothesis~=6.96.4',
        'flake8~=3.7.8',
        'pytest~=7.4.4',
        'pytest-cov~=4.1.0',
    ],
    'docs': [
        'sphinx~=2.2.1',
        'sphinx-rtd-theme~=1.0.0',
    ]
}

package_name = "driver_tester"
author = 'Sensirion'
author_email = 'info@sensirion.com'
description = 'Fast helper functions for drivers.'
keywords = 'protocol'

################################
# Required developer input end
################################


# It is important to NOT import anything, not even the version, from the package which is being built.
# Otherwise weird behavior is guaranteed.
version_line = open(os.path.join(package_name.replace("-", "_"), "version.py"), "rt").read()
result = re.search(r"^version = ['\"]([^'\"]*)['\"]", version_line, re.M)
if result:
    version_string = result.group(1)
else:
    raise RuntimeError("Unable to find version string")

long_description = open(os.path.join(os.path.dirname(__file__), 'CHANGELOG.md')).read().strip() + "\n"

swig_path = 'swig'

sensirion_driver_helper = Extension(
    'driver_tester._sensirion_common_wrap',
    include_dirs=[swig_path],
    library_dirs=[swig_path],
    sources=[
        os.path.join(swig_path, 'test_sensirion_common.c'),
        os.path.join(swig_path, 'test_sensirion_i2c.c'),
        os.path.join(swig_path, 'test_crc_tables.c'),
        os.path.join(swig_path, 'sensirion_common_wrap.c')
    ],
    depends=[
        os.path.join(swig_path, 'test_sensirion_common.h')
    ],
)

setup(
    name=package_name,
    version=version_string,
    author=author,
    author_email=author_email,
    description=description,
    license='Apache-2.0',
    keywords=keywords,
    url='https://developers.sensirion.com',
    packages=find_packages(exclude=['tests', 'tests.*']),
    long_description=long_description,
    python_requires=python_requires,
    install_requires=install_requires,
    extras_require=extras_require,
    ext_modules=[sensirion_driver_helper],
    classifiers=[
        'Intended Audience :: Developers',
        'License :: OSI Approved :: Apache Software License',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
        'Topic :: Software Development :: Libraries :: Python Modules'
    ]
)
