#include "base64.hpp"

char binary_to_base64(uint8_t v) {
  // Capital letters - 'A' is ascii 65 and base64 0
  if (v < 26)
    return v + 'A';

  // Lowercase letters - 'a' is ascii 97 and base64 26
  if (v < 52)
    return v + 71;

  // Digits - '0' is ascii 48 and base64 52
  if (v < 62)
    return v - 4;

  // '+' is ascii 43 and base64 62
  if (v == 62)
    return '+';

  // '/' is ascii 47 and base64 63
  if (v == 63)
    return '/';

  return 64;
}

uint8_t base64_to_binary(char c) {
  // Capital letters - 'A' is ascii 65 and base64 0
  if ('A' <= c && c <= 'Z')
    return c - 'A';

  // Lowercase letters - 'a' is ascii 97 and base64 26
  if ('a' <= c && c <= 'z')
    return c - 71;

  // Digits - '0' is ascii 48 and base64 52
  if ('0' <= c && c <= '9')
    return c + 4;

  // '+' is ascii 43 and base64 62
  if (c == '+')
    return 62;

  // '/' is ascii 47 and base64 63
  if (c == '/')
    return 63;

  return 255;
}

size_t decode_base64_length(const char *input, size_t input_length) {

  if (input_length == 0) { // no length provvided
    const char *start = input;
    while (*input != '\0' and base64_to_binary(*input) < 64) {
      ++input;
    }

    input_length = input - start;
  }

  return input_length / 4 * 3 + (input_length % 4 ? input_length % 4 - 1 : 0);
}

size_t encode_base64(const uint8_t *input, size_t input_length, char *output) {
  size_t full_sets = input_length / 3;

  // While there are still full sets of 24 bits...
  for (size_t i = 0; i < full_sets; ++i) {
    output[0] = binary_to_base64(input[0] >> 2);
    output[1] = binary_to_base64((input[0] & 0x03) << 4 | input[1] >> 4);
    output[2] = binary_to_base64((input[1] & 0x0F) << 2 | input[2] >> 6);
    output[3] = binary_to_base64(input[2] & 0x3F);

    input += 3;
    output += 4;
  }

  switch (input_length % 3) {
  case 0:
    output[0] = '\0';
    break;
  case 1:
    output[0] = binary_to_base64(input[0] >> 2);
    output[1] = binary_to_base64((input[0] & 0x03) << 4);
    output[2] = '=';
    output[3] = '=';
    output[4] = '\0';
    break;
  case 2:
    output[0] = binary_to_base64(input[0] >> 2);
    output[1] = binary_to_base64((input[0] & 0x03) << 4 | input[1] >> 4);
    output[2] = binary_to_base64((input[1] & 0x0F) << 2);
    output[3] = '=';
    output[4] = '\0';
    break;
  }

  return encode_base64_length(input_length);
}

size_t decode_base64(const char *input, size_t input_length, uint8_t *output) {
  size_t output_length = decode_base64_length(input, input_length);

  // While there are still full sets of 24 bits...
  for (size_t i = 2; i < output_length; i += 3) {
    output[0] =
        base64_to_binary(input[0]) << 2 | base64_to_binary(input[1]) >> 4;
    output[1] =
        base64_to_binary(input[1]) << 4 | base64_to_binary(input[2]) >> 2;
    output[2] = base64_to_binary(input[2]) << 6 | base64_to_binary(input[3]);

    input += 4;
    output += 3;
  }

  switch (output_length % 3) {
  case 1:
    output[0] =
        base64_to_binary(input[0]) << 2 | base64_to_binary(input[1]) >> 4;
    break;
  case 2:
    output[0] =
        base64_to_binary(input[0]) << 2 | base64_to_binary(input[1]) >> 4;
    output[1] =
        base64_to_binary(input[1]) << 4 | base64_to_binary(input[2]) >> 2;
    break;
  }

  return output_length;
}