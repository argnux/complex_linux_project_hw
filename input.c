#include <stdio.h>

#include "input.h"
#include "calc.h"
#include "convert.h"

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

static void unaryInputPrompt(Input *input, Error *err) {
    printf("Enter the number: ");
    if (scanf("%lf", &input->unaryInput.num) <= 0) {
        set_error(err, "You need to specify the number with or without floating point.");
    }
}

static void binaryInputPrompt(Input *input, Error *err) {
    printf("Enter two spaced numbers: ");
    if (scanf("%lf %lf", &input->binaryInput.num1, &input->binaryInput.num2) <= 0) {
        set_error(err, "You need to specify numbers with or without floating point.");
    }
}

static void textInputPrompt(Input *input, Error *err) {
    printf("Enter text: ");

    // Not the best way to read whole line but in our case can be available
    if (scanf(" %1023[^\n]", input->textInput.text) <= 0) {
        set_error(err, "Your text is too long or incorrect.");
    }
}

void process_input(char operation, Error *err) {
    Input input;
    double result;
    switch (operation) {
        case '+':
            binaryInputPrompt(&input, err);
            if (err->is_set) {
                print_and_unset_error(err);
            } else {
                result = sum(input.binaryInput.num1, input.binaryInput.num2, err);
                if (err->is_set) {
                    print_and_unset_error(err);
                } else {
                    printf("%.2lf + %.2lf = %.2lf\n", input.binaryInput.num1, input.binaryInput.num2, result);
                }
            }
            break;
        case '-':
            binaryInputPrompt(&input, err);
            if (err->is_set) {
                print_and_unset_error(err);
            } else {
                result = difference(input.binaryInput.num1, input.binaryInput.num2, err);
                if (err->is_set) {
                    print_and_unset_error(err);
                } else {
                    printf("%.2lf - %.2lf = %.2lf\n", input.binaryInput.num1, input.binaryInput.num2, result);
                }
            }
            break;
        case '*':
            binaryInputPrompt(&input, err);
            if (err->is_set) {
                print_and_unset_error(err);
            } else {
                result = product(input.binaryInput.num1, input.binaryInput.num2, err);
                if (err->is_set) {
                    print_and_unset_error(err);
                } else {
                    printf("%.2lf * %.2lf = %.2lf\n", input.binaryInput.num1, input.binaryInput.num2, result);
                }
            }
            break;
        case '/':
            binaryInputPrompt(&input, err);
            if (err->is_set) {
                print_and_unset_error(err);
            } else {
                result = fraction(input.binaryInput.num1, input.binaryInput.num2, err);
                if (err->is_set) {
                    print_and_unset_error(err);
                } else {
                    printf("%.2lf / %.2lf = %.2lf\n", input.binaryInput.num1, input.binaryInput.num2, result);
                }
            }
            break;
        case 'f':
            unaryInputPrompt(&input, err);
            if (err->is_set) {
                print_and_unset_error(err);
            } else {
                result = factorial(input.unaryInput.num, err);
                if (err->is_set) {
                    print_and_unset_error(err);
                } else {
                    printf("factorial(%.2lf) = %.2lf\n", input.unaryInput.num, result);
                }
            }
            break;
        case 'r':
            unaryInputPrompt(&input, err);
            if (err->is_set) {
                print_and_unset_error(err);
            } else {
                result = square_root(input.unaryInput.num, err);
                if (err->is_set) {
                    print_and_unset_error(err);
                } else {
                    printf("square_root(%.2lf) = %.2lf\n", input.unaryInput.num, result);
                }
            }
            break;
        case 'u':
            textInputPrompt(&input, err);
            upper(input.textInput.text);
            printf("Your string in uppercase: %s\n", input.textInput.text);
            break;
        case 'l':
            textInputPrompt(&input, err);
            lower(input.textInput.text);
            printf("Your string in lowercase: %s\n", input.textInput.text);
            break;
        case 'q': break;
        default:
            set_error(err, "Unknown operation!");
            break;
    }
}

