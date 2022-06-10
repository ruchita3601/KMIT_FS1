#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"price.h"
#define BUS_NUM 84
#define TOTAL_SEATS 32
#define FILENAME_SIZE 1024
struct Passenger{
	char name[20];
    char phoneno[20],age[10],from[20],to[20];
    int seat,id,tid;
    struct Passenger *link;
};
struct Bus {
    int unqID;
    struct Passenger *firstPassenger;
};
char ticid[50];
struct Bus *arr[BUS_NUM];
struct Passenger *cur,*first,*last;
void create(int,char from[100],char to[100],char day1[100]);
void nodecreation(int i);
void display();
void cancellation(int i,char day2[100]);

void nodecreation(int i){
	int j,k;
    first = NULL;
	for(j=0;j<BUS_NUM;j++){
		if(j==i){
			for(k=0;k<TOTAL_SEATS;k++){
				cur = (struct Passenger *)malloc(sizeof(struct Passenger));
				strcpy(cur->age," ");
				strcpy(cur->name," ");
				strcpy(cur->phoneno," ");
				cur->tid=NULL;
				cur->id=NULL;
				if(first==NULL){
					first=cur;
					cur->link=NULL;
					last=cur;
					struct Bus *bus = (struct Bus *)malloc(sizeof(struct Bus));
                    bus->unqID = i;
                    bus->firstPassenger = cur;
                    arr[i] = bus;
				}
				else{
					last->link=cur;
					cur->link=NULL;
					last=cur;
				}
			}
		}
	}
}


void seat(char from[100],char to[100],char day[100]){
	int i;
	char f1[100],t1[100];
	printf("Please Enter the Bus ID ");
    scanf("%d",&i);
	while(1){
		int ch,k,n;
		printf("\n\n1.Seat Selection\n2.Tickect Info\n3.Cancellation\n4.Menu\n\n");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				k=0;
                if (arr[i] == NULL) {
                    nodecreation(i);
                }
				printf("\nNumber of seats to be booked: ");
				scanf("%d",&n);
				while(k<n && k<=5){
					create(i,from,to,day);
					k++;
				}
				price(from,to,n);
				break;
			case 2:
				if(arr[i]==NULL){
					printf("Bus is empty\n");
				}
				else{
					display();
				}
				break;
			case 3:
				if(arr[i] == NULL){
					printf("Bus is empty!!\n");
				}
				else{
					cancellation(i,day);
				}
				break;
			case 4:
				return;
			default:
				printf("Invalid Choice!!");
		}
	}
}
	
	

void create(int c,char from[100],char to[100],char day1[100]){
    int seatNo,i,j1,j,seatNum;
    int c1=0,c2=0; 
	char name[20],phone[20],age[10];
	struct Passenger *t=arr[c]->firstPassenger; 
	struct Passenger *t2=arr[c]->firstPassenger; 
	for(j1=0;j1<BUS_NUM;j1++){
        if(j1==c){
	        for(seatNo=1;seatNo<=TOTAL_SEATS;seatNo++){
	        	if(strcmp(t2->name," ")==0 && strcmp(t2->phoneno," ")==0 && t2->tid==NULL){
					printf("[%02d]",seatNo);
					c1++;
					c2++;
				}
				else{
					printf("[XX]");
					c1++;
					c2++;
				}
				if(c1==2){
					printf("\t");
					c1=0;
				}
				if(c2==4){
					printf("\n");
					c2=0;
				}
				t2=t2->link;
			}
		}      
    }
	
	char se[100];
	char busid[100];
	printf("\nEnter the seat number (1-32): ");
	scanf("%d",&seatNum);
	sprintf(se,"%d",seatNum);
	for(j=0;j<BUS_NUM;j++){
		if(j==c){
			for(i=1;i<seatNum;i++){
				t=t->link;
			}
			
			if(strcmp(t->age," ")==0){
				printf("\nEnter the name: ");
				scanf("%s",name);
				printf("\nEnter the phone number: ");
			    scanf("%s",phone);
			    printf("\nenter the age: ");
			    scanf("%s",age);
				strcpy(t->name,name);
			    strcpy(t->phoneno,phone);
			    strcpy(t->age,age);
				strcpy(t->from,from);
				strcpy(t->to,to);
			    t->seat=seatNum;
			    t->id=c;
				srand(time(0));
				t->tid=(rand() % 9000)+1000;
				sprintf(ticid,"%d",t->tid);
			    FILE *fp;
			    
                char filename[FILENAME_SIZE];
                sprintf(filename,"%d",c);
                strcpy(busid,filename);
                strcat(filename,"_");
                strcat(filename,day1);
                printf(" Date : %s",day1);
                printf("\nTicket Confirmed\n");
                printf("\n****\nTicket ID: %s\nName of the passenger: %s\nAge : %s\nPhone number: %s\nSeat number: %s\nBus ID:%s\n****\n",ticid,name,age,phone,se,busid);
            	fp=fopen(filename,"a+");
            	fprintf(fp,"\n*****************************\nTicket_ID:%s\nName_of_the_passenger:%s\nAge:%s\nPhone_number:%s\nSeat_number:%s\nBus_ID:%s\n*****************************\n",ticid,name,age,phone,se,busid);
            	printf("\nDetails copied into file successfully!!!\n");
                fclose(fp);
			    // bus_details(busno,name,age,phone,seatNum);
			}
			else{
				printf("Already reserved!!\n");
				create(c,from,to,day1);
			}
			
		}
	}
}


