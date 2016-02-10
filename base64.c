char binary_to_base64[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char base64_to_binary[256] = {
  64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
  64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
  64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
  64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
  64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
  64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
  64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
  64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};

unsigned int encode_base64_length(unsigned int input_length) {
  unsigned int output_length = input_length/3*4;
  
  switch(input_length % 3) {
    case 1: output_length += 2; break;
    case 2: output_length += 3; break;
  }
  
  return output_length;
}

unsigned int decode_base64_length(unsigned char *input) {
  unsigned char *start = input;
  
  while(base64_to_binary[input[0]] < 64) {
    ++input;
  }
  
  unsigned int input_length = input - start;
  
  unsigned int output_length = input_length/4*3;
  
  switch(input_length % 4) {
    default: return output_length;
    case 2: return output_length + 1;
    case 3: return output_length + 2;
  }
}

unsigned int encode_base64(unsigned char *input, unsigned int input_length, unsigned char *output) {
  unsigned int output_length = encode_base64_length(input_length);
  
  // While there are still full sets of 24 bits...
  for(unsigned int i = 3; i < output_length; i += 4) {
    output[0] = binary_to_base64[                         input[0] >> 2];
    output[1] = binary_to_base64[(input[0] & 0x03) << 4 | input[1] >> 4];
    output[2] = binary_to_base64[(input[1] & 0x0F) << 2 | input[2] >> 6];
    output[3] = binary_to_base64[ input[2] & 0x3F];
    
    input += 3;
    output += 4;
  }
  
  switch(output_length % 4) {
    case 2:
      output[0] = binary_to_base64[                         input[0] >> 2];
      output[1] = binary_to_base64[(input[0] & 0x03) << 4];
      output[2] = '\0';
      break;
    case 3:
      output[0] = binary_to_base64[                         input[0] >> 2];
      output[1] = binary_to_base64[(input[0] & 0x03) << 4 | input[1] >> 4];
      output[2] = binary_to_base64[(input[1] & 0x0F) << 2];
      output[3] = '\0';
      break;
    default:
      output[0] = '\0';
  }
  
  return output_length;
}

unsigned int decode_base64(unsigned char *input, unsigned char *output) {
  unsigned int output_length = decode_base64_length(input);
  
  // While there are still full sets of 24 bits...
  for(unsigned int i = 2; i < output_length; i += 3) {
    output[0] = base64_to_binary[input[0]] << 2 | base64_to_binary[input[1]] >> 4;
    output[1] = base64_to_binary[input[1]] << 4 | base64_to_binary[input[2]] >> 2;
    output[2] = base64_to_binary[input[2]] << 6 | base64_to_binary[input[3]];
    
    input += 4;
    output += 3;
  }
  
  switch(output_length % 3) {
    case 1:
      output[0] = base64_to_binary[input[0]] << 2 | base64_to_binary[input[1]] >> 4;
      break;
    case 2:
      output[0] = base64_to_binary[input[0]] << 2 | base64_to_binary[input[1]] >> 4;
      output[1] = base64_to_binary[input[1]] << 4 | base64_to_binary[input[2]] >> 2;
      break;
  }
  
  return output_length;
}
