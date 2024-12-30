#include <stdio.h>
#include <time.h>


int input_choice();
void fill_time(char*, int);
void fill_date(char*);
void fill_day(char*);

int main(){
    char time[50], date[100], day[10];
    int choice = input_choice();

    fill_day(day);
    fill_date(date);  
    fill_time(time, choice);
    printf("\n Date : %s", date);                                    //display date
    printf("\n Day  : %s", day);                                     //display day                                      
    printf("\n Time : %s", time);                                    //display current time 

    return 0;
}

int input_choice(){
    int choice;

    printf("\n Choose the time format  ");
    printf("\n 1. 24 Hour format ");
    printf("\n 2. 12 Hour format (default) ");                         //default if in case user dont enter choice then format will be of 12hrs 
    printf("\n Enter your choice (1/2) :  ");
    scanf("%d", &choice);
    return choice;

}

void fill_time(char* buffer, int choice){                               
    time_t raw_time ;                                                  // to get raw time format
    struct tm *current_time;                                           // struct tm is a defined in struct in time.h which will give current time 

    time(&raw_time);                                                   //time will fill the current time of system in raw_time
    current_time = localtime(&raw_time);                               //localtime will convert the raw time in local country timezone "time"

    if(choice == 1){
        strftime(buffer, 50, "%H:%M:%S %p", current_time);             //(struct format time) will print the time in format of user choice {%I for 12hrs and %H for 24hrs}
    }   
    else {                            
       strftime(buffer, 50, "%I:%M:%S %p", current_time);
    }
}

void fill_date(char*buffer){
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time);                                  // same as above function but this will print the date 

    strftime(buffer, 100, "%B %d, %Y", current_time);                     //  %B = month, %d = date, %Y = year    

}

void fill_day(char*buffer){
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time);

    strftime(buffer, 10, "%A", current_time);                             // %A = day of the week

}