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

static void unary_input_prompt(UnaryInput *input, Error *err) {
    printf("Enter the number: ");
    if (scanf("%lf", &input->num) <= 0) {
        set_error(err, "You need to specify the number with or without floating point.");
    }
}

static void binary_input_prompt(BinaryInput *input, Error *err) {
    printf("Enter two spaced numbers: ");
    if (scanf("%lf %lf", &input->num1, &input->num2) <= 0) {
        set_error(err, "You need to specify numbers with or without floating point.");
    }
}

static void text_input_prompt(TextInput *input, Error *err) {
    printf("Enter text: ");

    // Not the best way to read whole line but in our case can be available
    if (scanf(" %1023[^\n]", input->text) <= 0) {
        set_error(err, "Your text is too long or incorrect.");
    }
}

static void process_unary_input(char operation, double (*callback)(double,Error*), Error *err) {
    UnaryInput input;
    double result;
    unary_input_prompt(&input, err);
    if (err->is_set) {
        print_and_unset_error(err);
    } else {
        result = (*callback)(input.num, err);
        if (err->is_set) {
            print_and_unset_error(err);
        } else {
            printf("%c(%.2lf) = %.2lf\n", operation, input.num, result);
        }
    }
}

static void process_binary_input(char operation, double (*callback)(double,double,Error*), Error *err) {
    BinaryInput input;
    double result;
    binary_input_prompt(&input, err);
    if (err->is_set) {
        print_and_unset_error(err);
    } else {
        result = (*callback)(input.num1, input.num2, err);
        if (err->is_set) {
            print_and_unset_error(err);
        } else {
            printf("%.2lf %c %.2lf = %.2lf\n", input.num1, operation, input.num2, result);
        }
    }
}

static void process_text_input(void (*callback)(char*,Error*), Error *err) {
    TextInput input;
    text_input_prompt(&input, err);
    (*callback)(input.text, err);
    printf("Your new string: %s\n", input.text);
}

void process_input(char operation, Error *err) {
    switch (operation) {
        case '+':
            process_binary_input(operation, sum, err);
            break;
        case '-':
            process_binary_input(operation, difference, err);
            break;
        case '*':
            process_binary_input(operation, product, err);
            break;
        case '/':
            process_binary_input(operation, fraction, err);
            break;
        case 'f':
            process_unary_input(operation, factorial, err);
            break;
        case 'r':
            process_unary_input(operation, square_root, err);
            break;
        case 'u':
            process_text_input(upper, err);
            break;
        case 'l':
            process_text_input(lower, err);
            break;
        case 'q': break;
        default:
            set_error(err, "Unknown operation!");
            break;
    }
}

