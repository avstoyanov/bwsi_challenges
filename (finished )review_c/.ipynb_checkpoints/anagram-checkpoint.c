#include <stdio.h>
#include <stdint.h>
#include "uart.h"
// IMPORTANT!!!! THIS DOES NOT CHECK WEATHER VALUES IN STR_B EXIST IN A. 
// THIS MEANS THAT IT ONLY WORKS FOR EQUAL-LENGTHED STRINGS IGNORING SPACES. SO "A V B E D S" AND "ABDFSD" WOULD BE FALSE, BUT "ADF ES" AND "ASDFEY" WOULD BE TRUE.
uint8_t isAnagram (char* str_a, char* str_b) {
    /* Your code goes here */
    int in_a;
    for (int i = 0; str_a[i] != '\0'; i++){
        //printf("outer loop");
        if (str_a[i] != ' '){
            
           // in_a = 0;
            for (int j = 0; str_b[j] != '\0'; j++){
                //printf("inner loop");
               // if (str_b[j] != ' '){
                    
                    if (str_b[j] == str_a[i]){
                        in_a = 1;
                        str_b[j] = ' ';
                        break;
                    }
                    in_a = 0;
                    
//                 } else{
//                     in_a = 2;
               // }
            }
            if (in_a == 0){
                return in_a;
            }
        }
    }
    return in_a;
} 

int main () {
    uart_init(UART2);
    int ret;
    uint8_t numTests;
    char str_a[50];
    char str_b[50];
    uint8_t strPtr = 0;
    uint8_t testResult = 0;
    
    // Get ammount of tests
    numTests = uart_read(UART2, BLOCKING, &ret);

    // Begin main program loop
    for (int i = 0; i < numTests; i++) {
        char value = 0;
        uint8_t strPtr = 0;

        // Recieve first string
        while (value != 10) {
            value = uart_read(UART2, BLOCKING, &ret);
            str_a[strPtr++] = value;
        }
        str_a[(strPtr-1)] = '\0';  // Replaces newline with null terminator
        value = 0;
        strPtr = 0;

        // Recieve next string
        while (value != 10) {
            value = uart_read(UART2, BLOCKING, &ret);
            str_b[strPtr++] = value;
        }
        str_b[(strPtr-1)] = '\0';

        // Return result of test
        testResult = isAnagram(str_a, str_b);
        uart_write(UART2, (char) testResult);
    }

    return 0;
}
