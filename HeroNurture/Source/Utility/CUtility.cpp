#include "CUtility.h"
#include <random>

CUtility::CUtility()
{
}

CUtility::~CUtility()
{
}

//��������
int CUtility::GenerateRandomValue(int min, int max)
{
    //�V�[�h�l
    std::random_device rd;
    //����������
    std::mt19937 gen(rd());
    //���z�ɗ����������n�����Ƃŗ����͈̔͂��w��
    std::uniform_int_distribution<int> rand_val(min, max);
    return rand_val(gen);
}
