#include "sensirion_i2c.h"
#include "sensirion_common.h"
#include <gtest/gtest.h>

TEST(ModuleTestsI2c, CrcTest)
{
	uint8_t input[2] = {0xBE, 0xEF};
	uint8_t expected = 0x92;
	uint8_t actual = sensirion_i2c_generate_crc(input, 2);
	ASSERT_EQ(actual, expected);
	EXPECT_EQ(sensirion_i2c_check_crc(input, 2, expected), NO_ERROR);

	uint8_t wrong_crc = 0x00;
	EXPECT_EQ(sensirion_i2c_check_crc(input, 2, wrong_crc), CRC_ERROR);
}

TEST(ModuleTestsI2c, FillCmdSendBuf)
{
	uint8_t buf[8] = {};
	uint16_t args[2] = {0xFEED, 0xBEEF};
	uint16_t n = sensirion_i2c_fill_cmd_send_buf(buf, 0xABCD, args, 2);
	ASSERT_EQ(n, 6 + (2 * CRC8_LEN));
	EXPECT_EQ(0xAB, buf[0]);
	EXPECT_EQ(0xCD, buf[1]);

	EXPECT_EQ(0xFE, buf[2]);
	EXPECT_EQ(0xED, buf[3]);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[2], 2, buf[4]), NO_ERROR);

	EXPECT_EQ(0xBE, buf[5]);
	EXPECT_EQ(0xEF, buf[6]);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[5], 2, buf[7]), NO_ERROR);
}

TEST(ModuleTestsI2c, AddCmd)
{
	uint8_t buf[4] = {};
	uint16_t offset = 0;

	offset = sensirion_i2c_add_command_to_buffer(buf, offset, 0xA1B2);
	ASSERT_EQ(offset, (uint16_t)2);
	EXPECT_EQ(0xA1, buf[0]);
	EXPECT_EQ(0xB2, buf[1]);
}

TEST(ModuleTestsI2c, AddCmd16)
{
	uint8_t buf[4] = {};
	uint16_t offset = 0;

	offset = sensirion_i2c_add_command16_to_buffer(buf, offset, 0xCCDD);
	ASSERT_EQ(offset, (uint16_t)2);
	EXPECT_EQ(0xCC, buf[0]);
	EXPECT_EQ(0xDD, buf[1]);
}

TEST(ModuleTestsI2c, AddCmd8)
{
	uint8_t buf[4] = {};
	uint16_t offset = 0;

	offset = sensirion_i2c_add_command8_to_buffer(buf, offset, 0x7F);
	ASSERT_EQ(offset, (uint16_t)1);
	EXPECT_EQ(0x7F, buf[0]);
}

TEST(ModuleTestsI2c, AddUint32)
{
	uint8_t buf[16] = {};
	uint16_t offset = 0;

	offset = sensirion_i2c_add_uint32_t_to_buffer(buf, offset, 0x01020304);
	ASSERT_EQ(offset, (uint16_t)(4 + (2 * CRC8_LEN)));

	EXPECT_EQ(0x01, buf[0]);
	EXPECT_EQ(0x02, buf[1]);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[0], 2, buf[2]), NO_ERROR);

	EXPECT_EQ(0x03, buf[3]);
	EXPECT_EQ(0x04, buf[4]);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[3], 2, buf[5]), NO_ERROR);
}

TEST(ModuleTestsI2c, AddInt32)
{
	uint8_t buf[16] = {};
	uint16_t offset = 0;

	offset = sensirion_i2c_add_int32_t_to_buffer(buf, offset, -1);
	ASSERT_EQ(offset, (uint16_t)(4 + (2 * CRC8_LEN)));
	EXPECT_EQ(0xFF, buf[0]);
	EXPECT_EQ(0xFF, buf[1]);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[0], 2, buf[2]), NO_ERROR);
	EXPECT_EQ(0xFF, buf[3]);
	EXPECT_EQ(0xFF, buf[4]);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[3], 2, buf[5]), NO_ERROR);
}

