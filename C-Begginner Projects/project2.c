#include<stdio.h>
#include<math.h>


void print_menu();
double divide(double a, double b);
double modulus(int a, int b);

int main(){
    int choice;
    double first, second, result;

    while(1){
        print_menu();
        printf("\n \nEnter your choice : ");
        scanf("%d", &choice);

        if(choice == 7){
            printf("\n \tThank You :)\n");
            break;
        }

        if(choice <1 || choice > 7){
            fprintf(stderr,"\n \t Invalid menu choice\n");
            continue;
        }
       
        printf("\nEnter you first number : ");
        scanf("%lf", &first);

        printf("Enter you second number : ");
        scanf("%lf", &second);
       


        switch (choice)
        {
        case 1 : //add
        result = first + second ;
            break;

        case 2 : //subtract
        result = first - second ;
            break;
            
        case 3 : //multiply
        result = first * second ;
            break;
        
        case 4 : //divide
        result = divide(first, second) ;
            break;

        case 5 : //modulus
        result = modulus (first, second) ;
            break;
        
        case 6 : //power
        result = pow(first, second);
            break;
            
        }

        if(!isnan(result)){  // !isnan - if result is not NAN then it will  print result 
        printf("\nResult of the operation is : %.2f", result);
        }

    };

    return 0;
}

void print_menu(){
     printf("\n \t _______________________________________________\n");

    printf("\n \t Welcome to the SIMPLE CALCULATOR\n");

        printf("\tPlease select your choice from given menu");
        printf("\n1.Add");
        printf("\n2.Subtract");
        printf("\n3.Multiply");
        printf("\n4.Divide");
        printf("\n5.Modulus");
        printf("\n6.Power");
        printf("\n7.EXIT");

}

double divide(double a, double b){
    if(b == 0){
        fprintf(stderr, "Invalid argument of division "); // fprintf (std function) to print an std err 
        return NAN; // NAN = NOT A NUMBER 
    }
    else{
     return a / b;
    }
}

double modulus(int a, int b){
    if(b==0){
        fprintf(stderr, "Invalid argument of modulus "); // fprintf (std function) to print an std err 
        return NAN; // NAN = NOT A NUMBER 
    }
    else if (b > 0){
     return a % b;
    }
}