#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
typedef struct
{
	char name[50]; char hour[50];char  min[50];char sec[50];char month[50];char year[50];char day[50];char date[50];
}record;
char *name="Admin";
char *password="ttcmp123";
void choices(int ch); void modify_record();void check_record();void file_manager();
void login_page();void username_password_change();
void admin_menu();
int admin_name_password(char u[50],char a[50]);
void admin(); void user();
int main()     //main function
{
	login_page();
	return 0;
}
void file_manager()          //for deleting file when it is empty
{
	FILE *f=fopen("Cyber Management.txt","r");
	if(f!=NULL)
	{
		int count=0;char cha;
		for (cha = getc(f); cha != EOF; cha = getc(f))
		{
      		if (cha == '\n') count = count + 1;
		}
		fclose(f);
		if(count==0){remove("Cyber Management.txt");}
	}
}
void user()      //user details
{   
	FILE *file;
	file=fopen("Cyber Management.txt","a");
	char n[30],c[50],cc[50]; 
	int ch=0;
	int ch2=0;
	system("cls||clear");
	system("Color 70");
	printf("USER MENU\n\n");
	printf("\t\t\t Enter Your Name:");
	scanf("\n");
	scanf("%[^\n]",n);
	printf("\n\n");
	printf("\tPress 1 to login or anything else to go to login page:");
	scanf("%s",c);ch=atoi(c);
	if(ch!=1)
	{	
		login_page();
	}
	else
	{	
		time_t now=time(NULL);         //using time library for noting current time
		struct tm *local=localtime(&now);
		fputs(n,file);
		fputs(",",file);
	    char sti[100];
		strftime(sti,100,"%H,%M,%S,%d,%B,%Y,%a,",local);
		fputs(sti,file);
		fputs("\n",file);
		sleep(1);
		printf("\n\n\tSuccesfully logged in!!\n Current Time: %s",ctime(&now));
		sleep(2);
		system("cls||clear");
		printf("USER MENU");
		printf("\n\n\t\tPress 1 For Entering Another Record");
		printf("\n\t\tPress 2 For Entering Teminating System");
		printf("\n\t\tPress Anything Else To Go Back To Login Screen");
		printf("\n\tNote: It is Necessary to terminate system for saving user data.");
		printf("\n\n\t\tEnter Your Choice:");
		scanf("\n");
		scanf("%[^\n]",cc);ch2=atoi(cc);
		if(ch2==1)  user();
		else if(ch2==2) 
		{
			fclose(file);
			system("exit");
			system("cls||clear");
			system("Color 0F");
		}
		else login_page();
	}
	fclose(file);
}	
void modify_record()     //for modifying record
{
	file_manager();
	system("cls||clear");
	char c[400];int ch;int delete_line=0;
	while(true)
	{
		printf("\n\n\t\t\tList Of Options Available:\n");
		printf("\n\n\t\t\t1.Delete A Record\n");
		printf("\t\t\t2.Return Back To Menu\n");
		printf("\n\t\t\tEnter Your Choice:");
		scanf("%s",c);
		ch=atoi(c);
		if(ch>=1 && ch<=2) break;
		else printf("Wrong Choice! Try Again!\n");
	}
	FILE *f1=fopen("Cyber Management.txt","r");if(f1==NULL){ printf("No Records Found!\n");sleep(1);admin_menu();}
	int count=0;char cha;
	for (cha = getc(f1); cha != EOF; cha = getc(f1))
	{
      	if (cha == '\n') count = count + 1;
	}
	switch(ch)
	{
		case 1:
			printf("\n");
			sleep(1);
			while(true)
			{
				printf("\tSpecify The Record Number You Want To Delete:");
				scanf("%s",c);
				delete_line=atoi(c);
				if(delete_line<1||delete_line>count) {printf("There is No Such Record!\n");continue;}
				else break;
			}
			FILE *file,*temp;
			file=fopen("Cyber Management.txt","r");temp=fopen("__temp__.txt","w");
			int current_line=1;char buffer[2400];bool keep_read=true;
			do
			{
				fgets(buffer,2000,file);
				if(feof(file)) keep_read=false;
				else if(current_line!=delete_line)
				{
					fputs(buffer,temp);
				}
				current_line++;
			}while(keep_read);
			fclose(file);fclose(temp);
			remove("Cyber Management.txt");
			rename("__temp__.txt","Cyber Management.txt");
			printf("Records Successfully Modified!!\n");
			sleep(1);
		case 2:
			printf("Returning To Admin Menu!\n");
			sleep(1);
			admin_menu();
	}
}
void check_record()    //for checking record
{ 
	file_manager();  
	FILE *file1=fopen("Cyber Management.txt","r");
	if(file1==NULL) 
	{printf("No Record Exists!\n");sleep(1);admin_menu();}
	else
	{
		record re[200];
		int counter=0;char line[200],*buffer;
		while(!feof(file1))
		{
			fscanf(file1,"%[^\n]\n",line);
			buffer=strtok(line,",");
			strcpy(re[counter].name,buffer);
			buffer=strtok(NULL,",");
			strcpy(re[counter].hour,buffer);
			buffer=strtok(NULL,",");
			strcpy(re[counter].min,buffer);
			buffer=strtok(NULL,",");
			strcpy(re[counter].sec,buffer);
			buffer=strtok(NULL,",");
			strcpy(re[counter].date,buffer);
			buffer=strtok(NULL,",");
			strcpy(re[counter].month,buffer);
			buffer=strtok(NULL,",");
			strcpy(re[counter].year,buffer);
			buffer=strtok(NULL,",");
			strcpy(re[counter].day,buffer);
			counter+=1;
		}

		printf("The Records Present:\n");
		int jk;
		printf(" Name:\t\tTime[HH|MM|SS]:\t\tDate:\n");
		for(jk=0;jk<counter;jk++)
		{
			printf("%d.%s\t%s:%s:%s\t\t%s,%s,%s,%s\n",jk+1,re[jk].name,re[jk].hour,re[jk].min,re[jk].sec,re[jk].date,
								re[jk].month,re[jk].year,re[jk].day);
		}
		while(true)
		{
			char c[200];int ch=0;
			printf("\nPress 1 to go back to admin menu:");
			scanf("%s",c);ch=atoi(c);
			if(ch==1) 
			{
				admin_menu();
				break;
			}
			else printf("Wrong Choice!!\n");
		}
		fclose(file1);
		
	}
}
void username_password_change()   //to change the default username and password
{
	char *n;char *p;
	n=name; p=password;
	char u1[500],u2[500],u3[500];
	system("cls||clear");
	system("Color 8F");
	printf("ADMIN MENU\n\n");
	printf("\t\t\t Enter New Username:");
	scanf("%s",u1);
	printf("\t\t\t Enter New Password:");
	scanf("%s",u2);
	printf("Enter The Previous Password To Confirm:");
	scanf("%s",u3);
	if(strcmp(u3,password)==0)
	{   
		name=u1;
		password=u2;
		system("cls||clear");
		printf("Username and Password changed Sucessfully!\n Returning to Main Menu");
		sleep(1);
		admin_menu();
	}
	else
	{
		printf("Authentication Failed! Returning to main menu\n");
		sleep(1);
		system("clear||cls");
		admin_menu();
	}
}
void admin_menu()    //admin main menu
{
	int cha;char cc[50];
	while(true)
	{
		system("cls||clear");
		system("Color 9F");
		printf("ADMIN MENU:");
		printf("\n\n\t\t\t List Of Choices:\n\n");
		printf("\t\t\t 1.Check Record\n");
		printf("\t\t\t 2.Modify Record\n");
		printf("\t\t\t 3.Change Username And Password\n");
		printf("\t\t\t 4.Terminate System\n");
		printf("\t\t\t 5.Logout\n\n");
		printf("\t\t Enter Your Choice:");
		scanf("%s",cc);cha=atoi(cc);
		if(cha>=1 && cha<=5)
			break;
		else
		{
			system("Color 4E");
			printf("\n\t\t\tWrong Choice, Try again!\n");
			sleep(1);
		}
	}
		switch(cha)
		{   
			case 1:
				check_record();
				break;
			case 2:
				modify_record();
				break;
			case 3:
				username_password_change();
				break;
			case 4:
				system("exit");
				system("cls||clear");
				system("Color 0F");
				break;
			case 5:
				login_page();
				break;
			default:
				printf("Internal Error");
		}
	}
