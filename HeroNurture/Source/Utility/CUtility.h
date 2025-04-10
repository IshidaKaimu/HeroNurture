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
//�ėp�N���X
//����ҁF�Γc�D��
//=====================================
class CUtility
	: public CSingleton<CUtility>
{
private:
	//�A�N�Z�X����^����
	friend class CSingleton<CUtility>;
	~CUtility();
public:

	//�����̐���
	//�e���v���[�g�֐�(�����̕��ɉ����ď�����ς���)
	template <typename T>
	static T GenerateRandomValue(T min, T max) 
	{
		//�V�[�h�l
		std::random_device rd;
		//����������
		std::mt19937 gen(rd());

		//�����������^�ł������ꍇ
		if constexpr (std::is_integral<T>::value) {
			//���z�ɗ����������n�����Ƃŗ����͈̔͂��w��
			std::uniform_int_distribution<T> rand_val(min, max);
			return rand_val(gen);
		}
		else if constexpr (std::is_floating_point<T>::value)
		{
			//���z�ɗ����������n�����Ƃŗ����͈̔͂��w��
			std::uniform_real_distribution<T> rand_val(min, max);
			return rand_val(gen);
		}

	}

	//�����N�̕\��
	void DrawRank(float value, int typeno, float x, float y);

	//�l�̌����ɂ��`��ʒu�̕␳
	D3DXVECTOR2 PosCorrection(double value, float digit, float x, float y);

private:
	CUtility();

private:
	//�����N�񋓌^
	enRankList m_Rank;
};
