#pragma once
#include "Singleton\CSingleton.h"
#include "UIObject\CUIObject.h"
#include "WriteText\WriteText.h"

//�����N���X�g
enum enRankList : char 
{
	S,	//S�����N
	A,	//A�����N
	B,	//B�����N
	C,	//C�����N
	D,  //D�����N
	E   //E�����N
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

