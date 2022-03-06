#pragma once

struct Point
{
	int x;
	int y;
};

class Character
{
    public:
		Point position; //позиция
		int maxHp, //максимальное здоровье
			Hp, //текущее здоровье
			maxMove, //максимальная дистанция за ход
			firstDamage, //урон в ближнем круге
			firstRange, //дистанция ближнего круга
			secondDamage, //урон в дальнем круге 
			secondRange, //дальний круг
			CoolDown, //перезарядка способности
			CoolDownTimer, //Таймер до использования способности
			Stunned; //Длительность текущего оглушения
		Point
			Capcan[3],
		    SkillPosition;
		void SkillUse(Character sec)
		{
			return;
		}
		bool amiInCap(Character sec)
		{
			bool res = false;
			for (int i = 0; i < 3; i++)
			{
				if (position.x == sec.Capcan[i].x && position.y == sec.Capcan[i].y)
				{
					res = true;
					sec.Capcan[i].x = -1;
					sec.Capcan[i].y = -1;
				}
			}
			return res;
		}

		bool amiInJija(Character sec)
		{
			return (abs(position.x - sec.position.x) + abs(position.y - sec.position.y) <= 1);
		}
};

/// Пират оружие ближнего боя, скил - крюк, подтягивает любого противника на расстоянии 7 клеток, оглушая его на ход
class Pirate :Character
{
public:
	int HookDistance;
	Pirate(int x, int y)
	{
		position.x = x, position.y = y;
		maxHp = 27;
		Hp = 27;
		maxMove = 3;
		firstDamage = 3;
		firstRange = 1;
		secondDamage = 3;
		secondRange = 1;
		CoolDown = 3;
		CoolDownTimer = 0;
		HookDistance = 5;
		Stunned = 0;
	}
	void SkillUse(Character& sec)
	{
		CoolDownTimer = CoolDown;
		if ((abs(position.x - sec.position.x) + abs(position.y - sec.position.y)) <= HookDistance)
		{
			sec.position.x = position.x - (position.x - sec.position.x) / abs(position.x - sec.position.x);
			sec.position.y = position.y - (position.y - sec.position.y) / abs(position.y - sec.position.y);
			sec.Stunned++;
		}
	}
};

/// Маг, верткий тип, обладает опасной магией на дистанции, ну а вблизи его магия еще опаснее. 
/// У деда деменция, поэтому телепортируется в случайное место
class Mage :Character
{
public:
	int BlinkDistance;
	Mage(int x, int y)
	{
		position.x = x, position.y = y;
		maxHp = 16;
		Hp = 15;
		maxMove = 1;
		firstDamage = 2;
		firstRange = 3;
		secondDamage = 1;
		secondRange = 7;
		CoolDown = 2;
		CoolDownTimer = 0;
		BlinkDistance = 5;
		Stunned = 0;
	}
	void SkillUse(Character& sec)
	{
		CoolDownTimer = CoolDown;
		position.x = rand() % 16;
		position.y = rand() % 16;
	}
};

/// Рэнджер, неприятный противник, его меткие выстрелы гораздо опаснее на дистанции.
/// Держит противников подальше при помощи капканов
/// Когда наступает в свой капкан не срабатывает
/// Противник, закончивший ход в капкане застревают в нем на 2 хода, капканы замаскированы, противник не знает где они.
/// У него проблемы с памятью, поэтому когда он ставит четвертый капкан первый схлопывается,
///даже если второй слот освободился
class Ranger :Character
{
public:
	Point Capcan[3];
	int CapcanDamage;
	int capNum;
	int capRange;
	Ranger(int x, int y)
	{
		position.x = x, position.y = y;
		maxHp = 19;
		Hp = 19;
		maxMove = 6;
		firstDamage = 2;
		firstRange = 1;
		secondDamage = 1;
		secondRange = 4;
		CoolDown = 2;
		CoolDownTimer = 0;
		Capcan[0].x = -1, Capcan[0].y = -1;
		Capcan[1].x = -1, Capcan[1].y = -1;
		Capcan[2].x = -1, Capcan[2].y = -1;
		capNum = 0;
		CapcanDamage = 3;
		//capRange = 1; Срет капканами под себя
		Stunned = 0;
	}
	void SkillUse(Character& sec)
	{
		CoolDownTimer = CoolDown;
		Capcan[capNum % 3].x = position.x;
		Capcan[capNum % 3].y = position.y;
		capNum++;
	}
};

/// Гладиатор, закаленный в тысячах боев на арене, обладает внушительными физическими данными, 
/// которые позволяют не только показывать невероятную стойкость, но и ужасающий урон на ближней дистанции
/// Вооружен трезубцем и сетью, что не только позволяет наносить огромный урон на близкой дистанции, но и догонять тех,
/// кто попытается улизнуть от него
class Gladiator :Character
{
public:
	int NetDistance;
	int NetStun;
	Gladiator(int x, int y)
	{
		position.x = x, position.y = y;
		maxHp = 34;
		Hp = 34;
		maxMove = 3;
		firstDamage = 4;
		firstRange = 2;
		secondDamage = 4;
		secondRange = 2;
		CoolDown = 3;
		CoolDownTimer = 0;
		NetDistance = 9;
		NetStun = 2;
		Stunned = 0;
	}
	void SkillUse(Character& sec)
	{
		CoolDownTimer = CoolDown;
		if ((abs(position.x - sec.position.x) + abs(position.y - sec.position.y)) <= NetDistance)
		{
			sec.Stunned += 2;
		}
	}
};

/// Волшебник обладает шлубокими познаниями в магии, а также огромным арсеналом заклинаний
/// Как жаль, что на арене большую их часть использовать не выйдет
/// Обладает способностью магической ловушки
/// Любой, кто находится в зоне действия магической ловушки будет получать вдвое больше урона
class Wizard :Character
{
public:
	Point SkillPosition;
	int SkillRange;
	Wizard(int x, int y)
	{
		position.x = x, position.y = y;
		maxHp = 18;
		Hp = 18;
		maxMove = 3;
		firstDamage = 2;
		firstRange = 4;
		secondDamage = 1;
		secondRange = 7;
		CoolDown = 3;
		CoolDownTimer = 0;
		SkillPosition.x = 0, SkillPosition.y = 0;
		Stunned = 0;
		SkillRange = 2;
	}
	void SkillUse(Character& sec)
	{
		CoolDownTimer = CoolDown;
		SkillPosition.x = position.x;
		SkillPosition.y = position.y;
	}
};