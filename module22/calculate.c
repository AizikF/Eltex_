#include <stdio.h>

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

        switch (choice) {
            case 1:
                printf("Введите два числа для сложения: ");
                scanf("%lf %lf", &num1, &num2);
                result = add(num1, num2);
                printf("Результат: %.2f\n", result);
                break;
            case 2:
                printf("Введите два числа для вычитания: ");
                scanf("%lf %lf", &num1, &num2);
                result = subtract(num1, num2);
                printf("Результат: %.2f\n", result);
                break;
            case 3:
                printf("Введите два числа для умножения: ");
                scanf("%lf %lf", &num1, &num2);
                result = multiply(num1, num2);
                printf("Результат: %.2f\n", result);
                break;
            case 4:
                printf("Введите два числа для деления: ");
                scanf("%lf %lf", &num1, &num2);
                result = divide(num1, num2);
                printf("Результат: %.2f\n", result);
                break;
            case 5:
                printf("Выход из программы.\n");
                return 0; 
            default:
                printf("Неверный выбор. Попробуйте еще раз.\n");
        }
    }

    return 0;
}
