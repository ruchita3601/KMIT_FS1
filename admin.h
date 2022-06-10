#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// #include"price.h"
#define QUEUESIZE 4

struct log_in{
    char mobile[50];
    char password[50];
}a;

struct employee{
    int empId;
    char empName[100],empPhoNo[100],empAge[10];
    char empAddress[1000],empSalary[100],empBusId[10],empPost[100];
    struct employee *rchild,*lchild;
};
int c=0;

struct bus1{
	char from[100],to[100],type[10],busid[5],driver_name[100],conductor_name[100];   
    struct bus1 *link;  
};
struct busdup{
	char fromd[100],tod[100],typed[10],busidd[5],driver_named[100],conductor_named[100];
}b; 
struct bus1 *front,*rear,*temp1,*cur1,*temp2;  


struct employee *newNode;
struct employee* insert(struct employee *,int);
struct employee* inorder(struct employee *,int,int);
struct employee* delete_node(struct employee *,int);
int count=0;


void add_bus();
void del_bus();
void disp_bus();
void enqueue();
void dequeue(int c, char frm[20]);
void sign_up();
void login();
void bus();
void employee();
void passenger();
void revenue();
void admin(){
    int var;
    do
    {
        printf("\n        1.Signup\n        2.Login\n       3.Main menu\n");
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
                return;
            default:
                printf("Enter Correct Choice\n");
                break;
        }
        
    }while(var!=3);
  //  return 0;
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
            while(fscanf(fp1,"%s %s",a.mobile,a.password)!= EOF)  //mobile number should not repeat
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
        int x=0,var2;
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
            do{
            	printf("\n        1.Employee\n        2.Bus\n        3.Passenger\n        4.Revenue\n        5.Return\n        \n");
                printf("          Enter your choice:");
                scanf("%d",&var2);
                switch(var2){
                	case 1:
                		employee();
                		break;
                	case 2:
                		bus();
                		break;
                	case 3:
                		passenger();
                		break;
                	case 4:
                		revenue();
                		break;
                	case 5:
                		return;
                	default:
                		printf("Invlaid choice!!!");
				}
            	
			}while(var2!=5);
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

struct employee* getNode(int id){
	FILE *fp;
    char empId[100],post[10],name[100],phoNo[10],age[10],address[100],busId[10],salary[100],a1[50];
    char i[50]="EMPLOYEE_ID:",p[50]="POST:",n[50]="NAME:",ph[50]="PHONE:",a[10]="AGE:",ad[50]="ADDRESS:",b[10]="BUS_ID:",s[10]="SALARY:";
    printf("\t\t\t*ADD EMPLOYEE*\t\t\t\n");
    fp=fopen("Employee.txt","a+");
	newNode=(struct employee *)malloc(sizeof(struct employee));
	fflush(stdin);
	newNode->empId=id;
    sprintf(a1,"%d",id);
    strcat(i,a1);
    fflush(stdin);
    fprintf(fp,"\n");
	fprintf(fp,a1);
    fprintf(fp,"\n%s\n",i);
    printf("Enter the post of the employee: \n");
    fflush(stdin);
    scanf("%s",newNode->empPost);
    strcat(p,newNode->empPost);
    fprintf(fp,"%s\n",p);
    printf("Enter the name of the employee: \n");
    fflush(stdin);
    scanf("%s",newNode->empName);
    strcat(n,newNode->empName);
	fprintf(fp,"%s\n",n);
    printf("Enter the phone Number of the employee: \n");
    fflush(stdin);
    scanf("%s",newNode->empPhoNo);
    strcat(ph,newNode->empPhoNo);
    fprintf(fp,"%s\n",ph);
    printf("Enter the age of the employee: \n");
    fflush(stdin);
    scanf("%s",newNode->empAge);
    strcat(a,newNode->empAge);
	fprintf(fp,"%s\n",a);
    printf("Enter the address of the employee: \n");
    fflush(stdin);
    scanf("%s",newNode->empAddress);
    strcat(ad,newNode->empAddress);
	fprintf(fp,"%s\n",ad);
    printf("Enter the bus ID for the employee: \n");
    fflush(stdin);
    scanf("%s",newNode->empBusId);
    strcat(b,newNode->empBusId);
	fprintf(fp,"%s\n",b);
    printf("Enter the salary for the employee: \n");
    fflush(stdin);
    scanf("%s",newNode->empSalary);
    strcat(s,newNode->empSalary);
	fprintf(fp,"%s\n",s);
	printf("EMPLOYEE ADDED SUCCESSFULLY!!");
	fprintf(fp,"***");
    fclose(fp);
    newNode->lchild = NULL;
	newNode->rchild = NULL;
	return(newNode);
}

