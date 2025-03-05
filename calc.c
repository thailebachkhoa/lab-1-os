#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "operations.h"

int is_valid_number(const char *s) {
    char *end;
    strtod(s, &end);
    return (*s != '\0' && *end == '\0');
}

int main() {
    double ans = 0.0;
    char input[256];

    while (1) {
        printf(">> ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "EXIT") == 0) {
            break;
        }

        char token1[64], token2[64], token3[64];
        if (sscanf(input, "%63s %63s %63s", token1, token2, token3) != 3) {
            printf("SYNTAX ERROR\n");
            continue;
        }

        if (strlen(token2) != 1 || (token2[0] != '+' && token2[0] != '-' &&
            token2[0] != 'x' && token2[0] != 'X' && token2[0] != '/' && token2[0] != '%')) {
            printf("SYNTAX ERROR\n");
            continue;
        }

        double num1, num2;
        if (strcmp(token1, "ANS") == 0) {
            num1 = ans;
        } else if (is_valid_number(token1)) {
            num1 = atof(token1);
        } else {
            printf("SYNTAX ERROR\n");
            continue;
        }

        if (strcmp(token3, "ANS") == 0) {
            num2 = ans;
        } else if (is_valid_number(token3)) {
            num2 = atof(token3);
        } else {
            printf("SYNTAX ERROR\n");
            continue;
        }

        double result;
        switch (token2[0]) {
            case '+':
                result = add(num1, num2);
                break;
            case '-':
                result = subtract(num1, num2);
                break;
            case 'x': case 'X':
                result = multiply(num1, num2);
                break;
            case '/':
                result = divide(num1, num2);
                break;
            case '%':
                result = modulo((int)num1, (int)num2);
                break;
            default:
                printf("SYNTAX ERROR\n");
                continue;
        }

        ans = result;
        
        if (token2[0] == '%' || result == (double)((int)result)) {
            printf("%d\n", (int)result);
        } else {
            printf("%.2f\n", result);
        }
    }
    return 0;
}

