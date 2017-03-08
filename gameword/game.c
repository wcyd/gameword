#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

#define Max_Line 10
#define Max_Rank 23
#define LineBegin 1
#define LineEnd Max_Line-2
#define RankBegin 1
#define RankEnd Max_Rank-3
#define Max_Level 10

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

int g_arryLevelScore[Max_Level+1]=
{
	0,50,100,150,200,250,300,350,400,450,500
};
int g_arryMoveIterval[Max_Level + 1] =
{
	0, 1000, 900, 800, 700, 600, 500, 400, 300, 200,100
};
int g_arryCreateWordIterval[Max_Level + 1] =
{
	0,2000,1800,1600,1400,1200,1000,800,600,400,200
};

void PrintMap(); //��ӡ��Ϸ��ͼ
void CreateWord();  //������ĸ
void Move();  //��ĸ�ƶ�
void CheckAttack(char key); //�����Ƿ����
void PrintInfo();  //�����Ϣ
void CheckLevel(); //����Ƿ���һ��
int g_score = 0; //����
int g_level = 1; //�ؿ�
int g_hpValue = 100; //Ѫ��
char g_tipStr[200]=""; //��ʾ����
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
	
		if (TimeNow-g_lastMoveTime >=g_moveTimeInterval)
		{
			Move();  //�ƶ�
			if (g_hpValue < 0)
			{
				system("cls");
				PrintMap(); //��ӡ��ͼ
				PrintInfo(); //�����Ϣ
				break;
			}
			g_lastMoveTime = TimeNow;
		}
		if (TimeNow-g_lastCreateWordTime >=g_createWordInterval)
		{
			CreateWord(); //������ĸ
			g_lastCreateWordTime = TimeNow;
		}
		system("cls");
		PrintMap(); //��ӡ��ͼ
				
		if (_kbhit()) //�м�����
		{
			char key = _getch();
			CheckAttack(key);  //����Ƿ������ȷ
			if (g_level>Max_Level)
			{
				break;
			}
		}
		PrintInfo(); //�����Ϣ
	
		
		Sleep(50);
	}
	//�жϵ����ǹ��˻���ͨ����
	if (g_hpValue< 0)
	{
		//����
		puts("����ˣ��������Ͱɣ�����");
	}
	else if (g_level>Max_Level)
	{
		//ͨ����
		puts("��ϲ�㣬ͨ���ˣ�����");
	}
	system("pause");
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
				if (g_map[i][j] != ' ')
				{
					//���˸���ĸ
					g_hpValue -= 20;
				}
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
				CheckLevel(); //���ͨ���ؿ�
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
void CheckLevel()
{
	if (g_score >= g_arryLevelScore[g_level])
	{
		g_level++;
		if (g_level > Max_Level)
		{
			// ͨ����
			return;
		}
		g_moveTimeInterval = g_arryMoveIterval[g_level];
		g_createWordInterval = g_arryCreateWordIterval[g_level];
			
	}
}