void choices(int ch)     //choices menu
{
	switch(ch)
	{
		case 1:
			admin();
			break;
		case 2:
			user();
			break;
	}
}
void login_page()     //main login page
{ 
	system("cls||clear");
	system("Color 8A");
	char c[50];int ch;
	printf("\t*************************************************\n");
	printf("\t****** WELCOME TO CYBER MANAGEMENT SYSTEM: ******\n");
	printf("\t*************************************************\n\n");
	printf("\t\t\t 1.Admin Login.\n");
	printf("\t\t\t 2.User Login.\n\n");
	while (true)
	{
		printf("\t\tEnter Your Choice=");
		scanf("%s",c);ch=atoi(c);
		fflush(stdin);
		if(ch==1 || ch==2)    break;
		else
		{
			printf("\n\t\tWrong Choice! Please Try again\n");
			sleep(1);
			system("cls||clear");
			login_page();
			break;
		}
	}
	choices(ch);
}
int admin_name_password(char u[50],char a[50])    //for authentication of details
{
	if(strcmp(u,name)==0 && strcmp(a,password)==0)
		return(0);
	return(1);
}
void admin()     //admin menu
{   
	int count=0,ch;char c[200];
	while(true)
	{   
		count=count+1;
		system("cls||clear");
		system("Color 4E");
		printf("\t\t\t\tWELCOME ADMIN!\n\n");
		if(count==1)
		{
			printf("Press 1 to Continue or any other key to go back to login page:");
			scanf("%s",c);ch=atoi(c);
			if(ch!=1)
				login_page();
		}
		char user[50],pass[50];
		printf("\n\t\t\tUsername:");
		scanf("%s",user);
		printf("\n\t\t\tPassword:");
		scanf("%s",pass);
		int i=admin_name_password(user,pass);
		if(i==0) break;
		else
		{
			printf("\n\t\tWrong Username or Password Entered..\n");
			if(count<=5)
				sleep(1);
		}
		if(count>5)
		{
			sleep(1);
			printf("Too many Wrong Choices! Returning to login page...") ;
			sleep(1);
			login_page();
			break;
		}
	}
	printf("\nSuccesfully Logged In...\n");
	sleep(1);
	admin_menu();
}