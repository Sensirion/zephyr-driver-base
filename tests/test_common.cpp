#include "sensirion_common.h"
#include <gtest/gtest.h>

TEST(ModuleTestsCommon, BytesToUint16)
{
	uint8_t b[2] = {0x12, 0x34};
	ASSERT_EQ(sensirion_common_bytes_to_uint16_t(b), (uint16_t)0x1234);
}

TEST(ModuleTestsCommon, BytesToUint32)
{
	uint8_t b[4] = {0xDE, 0xAD, 0xBE, 0xEF};
	ASSERT_EQ(sensirion_common_bytes_to_uint32_t(b), (uint32_t)0xDEADBEEF);
}

TEST(ModuleTestsCommon, BytesToInt16)
{
	uint8_t b[2] = {0xFF, 0xFE};
	ASSERT_EQ(sensirion_common_bytes_to_int16_t(b), (int16_t)-2);
}

TEST(ModuleTestsCommon, BytesToInt32)
{
	uint8_t b[4] = {0xFF, 0xFF, 0xFF, 0xFF};
	ASSERT_EQ(sensirion_common_bytes_to_int32_t(b), (int32_t)-1);
}

TEST(ModuleTestsCommon, BytesToFloat)
{
	float f = 23.75f;
	uint8_t b[4] = {};
	sensirion_common_float_to_bytes(f, b);
	EXPECT_FLOAT_EQ(sensirion_common_bytes_to_float(b), f);
}

TEST(ModuleTestsCommon, Uint32ToBytes)
{
	uint8_t out[4] = {};
	sensirion_common_uint32_t_to_bytes((uint32_t)0x01020304, out);
	EXPECT_EQ(0x01, out[0]);
	EXPECT_EQ(0x02, out[1]);
	EXPECT_EQ(0x03, out[2]);
	EXPECT_EQ(0x04, out[3]);
}

TEST(ModuleTestsCommon, Uint16ToBytes)
{
	uint8_t out[2] = {};
	sensirion_common_uint16_t_to_bytes((uint16_t)0xBEEF, out);
	EXPECT_EQ(0xBE, out[0]);
	EXPECT_EQ(0xEF, out[1]);
}

TEST(ModuleTestsCommon, Int32ToBytes)
{
	uint8_t out[4] = {};
	sensirion_common_int32_t_to_bytes(-1, out);
	EXPECT_EQ(0xFF, out[0]);
	EXPECT_EQ(0xFF, out[1]);
	EXPECT_EQ(0xFF, out[2]);
	EXPECT_EQ(0xFF, out[3]);
}

TEST(ModuleTestsCommon, Int16ToBytes)
{
	uint8_t out[2] = {};
	sensirion_common_int16_t_to_bytes((int16_t)-2, out);
	EXPECT_EQ(0xFF, out[0]);
	EXPECT_EQ(0xFE, out[1]);
}

TEST(ModuleTestsCommon, FloatToBytes)
{
	float in = -12.5f;
	uint8_t b[4] = {};
	sensirion_common_float_to_bytes(in, b);
	EXPECT_FLOAT_EQ(sensirion_common_bytes_to_float(b), in);
}

TEST(ModuleTestsCommon, CopyBytes)
{
	const uint8_t src[5] = {1, 2, 3, 4, 5};
	uint8_t dst[5] = {};
	sensirion_common_copy_bytes(src, dst, 5);
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(src[i], dst[i]);
	}
}

TEST(ModuleTestsCommon, ToInt_Exact)
{
	// data_length == int_type
	const uint8_t src[4] = {0x01, 0x02, 0x03, 0x04};
	uint8_t dst[4] = {0xFF, 0xFF, 0xFF, 0xFF};

	sensirion_common_to_integer(src, dst, INTEGER, 4);

	EXPECT_EQ(0x04, dst[0]);
	EXPECT_EQ(0x03, dst[1]);
	EXPECT_EQ(0x02, dst[2]);
	EXPECT_EQ(0x01, dst[3]);
}

TEST(ModuleTestsCommon, ToInt_Small)
{
	// data_length < int_type
	const uint8_t src[3] = {0xAA, 0xBB, 0xCC};
	uint8_t dst[4] = {0x11, 0x22, 0x33, 0x44};

	sensirion_common_to_integer(src, dst, INTEGER, 3);

	EXPECT_EQ(0xCC, dst[0]);
	EXPECT_EQ(0xBB, dst[1]);
	EXPECT_EQ(0xAA, dst[2]);
	EXPECT_EQ(0x00, dst[3]);
}

TEST(ModuleTestsCommon, ToInt_TooLong)
{
	// data_length > int_type
	const uint8_t src[5] = {0, 1, 2, 3, 4};
	uint8_t dst[4] = {0x11, 0x22, 0x33, 0x44};

	sensirion_common_to_integer(src, dst, INTEGER, 5);

	EXPECT_EQ(0x00, dst[0]);
	EXPECT_EQ(0x00, dst[1]);
	EXPECT_EQ(0x00, dst[2]);
	EXPECT_EQ(0x00, dst[3]);
}
