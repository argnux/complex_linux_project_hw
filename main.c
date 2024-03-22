#include <stdio.h> 

#include "error_handler.h"
#include "input.h"

void flush() {
    while ((getchar()) != '\n');
}

int main() {
    Error error;
    unset_error(&error);
    char operation = ' ';
    while (1) {
        printf("Choose the operation:\n");
        printf("\t+\tto find the sum of two numbers\n");
        printf("\t-\tto find the difference of two numbers\n");
        printf("\t*\tto find the product of two numbers\n");
        printf("\t/\tto find the fraction of two numbers\n");
        printf("\tf\tto find the factorial of the number\n");
        printf("\tr\tto find the square root of the number\n");
        printf("\tu\tto translate the text to uppercase\n");
        printf("\tl\tto translate the text to lowercase\n");
        printf("\tq\tto quit the program\n");

        printf("\nYour decision: ");
        operation = getchar();
        if (operation == 'q') break;

        if ((getchar()) != '\n') {
            set_error(&error, "Operation includes only one character");
            flush();
        } else {
            process_input(operation, &error);
        }

        if (error.is_set) {
            print_and_unset_error(&error);
            continue;
        }
        flush();
    }

    return 0;
}

