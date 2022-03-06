#pragma once

struct Point
{
	int x;
	int y;
};

class Character
{
    public:
		Point position; //�������
		int maxHp, //������������ ��������
			Hp, //������� ��������
			maxMove, //������������ ��������� �� ���
			firstDamage, //���� � ������� �����
			firstRange, //��������� �������� �����
			secondDamage, //���� � ������� ����� 
			secondRange, //������� ����
			CoolDown, //����������� �����������
			CoolDownTimer, //������ �� ������������� �����������
			Stunned; //������������ �������� ���������
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

/// ����� ������ �������� ���, ���� - ����, ����������� ������ ���������� �� ���������� 7 ������, ������� ��� �� ���
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

/// ���, ������� ���, �������� ������� ������ �� ���������, �� � ������ ��� ����� ��� �������. 
/// � ���� ��������, ������� ��������������� � ��������� �����
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

/// �������, ���������� ���������, ��� ������ �������� ������� ������� �� ���������.
/// ������ ����������� �������� ��� ������ ��������
/// ����� ��������� � ���� ������ �� �����������
/// ���������, ����������� ��� � ������� ���������� � ��� �� 2 ����, ������� �������������, ��������� �� ����� ��� ���.
/// � ���� �������� � �������, ������� ����� �� ������ ��������� ������ ������ ������������,
///���� ���� ������ ���� �����������
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
		//capRange = 1; ���� ��������� ��� ����
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

/// ���������, ���������� � ������� ���� �� �����, �������� ������������� ����������� �������, 
/// ������� ��������� �� ������ ���������� ����������� ���������, �� � ��������� ���� �� ������� ���������
/// �������� ��������� � �����, ��� �� ������ ��������� �������� �������� ���� �� ������� ���������, �� � �������� ���,
/// ��� ���������� �������� �� ����
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

/// ��������� �������� ��������� ���������� � �����, � ����� �������� ��������� ����������
/// ��� ����, ��� �� ����� ������� �� ����� ������������ �� ������
/// �������� ������������ ���������� �������
/// �����, ��� ��������� � ���� �������� ���������� ������� ����� �������� ����� ������ �����
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