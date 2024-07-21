#include <stdio.h>
#include <string.h>

typedef struct {
    char* name;
    double (*func)(double, double);
} Operation;

double add(double num1, double num2) {
    return num1 + num2;
}

double subtract(double num1, double num2) {
    return num1 - num2;
}

double multiply(double num1, double num2) {
    return num1 * num2;
}

double divide(double num1, double num2) {
    if (num2 == 0) {
        printf("Ошибка: деление на ноль\n");
        return 0;
    }
    return num1 / num2;
}

Operation operations[] = {
    {"add", add},
    {"subtract", subtract},
    {"multiply", multiply},
    {"divide", divide}
};

int main() {
    int choice;
    double num1, num2, result;

    while (1) {
        printf("\nВыберите действие:\n");
        printf("1. Сложение\n");
        printf("2. Вычитание\n");
        printf("3. Умножение\n");
        printf("4. Деление\n");
        printf("5. Выход\n");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            printf("Введите два числа: ");
            scanf("%lf %lf", &num1, &num2);
            result = operations[choice - 1].func(num1, num2);
            printf("Результат: %.2f\n", result);
        } else if (choice == 5) {
            printf("Выход из программы.\n");
            return 0;
        } else {
            printf("Неверный выбор. Попробуйте еще раз.\n");
        }
    }

    return 0;
}
