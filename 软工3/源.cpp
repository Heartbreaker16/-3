#include<math.h>
#include<graphics.h>
#include <stdio.h>
#include<time.h>
#include<malloc.h>
//随机生成的点
struct Block {
	int x;
	int y;
	int z;
};
//系统生成的空位
struct Square {
	int side;
	int num;
	int left;
	int right;
};
//计算最大方差
int MaxVariance(Block blocks[], int divide[], int m)
{
	double aver_x = 0, variance_x = 0;
	for (int i = 0; i < m; i++)
		aver_x = aver_x + (double)blocks[i].x / m;
	for (int i = 0; i < m; i++)
		variance_x = variance_x + (double)(blocks[i].x - aver_x)*(blocks[i].x - aver_x);
	double aver_y = 0, variance_y = 0;
	for (int i = 0; i < m; i++)
		aver_y = aver_y + (double)blocks[i].y / m;
	for (int i = 0; i < m; i++)
		variance_y = variance_y + (double)(blocks[i].y - aver_y)*(blocks[i].y - aver_y);
	double aver_z = 0, variance_z = 0;
	for (int i = 0; i < m; i++)
		aver_z = aver_z + (double)blocks[i].z / m;
	for (int i = 0; i < m; i++)
		variance_z = variance_z + (double)(blocks[i].z - aver_z)*(blocks[i].z - aver_z);

	if ((variance_x >= variance_y) && (variance_x >= variance_z))
	{
		for (int i = 0; i < m; i++) divide[i] = blocks[i].x; 
		return 1;
	}
	if ((variance_y >= variance_x) && (variance_y >= variance_z))
	{
		for (int i = 0; i < m; i++) divide[i] = blocks[i].y;
		return 2;
	}
	if ((variance_z >= variance_x) && (variance_z >= variance_y))
	{
		for (int i = 0; i < m; i++) divide[i] = blocks[i].z; 
		return 3;
	}
}
//按坐标值排序划分平面
void SelectSort1(int * ListData, int ListLength)
{
	int i, j;
	int length = ListLength;
	for (i = 0; i <= length - 2; i++)
	{
		int k = i;
		for (j = i + 1; j <= length - 1; j++)
		{
			if (ListData[k]>ListData[j])
			{
				k = j;
			}
		}
		if (k != i)
		{
			int tmp = ListData[i];
			ListData[i] = ListData[k];
			ListData[k] = tmp;
		}
	}
}
//按棱长排序系统生成的空位
void SelectSort2(struct Square ListData[], int ListLength)
{
	int i, j;
	int length = ListLength;
	for (i = 0; i <= length - 2; i++)
	{
		int k = i;
		for (j = i + 1; j <= length - 1; j++)
		{
			if (ListData[k].side<ListData[j].side)
			{
				k = j;
			}
		}
		if (k != i)
		{
			struct Square tmp = ListData[i];
			ListData[i] = ListData[k];
			ListData[k] = tmp;
		}
	}
}