void cancellation(int i,char day2[100]){
	int j,id,k=0,count=0;
    int pid;
    char id1[100],re[100],id2[100];
    char fn[FILENAME_SIZE];
    struct Passenger *t2;
    printf("\nEnter your bus ID: ");
	scanf("%d",&id);
	int id3=id;
	sprintf(fn,"%d",id);
	strcat(fn,"_");
	strcat(fn,day2);
	strcat(fn,".txt");
	printf("filename:%s\n",fn);
	FILE *fp,*fp1;
	fp=fopen(fn,"r+");
	fp1=fopen("copy","a+");
	if(fp1==NULL){
		printf("error opening the file.");
	}
	
	
	for(j=0;j<BUS_NUM;j++){
	    if(id==j){
	    	if(arr[j]==NULL){
	    		printf("Bus is empty!!");
			}
			else{
				t2=arr[j]->firstPassenger;
		    	printf("Enter the Ticket ID: ");
				scanf("%d",&pid);
				strcpy(id1,"Ticket_ID:");
				sprintf(id2,"%d",pid);
				strcat(id1,id2);
				while(fscanf(fp,"%s",re)!=EOF)
	        	{
			        fprintf(fp1,"%s\n",re);
			        if(strcmp(re,id1) == 0)
			        {
			        	fprintf(fp1,"		->RECORD_DELETED\n");
			        	fseek(fp,100,SEEK_CUR);
	    	        }
	            }
	            printf("Details deleted from file.");
	            fclose(fp);
	            fclose(fp1);
	            remove(fn);
	            rename("copy",fn);
		        //printf("Details removed from the file successfully!!!!");
				for(k=0;k<TOTAL_SEATS;k++){
				    if(pid==t2->tid){
				    	if(t2->age!=NULL){
							strcpy(t2->name," ");
							strcpy(t2->phoneno," ");
							strcpy(t2->age," ");
							strcpy(t2->from," ");
							strcpy(t2->to," ");
							t2->id=NULL;
							t2->seat=NULL;
							t2->tid=NULL;
							printf("Ticket Cancelled!!");
						}
					}
					else{
						count++;
					}
					t2=t2->link;    
				}
				if(count==32){
					printf("Details not found!!");
				}
				return;
			}  
		}       
	}
}

void display(){
    int j,id,k=0,count=0;
    int pid;
    struct Passenger *t2;
    printf("\nEnter your bus ID: ");
	scanf("%d",&id);
	
	for(j=0;j<BUS_NUM;j++){
	    if(id==j){
	    	if(arr[j]==NULL){
	    		printf("Bus is empty!!!");
			}
			else{
				t2=arr[j]->firstPassenger;
		    	printf("Enter the Ticket ID: ");
				scanf("%d",&pid);
				
				for(k=0;k<TOTAL_SEATS;k++){
				    if(pid==t2->tid){
				    	if(t2->age!=NULL){
				    		printf("\n*Ticket Display*\n");
							printf("Bus Id: %d\n",t2->id);
							printf("From: %s\nTo: %s\n",t2->from,t2->to);
				        	printf("Name = %s\tPhone Number = %s\tAge = %s\t\tSeat number = %d\n",t2->name,t2->phoneno,t2->age,t2->seat);
				        	printf("Ticket ID: %d",t2->tid);
							printf("\n");
						}
					}
					else{
						count++;
					}
					t2=t2->link;    
				}
				if(count==32){
					printf("Details not found!!");
				}
				return; 
			} 
		}       
	}
}