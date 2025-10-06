%module sensirion_common_wrap

%include cpointer.i
%include carrays.i
%include cstring.i
%include stdint.i
%include "typemaps.i"

%array_class(unsigned char, byte_array);

%{
#include "test_sensirion_common.h"
#include "test_sensirion_i2c.h"
%}

%include "test_sensirion_common.h"
%include "test_sensirion_i2c.h"
