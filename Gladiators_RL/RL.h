#pragma once
#include "Characters.h"
#include <vector>
#include <random>

using namespace std;

int gamma = 0.99;
int alpha = 0.17;
int epsilon = 0.067;

struct moveResult
{
	Point pos;
	bool skill;
};


Point SpawnChooseFirst(double mass[256][256][2]) //side 0 лево, 1 право;
{
	int i0[3] = { 1, 14, 7 }; int j0[3] = { 1, 1, 7 };
	int i1[3] = { 1, 14, 8 }; int j1[3] = { 14, 14, 8 };
	int min = -150;
	int pos = -1;
	for (int i = 0; i < 3; i++)
	{
		int minChal = mass[i0[i] * 16 + j0[i]][i1[0] + j1[0]][0];
		for (int j = 1; j < 3; j++)
		{
			if (minChal > mass[i0[i] * 16 + j0[i]][i1[j] + j1[j]][0])
			{
				minChal = mass[i0[i] * 16 + j0[i]][i1[j] + j1[j]][0];
			}
		}
		if (minChal > min)
		{
			min = minChal;
			pos = i;
		}
	}
	int Eps = rand() % 1000;
	Point ChoosenOne;
	if (Eps > 1000 * epsilon)
	{
		ChoosenOne.x = i0[pos]; ChoosenOne.y = j0[pos];
	}
	else
	{
		int R = rand() % 2;
		int K = 0;
		while (R > 0 || K == pos)
		{
			if (K != pos)
			{
				R--;
			}
			K++;
		}
		ChoosenOne.x = i0[K]; ChoosenOne.y = j0[K];
	}
	return ChoosenOne;
}

Point SpawnChooseSecond(double mass[256][256][2], Point firstChoose) //side 0 лево, 1 право;
{
	int i1[3] = { 1, 14, 8 }; int j1[3] = { 14, 14, 8 };
	int max = mass[firstChoose.y * 16 + firstChoose.x][i1[0] + j1[0]][0];
	int pos = 0;
	for (int i = 1; i < 3; i++)
	{
		if (mass[firstChoose.y * 16 + firstChoose.x][i1[i] + j1[i]][0] > max)
		{
			max = mass[firstChoose.y * 16 + firstChoose.x][i1[i] + j1[i]][0];
			pos = i;
		}
	}
	Point ChoosenOne; 
	int Eps = rand() % 1000;
	if (Eps > 1000 * epsilon)
	{
		ChoosenOne.x = i1[pos]; ChoosenOne.y = j1[pos];
	}
	else
	{
		int R = rand() % 2;
		int K = 0;
		while (R > 0 || K == pos)
		{
			if (K != pos)
			{
				R--;
			}
			K++;
		}
		ChoosenOne.x = i1[K]; ChoosenOne.y = j1[K];
	}
	return ChoosenOne;
}

moveResult MoveChoose(double mass[256][256][2], Point position1, Point position2, int maxMove) //side 0 лево, 1 право;
{

}

