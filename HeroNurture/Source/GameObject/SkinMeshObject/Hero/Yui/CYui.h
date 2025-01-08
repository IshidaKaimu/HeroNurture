#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"

//----�O���錾----
class CSceneManager;

//=====================================
//���C�N���X
//����ҁF�Γc�D��
//=====================================
class CYui
	:public CHeroBase
{
public:
	CYui();
	virtual ~CYui()	override;

	//�������֐�
	void Initialize() override;

	//�f�[�^�ǂݍ��݊֐�
	void LoadMeshData() override;

	//�p�����[�^���ǂݍ���
    void LoadParamData(const json& jsondata) override;

	//�o�g���p�����[�^���ǂݍ���
	void LoadBattleParamData() override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw() override;

	// =======================
	// �e�V�[�����Ƃ̃A�j���[�V����
	// =======================
	//�琬�q�[���[�I���V�[�� 
	void NatureHeroSelectAnimation() override;
	//�o�g���q�[���[�I���V�[��
	void BattleHeroSelectAnimation() override;
	// �琬�V�[��		
	void NatureAnimation(int no) override;
	// =======================
	// �g���[�j���O���Ƃ̃A�j���[�V�����֐�
	// =======================		
	//�ؗ�
	void PowerTraningAnimation() override;
	//����
	void MagicTraningAnimation() override;
	//�̗�
	void SpeedTraningAnimation()override;
	//Hp
	void HpTraningAnimation()override;



private:
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//�A�j���[�V�����؂�ւ��t���O���Ă�
	void AnimChange();

protected:
	bool           m_AnimChange;		//�A�j���[�V�����؂�ւ��t���O

};

