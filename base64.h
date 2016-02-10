#ifndef BASE64_H_INCLUDED
#define BASE64_H_INCLUDED

#ifdef _cplusplus
extern "C" {
#endif
  extern char binary_to_base64[65];
  extern char base64_to_binary[256];
  
  unsigned int encode_base64_length(unsigned int input_length);
  unsigned int decode_base64_length(unsigned char *input);
  unsigned int encode_base64(unsigned char *input, unsigned int input_length, unsigned char *output);
  unsigned int decode_base64(unsigned char *input, unsigned char *output);
#ifdef _cplusplus
}
#endif

#endif // ifndef
