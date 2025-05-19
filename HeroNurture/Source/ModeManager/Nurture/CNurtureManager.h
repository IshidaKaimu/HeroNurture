#pragma once
#include "Singleton\CSingleton.h"
#include "Utility\CUtility.h"

// =======================
// �萔�錾
// =======================
//�琬�^�[����
constexpr int MAX_TURN = 50;


//=====================================
//�琬���[�h�}�l�[�W���[�N���X
//����ҁF�Γc�D��
//=====================================
class CNurtureManager
	: public CSingleton<CNurtureManager>
{
private:
	//�t�����h�錾
	//�A�N�Z�X����^����
	friend class CSingleton<CNurtureManager>;
	~CNurtureManager();
public:

private:
	CNurtureManager();
public:

	//�ǂݍ��݉񐔐����t���O�̑���
	void SetIsDataLoaded(bool loaded) { m_IsDataLoaded = loaded; }

	//----�琬�o�߃^�[���֘A�֐�----
	//�^�[�����̌o��
	void TurnProgress() { m_Turn--; }
	//�^�[�����̏�����
	void InitTurn() { m_Turn = MAX_TURN; }

	//�X�^�~�i�Q�[�W�̕��̏�����
	void InitStaminaWidth() { m_GageWidth = 1.0f; }

	//----�Q�b�^�[�E�Z�b�^�[----
	//�ǂݍ��݉񐔐����t���O
	bool GetIsDataLoaded() { return m_IsDataLoaded; }
	//�^�[����
	int GetRemainingTurn() { return m_Turn; }
	//�X�^�~�i�Q�[�W�̕�
	float GetStaminaWidth() { return m_GageWidth; }
	void  SetStaminaWidth(float width) { m_GageWidth = width; }
	//�x���t���O
	bool GetRestFlag() { return m_Rest; }
	void SetRestFlag(bool rest) { m_Rest = rest; }

private:
	//�c��^�[����
	int         m_Turn;

	//�X�^�~�i�Q�[�W�̕�
	float m_GageWidth;

	//----�t���O----
	//�x����I���������̃t���O
	bool m_Rest;
	//�f�[�^�ǂݍ��݂����񂩂ǂ����̃t���O
	bool m_IsDataLoaded;
};
