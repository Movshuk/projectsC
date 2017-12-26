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
    int tmpNumber[30]; // массив под двоичное число
    printf("Введите десятичное число:");
    scanf("%d", &decNumber);
    startDecNumber = decNumber; // сохраняем превоначально введенное число
    if (decNumber == 0) {
        printf("Число %d в двоичной системе записывается: ", decNumber);
        printf("%d", decNumber);
        printf("\n");
    }
    else {
        int i = 0;
        while(decNumber >= 1) {
            bin = decNumber % baseNum; // остаток от деления на 2
            tmpNumber[i] = bin;
            decNumber = decNumber / baseNum;
            i++;
        }
        printf("\n");
        int binNumber[i];
        int x = i-1;
        for(int y=0; y < i; y++) {
            while(x >= 0){
                binNumber[y] = tmpNumber[x];
                break;
            }
            x--;
        }
        printf("Число %d в двоичной системе записывается: ", startDecNumber);
        for(int y=0; y < i; y++) {
            printf("%d", binNumber[y]);
        }
        printf("\n");
    }
    return 0;
}

