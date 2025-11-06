#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct user{
    char name[50];
    char mobile[15];
    char upi_id[50];
    int pin;
    float balance;
};
struct transaction{
    char sender_upi[50];
    char receiver_upi[50];
    float amount;
    char time[30];
};

//register new user
void registerUser(){
    struct user newUser;
    FILE *fp;
    int found =0;
    printf("\nenter your name: ");
    scanf("%s", newUser.name);
    printf("enter your mobile number: ");
    scanf("%s", newUser.mobile);
    printf("create your UPI id: ");
    scanf("%s", newUser.upi_id);
    printf("set your 4-digit pin: ");
    scanf("%d", &newUser.pin);
    newUser.balance = 0.0;

    //cheacking if upi id already exists
    fp = fopen("users.txt", "r");
    if(fp !=NULL){
        struct user tempUser;
        while(fscanf(fp,"%s %s %s %d %.2f", tempUser.name,tempUser.mobile,tempUser.upi_id,&tempUser.pin,&tempUser.balance) !=EOF){
            if(strcmp(tempUser.upi_id, newUser.upi_id) == 0){
                printf("upi id already exists.. try again\n");
                found =1;
                break;
            }
        }
        fclose(fp);
    }
    if(found){
        printf("\n this upi id is already registered. please try again with a different upi id.\n");
        return;
    }
    //saving new user data
    fp = fopen("users.txt", "a");
    if(fp == NULL){
        printf("error in opening file\n");
        return;
    }
    fprintf(fp,"%s %s %s %d %.2f\n",newUser.name,newUser.mobile,newUser.upi_id,newUser.pin,newUser.balance);
    fclose(fp);
    printf("\nregistration successful.. you can now login using your upi id and pin\n");
}
//login existing user
void loginUser(){
    struct user u;
    int input_pin;
    char input_upiId[20];
    FILE *fp;
    int found = 0;

    printf("enter your upi id : ");
    scanf("%s",input_upiId);
    printf("\nenter your 4-digit pin : ");
    scanf("%d",&input_pin);
    fp = fopen("users.txt", "r");
    if(fp == NULL){
        printf("no accounts found ! first register..\n");
        return;
    }
    while(fscanf(fp,"%s %s %s %d %.2f",u.name,u.mobile,u.upi_id,&u.pin,&u.balance) != EOF){
        if(strcmp(u.upi_id,input_upiId) ==0 && u.pin == input_pin){
                found = 1;
                break;
        }
    }
    fclose(fp);

    if(found){
        printf("\nLogin successful.. Welcome %s\n your current balance is %d\n",u.name,u.balance);
    }else{
        printf("invalid upi id or pin.. try again\n");
    }
}

int main(){
    int choice;
    printf("welcome to upi payment system\n");
    printf("1.register\n2.login\n3.exit\n");
    printf("enter your choice: ");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            registerUser();
            break;  
        case 2:
            loginUser();
            break;
        case 3:
            printf("exiting the program\n");
            break;                  
        default:
            printf("invalid choice\n");
    }
    return 0;
}
