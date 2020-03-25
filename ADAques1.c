#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

const int MAX = 10;

int max(int a, int b)
{
	return a>b ? a : b;
}

void printWeightValue(int w[MAX], int p[MAX], int num){
	int i;
	printf("Weight\tValue\n");
	for(i = 1; i <= num; i++){
		printf("%d\t%d\n", w[i], p[i]);
	}
}

void printProfitTable(int capacity, int table[MAX][MAX], int num){
	int i, j;
	for (i=0; i<=num; i++)
	{
		for(j=0; j<=capacity; j++)
		{
			printf("\t%d",table[i][j]);
		}
  		printf("\n");
	}
}

void fnPrintProfit(int num, int loaded[MAX], int value[MAX]){
	int totalProfit = 0;
	int i, j;
	for (i=1; i<=num; i++)
	{
		if (loaded[i])
		{
			printf("%d ",i);
			totalProfit += value[i];
		}
	}
	printf("}\n");
	printf("\nTotal Profit : %d\n",totalProfit);
}

void fnProfitTable(int w[MAX], int p[MAX], int n, int c, int t[MAX][MAX])
{
	int i,j;
	for (j=0; j<=c; j++)
		t[0][j] = 0;
		
	for (i=0; i<=n; i++)
		t[i][0] = 0;
		
	for (i=1; i<=n; i++)
	{
		for (j=1; j<=c; j++)
		{
			if (j-w[i] < 0)
				t[i][j] = t[i-1][j];
			else
				t[i][j] = max( t[i-1][j], p[i] + t[i-1][j-w[i]]);
		}
	}
}

void fnSelectItems(int n,int c, int t[MAX][MAX], int w[MAX], int l[MAX])
{
	int i,j;
	i = n;
	j = c;
	while (i >= 1 && j >= 1)
	{
		if (t[i][j] != t[i-1][j])
		{
			l[i] = 1;
			j = j - w[i];
			i--;
		}
		else
			i--;
	}
}

int main(void)
{
	
	FILE *fp;
	char fName[100];

	int i1;
	int i, j;
	int num = 0;			
	
	int weight[MAX];
	int value[MAX];
	int capacity;
	int loaded[MAX];
	int table[MAX][MAX];
	int choice;
	bool flag = false; //no need for flag here though
	
	weight[0] = 0;
	value[0] = 0;

	while(1){
		printf("1. Manual Input\n2. Take Input from file\n3. Exit\n");
		printf("Enter your choice:\t");
		scanf("%d", &choice);
		system("clear");

		switch(choice){
			case 1:
				printf("Enter the number of Items:\t");
				scanf("%d", &num);

				system("clear");

				printf("Enter the weights : \n");
				for (i=1; i<=num; i++)
				{
					printf("\nWeight %d :",i);
					scanf("%d",&weight[i]);
				}

				system("clear");

				printf("\nEnter the profits : \n");
				for (i=1; i<=num; i++)
				{
					printf("\nValue %d :",i);
					scanf("%d",&value[i]);
				}

				system("clear");

				flag = true;

				break;

			case 2:
				lable1:
				printf("Enter the name of file:\t");
				scanf("%s", fName);

				system("clear");

				fp = fopen(fName, "r");

				if(fp == NULL)
				{
					printf("%s file does not exist. Try angain\n", fName);
					goto lable1;
				}

				fclose(fp);

				system("clear");

				fp = fopen(fName, "r");
				char c = getc(fp);
				while(c != EOF){
					if( c == '\n')
						num++;
					c = getc(fp);
				}
				fclose(fp);

				fp = fopen(fName, "r");
	
				for(i = 1; i <= num; i++) {
					fscanf(fp, "%d %d %d", &i1, &weight[i], &value[i]);
				}
				fclose(fp);

				flag = true;
				break;
			case 3:
				exit(0);
			default:
				printf("Invalid input\n");
		}

		if(flag){
			printWeightValue(weight, value, num);
	
			printf("\nEnter the maximum capacity : ");
			scanf("%d",&capacity);

			for( i=1; i<=num; i++)
				loaded[i] = 0;

			fnProfitTable(weight,value,num,capacity,table);
			fnSelectItems(num,capacity,table,weight,loaded);
			
			printf("==========================================================\n");
			
			printf("Profit Matrix\n");

			printProfitTable(capacity, table, num);
			printf("==========================================================\n");

			printf("\nItem numbers which can be carried by Alia : \n{ ");

			fnPrintProfit(num, loaded, value);
		}
		flag = false;
		printf("Window will refresh after 10 sec\n");
		sleep(10);
		system("clear");
	}
	
	return 0;
}
