#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    printf("v3.0 hex words addressed\n");

    /*   
     *   7 segment LED display 
     *    
     *   pin 5 ->  ---
     *   pin 4 -> |   | <- pin 6 
     *   pin 3 ->  ---
     *   pin 2 -> |   | <- pin 0
     *   pin 1 ->  ---
     */

    const char DIGITS[10] = {
        0x77, /*0*/
        0x41, /*1*/
        0x6e, /*2*/
        0x6b, /*3*/
        0x59, /*4*/
        0x3b, /*5*/
        0x3f, /*6*/
        0x61, /*7*/
        0x7f, /*8*/
        0x7b, /*9*/
    };

    const int IMAGE_SIZE = 2048; // in bytes
    char image[IMAGE_SIZE];

    for (int i = 0; i < IMAGE_SIZE; ++i) {
        image[i] = 0;
    }

    // programming first half of EEPROM for displaying unsigned numbers 0 to 255
    const int UNSIGNED_MAX = 255;
    for (int num = 0; num <= UNSIGNED_MAX; ++num) {    
       image[num + 0x000] = DIGITS[num%10];    // least significant decimal digit
       image[num + 0x100] = DIGITS[(num/10)%10]; // second least significant decimal digit
       image[num + 0x200] = DIGITS[num/100]; // third least significant decimal digit
    }
    
    // programming second half of EEPROM for displaying signed numbers -128 to 127
    const int SIGNED_MIN = -128;
    const int SIGNED_MAX = 127;
    for (int num = SIGNED_MIN ; num <= SIGNED_MAX; ++num) {
        image[(unsigned char)num + 0x400] = DIGITS[(abs(num)%10)]; // least significant decimal digit
        image[(unsigned char)num + 0x500] = DIGITS[(abs(num)/10)%10]; // second least significant decimal digit
        image[(unsigned char)num + 0x600] = DIGITS[abs(num)/100]; // third least significant decimal digit
        image[(unsigned char)num + 0x700] = num < 0 ? 0x08 : 0x00; // minus sign
    }

    // print out image
    const int LINE_SIZE = 16;
    const int LINES = IMAGE_SIZE / LINE_SIZE;
    for (int line_count = 0; line_count < LINES; ++line_count) {
        fprintf(stdout, "%03x:", line_count * LINE_SIZE); 
        for (int byte_count = 0; byte_count < LINE_SIZE; ++byte_count) {
            printf(" %02x", image[line_count * LINE_SIZE + byte_count]); 
        }
        printf("\n");
    }
}
