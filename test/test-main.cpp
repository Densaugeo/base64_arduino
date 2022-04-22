#include <base64.hpp>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <unity.h>

void encode_test() {
  const uint8_t bytes_to_encode[] = {0x61, 0x38, 0x47, 0x2b, 0x34, 0x69, 0x35,
                                     0x41, 0x6e, 0x35, 0x62, 0x70, 0x50, 0x58,
                                     0x34, 0x52, 0x63, 0x35, 0x4d, 0x58, 0x4b,
                                     0x67, 0x3d, 0x3d, 0x8f};
  const char *expected_result = "YThHKzRpNUFuNWJwUFg0UmM1TVhLZz09jw==";
  const char *expected_result_13 = "YThHKzRpNUFuNWJwUA==";
  const char *expected_result_6 = "YThHKzRp";

  char actual_result[256];
  char actual_result_13[256];
  char actual_result_6[256];
  encode_base64(bytes_to_encode, 25, actual_result);
  encode_base64(bytes_to_encode, 13, actual_result_13);
  encode_base64(bytes_to_encode, 6, actual_result_6);

  TEST_ASSERT_EQUAL(strlen(expected_result), encode_base64_length(25));
  TEST_ASSERT_EQUAL(strlen(expected_result_13), encode_base64_length(13));
  TEST_ASSERT_EQUAL(strlen(expected_result_6), encode_base64_length(6));

  TEST_ASSERT_EQUAL_STRING(expected_result, actual_result);
  TEST_ASSERT_EQUAL_STRING(expected_result_13, actual_result_13);
  TEST_ASSERT_EQUAL_STRING(expected_result_6, actual_result_6);
}

void decode_test() {
  const char *input_string = "zn2XtTubOcNM6EdKazRbVqaNkqIdHH/eXA9QSg/LuHg=";
  const uint8_t expected_result[] = {
      0xce, 0x7d, 0x97, 0xb5, 0x3b, 0x9b, 0x39, 0xc3, 0x4c, 0xe8, 0x47,
      0x4a, 0x6b, 0x34, 0x5b, 0x56, 0xa6, 0x8d, 0x92, 0xa2, 0x1d, 0x1c,
      0x7f, 0xde, 0x5c, 0x0f, 0x50, 0x4a, 0x0f, 0xcb, 0xb8, 0x78};

  uint8_t result[44];
  uint8_t result_22[22];
  uint8_t result_11[11];
  decode_base64(input_string, result);
  decode_base64(input_string, 22, result_22);
  decode_base64(input_string, 11, result_11);

  TEST_ASSERT_EQUAL(32, decode_base64_length(input_string));
  TEST_ASSERT_EQUAL(16, decode_base64_length(input_string, 22));
  TEST_ASSERT_EQUAL(8, decode_base64_length(input_string, 11));

  TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_result, result, 32);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_result, result_22, 16);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_result, result_11, 8);
}

inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void encode_and_decode() {
  const size_t iterations = 1000;
  srand(time(0));
  for (size_t i = 0; i < iterations; ++i) {
    uint8_t data[32];
    char data_encoded[64];
    uint8_t data_decoded[64];

    for (size_t j = 0; j < 32; ++j)
      data[j] = map(rand(), 0, RAND_MAX, 0, 255);

    encode_base64(data, 32, data_encoded);
    size_t sz = decode_base64(data_encoded, data_decoded);
    TEST_ASSERT_EQUAL(32, sz);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(data, data_decoded, sz);
  }
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(encode_test);
  RUN_TEST(decode_test);
  RUN_TEST(encode_and_decode);
  UNITY_END();
  return 0;
}