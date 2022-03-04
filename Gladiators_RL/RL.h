#pragma once
#include "Characters.h"
#include <vector>
#include <random>

using namespace std;

int gamma = 0.99;
int alpha = 0.17;
int epsilon = 0.067;


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

Point MoveChoose(double mass[256][256][2], Point position1, Point position2, int maxMove) //side 0 лево, 1 право;
{

}

/// есть 3 допустимых места спавна, в зависимости от стороны игрока, верхний край, нижный край и ближе к центру арены.
void Learning()
{
	int gameRes[5][5];
	for (int i = 0; i < 5; i++)
	{
		for (int j = i; j < 5; j++)
		{
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
				for (int T = 0; T < 100 && flag; T++)
				{
					/// Расчитать Станы, могут ли ходить т.к. станы. Сел ли в капкан?
					MoveChoose(FirstM, First.position, Second.position, First.maxMove);
					// расчитываем урон и проверяем флаг
					MoveChoose(SecondM, Second.position, First.position, Second.maxMove);
					// Расчитываем урон и флаг. Заносим результаты в таблицы
				}
				//победитель получит +13 очков, заносим их в таблицу результатов.

				// Каждые N итераций сохраняем. в файлы
			}
		}
	}
	//Сохраняем таблицу рещультатов в файл.
}