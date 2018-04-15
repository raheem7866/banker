#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>



void input(int Alloc[][10],int Need[][10],int Max[10][10],int Available[1][10]);
void res_request(int Alloc[10][10],int Need[10][10],int Avail[10][10],int pid,int no_re);
int safety(int Alloc[][10],int Need[][10],int Avail[1][10],int no_p,int no_re,int a[]);
int banker(int Alloc[][10],int Need[][10],int Available[1][10],int no_p,int no_re);

int main()
{
	
 
 	int k,y;
	int Alloc[10][10];
	int Max[10][10];
	int Need[10][10];
	int Available[1][10];
	int no_p,no_re,pid,ch,j;

	printf("\n BANKER'S ALGORITHM\n");
	input(Alloc,Need,Max,Available);
	ch=banker(Alloc,Need,Available,no_p,no_re);
    if(ch==1)
    {
     printf("\n \n enter for which Process::");
     scanf("%d",&k);
     res_request(Alloc,Need,Available,k,no_re);
     y=banker(Alloc,Need,Available,no_p,no_re);

    }
    else
    {
    	printf("Deadlock occured so request cannot be made\n");
    }
	return 0;
}

void input(int Alloc[][10],int Need[][10],int Max[10][10],int Available[1][10])
{
	
	int i,j,no_p,no_re;
    printf("\n Enter total no. of processes : ");
	scanf("%d",&no_p);
	printf("\n Enter total no. of resources : ");
	scanf("%d",&no_re);
	for(i=0;i<no_p;i++){
		printf("\n Process %d\n",i+1);
		for(j=0;j<no_re;j++)
		{
			printf(" Allocation for resource %d : ",j+1);
			scanf("%d",&Alloc[i][j]);
			
		}
	}
	for(i=0;i<no_p;i++)
	{
		printf("\n \nEnter resources %d\n",i+1);
		for(j=0;j<no_re;j++)
		{
			printf(" Maximum for resource %d : ",j+1);
			scanf("%d",&Max[i][j]);
		}
	}
	printf("\n \n Enter Available resources : \n");
	for(i=0;i<no_re;i++)
	{
		printf(" Resource %d : ",i+1);
		scanf("%d",&Available[0][i]);
	}

	for(i=0;i<no_p;i++)
		for(j=0;j<no_re;j++)
			Need[i][j]=Max[i][j]-Alloc[i][j];

	printf("\n Allocation Matrix");
	for(i=0;i<no_p;i++)
	{ 
	printf("\n");
     for(j=0;j<no_re;j++)
     {
     	printf("%d\t",Alloc[i][j]);
     }
	}
	printf("\n Maximum Requirement Matrix");
	for(i=0;i<no_p;i++)
	{ 
	printf("\n");
     for(j=0;j<no_re;j++)
     {
     	printf("%d\t",Max[i][j]);
     }
	}
	
	printf("\n Need Matrix");
	for(i=0;i<no_p;i++)
	{ 
	printf("\n");
     for(j=0;j<no_re;j++)
     {
     	printf("%d\t",Need[i][j]);
     }
	}

}

void res_request(int Alloc[10][10],int Need[10][10],int Avail[10][10],int pid,int no_re)
{
	
	int reqmat[1][10];
	int i;
	printf("\n Enter additional request :- \n");
	for(i=0;i<no_re;i++)
	{
		printf(" Request for resource %d : ",i+1);
		scanf("%d",&reqmat[0][i]);
	}
	
	for(i=0;i<no_re;i++)
		if(reqmat[0][i] > Need[pid][i])
	{
			printf("\n Error encountered.\n");
			exit(0);
	}

	for(i=0;i<no_re;i++)
		if(reqmat[0][i] > Avail[0][i])
		{
			printf("\n Resources unavailable.\n");
			exit(0);
		}
	
	for(i=0;i<no_re;i++)
	{
		Avail[0][i]-=reqmat[0][i];
		Alloc[pid][i]+=reqmat[0][i];
		Need[pid][i]-=reqmat[0][i];
	}

}
int safety(int Alloc[][10],int Need[][10],int Avail[1][10],int no_p,int no_re,int a[])
{
    
	int i,j,k,x=0;
	int F[10],Available[1][10];
	int pflag=0,flag=0;
	for(i=0;i<no_p;i++)
		F[i]=0;
	for(i=0;i<no_re;i++)
		Available[0][i]=Avail[0][i];

	for(k=0;k<no_p;k++)
	{
		for(i=0;i<no_p;i++)
		{
			if(F[i] == 0)
			{
				flag=0;
				for(j=0;j<no_re;j++)
				{
					if(Need[i][j] > Available[0][j])
						flag=1;
				}
				if(flag == 0 && F[i] == 0)
				{
					for(j=0;j<no_re;j++)
						Available[0][j]+=Alloc[i][j];
					F[i]=1;
					pflag++;
					a[x++]=i;
				}
			}
		}
		if(pflag == no_p)
			
			return 1;
	}
	
	return 0;
}


int banker(int Alloc[][10],int Need[][10],int Available[1][10],int no_p,int no_re)
{
	
	int j,i,a[10];
	j=safety(Alloc,Need,Available,no_p,no_re,a);
	if(j != 0 )
	{
		printf("\n\n");
		for(i=0;i<no_p;i++)
		     printf(" P%d  ",a[i]);
		printf("\n A safety sequence has been detected.\n");
		return 1;
	}
	else
	{
		printf("\n Deadlock has occured.\n");
		return 0;
	}
	

}



