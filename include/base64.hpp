/**
 * Base64 encoding and decoding of strings. Uses '+' for 62, '/' for 63, '=' for
 * padding
 */

#ifndef BASE64_H_INCLUDED
#define BASE64_H_INCLUDED

#include <stddef.h>
#include <stdint.h>

/**
 *  \brief Converts a single byte from a binary value to the corresponding
 *         base64
 *
 *  \param[in] v Byte to convert
 *  \return ascii code of base64 character.
 *          If byte is >= 64, then there is not corresponding base64 character
 *          and 64 is returned
 */
char binary_to_base64(uint8_t v);

/**
 * \brief Converts a single byte from a base64 character to the corresponding
 *        binary value
 *
 * \param[in] c - Base64 character (as ascii code)
 * \return 6-bit binary value
 */
uint8_t base64_to_binary(char c);

/**
 * \brief Calculates length of base64 string needed for a given number of binary
 *        bytes
 * \param[in] input_length   Amount of binary data in bytes
 *
 * \return Number of base64 characters needed to encode input_length bytes of
 *         binary data
 */
inline size_t encode_base64_length(size_t input_length) {
  return (input_length + 2) / 3 * 4;
}

/**
 * \brief Calculates number of bytes of binary data in a base64 string
 *
 *        Variant that does not use input_length no longer used within library,
 *        retained for API compatibility
 *
 * \param[in] input Base64-encoded string
 * null-terminated string input_length (optional) - Number of bytes to read from
 * input pointer Returns: Number of bytes of binary data in input
 */
size_t decode_base64_length(const char *input, size_t input_length = 0);

/**
 * \brief Converts an array of bytes to a base64 null-terminated string
 *
 * \param[in] input Pointer to input data
 * \param[in] input_length Number of bytes to read from input pointer
 * \param[out] output Pointer to output string. Null terminator will be added
 * automatically
 *
 * \return Length of encoded string in bytes (not including null terminator)
 */
size_t encode_base64(const uint8_t *input, size_t input_length, char *output);

/**
 * \brief Converts a base64 null-terminated string to an array of bytes
 *
 * \param[in]  input        Pointer to input string
 * \param[in]  input_length (optional) - Number of bytes to read from input
 * pointer \param[out] output       Pointer to output array Returns: Number of
 * bytes in the decoded binary
 */
size_t decode_base64(const char *input, size_t input_length, uint8_t *output);
inline size_t decode_base64(const char *input, uint8_t *output) {
  return decode_base64(input, 0, output);
}
#endif // ifndef
