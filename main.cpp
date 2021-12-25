//
//  main.cpp
//  cursovaya
//
//  Created by Андрей Осадченко on 08.11.2021.
//


#include <stdio.h>
#include <string.h>
#include <locale.h>


int COUNTER = 0;

void database_delete(void);
void database_save(void);
void add_control(void);
void price_check(void);
void database_load(void);
int menu(void);
void database_print(int numb);
void minimal_time(void);
void database_rewrite(void);

struct Item_avia{
    char start_city[100];
    char end_city[100];
    int price, time_start,time_go;
};

struct Item_avia avia[1000];


int main() {
    setlocale(LC_ALL, "russian");
    database_load();
    for(;;){
        int temp = menu();
        if(temp == 1){
            add_control();
        } else if(temp == 2){
            database_delete();
        } else if (temp == 3){
            database_rewrite();
        } else if (temp == 4){
            price_check();
        } else if (temp == 5){
            minimal_time();
        } else if (temp == 6){
            for(int i = 0; i < COUNTER; i++){
                database_print(i);
            }
        } else if (temp == 7){
            database_save();
            return 0;
        }
        
    }

    return 0;
}


int menu(){
    int n;
    printf("Введите:\n 1 - для записи\n 2 - для удаления\n 3 - для перезаписи\n 4 - для подбора маршрута с минимальной стоимостью\n 5 - для подбора маршрута с минимальным временем ожидания\n 6 - вывода всей базы\n 7 - для выхода\n");
    scanf("%i",&n);
    return n;
}


void minimal_time(){
    char str[100],str1[100];
    int arrival_time, min_time = -1, city_one = 0, city_two = 0;
    printf("Введите город откуда летим: ");
    scanf("%s", str);
    printf("Введите город куда летим: ");
    scanf("%s", str1);
    for(int i = 0; i < COUNTER; i++){
        if(strcmp(str, avia[i].start_city) == 0){
            for(int j = 0; j < COUNTER; j++){
                if((strcmp(avia[i].end_city, avia[j].start_city) == 0) && (strcmp(str1, avia[j].end_city) == 0)){
                    arrival_time = avia[i].time_start + avia[i].time_go;
                    if(arrival_time < avia[j].time_start){
                        if(min_time == -1){
                            min_time = avia[j].time_start - arrival_time;
                            city_one = i;
                            city_two = j;
                        }
                        else{
                            int temp_time = avia[j].time_start - arrival_time;
                            if(temp_time < min_time ){
                                min_time = temp_time;
                                city_one = i;
                                city_two = j;
                            }
                        }
                    }
                }
            }
        }
    }
    if(min_time > 0){
        printf("время ожидания составит: %i минут\n", min_time);
        database_print(city_one);
        database_print(city_two);
    }else{
        printf("Error\n");
    }
}


void database_print(int numb){
    printf("%s - %s ", avia[numb].start_city, avia[numb].end_city);
    int hour = avia[numb].time_start / 60, minutes = avia[numb].time_start % 60;
    printf("время: %i:%i стоимость: %i\n",hour, minutes, avia[numb].price);
    
}

void database_load(){
    FILE *f;
    f = fopen("/Users/andrey/Desktop/code/kursovaya/cursovaya/data.txt", "r");
    fscanf(f,"%i", &COUNTER);
    for(int i = 0; i < COUNTER; i++){
        fscanf(f,"%s", avia[i].start_city);
        fscanf(f,"%s", avia[i].end_city);
        fscanf(f,"%i", &avia[i].price);
        fscanf(f,"%i", &avia[i].time_start);
        fscanf(f,"%i", &avia[i].time_go);
    }
}


void price_check(){
    int numb = 0, minimal = 999999;
    char str[100], str1[100];
    printf("Введите город откуда летим: ");
    scanf("%s", str);
    printf("Введите город куда летим: ");
    scanf("%s", str1);
    for(int i = 0; i < COUNTER;i++){
        if((strcmp(str, avia[i].start_city) == 0) && (strcmp(str, avia[i].end_city) != 0)){
            if(avia[i].price < minimal){
                minimal = avia[i].price;
                numb = i;
            }
        }
    }
    printf("Ситомость составит: %i\n", minimal);
    database_print(numb);
}

void database_delete(){
    int number;
    for(int i = 0; i < COUNTER; i++){
        database_print(i);
    }
    printf("Введите нормер записи которую удалить: ");
    scanf("%i", &number);
    number--;
    
    for(int i = number; i < COUNTER - 1; i++){
        avia[i] = avia[i + 1];
    }
    
    COUNTER--;
 
}


void database_rewrite(){
    int numb;
    for(int i = 0; i < COUNTER; i++){
        database_print(i);
    }
    printf("какую строку изменть: ");
    scanf("%i", &numb);
    numb++;
    printf("Введите город из которого вылетаем: ");
    scanf("%s", avia[numb].start_city);
    printf("Введите горрд в который летим: ");
    scanf("%s", avia[numb].end_city);
    printf("Введите стоимость полета: ");
    scanf("%i", &avia[numb].price);
    printf("Введите время вылета (часы пробел минуты): ");
    int hour, min;
    scanf("%i%i",&hour, &min);
    avia[COUNTER].time_start = hour * 60 + min;
    printf("Введите время полета: ");
    scanf("%i", &avia[numb].time_go);
}


void add_control(){
    printf("Введите город из которого вылетаем: ");
    scanf("%s", avia[COUNTER].start_city);
    printf("Введите горрд в который летим: ");
    scanf("%s", avia[COUNTER].end_city);
    printf("Введите стоимость полета: ");
    scanf("%i", &avia[COUNTER].price);
    printf("Введите время вылета (часы пробел минуты): ");
    int hour, min;
    scanf("%i%i",&hour, &min);
    avia[COUNTER].time_start = hour * 60 + min;
    printf("Введите время полета: ");
    scanf("%i", &avia[COUNTER].time_go);
    COUNTER++;
    
}


void database_save(){
    FILE *f;
    f = fopen("/Users/andrey/Desktop/code/kursovaya/cursovaya/data.txt", "w");
    fprintf(f,"%i\n", COUNTER);
    for(int i = 0; i < COUNTER; i++){
        fprintf(f,"%s\n", avia[i].start_city);
        fprintf(f,"%s\n", avia[i].end_city);
        fprintf(f,"%i\n", avia[i].price);
        fprintf(f,"%i\n", avia[i].time_start);
        fprintf(f,"%i\n", avia[i].time_go);
    }
}
