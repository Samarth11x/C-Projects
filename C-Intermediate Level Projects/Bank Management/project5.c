#include <stdio.h>
#include <string.h>
 


typedef struct {
    char name [50];
    int Acc_number;
    char address [50];
    int contact_no;
    int pin;
    float balance;
} account ;

const char* ACCOUNT_FILE = "account.dat";

void print_menu(int choice, int option );
void create_account();
void view_account_details();
void edit_account_details();
void Delete_account();
void fix_fgets_input(char*);

void deposit_money();
void withdraw_money();
void check_balance();
 

int main() {
   int choice = 0, option = 0;
    FILE *file = fopen(ACCOUNT_FILE, "ab+");
   print_menu(choice, option);
}


void print_menu(int choice, int option ){
    while(1){
    printf("\n_______________________________________________\n");
    printf("\n \t SBI welcomes You!!\n");
    printf("\n1. Account Management");
    printf("\n2. Transaction");
    printf("\n3. Fund Transfer");
    printf("\n4. Exit\n");

    printf("\n-> Enter Your Choice : ");
    scanf("%d", &choice);
    
    switch (choice){
        case 1 : printf("\n-*Account management*-\n");
        printf("\n1. create Bank Account");
        printf("\n2. view Account Details");
        printf("\n3. Edit Account Details");
        printf("\n4. Delete Account");
        printf("\n5. Back\n");
        
        printf("\n-> Choose your option : ");
        scanf("%d", &option);

        switch(option){
            case 1 :
            create_account();
            break;
            case 2 : view_account_details();
            break;
            case 3 : edit_account_details();
            break;
            case 4 : Delete_account();
            break ;
            case 5 : printf("\nBack to Main Menu \n");
            return ;
            default : printf("Invalid Choice!! \n Enter Correct Option !! \n");
            break ;
        }
        break;

        case 2 : printf("\n -*Transaction*-");
        printf("\n1. Deposit Money");
        printf("\n2. Withdraw Money");
        printf("\n3. Check Bank Balance");
        printf("\n4. Back\n");

        printf("\n-> Choose your option : ");
        scanf("%d", &option);

        switch(option){
            case 1 : deposit_money();
            break;
            case 2 : withdraw_money();
            break;
            case 3 : check_balance();
            break;
            case 4 : printf("\nBack to Main Menu \n");
            return ;
            default : printf("Invalid Choice!! \n Enter Correct Option !! \n");
            break ;
        }
        break;

        case 4 :printf("\n\tClosing the bank!!\n    Thank you for your visit :)\n");
        return ;
        break ;

        default : printf("\t Invalid Choice!! \n\t Enter Correct Choice !!");
        break ;
    }
}

}

void create_account(){
    account acc;
    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    if(file == NULL ){
        printf("\n Unable to open file !!\n");
        return ;
    }

    char ch ;
    do{
        ch = getchar();
    }while (ch != '\n' && ch != EOF);

    printf("\nEnter your Name : ");
    fgets(acc.name, sizeof(acc.name), stdin);
    fix_fgets_input(acc.name);

    printf("\nEnter your Account Number : ");
    scanf("%d", &acc.Acc_number);
   
    do{
        ch = getchar();
    }while (ch != '\n' && ch != EOF);

    printf("\nEnter your Address : ");
    fgets(acc.address, sizeof(acc.address), stdin);
    fix_fgets_input(acc.address);

    printf("\nEnter your Contact Number : ");
    scanf("%d", &acc.contact_no);

    printf("\nCreate your Pin (6-digit) : ");
    scanf("%d", &acc.pin);

    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\nAccount created successfully!!\n");

}

void view_account_details() {
  FILE *file = fopen(ACCOUNT_FILE, "rb");  
  if(file == NULL ){
        printf("\n Unable to open file !!\n");
        return ;
    }

    int acc_no;
    account acc_read;

    printf("Enter your Account Number : ");
    scanf("%d", &acc_no);


    while(fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.Acc_number == acc_no){
            printf("\nAccount Holder Name = %s", acc_read.name);
            printf("\nAcc. Number = %d", acc_read.Acc_number);
            printf("\nAddress = %s", acc_read.address);
            printf("\nContact No. = %d", acc_read.contact_no);
            printf("\nAvailable Balance : Rs. %.2f\n", acc_read.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("\n Account No. %d was not found.\n", acc_no);
}

void edit_account_details(){
    printf("1");
}

void Delete_account(){
    printf("1");
}

void fix_fgets_input(char* string){
    int index = strcspn(string, "\n");
    string[index] = '\0';
}

void deposit_money(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL){
        printf("\n Unable to find file !! \n");
        return;
    }

    int acc_no;
    int acc_pin;
    account acc_r;
    float money;

    printf("Enter your Account no. : ");
    scanf("%d", &acc_no);
    printf("Enter your Pin (6-digit) : ");
    scanf("%d", &acc_pin);
    printf("Enter amount to deposit : ");
    scanf("%f", &money);

    while(fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if(acc_r.Acc_number == acc_no && acc_r.pin == acc_pin){
            acc_r.balance += money;
            fseek(file, -(long int)sizeof(acc_r), SEEK_CUR);
            fwrite(&acc_r, sizeof(acc_r), 1, file);
            fclose(file);
            printf("Successfully Deposited Rs.%.2f \nYour current Balance is Rs. %.2f", money, acc_r.balance);
            return;
        }
    }
    fclose(file);
    printf("\n Account No. %d was not found in records.\nyour money could not be deposited !!", acc_no);
}

void withdraw_money(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL ){
        printf("Unable to access the file.!!");
        return ;
    }

    int acc_no;
    int acc_pin;
    float money;
    account acc_rea;
    
    printf("Enter account no : ");
    scanf("%d", &acc_no);
    printf("Enter your pin (6-digit) : ");
    scanf("%d", &acc_pin);
    printf("Enter withdrawal amount : ");
    scanf("%f", &money);

    while(fread(&acc_rea, sizeof(acc_rea), 1, file))
    {
        if(acc_rea.Acc_number == acc_no && acc_rea.pin == acc_pin){
            acc_rea.balance -= money;
            fseek(file , -(long int)sizeof(acc_rea), SEEK_CUR );
            fwrite(&acc_rea, sizeof(acc_rea), 1, file);
            fclose(file);
            printf("\nRs. %.2f Withdrawn Successfully from you bank account of account no %d\nYour current balance is Rs.%.2f\n", money, acc_no, acc_rea.balance);
            return;
        }

    }
    fclose(file);
    printf("\nAccount No. %d was not found in records. \nYour can not withdraw your amount");
}

void check_balance(){
     FILE *file = fopen(ACCOUNT_FILE, "rb");  
  if(file == NULL ){
        printf("\n Unable to open file !!\n");
        return ;
    }

    int acc_no;
    int acc_pin;
    account acc_re;

    printf("Enter your Account Number : ");
    scanf("%d", &acc_no);
    printf("Enter your Pin (6-digit) : ");
    scanf("%d", &acc_pin);


     while(fread(&acc_re, sizeof(acc_re), 1, file)){
        if(acc_re.Acc_number == acc_no && acc_re.pin == acc_pin){
            printf("\nAvailable Balance : Rs. %.2f\n", acc_re.balance);
            fclose(file);
            return;
        }
    }
    printf("\n Account No. %d was not found in records.\n", acc_no);
    fclose(file);
}