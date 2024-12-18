#pragma once
#include "Singleton\CSingleton.h"
#include "UIObject\CUIObject.h"
#include "WriteText\WriteText.h"

//�����N�\����
enum enRankList : char 
{
	S,
	A,
	B,
	C,
	D,
	E
};

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

	//�����N�̕\��
	void DrawRank(float value, int typeno, float x, float y);

private:
	CUtility();

private:
	//�����N�񋓌^
	enRankList m_Rank;
};

