#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

int password();
int mainmenu();
void add();
void search();
void mydelete();
void update();
void sort();
void display();

struct product
{
	int hps, fps,id;
	char name[40];
};

int password()
{
	char username[]="project", password[]="2019",P[15],U[15],A[20];
	int n=1,a,b;
	printf("\n\n				****LOGIN MODULE FOR RESTAURANT BILLING SYSTEM****");
	printf("\n\n     						ADMIN LOGIN");
	printf("\n\n\n                 Enter your Username and Password");
	while(n<=3)
	{
		printf("\n \nusername  ");
		scanf("%s",&U);
		printf("\n \npassword  ");
		scanf("%s",&P);
		a=strcmp(U,username);
		b=strcmp(P,password);
		if(a==0 && b==0)
		{
			printf("\n You have loged in successfully \n");
			mainmenu();
			break;
		}
			else
			printf(" Invalid username or password");
				n++;
	}
	if(n==4)
	{
		printf("\n You cannot login again \n");
	}
}

int mainmenu()
{
    int ch,i,n,arr[20],sum=0;
    char chs;
    printf("What do you want to do:-");
    printf("\n 1. Generate Bill \n 2. Add product \n 3. Search product \n 4. Delete product \n 5. Update product \n 6. Sort product \n 7. View product\n 8. Want to Exit the Panel Window \n" );
    printf("Enter your choice: ");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
        	printf("\n ********Your Bill Generator is ready******** ");
        	printf("\n How many products did the customer bought:  ");
        	scanf("%d",&n);
        	for(i=1;i<=n;i++)
        	{
        		printf("\n Enter the price of the product%d: ",i);
        		scanf("%d",&arr[i]);
        		
			}
			for(i=1;i<=n;i++)
			{
				sum=sum+arr[i];
			}
			printf("\n The total bill is: %d",sum);
			break;
		case 2:
        	printf("Add product");
        	printf("\n Which product do you want to add\n");
        	add();
        	break;
    	case 3:
        	printf("Search product");
        	search();
        	break;
    	case 4:
        	printf("Delete product");
        	mydelete();
        	printf("\n Record Deleted");
   			break;
   		case 5:
        	printf("Update product");
        	update();
        	break;
    	case 6:
        	printf("Sort product");
        	system("CLS");
        	sort();
        	break;
    	case 7:
        	printf("View product");
        	system("CLS");
        	printf("\n\n Displaying all the entries");
        	display();
        	break;
        case 8:
        	exit(0);
        	printf("\n\n Thank You for visting our RESTAURANT BILLING SYSTEM");
   		default:
   			printf("Invalid choice");
    }
    printf("\n Do you want to perform more operations: ");
    fflush(stdin);
    scanf("%s",&chs);
    if(chs=='Y' || chs=='y')
    {
    	mainmenu();
	}
	else
	{
		printf("\n\n Thank You for visting our RESTAURANT BILLING SYSTEM");
		exit(0);
	}
	getch();

}

void add()
{
	FILE *fp;
	struct product s;
	system("CLS");
	printf("\n ********Welcome to Add product module********");
	fp=fopen("product","a");
	printf("\n Enter the product ID: ");
	scanf("%d",&s.id);
	printf("\n Enter the name of the dish: ");
	scanf("%s",&s.name);
	printf("\n Enter the price of half plate: ");
	scanf("%d",&s.hps);
	printf("\n Enter the price of full plate: ");
	scanf("%d",&s.fps);
	fwrite(&s,sizeof(struct product),1,fp);
	fclose(fp);
	printf("\n Dish is added successfully");
	getch();
}

void display()
{
	FILE *fp;
	struct product p;
	fp=fopen("product","r");
	if(fp==NULL)
	{
		printf("\n File does not exist");
		exit(0);
	}
	fseek(fp,0,SEEK_SET);
	printf("\n\n");
	printf("\n\tID \tName \t\t\HP \tFP");
	while(fread(&p,sizeof(p),1,fp)!=NULL)
	{
		printf("\n\t%d \t%s \t%d \t%d",p.id,p.name,p.hps,p.fps);
	}
	fclose(fp);
	printf("\n Enter any key ");
	getch();
}

void search()
{
	FILE *fp;
	int k, key, found=0;
	struct product p;
	system("CLS");
	printf("\n Enter ID to search: ");
	scanf("%d",&key);
	fp=fopen("product","r");
	if(fp==NULL)
	{
		printf("\n File does not exist!!!");
		exit(0);
	}
	fseek(fp,0,SEEK_SET);
	while(fread(&p,sizeof(p),1,fp)!=NULL)
	{
		if(p.id==key)
		{
			found=1;
			printf("\n Record Found");
			printf("\n\tID \tName \t\t\HP \tFP");
			printf("\n\t%d \t%s \t%d \t%d",p.id,p.name,p.hps,p.fps);
			exit(0);
		}
	}
	fclose(fp);
	if(found==0)
	{
		printf("\n Record not found!!!");
	}
}

void sort()
{
	int arr[30],i,j,count = 0,t;
	FILE *fp;
	struct product p;
	fp=fopen("product","r");
	while(fread(&p,sizeof(p),1,fp))
	{
		arr[count]=p.id;
		count++;
	}
	for(i=0;i<count-1;i++)
	{
		for(j=i+1;j<count;j++)
		{
			if(arr[i]>arr[j])
			{
				t=arr[i];
				arr[i]=arr[j];
				arr[j]=t;
			}
		}
	}
	printf("\n The Sorted List is");
	printf("\n\n");
	printf("\n\tID \tName \tHP \tFP");
	for(i=0;i<count;i++)
	{
		rewind(fp);
		while(fread(&p,sizeof(p),1,fp))
		{
			if(arr[i]==p.id)
			{
				printf("\n\t%d \t%s \t%d \t%d",p.id,p.name,p.hps,p.fps);
			}
		}
	}
}

void mydelete()
{
	FILE *fp, *ft;
	int i, key, found;
	struct product p;
	system("CLS");
	printf("\n Enter ID to delete: ");
	scanf("%d",&key);
	fp=fopen("product","r");
	ft=fopen("products","wb+");
	if(fp==NULL)
	{
		printf("\n File does not exist!!!!");
		exit(0);
	}
	fseek(fp,0,SEEK_SET);
	while(fread(&p,sizeof(p),1,fp)==1)
	{
		if(p.id!=key)
		{
			fwrite(&p,sizeof(p),1,ft);
		}
	}
	fclose(fp);
	fclose(ft);
	remove("product");
	rename("products","product");
}
void update()
{
	FILE *fp;
	int i, key, found;
	struct product p;
	system("CLS");
	printf("\n Enter ID to update: ");
	scanf("%d",&key);
	fp=fopen("product","rb+");
	if(fp==NULL)
	{
		printf("\n File does not exist!!!");
		exit(0);
	}
	fseek(fp,0,SEEK_SET);
	while(fread(&p,sizeof(p),1,fp)==1)
	{
		if(p.id==key)
		{
			printf("\n Enter name: ");
			scanf("%s",p.name);
			fseek(fp,sizeof(p),SEEK_CUR);
			found=fwrite(&p,sizeof(p),1,fp);
			break;
		}
	}
	fclose(fp);
	if(found==0)
	{
		printf("\n File does not exist!!!");
	}
	else
	{
		printf("\n Record Updated");
	}
}

int main()
{
	password();
	getch();
	return 0;
}
