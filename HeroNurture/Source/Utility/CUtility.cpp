#include "CUtility.h"
#include <random>

CUtility::CUtility()
{
}

CUtility::~CUtility()
{
}

//乱数生成
int CUtility::GenerateRandomValue(int min, int max)
{
    //シード値
    std::random_device rd;
    //乱数生成器
    std::mt19937 gen(rd());
    //分布に乱数生成器を渡すことで乱数の範囲を指定
    std::uniform_int_distribution<int> rand_val(min, max);
    return rand_val(gen);
}
