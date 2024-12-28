#include <stdio.h>
#include<stdlib.h>  // to generate random number
#include<time.h>    // to seed random number using current time

int main(){
    int random, guess;
    int no_of_attempts = 0;      // Initialize the number of attempts

    srand(time(NULL)); 
     // srand = seed random number 
    //  (time(NUll)) = using current time to seed the random number generator


    printf("\n \t * Welcome to NUMBER GUESSING game *\n");

    random = (rand() % 20 + 1 );
    // rand() % 20  will give values from 1 - 19 (+1) to do 1 - 20 


    do{
        printf("\nEnter a Number between (1 - 20) : ");
        scanf("%d", &guess);
        no_of_attempts++;     // increment the attempt count each time the user enters a number 

        if(random > guess){
            printf("Guess a greater number.\n");
        }
        else if(random < guess){
            printf("Guess a  smaller number.\n");
        }
        else{
            printf("\n \t Congratulations !! \n You have guessed a right Number in %d attempt\n", no_of_attempts );
        }

    }while(guess != random);


    printf("\n \t Thank you :) \nHope you enjoyed the game \n");
    printf("\nDeveloped by : SAM \n");


    return 0;
}