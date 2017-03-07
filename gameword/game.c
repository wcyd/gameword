#include <stdio.h>
#include <windows.h>

#define Max_Line 10
#define Max_Rank 23
#define LineBegin 1
#define LineEnd Max_Line-2
#define RankBegin 1
#define RankEnd Max_Rank-3

char g_map[Max_Line][Max_Rank] =
{
	"**********************",
	"*                    *",
	"*                    *",
	"*                    *",
	"*                    *",
	"*                    *",
	"*                    *",
	"*                    *",
	"*                    *",
	"**********************",
};

void PrintMap(); //��ӡ��Ϸ��ͼ
void CreateWord();  //������ĸ
void Move();  //��ĸ�ƶ�

void main()
{
	srand(GetTickCount());  //�����������
	//GetTickCount()��õ�ǰʱ�䣨���뼶��������ڿ��������ڵ�ʱ��

	while (1)
	{
		
		system("cls");
		CreateWord();
		Move();
		PrintMap();

		Sleep(500);

	}
}

void PrintMap()
	{
		for (int i = 0; i < Max_Line; i++)
		{
			puts(g_map[i]);
		}

	}

void Move()
{
	for (int i = LineEnd; i >= LineBegin; i--)
	{
		if (i == LineEnd)
		{
			for (int j = RankBegin; j <= RankEnd; j++)
			{
				g_map[i][j] = ' ';
			}
		}
		else
		{
			for (int j = RankBegin; j <= RankEnd; j++)
			{
				g_map[i + 1][j] = g_map[i][j];
				g_map[i][j] = ' ';
			}
		}

	}
}

void CreateWord()
{
	while (1)
	{
		//��Nȡ��  ���Ϊ0-��N-1��
		int indexRank = rand() % (RankEnd - RankBegin + 1) + RankBegin;
		if (g_map[LineBegin][indexRank] != ' ')
		{
			//�Ѿ�����ĸ
			continue;

		}
		//���һ����ĸ
		char word = rand() % 26 + 'A';
		g_map[LineBegin][indexRank] = word;
		break;
	}
}