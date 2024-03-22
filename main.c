#include <stdio.h>

#include "calc.h"

#define BUFFER_SIZE 1024 // assume max buffer size is 1kB

typedef struct {
    double num;
} UnaryInput;

typedef struct {
    double num1, num2;
} BinaryInput;

typedef struct {
    char text[BUFFER_SIZE];
} TextInput;

typedef union {
    UnaryInput unaryInput;
    BinaryInput binaryInput;
    TextInput textInput;
} Input;

void unaryInputPrompt(Input *input) {
    printf("Enter the number: ");
    scanf("%lf", &input->unaryInput.num);
}

void binaryInputPrompt(Input *input) {
    printf("Enter two spaced numbers: ");
    scanf("%lf %lf", &input->binaryInput.num1, &input->binaryInput.num2);
}

void textInputPrompt(Input *input) {
    printf("Enter text: ");

    char *buf = input->textInput.text;
    size_t sz = BUFFER_SIZE;
    getline(&buf, &sz, stdin);
}

void process_input(char operation) {
    Input input;
    double result;
    switch (operation) {
        case '+':
            binaryInputPrompt(&input);
            result = sum(input.binaryInput.num1, input.binaryInput.num2);
            printf("%.2lf + %.2lf = %.2lf\n", input.binaryInput.num1, input.binaryInput.num2, result);
            break;
        case '-':
            binaryInputPrompt(&input);
            result = difference(input.binaryInput.num1, input.binaryInput.num2);
            printf("%.2lf - %.2lf = %.2lf\n", input.binaryInput.num1, input.binaryInput.num2, result);
            break;
        case '*':
            binaryInputPrompt(&input);
            result = product(input.binaryInput.num1, input.binaryInput.num2);
            printf("%.2lf * %.2lf = %.2lf\n", input.binaryInput.num1, input.binaryInput.num2, result);
            break;
        case '/':
            binaryInputPrompt(&input);
            result = fraction(input.binaryInput.num1, input.binaryInput.num2);
            printf("%.2lf / %.2lf = %.2lf\n", input.binaryInput.num1, input.binaryInput.num2, result);
            break;
        case 'f':
            unaryInputPrompt(&input);
            result = factorial(input.unaryInput.num);
            printf("factorial(%.2lf) = %.2lf\n", input.unaryInput.num, result);
            break;
        case 'r':
            unaryInputPrompt(&input);
            result = square_root(input.unaryInput.num);
            printf("square_root(%.2lf) = %.2lf\n", input.unaryInput.num, result);
            break;
        //case 'u': upper(); break;
        //case 'l': lower(); break;
        case 'q': break;
        default:
            fprintf(stderr, "Unknown operation: %c.\n", operation);
            break;
    }
}

int main() {
    char operation = ' ';
    while (operation != 'q') {
        printf("Choose the operation:\n");
        printf("\t+\tto find the sum of two numbers\n");
        printf("\t-\tto find the difference of two numbers\n");
        printf("\t*\tto find the product of two numbers\n");
        printf("\t/\tto find the fraction of two numbers\n");
        printf("\tf\tto find the factorial of the number\n");
        printf("\tr\tto find the square root of the number\n");
        //printf("\tu\tto translate the text to uppercase\n")
        //printf("\tl\tto translate the text to lowercase\n");
        printf("\tq\tto quit the program\n");

        printf("\nYour decision: ");
        operation = getchar();
        process_input(operation);
        while ((getchar()) != '\n'); // to flush stdin before the next iteration
    }

    return 0;
}

