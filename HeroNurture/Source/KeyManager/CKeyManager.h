#pragma once
#include <vector>
#include "Singleton\CSingleton.h"
using namespace std;

//=====================================
// �L�[���̓}�l�[�W���[�N���X
// �����:�Γc�D��
//=====================================

class CKeyManager
	: public CSingleton<CKeyManager>
{
private:
	friend class CSingleton<CKeyManager>;
	~CKeyManager();

public:
	//�X�V����
	void Update();

	//�L�[�������ꂽ�Ƃ�
	bool IsUp(int input);
	//�L�[�������ꂽ�Ƃ�
	bool IsDown(int input);
	//�L�[�������������Ă���Ƃ�
	bool IsKeep(int input);

	bool KeyCore(int input,vector<int> keymax);

private:
	//������A�N�Z�X����邱�Ƃ��Ȃ��悤��
	CKeyManager();
private:
	//�ߋ��ɉ�����Ă����L�[���i�[����z��
	vector<int> m_OldKeys;
	//���݉�����Ă���L�[���i�[����z��
	vector<int> m_NowKeys;
};

