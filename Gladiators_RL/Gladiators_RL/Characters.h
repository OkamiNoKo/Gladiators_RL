#pragma once

struct Point
{
	int x;
	int y;
};

class Character
{
    public:
		Point position; //позици€
		int maxHp, //максимальное здоровье
			Hp, //текущее здоровье
			maxMove, //максимальна€ дистанци€ за ход
			firstDamage, //урон в ближнем круге
			firstRange, //дистанци€ ближнего круга
			secondDamage, //урон в дальнем круге 
			secondRange, //дальний круг
			CoolDown, //перезар€дка способности
			CoolDownTimer, //“аймер до использовани€ способности
			Stunned; //ƒлительность текущего оглушени€
};

/// ѕират оружие ближнего бо€, скил - крюк, подт€гивает любого противника на рассто€нии 7 клеток, оглуша€ его на ход
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
};

/// ћаг, верткий тип, обладает опасной магией на дистанции, ну а вблизи его маги€ еще опаснее. 
/// ћожет телепортироватьс€ на небольшие рассто€ни€
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
};

/// –энджер, непри€тный противник, его меткие выстрелы гораздо опаснее на дистанции.
/// ƒержит противников подальше при помощи капканов
///  огда наступает в свой капкан не срабатывает
/// ѕротивник, закончивший ход в капкане застревают в нем на 2 хода, капканы замаскированы, противник не знает где они.
class Ranger :Character
{
public:
	Point Capcan1;
	Point Capcan2;
	Point Capcan3;
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
		Capcan1.x = -1, Capcan1.y = -1;
		Capcan2.x = -1, Capcan2.y = -1;
		Capcan3.x = -1, Capcan3.y = -1;
		capNum = 0;
		capRange = 3;
		Stunned = 0;
	}
};

/// √ладиатор, закаленный в тыс€чах боев на арене, обладает внушительными физическими данными, 
/// которые позвол€ют не только показывать неверо€тную стойкость, но и ужасающий урон на ближней дистанции
/// ¬ооружен трезубцем и сетью, что не только позвол€ет наносить огромный урон на близкой дистанции, но и догон€ть тех,
/// кто попытаетс€ улизнуть от него
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
};

/// ¬олшебник обладает шлубокими познани€ми в магии, а также огромным арсеналом заклинаний
///  ак жаль, что на арене большую их часть использовать не выйдет
/// ќбладает способностью магической ловушки
/// Ћюбой, кто находитс€ в зоне действи€ магической ловушки будет получать вдвое больше урона
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
};