TEST(ModuleTestsI2c, AddUint16)
{
	uint8_t buf[8] = {};
	uint16_t offset = 0;

	offset = sensirion_i2c_add_uint16_t_to_buffer(buf, offset, 0xBEEF);
	ASSERT_EQ(offset, (uint16_t)(2 + CRC8_LEN));
	EXPECT_EQ(0xBE, buf[0]);
	EXPECT_EQ(0xEF, buf[1]);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[0], 2, buf[2]), NO_ERROR);
}

TEST(ModuleTestsI2c, AddInt16)
{
	uint8_t buf[8] = {};
	uint16_t offset = 0;

	offset = sensirion_i2c_add_int16_t_to_buffer(buf, offset, -2);
	ASSERT_EQ(offset, (uint16_t)(2 + CRC8_LEN));
	EXPECT_EQ(0xFF, buf[0]);
	EXPECT_EQ(0xFE, buf[1]);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[0], 2, buf[2]), NO_ERROR);
}

TEST(ModuleTestsI2c, AddFloat)
{
	uint8_t buf[16] = {};
	float input = 23.75f;
	uint16_t offset = 0;

	offset = sensirion_i2c_add_float_to_buffer(buf, offset, input);
	ASSERT_EQ(offset, (uint16_t)(4 + (2 * CRC8_LEN)));

	// ckeck for correct crc
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[0], 2, buf[2]), NO_ERROR);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[3], 2, buf[5]), NO_ERROR);

	uint8_t float_buf[4] = {buf[0], buf[1], buf[3], buf[4]};
	EXPECT_EQ(sensirion_common_bytes_to_float(float_buf), input);
}

TEST(ModuleTestsI2c, AddBytesOk)
{
	const uint8_t in[4] = {0xAA, 0xBB, 0x01, 0x02};
	uint8_t buf[16] = {};
	uint16_t offset = 0;

	offset = sensirion_i2c_add_bytes_to_buffer(buf, offset, in, 4);
	ASSERT_EQ(offset, (uint16_t)(4 + (2 * CRC8_LEN)));

	EXPECT_EQ(0xAA, buf[0]);
	EXPECT_EQ(0xBB, buf[1]);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[0], 2, buf[2]), NO_ERROR);

	EXPECT_EQ(0x01, buf[3]);
	EXPECT_EQ(0x02, buf[4]);
	EXPECT_EQ(sensirion_i2c_check_crc(&buf[3], 2, buf[5]), NO_ERROR);
}

TEST(ModuleTestsI2c, AddBytesBadLen)
{
	const uint8_t in[3] = {0xAA, 0xBB, 0x01};
	uint8_t buf[8] = {};
	uint16_t offset = 0;

	int16_t rc = sensirion_i2c_add_bytes_to_buffer(buf, offset, in, 3);
	ASSERT_EQ(rc, BYTE_NUM_ERROR);
}

TEST(ModuleTestsI2c, ReadInplaceOk)
{
	// prefill the buffer as read doesnt change the buffer.
	uint8_t buf[16] = {0xBE, 0xEF, 0x92, 0x12, 0x34, 0x37};
	// expected_data_length is payload bytes (without CRCs)
	const uint16_t expected = 4;

	const struct i2c_dt_spec *spec = nullptr;
	ASSERT_EQ(sensirion_i2c_read_data_inplace(spec, buf, expected), NO_ERROR);

	EXPECT_EQ(0xBE, buf[0]);
	EXPECT_EQ(0xEF, buf[1]);
	EXPECT_EQ(0x12, buf[2]);
	EXPECT_EQ(0x34, buf[3]);
}

TEST(ModuleTestsI2c, ReadInplaceBadLen)
{
	uint8_t buf[8] = {};
	const struct i2c_dt_spec *spec = nullptr;

	ASSERT_EQ(sensirion_i2c_read_data_inplace(spec, buf, 3), BYTE_NUM_ERROR);
}
