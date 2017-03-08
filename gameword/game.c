#define _CRT_SECURE_NO_WARNINGS
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
void CheckAttack(char key); //�����Ƿ����
void PrintInfo();  //�����Ϣ
int g_score = 0; //����
int g_level = 1; //�ؿ�
int g_hpValue = 100; //Ѫ��
char g_tipStr[20]=""; //��ʾ����
unsigned g_moveTimeInterval= 1000; //��ĸ�ƶ�ʱ����
unsigned g_createWordInterval = 2000; //������ĸ��ʱ����
unsigned g_lastMoveTime = 0; //�ϴ��ƶ���ʱ��
unsigned g_lastCreateWordTime = 0; //�ϴ���ĸ���ɵ�ʱ��

void main()
{
	srand(GetTickCount());  //�����������
	//GetTickCount()��õ�ǰʱ�䣨���뼶��������ڿ��������ڵ�ʱ��

	while (1)
	{

		unsigned TimeNow = GetTickCount();
		system("cls");
		if (TimeNow-g_lastMoveTime >=g_moveTimeInterval)
		{
			Move();  //�ƶ�
			g_lastMoveTime = TimeNow;
		}
		if (TimeNow-g_lastCreateWordTime >=g_createWordInterval)
		{
			CreateWord(); //������ĸ
			g_lastCreateWordTime = TimeNow;
		}
				
		PrintMap(); //��ӡ��ͼ
		PrintInfo(); //�����Ϣ
		if (_kbhit()) //�м�����
		{
			char key = _getch();
			CheckAttack(key);  //����Ƿ������ȷ
		
		}

		Sleep(50);

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
void CheckAttack(char key)
{
	if (!((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')))
	{
		return;
	}
	int num = 0;
	for (int i = LineBegin; i <= LineEnd; i++)
	{
		for (int j = RankBegin; j <= RankEnd; j++)
		{
			if (key == g_map[i][j] || g_map[i][j]+('a'-'A')==key)
			{
				//ƥ��ɹ�
				g_score += 10;
				g_map[i][j] = ' ';
				num++;
			}
		}
	}
	if (num == 0 || num == 1)
	{
		strcpy(g_tipStr, "");
	}
	else if (num == 2)
	{
		strcpy(g_tipStr, "��ϲ�㣬�����һ��˫ɱ��");
		g_score += 5;
	}
	else if (num == 3)
	{
		strcpy(g_tipStr, "��ϲ�㣬�����һ����ɱ��");
		g_score += 10;
	}
	else if (num == 4)
	{
		strcpy(g_tipStr, "��ϲ�㣬�����һ����ɱ��");
		g_score += 30;
	}
	else
	{
		strcpy(g_tipStr, "��ţB���ޣ���");
		g_score += 1000;
	}
}
void PrintInfo() //�����Ϣ
{
	//�ؿ���Ϣ
	char info[100] = "";
		sprintf(info, "��ǰ�ؿ���%d", g_level);
		puts(info);

    // ������Ϣ
		sprintf(info, "��ǰ������%d", g_score);
		puts(info);

    // Ѫ��
		sprintf(info, "ʣ��Ѫ����%d", g_hpValue);
		puts(info);

    //��ʾ��Ϣ
		puts(g_tipStr);
}