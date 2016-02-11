/**
 * Base64 encoding and decoding of strings. Uses '+' for 62, '/' for 63, '=' for padding
 */

#ifndef BASE64_H_INCLUDED
#define BASE64_H_INCLUDED

// Base64 characters, ordered by their 6-bit value
extern const char binary_to_base64[65];

// 6-bit values of base64 characters, indexed by their ascii codes
extern const char base64_to_binary[256];

/* encode_base64_length:
 *   Description:
 *     Calculates length of base64 string needed for a given number of binary bytes
 *   Parameters:
 *     input_length - Amount of binary data in bytes
 *   Returns:
 *     Number of base64 characters needed to encode input_length bytes of binary data
 */
unsigned int encode_base64_length(unsigned int input_length);

/* decode_base64_length:
 *   Description:
 *     Calculates number of bytes of binary data in a base64 string
 *   Parameters:
 *     input - Base64-encoded null-terminated string
 *   Returns:
 *     Number of bytes of binary data in input
 */
unsigned int decode_base64_length(unsigned char input[]);

/* encode_base64:
 *   Description:
 *     Converts an array of bytes to a base64 null-terminated string
 *   Parameters:
 *     input - Pointer to input data
 *     input_length - Number of bytes to read from input pointer
 *     output - Pointer to output string. Null terminator will be added automatically
 *   Returns:
 *     Length of encoded string in bytes (not including null terminator)
 */
unsigned int encode_base64(unsigned char input[], unsigned int input_length, unsigned char output[]);

/* decode_base64:
 *   Description:
 *     Converts a base64 null-terminated string to an array of bytes
 *   Parameters:
 *     input - Pointer to input string
 *     output - Pointer to output array
 *   Returns:
 *     Number of bytes in the decoded binary
 */
unsigned int decode_base64(unsigned char input[], unsigned char output[]);

#endif // ifndef
