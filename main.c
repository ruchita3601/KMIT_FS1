#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ticket_display.h"
#include"admin.h"
void reservation();
void user();
void places();
void contact_info(); 
void Management();
int main(){
    int n,i=0;
    char name[20];
    int phone,age;
    while(1){
        int m;
        printf("1.User\n2.Management\n3.Exit\n\n");
        printf("Enter u r choice: ");
        scanf("%d",&m);
        switch (m){
            case 1:
                user();
                break;
            case 2:
                Management();
                break;
            case 3:
           	    exit(0);
            default:
                printf("enter crct choice!!");
        }
    }
}

void user(){
    int n;
    while(1){
        printf("\n\n1.Services Available for Places\n2.Reservation\n3.Contact Information\n4.Main Menu");
        printf("\n\nEnter your choice: ");
        scanf("%d",&n);
        switch(n){
        	case 1:
        		places();
        		break;
            case 2:
                reservation();
                break;
			case 3:
				contact_info();
				break;
			case 4:
				return;
            default:
                printf("Enter the crct choice!!");
        }
    }
	
}
void reservation(){
    ticket_booking();

}
void contact_info(){
	printf("ABC Pvt.ltd\n");
	printf("For any Queries: \n");
	printf("Contact Number: +91971984625\n");
	printf("Email Id: abcpvt.ltd@gmail.com\n");
	printf("Address: Besides Paradise Hotel Secunderabad\n\n");
	
}

void places(){
	FILE *fp;
	int size=100;
	char ch[size];
	fp=fopen("C:\\Users\\BELLARY RUCHITA\\Desktop\\Bus Reservation\\places.txt","r");
	while(fgets(ch,size,fp)){
		printf("%s",ch);
	}
	fclose(fp);
}

void Management(){
    admin();
}