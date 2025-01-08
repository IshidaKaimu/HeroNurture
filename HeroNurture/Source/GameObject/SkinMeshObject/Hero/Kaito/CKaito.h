#pragma once
#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"

//=====================================
//�J�C�g�N���X
//����ҁF�Γc�D��
//=====================================

class CKaito
	:public CHeroBase
{
public:
	CKaito();
	virtual ~CKaito() override;


	//�������֐�
	void Initialize() override;

	//�f�[�^�ǂݍ��݊֐�
	void LoadMeshData() override;

	//�p�����[�^���ǂݍ���
	void LoadParamData(const json& jsondata) override;

	//�o�g���p�����[�^���ǂݍ���
	void LoadBattleParamData(const json& jsondata) override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw() override;

	// =======================
	// �e�V�[�����Ƃ̃A�j���[�V����
	// =======================
	//�琬�q�[���[�I���V�[��
	virtual void NatureHeroSelectAnimation() override;
	//�o�g���q�[���[�I���V�[��
	virtual void BattleHeroSelectAnimation() override;
	// �琬�V�[��		
	void NatureAnimation(int no) override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//��ʐ؂�ւ�
	bool SceneChange();

	//�A�j���[�V�����؂�ւ��t���O���Ă�
	void AnimChange();

protected:
	D3DXVECTOR3    m_BonePos;			//�J�C�g:�{�[�����W
	bool           m_Run;				//����o���t���O
	bool           m_AnimChange;		//�A�j���[�V�����؂�ւ��t���O
	float          m_EffPosZ;			//�G�t�F�N�g��Z���ʒu

};

