#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
// =======================
// �O���錾
// =======================
//�G�t�F�N�g
class CEffect;

// =======================
// �萔�錾
// =======================
namespace Constant_RaccoonDog 
{
	//----�����ݒ�----
	const D3DXVECTOR3 INIT_POS       = { 0.0f, 4.5f, 30.0f };	//���W
	const D3DXVECTOR3 INIT_SCALE     = { 0.04f, 0.04f, 0.04f }; //�g�k
	const D3DXVECTOR3 INIT_ROTATE    = { D3DXToRadian(-110.0f), D3DXToRadian(90.0f), D3DXToRadian(-2.0f) };//��]
	const D3DXVECTOR3 UPRIGHT_ROTATE = { D3DXToRadian(-100.0f), D3DXToRadian(90.0f), D3DXToRadian(-2.0f) };//�������̉�]
	//----�A�j���[�V�����֘A----
	//�^�k�L
	constexpr float MOVE_SPEED = 0.2f; //�ړ����x
	constexpr float MAX_UP     = 5.0f; //�㉺�̓����̍������
	constexpr float UP_SPEED   = 0.04f;//�㉺�̓����̑���
	constexpr int   HIDDEN_TIME= 190;  //��\���ɂ���^�C�~���O
	//���G�t�F�N�g
	constexpr int   STEAM_TIME = 120;  //�Đ��܂ł̎���
	constexpr float STEAM_DELAY= 5.0f; //�^�k�L���炸�炷�l
}


class CRaccoonDog
	: public CHeroBase
{
public:
	CRaccoonDog();
	~CRaccoonDog();
	
	//������
	void Initialize() ;

	//�q�[���[�o��V�[���ł̃A�j���[�V����
	void AppearanceAnim(float camz);

	//�`��֐�
	void Draw() override;
public:
	//�^�k�L����\���ɂȂ����t���O�̎擾
	bool GetHiddenFlag() { return m_HiddenFlag; }

private:
	//�㉺�̓���
	void UpDown();

private:
	//----�t���O----
	//�^�k�L���J�����ɓ��B������
	bool m_ReachCamFlag;
	//��\��
	bool m_HiddenFlag;
	//�̂��㉺�����铮��
	bool m_Up;
};

