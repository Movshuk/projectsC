// Консольная программа. Загружает текст, запрашивает слово от пользователя, ищет его порядковый номер
// в каждом предложении.
// Простая версия
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <cctype>

void text_menu();
int chois_menu();
void open_to_print_file();
void find_pos_word();
void exit();
int main()
{
    setlocale(LC_CTYPE, "Russian");
    bool work_program = true;
    text_menu();
    while(work_program) {
        switch (chois_menu())
        {
            case 1:
                open_to_print_file();
                break;
            case 2:
                find_pos_word();
                break;
            case 0:
                exit();
                break;
        }
    }
    return 0;
}
// завершение программы
void exit()
{
    printf("> Вы нажали [0]. Работа с программой завершена.\n");
    exit(10);
}
// содержание меню
void text_menu()
{
    printf("Меню программы:\n");
    printf("[1] - Прочитать текст из файла;\n");
    printf("[2] – Найти порядковый номер слова в каждом предложении текста;\n");
    printf("[0] – Выход.\n");
    printf("\n\n");
}
// обработка выбора позиции меню
int chois_menu()
{
    int index;
    do
    {
      printf(">> Выберите пункт меню:");
      scanf("%d", &index);
    } while(index < 0 || index > 2);
    printf("\n");
    return index;
}
// открытие файла и его чтение
void open_to_print_file() {
    printf("> Вы нажали [1].\n");
    FILE *f;
    char f_text[1001];
    if ((f = fopen("путь к файлу", "r")) == NULL) {
        printf("Ошибка открытия файла!\n");
        exit(101);
    }
    printf("> Чтение текста из файла: \n");
    while (fgets(f_text, 70, f) != NULL) {
        printf("%s", f_text);
    }
    printf("\n");
    fclose(f);
}
// поиск слова в тексте
void find_pos_word() {
    printf("> Вы нажали [2].\n");
    FILE *f;
    if ((f = fopen("путь к файлу", "r")) == NULL) {
        printf("Ошибка открытия файла!\n");
        exit(101);
    }
    int i=0;
    int strs_count = 0;
    int words_count = 1;
    char textToStr[1020]; // считанный текст из файла в строку с \n
    while (getchar() != '\n');
    // считается в тексте разделитель (' ', ',')
    while((textToStr[i] = fgetc(f)) != EOF){
        if(textToStr[i] == '.') {
           strs_count++;    // количество предложений в тексте
        }
        if(textToStr[i] == ' ') {
           words_count++;   // количество слов в тексте
        }
        i++;
    }
    textToStr[i] = '\0';
    // рафинирование строки
    char onlyWordsFromStr[1020];
    int lenght = strlen(textToStr);
    int w = 0; // счетчик
    for (int q=0; q < lenght; q++) {
        if ((textToStr[q] == ',' || textToStr[q] == '\n') || (textToStr[q] == ' ' && textToStr[q-1] == '.')) {
            continue;
        }
        else {
            onlyWordsFromStr[w] = toupper(textToStr[q]);
            w++;
        }
    }
    onlyWordsFromStr[w] = '\0';
    int ***arr = new int**[30];
    for(int i=0; i<30; i++){
        arr[i] = new int*[30]; //выделяем память на столбцы
        for(int j=0; j<30;j++){
            arr[i][j] = new int[30]; //выделяем память на строки.
        }
    }
    int a = 0; int e = 0; int o = 0;
    for (int n=0; n < strlen(onlyWordsFromStr); n++) {
        if(onlyWordsFromStr[n] == ' ') {
            *(*(*(arr+a)+e)+o) = '\0'; // добавляю \0
            e++;
            o = 0;
            continue;
        }
        if(onlyWordsFromStr[n] == '.') {
            o = 0;
            *(*(*(arr+a)+e+1)+o) = '.'; // в новом слове  точка
            a++;
            e = 0;
            continue;
        }
            *(*(*(arr+a)+e)+o) = onlyWordsFromStr[n]; // [23][2] => [24][1][0]
            //printf("пункт строки {%d} = {%c} ", n, onlyWordsFromStr[n]);
            //printf("[%d][%d][%d] = {%c}\n", a, e, o, *(*(*(arr+a)+e)+o)); // тест номера ячеек
            o++;
    }
    // запрос слова для поиска
    char wordToFind[30]; // ограничение длины
    int lenghtWord;
    do {
        printf("\n> Введите слово для поиска: ");
        gets(wordToFind);
        lenghtWord = strlen(wordToFind);
    } while (lenghtWord == 0); // ввод пока не пусто
    int ii=0; // будет длина введенного слова
    for (ii; ii < lenghtWord; ii++) {
        wordToFind[ii] = toupper(wordToFind[ii]);
    }
    int yesWord = 0;
    for (int a=0; a < strs_count;a++) {
        for (int e=0; *(*(*(arr+a)+e)+0) != '.'; e++) {
            int count = 0;
            for (int o=0; *(*(*(arr+a)+e)+o);o++) {
                if (wordToFind[o] == *(*(*(arr+a)+e)+o)) {
                    count++;
                }
                if (count == ii && (*(*(*(arr+a)+e)+ii + 1) == '\0')) {
                    printf("\nСлово встречается на позиции: предл [%d] номер слова [%d]\n", a+1, e+1);
                    yesWord++;
                    break;
                }
            }
        }
    }
    if (yesWord == 0) {
        puts("ERROR: Заданного слова не встречается в этом тексте!");
    }
    // освобождаем память от матрицы слов
    for(int i=0; i<30; i++) {
        for(int j=0; j<30; j++) {
            delete[] *(*(arr+i)+j); // удаляем лист слов и символов
        }
    }
    delete[] arr; // удаляем лист предложений
    //while (getchar() != '\n'); // ловим поток
}
