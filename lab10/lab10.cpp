#include <stdio.h>
#include <locale.h>
#include <math.h>
#define M_PI 3.14159265358979323846

double fa(double x) 
{
    double y;
    if (x <= 3)
    {
        y = x * x - 3 * x + 9;
    }
    else
    {
        y = 1.0 / (x * x * x + 3);
    }
    return y;
}
double fb(double x)
{
    double y;
    y = x * exp(sin(x * x));
    return y;
}
int prac1(double fa, double fb, char choice)
{
    switch (choice)
    {
    case 1:
        printf("fa(x) = %lf\n", fa);
        break;
    case 2:
        printf("fb(x) = %lf\n", fb);
        break;
    case 3:
        printf("Произведение = %lf\n", fa * fb);
        break;
    case 4:
        printf("Разность квадратов = %lf\n", (fa * fa) - (fb * fb));
        break;
    case 5:
        printf("Удвоенная сумма = %lf\n", 2 * (fa + fb));
        break;
    default:
        printf("Неверный выбор пункта меню!\n");
        break;
    }
    return 0;
}

double sin_n(double x, int N)
{
    double sum = 0.0;
    double term = x;

    for (int k = 1; k <= N; k++) 
    {
        if (k > 1) 
        {
            int idx = 2 * k - 1;
            term = -term * x * x / ((idx - 1) * idx);
        }
        sum += term;
    }
    return sum;
}
double sin_eps(double x, double eps)
{
    double sum = 0.0;
    double term = x;
    int k = 1;

    while (fabs(term) > eps && k < 1000) {
        sum += term;
        k++;
        int idx = 2 * k - 1;
        term = -term * x * x / ((idx - 1) * idx);
    }
    return sum;
}
int tabl(int maxN, double xx)
{
    double res_lib = sin(xx);
    for (int n = 1; n <= maxN; n++) {
        double val = sin_n(xx, n);
        double deviation = res_lib - val;

        printf("%2d | %11.4f | %+11.4e\n", n, val, deviation);
    }
    return 0;
}

float area_quad(float d1, float d2, float alpha_deg)
{
    float alpha_rad = alpha_deg * (float)M_PI / 180.0f;
    return 0.5f * d1 * d2 * sinf(alpha_rad);
}
int print_definition()
{
    printf("\n___ОПРЕДЕЛЕНИЕ ФИГУРЫ___\n");
    printf("Четырёхугольник — это геометрическая фигура (многоугольник),\n");
    printf("имеющая четыре вершины и четыре последовательно соединяющие их стороны.\n");
    printf("Площадь произвольного выпуклого четырёхугольника вычисляется по формуле:\n");
    printf("S = 0.5 * d1 * d2 * sin(alpha),\n");
    printf("где d1 и d2 — диагонали, а alpha — угол между ними.\n\n");
    return 0;
}
int draw_quad(int d1, int d2, double alpha, char symb) {
    printf("\n___Отрисовка четырёхугольника (символ '%c')___\n\n", symb);

    for (int i = 0; i < d1; i++)
    {
        int shift = (int)(i * tan((90.0 - alpha / 2.0) * M_PI / 180.0));
        if (shift < 0) shift = 0;

        for (int s = 0; s < shift; s++) {
            printf(" ");
        }

        for (int j = 0; j < d2; j++) {
            printf("%c ", symb);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    double x;
    int choice;
    char repeat;

    do {
        printf("___Задание 1: Вычисления для двух функций___\n\n");
        printf("Введите значение x: ");
        scanf("%lf", &x);

        printf("\n");
        printf("fa(x)=%lf , fb(x)=%lf\n\n", fa(x), fb(x));

        printf("Дополнительные расчеты для введенного x:\n");
        printf("Произведение: %lf\n", fa(x) * fb(x));
        printf("Разность квадратов: %lf\n", (fa(x) * fa(x)) - (fb(x) * fb(x)));
        printf("Удвоенная сумма: %lf\n\n", 2 * (fa(x) + fb(x)));

        printf("___МЕНЮ ВЫБОРА___\n");
        printf("1. Вычислить значение первой функции fa(x)\n");
        printf("2. Вычислить значение второй функции fb(x)\n");
        printf("3. Вычислить произведение\n");
        printf("4. Вычислить разность квадратов\n");
        printf("5. Вычислить удвоенную сумму\n");
        printf("Выберите пункт меню (1-5): ");

        scanf("%d", &choice);
        printf("\n___Результат выбора___\n");
        prac1(fa(x), fb(x), choice);

        printf("\nПродолжить работу? (y - да, n - нет): ");
        scanf(" %c", &repeat);
        printf("\n----------------------------------------\n\n");

    } while (repeat == 'y' || repeat == 'Y');


    double eps;
    int maxN;
    printf("___Задание 2: Вычисление sin(x) тремя способами___\n\n");

    printf("Введите значение x (в радианах, например, 0.7854): ");
    scanf("%lf", &x);

    printf("Введите максимальное N для таблицы (например, 20): ");
    scanf("%d", &maxN);

    printf("Введите точность eps (например, 0.000001): ");
    scanf("%lf", &eps);

    double res_lib = sin(x);
    double res_eps = sin_eps(x, eps);

    printf("\n___Сравнение основных результатов___\n");
    printf("Стандартная библиотека sin(x) : %.10f\n", res_lib);
    printf("Через точность eps (%g)       : %.10f (отклонение: %.10e)\n\n", eps, res_eps, fabs(res_lib - res_eps));

    printf("Таблица сходимости (число членов ряда N):\n\n");
    printf(" N |    sin_N    |   отклонение\n");
    tabl(maxN, x);

    float d1, d2, alpha;
    char symb;

    printf("___Задание 3___\n\n");

    printf("Введите значение d1 (высота): ");
    scanf("%f", &d1);

    printf("Введите значение d2 (ширина): ");
    scanf("%f", &d2);

    printf("Введите угол alpha (в градусах): ");
    scanf("%f", &alpha);

    printf("Введите символ для рисования фигуры: ");
    scanf(" %c", &symb);

    do {
        printf("\n_________МЕНЮ ВЫБОРА_________\n");
        printf("1) Рассчитать площадь\n");
        printf("2) Вывести определение фигуры\n");
        printf("3) Нарисовать фигуру\n");
        printf("4) Выход\n");
        printf("Выберите операцию (1-4): ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nПлощадь четырёхугольника S = %.2f\n", area_quad(d1, d2, alpha));
            break;

        case 2:
            print_definition();
            break;

        case 3:
            draw_quad((int)d1, (int)d2, (double)alpha, symb);
            break;

        case 4:
            printf("\nЗавершение работы программы.\n");
            break;
        }

    } while (choice != 4);

    return 0;
}