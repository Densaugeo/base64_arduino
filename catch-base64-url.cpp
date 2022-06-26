// Unit tests for the BASE64_URL configuration. Copied from catch-standard.cpp and modified

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#define BASE64_URL
#include "base64.hpp"

TEST_CASE("encode_base64()", "[]") {
  unsigned char actual_base64[100];
  
  SECTION("Length divisible by 3 (no padding)") {
    unsigned char binary_4[] = {99, 225, 39, 195, 8, 43, 209, 151, 8, 43, 195, 183};
    encode_base64(binary_4, 12, actual_base64);
    REQUIRE(memcmp(actual_base64, "Y-Enwwgr0ZcIK8O3", 17) == 0);
    
    unsigned char binary_5[] = {171, 65, 164, 64, 60, 221, 46, 226, 252, 167, 250, 252};
    encode_base64(binary_5, 12, actual_base64);
    REQUIRE(memcmp(actual_base64, "q0GkQDzdLuL8p_r8", 17) == 0);
  }
  
  SECTION("Length not divisible by 3 (padded)") {
    unsigned char binary_8[] = {24, 6, 234, 175, 34, 198, 47, 173, 234, 158, 106, 203, 80, 171, 218, 163, 60, 105, 183, 152, 73, 142, 190, 107, 189, 223, 215, 169, 63, 169, 163, 29, 9, 134, 235, 107, 35, 5, 16, 50, 7};
    encode_base64(binary_8, 41, actual_base64);
    REQUIRE(memcmp(actual_base64, "GAbqryLGL63qnmrLUKvaozxpt5hJjr5rvd_XqT-pox0JhutrIwUQMgc=", 57) == 0);
  }
}

TEST_CASE("decode_base64() - no length argument", "[]") {
  unsigned char actual_binary[100];
  
  SECTION("Divisible by 4 (no padding)") {
    unsigned char expected_binary_1[] = {255, 255, 255};
    decode_base64((unsigned char*) "____", actual_binary);
    REQUIRE(memcmp(actual_binary, expected_binary_1, 3) == 0);
    
    unsigned char expected_binary_2[] = {99, 225, 39, 195, 8, 43, 209, 151, 8, 43, 195, 183};
    decode_base64((unsigned char*) "Y-Enwwgr0ZcIK8O3", actual_binary);
    REQUIRE(memcmp(actual_binary, expected_binary_2, 12) == 0);
  }
  
  SECTION("Not divisible by 4 (padded)") {
    unsigned char expected_binary_5[] = {220, 92, 67, 95, 157, 76, 162, 210, 254, 202, 136, 157, 104, 178, 103, 81, 35, 103, 244, 71, 92, 25, 69, 64, 61, 232, 255, 108, 217, 106, 63, 103, 234, 39, 156, 108, 4, 101, 212, 198, 57, 223, 75, 255, 160, 26, 193, 139, 16, 89, 12, 45, 183, 133, 33};
    decode_base64((unsigned char*) "3FxDX51MotL-yoidaLJnUSNn9EdcGUVAPej_bNlqP2fqJ5xsBGXUxjnfS_-gGsGLEFkMLbeFIQ==", actual_binary);
    REQUIRE(memcmp(actual_binary, expected_binary_5, 55) == 0);
  }
}

// NOTE This case is a duplicate of "decode_base64() - no length argument" with the length argument added
TEST_CASE("decode_base64() - with length argument", "[]") {
  unsigned char actual_binary[100];
  
  SECTION("Divisible by 4 (no padding)") {
    unsigned char expected_binary_1[] = {255, 255, 255};
    decode_base64((unsigned char*) "____", 4, actual_binary);
    REQUIRE(memcmp(actual_binary, expected_binary_1, 3) == 0);
    
    unsigned char expected_binary_2[] = {99, 225, 39, 195, 8, 43, 209, 151, 8, 43, 195, 183};
    decode_base64((unsigned char*) "Y-Enwwgr0ZcIK8O3", 16, actual_binary);
    REQUIRE(memcmp(actual_binary, expected_binary_2, 12) == 0);
  }
  
  SECTION("Not divisible by 4 (padded)") {
    unsigned char expected_binary_5[] = {220, 92, 67, 95, 157, 76, 162, 210, 254, 202, 136, 157, 104, 178, 103, 81, 35, 103, 244, 71, 92, 25, 69, 64, 61, 232, 255, 108, 217, 106, 63, 103, 234, 39, 156, 108, 4, 101, 212, 198, 57, 223, 75, 255, 160, 26, 193, 139, 16, 89, 12, 45, 183, 133, 33};
    decode_base64((unsigned char*) "3FxDX51MotL-yoidaLJnUSNn9EdcGUVAPej_bNlqP2fqJ5xsBGXUxjnfS_-gGsGLEFkMLbeFIQ==", 76, actual_binary);
    REQUIRE(memcmp(actual_binary, expected_binary_5, 55) == 0);
  }
}
