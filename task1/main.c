#include<stdio.h>
#include<malloc.h>

int main(int argc, char** argv)
{
	int n;
	scanf("%d", &n);
	int* arr = (int*)malloc((n + 1) * (n + 1) * sizeof(int));
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			*(arr + i * n + j) = i * j;
		}
	}

	int x1, x2, y1, y2;
	scanf("%d", &x1);

	while (x1)
	{
		scanf("%d %d %d", &y1, &x2, &y2);
		for (i = y1; i <= y2; i++)
		{
			for (j = x1; j <= x2; j++)
			{
				printf("%4d", *(arr + i * n + j));
			}
			printf("\n");
		}
		scanf("%d", &x1);
	}

	free(arr);
	return 0;
}