int main()
{
	int m,n;//点和圆的数量 (等待用户输入)
	printf("请输入将在空间内随机生成点的个数："); scanf_s("%d", &m);
	printf("请输入你想在空间内填充的球的个数："); scanf_s("%d",  &n);
	//随机点坐标的结构体数组
	struct Block *blocks;
	blocks = (Block*)malloc(m*sizeof(Block));
	int *divide;
	divide = (int*)malloc(m*sizeof(int));
	srand((unsigned)time(NULL));
	for (int i = 0; i < m; i++)
	{
		blocks[i].x = 1+(rand() % 1000);
		blocks[i].y = 1 + (rand() % 1000);
		blocks[i].z = 1 + (rand() % 1000);
	}
	Sleep(500);
	printf("\n随机生成的%d个随机点：\n\n",m);
	Sleep(400);
	for (int i = 0; i < m; i++)
	{
		printf("(%d,%d,%d)\n", blocks[i].x, blocks[i].y, blocks[i].z);
		Sleep(500);
	}
	int xyz;
	switch (MaxVariance(blocks, divide, m)) {
	case 1: { printf("\n方案：平行于yz平面沿x坐标分割正方体空间\n"); xyz = 1; }  break;
	case 2: { printf("\n方案：平行于xz平面沿y坐标分割正方体空间\n"); xyz = 2; }   break;
	case 3: { printf("\n方案：平行于xy平面沿z坐标分割正方体空间\n"); xyz = 3; }   break;
	}
	SelectSort1(divide, m);
	printf("分割平面：");
	switch (xyz) {
	case 1:for (int i = 0; i < m; i++) { printf(" X=%d", divide[i]); Sleep(300); } break;
	case 2:for (int i = 0; i < m; i++) { printf(" Y=%d", divide[i]); Sleep(300); }  break;
	case 3:for (int i = 0; i < m; i++) { printf(" Z=%d", divide[i]); Sleep(300); }  break;
	}
	printf("\n沿以上平面分隔正方体空间，将封闭空间分割成多个夹层，在每个夹层里填充球体\n\n");
	int square_num;
	//记录空位的结构体数组
	struct Square *squares;
	squares = (Square*)malloc((2*m+2)*sizeof(Square));
	for (int p = 0; p <= m; p++)
	{
		if (p == 0)//划分第一个夹层
		{
			square_num = (1000 / divide[0])* (1000 / divide[0]);
			squares[2*p].side = divide[0];
			squares[2 * p].num = square_num;
			squares[2 * p].left = 0;
			squares[2 * p].right = divide[0];
			squares[2 * p + 1].side = 1000 % divide[0];
			squares[2 * p+1].left = 0;
			if (squares[2 * p + 1].side != 0)
			{
				squares[2 * p + 1].num = 2 * (divide[0] / squares[2 * p + 1].side)*((1000 - 1000 % divide[0]) / squares[2 * p + 1].side) + (divide[0] / squares[2 * p + 1].side);
				squares[2 * p + 1].right = divide[0];
			}
			else
			{
				squares[2 * p + 1].num = 0;
				squares[2 * p + 1].right = 0;
			}
		}
		if ((p > 0) && (p < m))//划分中间每个夹层
		{
			square_num = square_num + (1000 / (divide[p] - divide[p - 1]))*(1000 / (divide[p] - divide[p - 1]));
			squares[2 * p].side = divide[p] - divide[p - 1];
			squares[2 * p].num = (1000 / (divide[p] - divide[p - 1]))*(1000 / (divide[p] - divide[p - 1]));
			squares[2 * p].left = divide[p - 1];
			squares[2 * p].right = divide[p];
			squares[2 * p + 1].side = 1000 % squares[2 * p].side;
			
			if (squares[2 * p + 1].side != 0)
			{
				squares[2 * p + 1].num = 2 * (squares[2 * p].side / squares[2 * p + 1].side)*((1000 - squares[2 * p + 1].side) / squares[2 * p + 1].side) + (squares[2 * p].side / squares[2 * p + 1].side);
				squares[2 * p + 1].left = divide[p - 1]; 
				squares[2 * p + 1].right = divide[p];
			}
			else
			{
				squares[2 * p + 1].num = 0;
				squares[2 * p + 1].left = 0;
				squares[2 * p + 1].right = 0;
			}
		}
		if (p == m)//划分最后一个夹层
		{
			square_num = square_num + (1000 / (1000 - divide[p-1]))*(1000 / (1000 - divide[p-1]));
			squares[2*p].side = 1000 - divide[p-1];
			squares[2*p].num = 1000 / (1000 - divide[p-1]);
			squares[2 * p].left = divide[p - 1];
			squares[2 * p].right = 1000;
			squares[2 * p + 1].side = 1000 % squares[2 * p].side;
			if (squares[2 * p + 1].side != 0)
			{
				squares[2 * p + 1].num = 2 * (squares[2 * p].side / squares[2 * p + 1].side)*((1000 - squares[2 * p + 1].side) / squares[2 * p + 1].side) + (squares[2 * p].side / squares[2 * p + 1].side);
				squares[2 * p + 1].left = divide[p - 1];
				squares[2 * p + 1].right = 1000;
			}
			else
			{
				squares[2 * p + 1].num = 0;
				squares[2 * p + 1].left = 0;
				squares[2 * p + 1].right = 0;
			}
		}
	}
	SelectSort2( squares, 2*m+2);
	Sleep(500);
	printf("系统生成的空位：\n\n");
	Sleep(500);
	for (int l = 0; l < 2*m+2; l++)
		printf("棱长：%d   数量：%d \n", squares[l].side, squares[l].num); 
	printf("\n\n");
	Sleep(500);
	    printf("所填充的%d个球的直径和区域依次如下： \n",n); 
		Sleep(500);
		printf("(注：球放置的位置十分规则，不需要给出球心坐标。只需注意在放置时球尽量向两个邻边靠拢，彼此紧密排列)\n\n");
		Sleep(1000);
	int count = 0;
	for (int l = 0; l < n; l++)
	{		
		while (squares[l].num != 0)
			{
				printf("直径：%d   区域：[%d ,%d]  \n", squares[l].side, squares[l].left, squares[l].right);
				squares[l].num--;
				count++;
				if (count == n) break;
			}
		if (count == n) break;
	}
	getchar();
	getchar();
	return 0;
}
