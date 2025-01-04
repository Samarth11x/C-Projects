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
void verification(int* acc_No, int* acc_pin);
void view_account_details();
void edit_account_details();
void edit_Name();
void edit_Address();
void edit_contact_No();
void edit_pin();
void Delete_account();
void fix_fgets_input(char*);

void deposit_money();
void withdraw_money();
void check_balance();

void fund_transfer();
 

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
            continue;
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
            continue;
            return ;
            default : printf("Invalid Choice!! \n Enter Correct Option !! \n");
            break ;
        }
        break;

        case 3 : fund_transfer();
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

    printf("Enter your Account Number : ");
    scanf("%d", &acc.Acc_number);
   
    do{
        ch = getchar();
    }while (ch != '\n' && ch != EOF);

    printf("Enter your Address : ");
    fgets(acc.address, sizeof(acc.address), stdin);
    fix_fgets_input(acc.address);

    printf("Enter your Contact Number : ");
    scanf("%d", &acc.contact_no);

    printf("Create your Pin (6-digit) : ");
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
    int acc_pin;
    account acc_read;
    verification(&acc_no, &acc_pin);

    while(fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.Acc_number == acc_no && acc_read.pin == acc_pin){
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

void verification(int* acc_no, int* acc_pin){
    printf("Enter your Account Number : ");
    scanf("%d", &(*acc_no));
    printf("Enter your PIN (6-digit) : ");
    scanf("%d", &(*acc_pin));
    return;
}

void edit_account_details(){
    int choice;
    
    
    printf("\n-*Choose the Option*-");
    printf("\n1.Name");
    printf("\n2.Address");
    printf("\n3.Contact Number");
    printf("\n4.PIN");
    printf("\n5.Back\n");

    printf("\n-> Enter your choice : ");
    scanf("%d", &choice);


        switch(choice){
            case 1 : edit_Name();
            break;

            case 2 : edit_Address();
            break;

            case 3 : edit_contact_No();
            break;

            case 4 : edit_pin();
            break;

            case 5 : printf("\nBack to Menu \n");
            return;
            break;

            default : printf("Invalid Choice!! \n Enter Correct Option !! \n");
            break;
        
        }
    
}

void edit_Name(){
    FILE *file = fopen (ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("\nUnable to access the file.\n");
        return;
    }
    int acc_no;
    int acc_pin;
    verification(&acc_no, &acc_pin);
    account acc_read;
    char NEW_name [50];
    char ch ;
    do{
        ch = getchar();
    }while(ch != '\n' && ch != EOF);
    printf("Enter your New Name : ");
    fgets(NEW_name, sizeof(NEW_name), stdin);
    fix_fgets_input(NEW_name);

    while(fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.Acc_number == acc_no && acc_read.pin == acc_pin){
            strcpy(acc_read.name, NEW_name);
            fseek(file,-(long int)sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);
            printf("\nYour Name Changed successfully!!\n");
            return ;
        } 
    }
    fclose(file);
    printf("\nAccount No. %d was not found in records or incorrect PIN.\n", acc_no);


}

void edit_Address(){
    FILE *file = fopen (ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("\nUnable to access the file.\n");
        return;
    }
    int acc_no;
    int acc_pin;
    verification(&acc_no, &acc_pin);
    account acc_read;
    char NEW_add [50];
    char ch ;
    do{
        ch = getchar();
    }while(ch != '\n' && ch != EOF);
    printf("Enter your New Address : ");
    fgets(NEW_add, sizeof(NEW_add), stdin);
    fix_fgets_input(NEW_add);

    while(fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.Acc_number == acc_no && acc_read.pin == acc_pin){
            strcpy(acc_read.address, NEW_add);
            fseek(file,-(long int)sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);
            printf("\nYour Address Updated successfully!!\n");
            return ;
        } 
    }
    fclose(file);
    printf("\nAccount No. %d was not found in records or incorrect PIN.\n", acc_no);

}

void edit_contact_No(){
    FILE *file = fopen (ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("\nUnable to access the file.\n");
        return;
    }
    int acc_no;
    int acc_pin;
    verification(&acc_no, &acc_pin);
    account acc_read;
    int New_contact;

    printf("Enter your New Contact no. : ");
    scanf("%d", &New_contact);

    while (fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.Acc_number == acc_no && acc_read.pin == acc_pin){
            acc_read.contact_no = New_contact;
            fseek(file, -(long int)sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);
            printf("\nYour Contact No. *+91 %d* Updated successfully !!\n", New_contact);
            return;
        }
    }
    fclose(file);
    printf("\nAccount No. %d was not found in records or incorrect PIN.\n", acc_no);

}

