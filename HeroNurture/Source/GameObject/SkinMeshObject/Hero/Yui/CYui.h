#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Utility\CUtility.h"

// =======================
// �O���錾
// =======================
//----�}�l�[�W���[�N���X----
//�V�[��
class CSceneManager; 
//�琬���[�h
class CNurtureManager;
//�T�E���h
class CSoundManager;
//�G�t�F�N�g
class CEffect;

// =======================
// �萔�錾
// =======================
namespace Constant_Yui 
{
	//----�o�g���J�n���o��V�[��----
	const D3DXVECTOR3 APPEALANCE_POS     = { 0.0f, 1.0f, -5.0f }; //�������W
	const float       APPEALANCE_SPEED   =  0.05f;				  //�ړ����x
	const float       APPEALANCE_GOAL_Z  =  -13.0f;				  //�Ō�ɒ�~������W��Z�l
	//------------------------------
	
	//----�o�g���V�[��----
	const D3DXVECTOR3 BATTLE_SCALE   = { 0.04f,0.04f,0.04f }; //�g�k
	//--------------------

	//----�U��1-----
	//T���ɕύX����^�C�~���O
	constexpr int CHANGE_TSHARP = 60;
	//��]���x�̉����^�C�~���O
	constexpr int ROTATE_ADDSPEED_FAST    = 80;	 //1�i�K��
	constexpr int ROTATE_ADDSPEED_SECOND  = 120; //2�i�K��
	constexpr int ROTATE_ADDSPEED_THIRD   = 150; //3�i�K��
	constexpr int ROTATE_ADDSPEED_FOURTH  = 240; //4�i�K��
	//�A�j���[�V�����I���^�C�~���O
	constexpr int FASTATTACK_ANIM_END     = 300;
	//--------------
    
	//----�U��2----
	//�A�j���[�V�����I���^�C�~���O
	constexpr int SECONDATTACK_ANIM_END = 300;
	//-------------
	
	//----�G�t�F�N�g----
	//�����G�t�F�N�g
	const D3DXVECTOR3 TORNADE_POS      = { 0.3f, 0.3f, 0.3f };  //���W
	const D3DXVECTOR3 TORNADE_SCALE    = { 0.3f, 0.3f, 0.3f };  //�g�k
	//�΂̋ʃG�t�F�N�g
	const D3DXVECTOR3 FIREBALL_SCALE    = { 0.3f, 0.3f, 0.3f }; //�g�k
	constexpr float   FIREBALL_ROTATE_Y = 90.0f;				//�����ɂ���ĕς��Y���̉�]�l
	//------------------
}

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
private:

	//�A�j���[�V�����ԍ�
	enum Anim_No 
	{
		Jump,	//�W�����v
		Run,	//����
		Walk,	//����
		Wait,	//�ҋ@
		TSharp  //T��
	};

public:

	// =======================
	// �e�V�[�����Ƃ̏�����
	// =======================
	//��Ɏg�p���鏉����
	void Initialize() override;
	//�o�g���V�[���Ŏg�p���鏉����
	void BattleInitialize() override;
	//�G�ɂȂ����ۂ̏������֐�
    void EnemyInitialize()  override;
	//�o��V�[���̏�����
	void AppearanceInitialize() override;

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
	//�o�g���J�n���o��V�[��
	void AppearanceAnimation() override;
	//�琬�V�[��		
	void NurtureAnimation(int no) override;


	// =======================
	// �U���֐�
	// =======================
	//�U��1
	float PowerAttack() override;
	//�U��2
	float MagicAttack() override;


	// =======================
	// �e�o�g���t�F�[�Y�ł̃A�j���[�V����
	// =======================
	// �s���I�𒆂̃A�j���[�V����
	void MoveSelectAnim() override;
	//----�U���t�F�[�Y----
	//�U��1���̃A�j���[�V����
	void PowerAttackAnim(float vector) override;
	//�U��2���̃A�j���[�V����
	void MagicAttackAnim(float vector) override;
	//�_���[�W���̃A�j���[�V����
	void DamageAnim(float vector) override;

private:
	//----�A�j���[�V�����֘A----
	//�A�j���[�V�����Ɋւ��鏉����
	void AnimInit();
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }
	//�A�j���[�V�����؂�ւ��֐�
	void AnimChange(int animno) override;

private:
	//�ϓ������]��
	float m_MoveRotateY; //Y��
	float m_MoveRotateZ; //Z��

	//Y����]�̑���
	float m_RotateSpeedY;

	//�A�j���[�V�����؂�ւ��t���O
	bool  m_AnimChange;	 

	//�_���[�WSE�����p�J�E���g
	int m_DamageSECnt;
};

