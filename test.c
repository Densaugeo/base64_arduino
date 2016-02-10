#include<stdio.h>

#include "base64.h"

int main() {
  unsigned char some_message[] = {1,2,3,5,67,67,65,8,4,32,134,56};
  unsigned char buffer[100];
  
  encode_base64(some_message, 12, buffer); // Should give 'AQIDBUNDQQgEIIY4'
  
  printf((char *) buffer);
  printf("\n");
  
  unsigned char encoded_message[] = "AQIDBUNDQQgEIIY4";
  unsigned char decoded[100];
  
  unsigned int decoded_length = decode_base64(encoded_message, decoded);
  
  printf("[");
  for(int i = 0; i < decoded_length - 1; ++i) {
    printf("%d, ", decoded[i]);
  }
  printf("%d]\n", decoded[decoded_length - 1]);
  
  return 0;
}