void edit_pin(){
    FILE* file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("\nUnable to access the File\n");
        return;
    }

    int acc_no;
    int acc_pin;

    account acc_read;
    int NEW_Pin;

    verification(&acc_no, &acc_pin);
    printf("Enter Your New PIN (6-digit) : ");
    scanf("%d", &NEW_Pin);

    while(fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.Acc_number == acc_no && acc_read.pin == acc_pin){
            acc_read.pin = NEW_Pin;
            fseek(file, -(long int)sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);
            printf("\nYour New Pin Updated Successfully!!\n");
            return;
        }
    }
    fclose(file);
    printf("\nAccount No. %d was not found in records or incorrect PIN.\n", acc_no);

}


void Delete_account(){
    printf("function Not Build Yet !");
}

void fix_fgets_input(char* string){
    int index = strcspn(string, "\n");
    string[index] = '\0';
}

void deposit_money(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL){
        printf("\n Unable to access the file !! \n");
        return;
    }

    int acc_no;
    int acc_pin;
    account acc_read;
    float money;

    verification (&acc_no, &acc_pin);
    printf("Enter amount to deposit : ");
    scanf("%f", &money);

    while(fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if(acc_read.Acc_number == acc_no && acc_read.pin == acc_pin){
            acc_read.balance += money;
            fseek(file, -(long int)sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);
            printf("Successfully Deposited Rs.%.2f \nYour New Balance is Rs. %.2f", money, acc_read.balance);
            return;
        }
    }
    fclose(file);
    printf("\nAccount No. %d was not found in records or incorrect PIN.\n", acc_no);
    printf("\nYour money Can not be Deposited");
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
    account acc_read;
    
    verification (&acc_no, &acc_pin);

    printf("Enter withdrawal amount : ");
    scanf("%f", &money);

    while(fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if(acc_read.Acc_number == acc_no && acc_read.pin == acc_pin){
           if(acc_read.balance >= money){
           acc_read.balance -= money;
            fseek(file , -(long int)sizeof(acc_read), SEEK_CUR );
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            printf("\nRs. %.2f Withdrawn Successfully from you bank account of account no %d\nAvailable balance is Rs.%.2f\n", money, acc_no, acc_read.balance);
            return;
            }
            else{
                printf("\nInsufficient Balance!!\n");
            }
            fclose(file);
            return;
        }

    }
    fclose(file);
    printf("\nAccount No. %d was not found in records or incorrect PIN.\n", acc_no);
    printf("\nYou can not withdraw your amount\n");
}

void check_balance(){
    FILE *file = fopen(ACCOUNT_FILE, "rb");  
    if(file == NULL ){
        printf("\n Unable to access the file !!\n");
        return ;
    }

    int acc_no;
    int acc_pin;
    account acc_read;

    verification (&acc_no, &acc_pin);

     while(fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.Acc_number == acc_no && acc_read.pin == acc_pin){
            printf("\nAvailable Balance : Rs. %.2f\n", acc_read.balance);
            fclose(file);
            return;
        }
    }
    printf("\nAccount No. %d was not found in records or incorrect PIN.\n", acc_no);
    fclose(file);
}

void fund_transfer(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("\nUnable to access the File.\n");
        return;
    }

    int from_acc_x ;
    int to_acc_y ;
    int acc_pin ;
    account acc_read;
    float money ;
    int found_from = 0, found_to = 0;

    verification (&from_acc_x, &acc_pin);

    printf("Enter Amount : ");
    scanf("%f", &money);

    printf("Transfer Amount to  Account No. : ");
    scanf("%d", &to_acc_y);

    // Debit from sender's account
    while (fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.Acc_number == from_acc_x && acc_read.pin == acc_pin ){
            if(acc_read.balance < money){
                printf("Insufficient balance.\n");
                fclose(file);
                return;
            }
            acc_read.balance -= money;
            fseek(file , -(long int)sizeof(acc_read), SEEK_CUR );
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            found_from = 1;
            break;
        }
    }

    if(!found_from){
        printf("\nAccount No. %d was not found in records or incorrect PIN.\n", from_acc_x);
        fclose(file);
        return;
    }

    // Credit to receiver's account
    rewind(file);
    while (fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.Acc_number == to_acc_y){
            acc_read.balance += money;
            fseek(file , -(long int)sizeof(acc_read), SEEK_CUR );
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            found_to = 1;
            break;
        }
    }

    if(!found_to){
        printf("\nAccount No. %d was not found in records.\n", to_acc_y);

        // Revert the debit transaction
        rewind(file);
        while (fread(&acc_read, sizeof(acc_read), 1, file)){
            if(acc_read.Acc_number == from_acc_x){
                acc_read.balance += money;
                fseek(file , -(long int)sizeof(acc_read), SEEK_CUR );
                fwrite(&acc_read, sizeof(acc_read), 1, file);
                break;
            }
        }
    } else {
        printf("\nRs. %.2f Transferred Successfully from your bank account of account no %d to account no %d", money, from_acc_x, to_acc_y);
    }

    fclose(file);
}