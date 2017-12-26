// программа переводит положительное десятичное числов в двоичное
#include <iostream>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Russian");
    int decNumber,
        startDecNumber,
        baseNum,
        bin;
    baseNum = 2; // база двоичной системы
    int tmpNumber[30]; // массив под запись двоичного число
    printf("Введите десятичное число:");
    scanf("%d", &decNumber);
    startDecNumber = decNumber; // сохраняем превоначально введенное число
    // проверяем введеное число, если ноль:
    if (decNumber == 0) {
        printf("Число %d в двоичной системе записывается: ", decNumber);
        printf("%d", decNumber);
        printf("\n");
    }
    // если не ноль,то:
    else {
        int i = 0;
        // формируем набор из чисел составляющих будущее двоичное число
        while(decNumber >= 1) {
            bin = decNumber % baseNum; // остаток от деления на 2
            tmpNumber[i] = bin;
            decNumber = decNumber / baseNum;
            i++;
        }
        printf("\n");
        int binNumber[i];
        int x = i-1;
        // переворачиваем набор чисел
        for(int y=0; y < i; y++) {
            while(x >= 0){
                binNumber[y] = tmpNumber[x];
                break;
            }
            x--;
        }
        // вывод на экран полученного двоичного числа
        printf("Число %d в двоичной системе записывается: ", startDecNumber);
        for(int y=0; y < i; y++) {
            printf("%d", binNumber[y]);
        }
        printf("\n");
    }
    return 0;
}

