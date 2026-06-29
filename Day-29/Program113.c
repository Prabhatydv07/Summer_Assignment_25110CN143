#include<stdio.h>
#include<math.h>


void print_menu() {
      printf("\n\n\n-------------------------------------------------");
      printf("\n Welcome To Simple Calculator \n");
      printf("\nChoose One Of The Following Options : ");
      printf("\n1.Addidtion");
      printf("\n2.Substracion");
      printf("\n3.Multiplication");
      printf("\n4.Division");
      printf("\n5.Modulus");
      printf("\n6.Power");
      printf("\n7.Exit");
      printf("\nNow, Enter Your Choice :");

}

double Division(double a , double b){
   if(b==0) {
      fprintf(stderr, "Invalid Argument For Division ");
      return 0;
   }

   else{
      return a/b;
   }


}

int Modulus(int  a , int  b) {
   if(b==0) {
      fprintf(stderr, "Invalid Argument For Modulus ");
      return 0;
   }

   else{
      return a%b;
   }
   
}

int main() {
   int choice;
   double first,second,result;
   while(1){
      print_menu();
      scanf("%d", &choice);
      if(choice == 7) {
         break;
      }
      else if(choice > 7 || choice < 1) {
         printf("Invalid Choice Run Program Again !!!\n");
         break;
      }

      printf("\nPlease Enter The First Number : ");
      scanf("%lf", &first);
      printf("Now, Enter The Second Number : ");
      scanf("%lf", &second);

      switch (choice) {
         case 1:
           result = first + second;
           break;
         case 2:
            result = first - second;
            break;
         case 3:
            result = first * second;
           break;
         case 4:
            Division(first, second);
           break;
         case 5:
            result = Modulus(first, second);
           break;
         case 6:
            result = pow(first,second);
           break;
         default:
           break;
      }

      if(!isnan(result)) {
         printf("\nResult Of Operation Is : %.2f ", result);
      }
      
   };
   return 0;
}