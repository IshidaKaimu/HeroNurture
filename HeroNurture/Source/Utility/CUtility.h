#pragma once
#include "Singleton\CSingleton.h"

//=====================================
//�ėp�N���X
//����ҁF�Γc�D��
//=====================================
class CUtility
	: public CSingleton<CUtility>
{
public:
	//�A�N�Z�X����^����
    friend class CSingleton<CUtility>;
	~CUtility();

	//�����̐���
	static int GenerateRandomValue(int min,int max);

private:
	CUtility();

};

