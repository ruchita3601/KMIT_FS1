#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct log_in{
    char mobile[50];
    char password[50];
}a;
void sign_up();
void login();
int admin(){
    int var;
    do
    {
        printf("\n        1.Signup\n        2.Login\n        3.Exit\n");
        printf("        Enter your choice:");
        scanf("%d",&var);
        switch(var)
        {
            case 1:
                sign_up();
                break;
            case 2:
                login();
                break;
            case 3:
                break;
            default:
                printf("Enter Correct Choice\n");
                break;
        }
        
    }while(var!=3);
    return 0;
}

void sign_up(){
    FILE *fp,*fp1;
    int count=0,flag=0;
    char m[50]="Mobile_no:",p[50]="PassWord_:"; //predefined in file... 
    char mob[50],pass[50],confirm_pass[50]; //user credentials gets appended
    printf("\t\t\t*SIGN UP*\t\t\t\n");
    fp=fopen("User_login.txt","a");
    printf("        Enter your Mobno:\n");
    fflush(stdin);
    gets(mob);//or use scanf
    while(1){
        if(strlen(mob)!=10){
            printf("        Please enter correct 10 digits phone number\n");
            gets(mob);
            count++;
            if(count>=10){
                printf("        Many number of Incorrect Attempts!!\t Sign up Again!!\n");
                sign_up();
                return;
            }
        }
        else{
            break;
        }
    }
            fp1=fopen("User_login.txt","r");
            while(fscanf(fp1,"%s %s",a.mobile,a.password)!= EOF)
		        {
                    if((strcmp (a.mobile+10,mob) == 0)){  //by giving +12 the useranme which is already determined in file gets excluded
                        printf("\n        MOBILE NUMBER ALREDY EXISTS\n");
                        flag=1;
                        break;
                    }
		        }
            fclose(fp1);
                if(flag==1){
                    return;
                }
    strcat(m,mob);
	fprintf(fp,"%s",m);
    password:
    printf("        Enter your pass:\n");
    fflush(stdin);
    gets(pass);
    printf("        Confirm your password:");
    fflush(stdin);
    gets(confirm_pass);
    if (strcmp(pass,confirm_pass)==0)
        {  
            strcat(p,pass);
            fprintf(fp,"\n");
            fprintf(fp,"%s",p);
            fprintf(fp,"\n");
            printf("\n        Registration successful");
        }
    else
        {
            printf("\n        Password Not Matched Re-Enter Again\n");
            goto password;
    }
    fclose(fp);
}
void login(){
        int x=0;
		FILE *fp;
        fp=fopen("User_login.txt","r");
		char mob[50],passw[50],ch;
        printf("\t\t\t*LOGIN*\t\t\t\n");
        fflush(stdin);
        printf("\n        Enter your Mobile no:");
        fflush(stdin);
        gets(mob);
        printf("\n        Enter your Password:");
        fflush(stdin);
        gets(passw);
		while(fscanf(fp,"%s %s",a.mobile,a.password) != EOF)
		{
            if((strcmp (a.mobile+10,mob) == 0) && (strcmp (a.password+10,passw) == 0 ))
			{
                x=1;
                break;
            }
		}
        if(x==1){
            printf("\n         LogIn Successfull");
            
			}
        else{
            printf("\nLogIn Failed!! To Re-attempt Press!!\n");
            do{
                printf("SignIn-Y\nLogIn-N\n");
                scanf("%c",&ch);
                if((ch == 'Y')||(ch=='y')){
                    sign_up();
                    break;
                }
                if((ch=='N')||(ch=='n')){
                    login();
                    break;
                }
            }while(1);
        }
            fclose(fp);

}