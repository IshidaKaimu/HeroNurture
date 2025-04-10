#pragma once
#include "Singleton\CSingleton.h"
#include "UIObject\CUIObject.h"
#include "WriteText\WriteText.h"
#include "Json\CJson.h"
#include <random>
#include <type_traits>

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
//�琬�����N�N���X
//����ҁF�Γc�D��
//=====================================
class CRank
	: public CSingleton<CRank>
{
private:
	//�A�N�Z�X����^����
	friend class CSingleton<CRank>;
	~CRank();
public:
	//�����N�̕\��
	void DrawRank(float value, int typeno, float x, float y);

private:
	CRank();

private:
	//�����N�񋓌^
	enRankList m_Rank;
};