void employee(){
    int c1;
    int n,id,eid,e1id;
    struct employee *root=NULL;
    while (1){
        printf("\n\n1.Add Employee\n2.Employee Information\n3.Employee Deletion\n4.Return\n");
        scanf("%d",&n);
        switch(n){
            case 1:
                printf("Enter the id of the employee: ");
                scanf("%d",&id);
                root = insert(root,id);  //returns the root which contains employee details
                c++;
                break;
            case 2:  //searching the employee from the previously generated BST
                c1=-1;
                printf("Enter the id of the employee: ");
                scanf("%d",&e1id);
                inorder(root,e1id,c1);
                break;
            case 3:
                printf("Enter the id of the employee: ");
                scanf("%d",&eid);
                delete_node(root,eid);
                c--;
                printf("\n\nDetails deleted!!");
                break;
            case 4:
            	return;
            default:
            	printf("Invalid input!!!");
        }
    }
    
}

struct employee* insert(struct employee *root,int id){
    struct employee *temp=root;
    if(root == NULL){
        root = getNode(id);
        return(root);
    }
    while(1){
        if(temp->empId>id){
            if(temp->lchild==NULL){
                temp->lchild=getNode(id);
                break;
            }
            else{
                temp=temp->lchild;
            }
        }
        else{
            if(temp->rchild==NULL){
                temp->rchild=getNode(id);
                break;
            }
            else{
                temp=temp->rchild;
            }
        }
    }
    return(root);
}

struct employee *inorder(struct employee *root,int id,int count){
    count++;
    if(count==c){  //c is total number of nodes and count gets incremented when traversed
        printf("details not found!!");
        return(0);
    }
    else if(id == root->empId){
        printf("\n\nName = %s",root->empName);
        printf("\nEmployeeID = %d",root->empId);
        printf("\nDesignation = %s",root->empPost);
        printf("\nAge = %s",root->empAge);
        printf("\nPhoneNumber = %s",root->empPhoNo);
        printf("\nAddress = %s",root->empAddress);
        printf("\nSalary = %s",root->empSalary);
        printf("\nBusID = %s",root->empBusId);
        return(0);
    }    
    else if(root->empId > id){
        inorder(root->lchild,id,count);
    }
    else if(root->empId < id){
        inorder(root->rchild,id,count);
    }
        
}


struct employee* delete_node(struct employee *root,int id){
	FILE *fp,*fp1;
	char id1[10],re[100],a1[10];
	char buffer[100];
	fp=fopen("Employee.txt","r+");
	fp1=fopen("copy","a+");
	newNode=(struct employee *)malloc(sizeof(struct employee));
	newNode->empId=id;
    sprintf(a1,"%d",id);
    while(fscanf(fp,"%s",re) != EOF){
    	fprintf(fp1,"%s\n",re);
    	if(strcmp(re,a1)==0)
    	{
    		fprintf(fp1,"		->RECORD_DELETED\n");
    		fseek(fp,96,SEEK_CUR);
		}
	}
	fclose(fp);
	fclose(fp1);
	remove("Employee.txt");
	rename("copy","Employee.txt");
    if (root == NULL)
    return root;
    
    if (id < root->empId)
    root->lchild = delete_node(root->lchild,id);
    
    else if (id > root->empId)
    root->rchild = delete_node(root->rchild,id);
    
    else{
        if (root->lchild == NULL){
            struct employee *temp = root->rchild;
            free(root);
            return temp;
        }
        else if (root->rchild == NULL){
            struct employee *temp = root->lchild;
            free(root);
            return temp;
        }
    }
}

void bus()
{
    int ch,n;
    while(1){
        printf("\n\n1.ADD BUS\n2.BUS DETAILS\n3.DELETE BUS\n4.RETURN\n");
        printf("\n\nEnter your choice: ");
        scanf("%d",&ch);
        switch (ch){
        case 1:
            add_bus();
            break;
        case 2:
            disp_bus();
            break;
        case 3:
            del_bus();
            break;
        case 4:
        	return;
        default:
            printf("invalid choice!!");
        }
    }
}

