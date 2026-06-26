#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {
   srand(time(NULL));
   printf("Welcome To The Game Of Guessing Number\n");
   int nguess=0;
   int random, guess;
   random = rand() % 100 + 1; //Generating Between 0 to 100

   do {
    printf("Please Enter Your Guess Between 1 and 100 : ");
    scanf("%d", &guess);
    nguess++;
    if(guess < random) {
        printf("Guess Larger Number\n");
    }
    else if(guess > random) {
        printf("Guess Smaller Number\n");
    }
    else{
        printf("Congratulations!!!\n");
        printf("You Have Gueesed Correct Number In %d Attempts", nguess);
    }

     }while(guess != random);

   printf("\nBye Bye, Thanks For Playing.");
   printf("\n Developed By --- Prabhat Yadav");
   return 0;
}