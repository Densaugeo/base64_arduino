#include "base64.hpp"

typedef uint8_t u8;

u8 input_buffer[128];
u8 input_length;
u8 output_buffer[128];
u8 output_length;
u8 hex_buffer[384];
u8 hex_length;

// Convert an unsigned integer to a hex value
u8 hex(u8 u) {
  if(u < 10) return '0' + u;
  if(u < 16) return 'a' - 10 + u;
  return 0xff;
}

void setup() {
  input_length = 0;
  
  Serial.begin(115200);
}

void loop() {
  u8 next = Serial.read();
  
  if(next == 0xff) { 
    delay(1);
  }
  else if(next == '\n') {
    if(input_length > 2 && input_buffer[0] == 'e' && input_buffer[1] == ' ') {
      encode_base64(input_buffer + 2, input_length - 2, output_buffer);
      Serial.println((char *) output_buffer);
      input_length = 0;
    } else if (input_length > 2 && input_buffer[0] == 'd' && input_buffer[1] == ' ') {
      output_length = decode_base64(input_buffer + 2, input_length - 2, output_buffer);
      for(u8 i = 0; i < output_length; ++i) {
        hex_buffer[3*i    ] = hex(output_buffer[i] / 16);
        hex_buffer[3*i + 1] = hex(output_buffer[i] % 16);
        hex_buffer[3*i + 2] = ' ';
      }
      hex_buffer[3*output_length] = 0;
      Serial.println((char *) hex_buffer);
      input_length = 0;
    } else {
      Serial.println("To encode: e STRING");
      Serial.println("To decode: d BASE64");
      input_length = 0;
    }
  }
  else {
    input_buffer[input_length++] = next;
  }
}
