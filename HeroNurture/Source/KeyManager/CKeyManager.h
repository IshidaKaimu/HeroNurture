#pragma once
#include <vector>
using namespace std;

class CKeyManager
{
public:
	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
	static CKeyManager* GetInstance()
	{
		//�B��̃C���X�^���X����.
		static CKeyManager s_Instance;
		return &s_Instance;
	}

	~CKeyManager();

	void Update();

	//�L�[�������ꂽ�Ƃ�
	bool IsUp(int input);
	//�L�[�������ꂽ�Ƃ�
	bool IsDown(int input);
	//�L�[�������������Ă���Ƃ�
	bool IsKeep(int input);

	bool KeyCore(int input,vector<int> keymax);

private:
	CKeyManager();
	CKeyManager(const CKeyManager& rhs) = delete;
	CKeyManager& operator = (const CKeyManager& rhs) = delete;

private:
	//�ߋ��ɉ�����Ă����L�[���i�[����z��
	vector<int> m_OldKeys;
	//���݉�����Ă���L�[���i�[����z��
	vector<int> m_NowKeys;
};

