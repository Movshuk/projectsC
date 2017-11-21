//#include <iostream>
#include <locale.h>
#include <string.h>
//#include <math.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

//using namespace std;

bool find_space(char *plimit_string, int *plength_limit)
{
    int basket = 0;
    for (int i = 0; i < *plength_limit; i++){
        if (*(plimit_string+i) == ' '){
            basket++;
        }
    }
    if (basket == 0){
        return false;
    }
    else{
        return true;
    }
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    printf("<1.> Ввести строку символов. \n<2.> Если ее длина >6, выделить подстроку после последнего пробела.\n\n");
    printf("-------------------------------------------------\n\n");

    char *string, *limit_string, *endl_string, *behind_string;
    int length_string;
    int length_limit = 6;
    int space_index;
    int behind_lenght;
    bool is_space;

    string = new char[80];

    do{
        printf("Введите строку символов: ");
        fflush(stdin);
        gets(string);
        length_string = strlen(string);
    }while(length_string == 0);

    printf("Заданная строка: [%s] \n\nДлина заданной строки: [%d] символов.\n\n", string, length_string);

    if (length_string <= length_limit){
        printf("Длина строки не более установленного лимита.\n");
        exit; // *********
    }
    else{
        limit_string = new char[7];
        strncpy(limit_string, string, length_limit);
        limit_string[length_limit] = '\0';
        is_space = find_space(limit_string, &length_limit);
        if (!is_space){
            printf("В подстроке [%s] нет пробелов.\n", limit_string);
        }
        else{
            printf("В подстроке [%s] есть пробельные символы.\n", limit_string);
            for (int j = length_limit; j > 0; j--){    // поиск последнего пробела в подстроке в 6 символов
                 if (limit_string[j] == ' '){
                     space_index = j;
                     printf("Номер последнего пробела: [%d] \n\n", space_index);
                     break;
                 }
            }
            endl_string = new char[6];
            strncpy(endl_string, limit_string, space_index);
            endl_string[space_index] = '\0';

            behind_lenght = length_string - space_index;
            behind_string = new char[behind_lenght];

            for (int n = 0; n < behind_lenght; n++){
               int t = space_index + n;
               behind_string[n] = string[t];
            }
            behind_string[behind_lenght] = '\0';

            printf("Подстрока в %d символов до последнего пробела: [%s].\nОтброшенный кусок строки <%s>\n", length_limit, endl_string, behind_string);
            delete[] behind_string;
        }
    }

    delete[] string;
    delete[] limit_string;
    delete[] endl_string;

    return 0;
}