void add_bus(){
	int s=1;
    char frm[20];
	printf("\t\t\t*ADD BUS*\t\t\t\n");
	while((s!=0)&&(count<QUEUESIZE)){
        printf("\nEnter FROM:");
        scanf("%s",b.fromd);
        strcpy(frm,b.fromd);
        printf("Enter TO:");
        scanf("%s",b.tod);
        printf("Type:");
        scanf("%s",b.typed);
        printf("Bus ID:");
        scanf("%s",b.busidd);
        printf("Driver name:");
        scanf("%s",b.driver_named);
        printf("Conductor name:");
        scanf("%s",b.conductor_named);
        enqueue();
		count=count+1;
		if(count<QUEUESIZE){
			printf("\nDo you want to continue???(0/1)\n");
		    scanf("%d",&s);
		}
		if(count==QUEUESIZE){
			printf("\nQUEUE IS FULL\n");
		}	
	}
	dequeue(count,frm);	
}
void enqueue(){
	cur1=(struct bus1*)malloc(sizeof(struct bus1));
	strcpy(cur1->from,b.fromd);
    strcpy(cur1->to,b.tod);
    strcpy(cur1->type,b.typed);
    strcpy(cur1->busid,b.busidd);
    strcpy(cur1->driver_name,b.driver_named);
    strcpy(cur1->conductor_name,b.conductor_named);	
	if(front==NULL){
		cur1->link=NULL;
		front=cur1;
	    rear=cur1;
	}
	else{
		cur1->link=NULL;
		rear->link=cur1;
		rear=cur1;
	}
}
void dequeue(int c, char frm[20]){
	if(c==0){
		printf("Queue is empty\n");
	}
	else{
        FILE *fp;
		temp1=front;
        strcat(frm,".txt");
	    fp=fopen(frm,"a+");
		temp1=front;
      	while(temp1!=NULL && c>=0)
	    { 
	        fprintf(fp,"%s\nFrom=%s\nTo=%s\nType=%s\nBus ID=%s\nDriver Name=%s\nConductor Name=%s\n",temp1->to,temp1->from,temp1->to,temp1->type,temp1->busid,temp1->driver_name,temp1->conductor_name);
	        fprintf(fp,"***");
	        temp2=temp1;
	        temp1=temp1->link;
	        // front=front->link;
	        free(temp2);
            c--;
     	}printf("Details copied into the file successfully!!!");
     	fclose(fp);
     	
	}
	count=0;
	
}
void disp_bus(){
	char fr[50],ch;
	printf("Enter FROM:");
	scanf("%s",fr);
    strcat(fr,".txt");
    // printf("%s",fr);
	FILE *fp;
	fp=fopen(fr,"r+");
	if(fp==NULL){
		printf("Unable to open the file...");
	}
	do{
		ch=fgetc(fp);
		printf("%c",ch);
	}while(ch!=EOF);
}

void del_bus()
{
	FILE *fp,*fp1;
	char id1[100],id2[100],re[100],from[50],from1[50],to[50];
	printf("\t\t\t*DELETE BUS*\t\t\t\n");
    printf("Enter FROM: ");
    scanf("%s",from);
    strcpy(from1,from);
    char buffer[100];
    int size=100;
	char ch[size];
    strcat(from,".txt");
	fp=fopen(from,"r+");
	fp1=fopen("copy","a+");
	if(fp1==NULL)
	{
		printf("Error opening the file");
	}
	printf("Enter TO:");
	scanf("%s",to);
	while(fscanf(fp,"%s",re)!=EOF)
	{
		fprintf(fp1,"%s\n",re);
		if(strcmp(re,to)==0)
		{
			fprintf(fp1,"		->RECORD_DELETED\n");
			fseek(fp,100,SEEK_CUR);
		}
	}
	printf("Details deleted from file.");
	fclose(fp);
	fclose(fp1);
	remove(from);
	rename("copy",from);
}


void passenger(){
	char bid[50],date[20],ch;
	printf("Enter Bus Id:");
	scanf("%s",bid);
	printf("Enter date(ddllmmllyyyy):");
	scanf("%s",date);
	printf("\n    Passenger details travelling in the bus %s    \n",bid);
	strcat(bid,"_");
	strcat(bid,date);
	strcat(bid,".txt");
	FILE *fp=fopen(bid,"r");
	if(fp==NULL){
		printf("Unable to open the file...");
	}
	do{
		ch=fgetc(fp);
		printf("%c",ch);
	}while(ch!=EOF);	
}
void revenue(){
    FILE *fp,*fp1;
    char places[100],re[100],buffer[1024],name[100],ch;
    char re1[100],buffer1[1024],from1[100],from[100],to[100],day[100],month[100],yr[100],id1[100];
    int d1, m, year,d2,m1,year1,id;
    printf("Enter from: ");
    scanf("%s",from);
    printf("Enter to: ");
    scanf("%s",to);
    printf("Enter bus id: ");
    scanf("%d",&id);
    strcpy(from1,from);
    strcat(from1,"_fares.txt");
    top:
    printf("Enter date (dd/mm/yy): ");
    scanf("%d/%d/%d", &d1,&m,&year);
    if(d1<=31 && m<=12 && year>=2022)
    {
        sprintf(day,"%d",d1);
        sprintf(month,"%d",m);
        sprintf(yr,"%d",year);
        sprintf(id1,"%d",id);
        strcat(day,"ll");
        strcat(day,month);
        strcat(day,"ll");
        strcat(day,yr);
        strcat(day,".txt");
        strcat(id1,"_");
        strcat(id1,day);
    }
    else
    {
        printf("Invalid input format\n");
        goto top;
    }
    fp=fopen(id1,"r");
 
    while(!feof(fp)){ 
        fscanf(fp,"%s",re);
        
        if(strcmp(re,"Name_of_the_passenger:") == 0){
            count++;
        }
    }

    fp1=fopen(from1,"r");
    while(!feof(fp1)){
        fscanf(fp1,"%s",re);
        if(strcmp(re,to) == 0){
            while (fgets(buffer, 1024, fp1) != NULL){
                if((strcmp(buffer,"\n")==0) || (strcmp(buffer,"\t\n")==0) || (strcmp(buffer," \n")==0)){
                    continue;
                }
                // printf("The total distance from %s to %s is %s",from,to,buffer);
                break;
            }
        }
    }
    float fare=atof(buffer);
    printf("The total revenue generated is: %.2f",(fare*count*2.5));
}