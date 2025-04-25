#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"

// =======================
// �萔�錾
// =======================
namespace Constant_RaccoonDog 
{
	//�����ݒ�
	const D3DXVECTOR3 INIT_POS    = { 0.0f, 4.5f, 30.0f };	//���W
	const D3DXVECTOR3 INIT_SCALE  = { 0.04f, 0.04f, 0.04f };//�g�k
	const D3DXVECTOR3 INIT_ROTATE = { D3DXToRadian(-110.0f), D3DXToRadian(90.0f), D3DXToRadian(-2.0f) };//��]
	//�A�j���[�V�����֘A
	constexpr float MOVE_SPEED = 0.4f; //�ړ����x
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

private:

};

