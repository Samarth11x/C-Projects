#include <stdio.h>
#include <string.h>

#define MAX_USERS 10                                    //globally defining max number of User
#define CREDENTIALS_LENGTH 30                           // globally defining credentials length

typedef struct {
    char username [CREDENTIALS_LENGTH];
    char password [CREDENTIALS_LENGTH];
} user ;                                                //structure to store credentials

user users[MAX_USERS];                                  // array to store [Max_user] 
int User_count = 0;                                     //globally initialization of User count from 0

void register_user();
void input_password(char*);
int login_user();                                       // to return the user index 
void fix_fgets_input(char*);

int main() {
    int option;
    int user_index;


    while(1){
      printf("\n Welcome to User Management \n");
    printf("\n1.Register");
    printf("\n2.Log in");
    printf("\n3.Exit\n");

    printf("\nSelect an option : ");
    scanf("%d", &option);
    getchar();

    switch (option){
        case 1 :
          register_user();
          break;

        case 2 :
          user_index = login_user();
          if(user_index >= 0){
            printf("\nLogin Successful ! Welcome %s !\n", users[user_index].username );

          }
          else{
            printf("\nLogin failed! Incorrect User Name or Password\n");

          }
          break;

        case 3 :
          printf("\n \t Exiting Program \n ");
          return 0;
          break;

        default :
          printf("\nInvalid Option! \n Please try again !!\n");
          break;
        }
    }

    return 0;
}

void register_user(){
    if(User_count == MAX_USERS){
        printf("\nMaximum %d users are supported. \nNo more registration are allowed!!\n", MAX_USERS);   
        return;
        }

    int New_index = User_count;
    printf("\nRegister a New User\n");
    printf("Enter Username : ");
    fgets(users[New_index].username, CREDENTIALS_LENGTH, stdin);
    fix_fgets_input(users[New_index].username);                   // to detect '\n' and change it to '\0' which converts it in the form of string
    input_password(users[New_index].password);   
    User_count++;
    printf("\n Registration Successful!!\n");
}

void input_password(char* password){
  printf("Enter Password : ");
  fgets(password, CREDENTIALS_LENGTH, stdin);
  fix_fgets_input(password);
}

int login_user(){
  char username [CREDENTIALS_LENGTH];
  char password [CREDENTIALS_LENGTH];
  
  printf("Enter Username : ");
  fgets(username, CREDENTIALS_LENGTH, stdin);
  fix_fgets_input(username);
  input_password(password);

   for (int i = 0 ; i < User_count ; i++ ){
    if( strcmp(username, users[i].username) == 0 && strcmp (password, users[i].password) == 0){
      return i;
    }
   }

   return -1;

}

void fix_fgets_input(char* string){
    int index = strcspn(string, "\n");                          // strcspn will replace the '\n' entered by user to '\0' "Null Terminator" 
    string[index] = '\0' ;                                      // input changed to string
}