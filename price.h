#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define FIXED_PRICE 2.5
int price(char from[100],char to[100],int n){
    FILE *fp;
    char places[100],re[100],buffer[1024],from1[100];
    int i=0;
    strcpy(from1,from);
    strcat(from1,"_fares.txt");
    fp=fopen(from1,"r");
    while(!feof(fp)){
        fscanf(fp,"%s",re);
        if(strcmp(re,to) == 0){
            while (fgets(buffer, 1024, fp) != NULL){
                if((strcmp(buffer,"\n")==0) || (strcmp(buffer,"\t\n")==0) || (strcmp(buffer," \n")==0)){
                    continue;
                }
                printf("The total distance from %s to %s is %s",from,to,buffer);
                break;
            }
        }
    }
    float fare=atof(buffer);
    printf("Total price: %.2f",fare*FIXED_PRICE*n);
    fclose(fp);
}