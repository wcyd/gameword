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

void PrintMap(); //打印游戏地图
void CreateWord();  //生成字母
void Move();  //字母移动
void CheckAttack(char key); //按键是否打中
void PrintInfo();  //输出信息
int g_score = 0; //分数
int g_level = 1; //关卡
int g_hpValue = 100; //血量
char g_tipStr[20]=""; //提示文字
unsigned g_moveTimeInterval= 1000; //字母移动时间间隔
unsigned g_createWordInterval = 2000; //创建字母的时间间隔
unsigned g_lastMoveTime = 0; //上次移动的时间
unsigned g_lastCreateWordTime = 0; //上次字母生成的时间

void main()
{
	srand(GetTickCount());  //设置随机种子
	//GetTickCount()获得当前时间（毫秒级），相对于开机到现在的时间

	while (1)
	{

		unsigned TimeNow = GetTickCount();
		system("cls");
		if (TimeNow-g_lastMoveTime >=g_moveTimeInterval)
		{
			Move();  //移动
			g_lastMoveTime = TimeNow;
		}
		if (TimeNow-g_lastCreateWordTime >=g_createWordInterval)
		{
			CreateWord(); //生成字母
			g_lastCreateWordTime = TimeNow;
		}
				
		PrintMap(); //打印地图
		PrintInfo(); //输出信息
		if (_kbhit()) //有键按下
		{
			char key = _getch();
			CheckAttack(key);  //检测是否打字正确
		
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
		//对N取余  结果为0-（N-1）
		int indexRank = rand() % (RankEnd - RankBegin + 1) + RankBegin;
		if (g_map[LineBegin][indexRank] != ' ')
		{
			//已经有字母
			continue;

		}
		//随机一个字母
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
				//匹配成功
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
		strcpy(g_tipStr, "恭喜你，完成了一次双杀！");
		g_score += 5;
	}
	else if (num == 3)
	{
		strcpy(g_tipStr, "恭喜你，完成了一次三杀！");
		g_score += 10;
	}
	else if (num == 4)
	{
		strcpy(g_tipStr, "恭喜你，完成了一次四杀！");
		g_score += 30;
	}
	else
	{
		strcpy(g_tipStr, "你牛B！赞！！");
		g_score += 1000;
	}
}
void PrintInfo() //输出信息
{
	//关卡信息
	char info[100] = "";
		sprintf(info, "当前关卡：%d", g_level);
		puts(info);

    // 分数信息
		sprintf(info, "当前分数：%d", g_score);
		puts(info);

    // 血量
		sprintf(info, "剩余血量：%d", g_hpValue);
		puts(info);

    //提示信息
		puts(g_tipStr);
}