/// есть 3 допустимых места спавна, в зависимости от стороны игрока, верхний край, нижный край и ближе к центру арены.
void Learning()
{
	int gameRes[5][5];
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			gameRes[i][j] = 0;

			double FirstM[256][256][2];
			double SecondM[256][256][2];
			for (int i0 = 0; i0 < 256; i0++)
			{
				for (int j0 = 0; j0 < 256; j0++)
				{
					FirstM[i0][j0][0] = 0;
					FirstM[i0][j0][1] = 0;
					SecondM[i0][j0][0] = 0;
					SecondM[i0][j0][1] = 0;
				}
			}

			// Добавить выбор спавна
			//int r = rand() % 2;
			
			for (int K = 0; K < 500; K++)
			{
				Point FirstSpawn = SpawnChooseFirst(FirstM);
				Point SecondSpawn = SpawnChooseSecond(SecondM, FirstSpawn);

				Character First;
				Character Second;

				/// Создаем игроков
				switch (i)
				{
				case 0:
					Pirate First = Pirate(FirstSpawn.x, FirstSpawn.y);
					break;
				case 1:
					Mage First = Mage(FirstSpawn.x, FirstSpawn.y);
					break;
				case 2:
					Ranger First = Ranger(FirstSpawn.x, FirstSpawn.y);
					break;
				case 3:
					Gladiator First = Gladiator(FirstSpawn.x, FirstSpawn.y);
					break;
				case 4:
					Wizard First = Wizard(FirstSpawn.x, FirstSpawn.y);
					break;
				}

				switch (j)
				{
				case 0:
					Pirate Second = Pirate(SecondSpawn.x, SecondSpawn.y);
					break;
				case 1:
					Mage Second = Mage(SecondSpawn.x, SecondSpawn.y);
					break;
				case 2:
					Ranger Second = Ranger(SecondSpawn.x, SecondSpawn.y);
					break;
				case 3:
					Gladiator Second = Gladiator(SecondSpawn.x, SecondSpawn.y);
					break;
				case 4:
					Wizard Second = Wizard(SecondSpawn.x, SecondSpawn.y);
					break;
				}

				bool flag = true;
				double fullRes = 0;
				double result;
				bool FSkill = 0, SSkill = 0;
				for (int T = 0; T < 100 && flag; T++)
				{
					Point firstStart, secondStart;
					firstStart.x = First.position.x; firstStart.y = First.position.y;
					secondStart.x = Second.position.x; secondStart.y = Second.position.y;
					result = 0;
					moveResult FR;
					moveResult SR;
					/// Расчитать Станы, могут ли ходить т.к. станы. Сел ли в капкан?
					if (First.Stunned > 0)
					{
						First.Stunned--;
						First.CoolDownTimer--;
					}
					else
					{
				
						//в выборе хода долэна быть проыерка на возможность скила
						FR = MoveChoose(FirstM, First.position, Second.position, First.maxMove);
						if (FR.skill == true)
						{
							First.SkillUse(Second);
						}
						else
						{
							First.CoolDownTimer--;
						}
						//расписать урон
						if ((abs(First.position.x - Second.position.x) + abs(First.position.y - Second.position.y)) < First.firstRange)
						{
							Second.Hp -= First.firstDamage;
							result += First.firstDamage / Second.Hp;
							if (i == 4 && Second.amiInJija(First))
							{
								Second.Hp -= First.firstDamage;
								result += First.firstDamage / Second.Hp;
							}
						}
						else
						{
							if ((abs(First.position.x - Second.position.x) + abs(First.position.y - Second.position.y)) < First.secondRange)
							{
								Second.Hp -= First.secondDamage;
								result += First.secondDamage / Second.Hp;
							}
						}
						First.position.x = FR.pos.x;
						First.position.y = FR.pos.y;
						//if () наступил в капкан и стоит ли в жиже?	
						if (j == 2)
						{
							if (First.amiInCap(Second))
							{
								First.Stunned += 1;
								First.Hp -= 3;
								result -= 3 / First.Hp;
							}
						}
					}


					if(Second.Hp <= 0)
					{
						flag = false;
						fullRes += 13;
					}
					if (Second.Stunned > 0)
					{
						Second.Stunned--;
						Second.CoolDownTimer--;
					}
					else
					{

						SR = MoveChoose(SecondM, Second.position, First.position, Second.maxMove);

						if (SR.skill == true)
						{
							Second.SkillUse(First);
						}
						else
						{
							Second.CoolDownTimer--;
						}

						if ((abs(First.position.x - Second.position.x) + abs(First.position.y - Second.position.y)) < Second.firstRange)
						{
							First.Hp -= Second.firstDamage;
							result -= Second.firstDamage / First.Hp;
						}
						else
						{
							if ((abs(First.position.x - Second.position.x) + abs(First.position.y - Second.position.y)) < Second.secondRange)
							{
								First.Hp -= Second.secondDamage;
								result -= Second.secondDamage / First.Hp;

								if (j == 4 && First.amiInJija(Second))
								{
									First.Hp -= Second.secondDamage;
									result -= Second.secondDamage / First.Hp;
								}
							}
						}
						Second.position.x = SR.pos.x;
						Second.position.y = SR.pos.y;
						if (i == 2)
						{
							if (Second.amiInCap(First))
							{
								Second.Stunned += 1;
								Second.Hp -= 3;
								result += 3 / Second.Hp;
							}
						}
					}
					if (First.Hp <= 0)
					{
						flag = false;
						fullRes -= 13;
					}
					// Расчитываем урон и флаг. Заносим результаты в таблицы

					FirstM[firstStart.x + firstStart.y * 16][secondStart.x + secondStart.y * 16][FSkill] =
						FirstM[firstStart.x + firstStart.y * 16][secondStart.x + secondStart.y * 16][FSkill] +
						alpha * (result + 
							gamma * FirstM[FR.pos.x + FR.pos.y * 16][secondStart.x + secondStart.y * 16][FR.skill] - 
							FirstM[firstStart.x + firstStart.y * 16][secondStart.x + secondStart.y * 16][FSkill]);
					FSkill = FR.skill;
					SecondM[secondStart.x + secondStart.y * 16][First.SkillPosition.x + First.SkillPosition.y * 16][SSkill] = 
						SecondM[secondStart.x + secondStart.y * 16][First.SkillPosition.x + First.SkillPosition.y * 16][SSkill] + 
						alpha * (-result + 
							gamma * SecondM[SR.pos.x + SR.pos.y * 16][First.SkillPosition.x + First.SkillPosition.y * 16][SR.skill] -
							SecondM[secondStart.x + secondStart.y * 16][First.SkillPosition.x + First.SkillPosition.y * 16][SSkill]);
				}
				fullRes += result;

				gameRes[i][j] = gameRes[i][j] + alpha * (fullRes - gameRes[i][j]);
				//победитель получит +13 очков, заносим их в таблицу результатов.

				// Каждые N итераций сохраняем. в файлы
			}
		}
	}
	//Сохраняем таблицу рещультатов в файл.
}