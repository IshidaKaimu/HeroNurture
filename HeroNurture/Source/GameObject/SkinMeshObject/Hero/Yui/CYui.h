#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Utility\CUtility.h"

// =======================
// �O���錾
// =======================
class CSceneManager;

// =======================
// �萔�錾
// =======================
//�o�g���V�[���ł̏������
const D3DXVECTOR3 BATTLEINIT_POS_YUI = { -4.0f,0.0f,0.0f };		//���W
const D3DXVECTOR3 BATTLEINIT_SCALE_YUI = { 0.04f,0.04f,0.04f }; //�g�k
const D3DXVECTOR3 BATTLEINIT_ROTATE_YUI = { 0.04f,D3DXToRadian(-90.0f),0.04f }; //��]
//�G�ɂȂ����ۂ̏������
const D3DXVECTOR3 ENEMYINIT_POS_YUI    = { 2.0f,0.0f,0.0f };
const D3DXVECTOR3 ENEMYINIT_ROTATE_YUI = { 0.0f,D3DXToRadian(90.0f),0.0f };

//=====================================
//���C�N���X
//����ҁF�Γc�D��
//=====================================
class CYui
	:public CHeroBase
{
public:
	CYui();
    ~CYui();

	// =======================
	// �e�V�[�����Ƃ̏�����
	// =======================
	//��Ɏg�p���鏉����
	void Initialize() override;
	//�o�g���V�[���Ŏg�p���鏉����
	void BattleInitialize() override;
	//�G�ɂȂ����ۂ̏������֐�
    void EnemyInit()  override;

	//�f�[�^�ǂݍ��݊֐�
	void LoadMeshData() override;

	//�p�����[�^���ǂݍ���
    void LoadParamData(const json& jsondata) override;

	//�o�g���p�����[�^���ǂݍ���
	void SetBattleParamData(const json& jsondata) override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw() override;

	//�f�o�b�O�֐�
	void Debug() override;

public:
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
	// �U���֐�
	// =======================
	//�U��1
	float PowerAttack() override;
	//�U��2
	float MagicAttack() override;
	//�ŗL�U��
	float UniqueAttack() override;

private:
	//�A�j���[�V�����Ɋւ��鏉����
	void AnimInit();

	//�A�j���[�V�����X�s�[�h�̐ݒ�
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//�A�j���[�V�����؂�ւ��t���O���Ă�
	void AnimChange();

protected:
	bool           m_AnimChange;		//�A�j���[�V�����؂�ւ��t���O

};

