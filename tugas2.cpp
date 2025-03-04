// infix -> postfix dan postfix -> infix

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100 

//  Stack Array
typedef struct {
    char arr[MAX][MAX]; // Stack untuk menyimpan string
    int top;
} Stack;

// Stack
void initStack(Stack *s) { s->top = -1; }
void push(Stack *s, char *val) { strcpy(s->arr[++(s->top)], val); }

char* pop(Stack *s) {
    if (s->top == -1) {
        static char empty[MAX] = ""; // Gunakan array statis sebagai return value
        return empty;
    }
    return s->arr[(s->top)--];
}

// precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isalnum(c)) { 
            postfix[j++] = c;
        } else if (c == '(') {
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (c == ')') {
            while (s.top != -1 && s.arr[s.top][0] != '(') {
                postfix[j++] = pop(&s)[0];
            }
            pop(&s);
        } else { 
            while (s.top != -1 && precedence(s.arr[s.top][0]) >= precedence(c)) {
                postfix[j++] = pop(&s)[0];
            }
            char temp[2] = {c, '\0'};
            push(&s, temp);
        }
    }

    while (s.top != -1) { 
        postfix[j++] = pop(&s)[0];
    }
    postfix[j] = '\0'; 
}

void postfixToInfix(char* postfix, char* infix) {
    Stack s;
    initStack(&s);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isalnum(c)) {  
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else {  
            char op2[MAX], op1[MAX], expr[MAX];
            strcpy(op2, pop(&s));
            strcpy(op1, pop(&s));

            snprintf(expr, sizeof(expr), "(%s%c%s)", op1, c, op2);
            push(&s, expr);
        }
    }
    strcpy(infix, pop(&s));
}

int main() {
    char infix[MAX], postfix[MAX], convertedInfix[MAX];
    int choice;

    while (1) {
        printf("\n===== Konversi =====\n");
        printf("1. Infix ke Postfix\n");
        printf("2. Postfix ke Infix\n");
        printf("3. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Masukkan ekspresi Infix: ");
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = 0;
                infixToPostfix(infix, postfix);
                printf("Postfix: %s\n", postfix);
                break;

            case 2:
                printf("Masukkan ekspresi Postfix: ");
                fgets(postfix, MAX, stdin);
                postfix[strcspn(postfix, "\n")] = 0; // Hapus newline
                postfixToInfix(postfix, convertedInfix);
                printf("Infix: %s\n", convertedInfix);
                break;

            case 3:
                printf("EXIT\n");
                return 0;

            default:
                printf("ERROR\n");
        }
    }
}
