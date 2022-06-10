#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"seat.h"
struct bus{
    char From[50];
    char To[50];
    char DriverName[50];
    char Type[50];
    char BUSID[10];
}s;

void ticket_booking(){
    FILE *fp,*fp1,*fp2;
    int x,y;
    char from[100],from1[100],to[100],day[100],month[100],yr[100];
    int d1, m, year,d2,m1,year1;
    top:
    printf("\nEnter date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &d1,&m,&year);
    if(d1<=31 && m<=12 && year>=2022)
    {
        sprintf(day,"%d",d1);
        sprintf(month,"%d",m);
        sprintf(yr,"%d",year);
        strcat(day,"ll");
        strcat(day,month);
        strcat(day,"ll");
        strcat(day,yr);
    }
    else
    {
        printf("Invalid input format\n");
        goto top;
    }
    printf("\nEnter FROM: ");
    scanf("%s",from);
    strcpy(from1,from);
    char buffer[100];
    int size=100;
	char ch[size];
    strcat(from,".txt");
    char d[10],re[100];
	printf("Enter to: ");
	scanf("%s",d);
    strcpy(to,d);    
    fp1=fopen("places.txt","r");  
    while(fscanf(fp1," %s ",s.From) != EOF){   //we are reading the string from file and stored in s.FROM
        if((strcmp (s.From,from1) == 0))
        {
            x=1;      //if from is present in the places.txt file then x=1
            break;
        }
	}
    fp2=fopen("places.txt","r");
    while(fscanf(fp2," %s ",s.To) != EOF){
        if((strcmp (s.To,to) == 0))
        {
            y=1;       //if to is present in the places.txt file then y=1
            break;
        }
	}

    if(x==1 && y==1){
        if(strcmp(from1,to)!=0){
            fp=fopen(from,"r");
            printf("\t\t\t*BUS DETAILS*\t\t\t\n");
            while(!feof(fp)){
                fscanf(fp,"%s",re);
                if(strcmp(re,d) == 0){
                    while(1){
                        char ch = fgetc(fp);
                        if(ch == '*')
                        {
                            break;        //the data gets printed till *
                        }
                        printf("%c",ch);
                    }
                }
            }
            seat(from1,d,day);
        }
        else{
            printf("Invalid Input!!");

        }
    }
    else{
        printf("\nInvalid");
    }
}