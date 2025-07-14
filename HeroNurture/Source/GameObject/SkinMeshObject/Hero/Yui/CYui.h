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
//--------------------------

// =======================


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
	//T��
	constexpr int CHANGE_TSHARP  = 60;	//�A�j���[�V�������Đ�����^�C�~���O
	constexpr int PLAY_TSHARP_SE = 60;	//T���̍ۂ�SE���Đ�����^�C�~���O
	//��]
	constexpr float ROTATE_ADDSPEED          = 0.05f;  //�����x
	constexpr float ROTATE_ADDSPEED_MAX      = 8.0f;   //�ő呬�x
	constexpr int   ROTATE_ADDSPEED_INTERVAL = 30;  //��������Ԋu
	//�����̕ύX�^�C�~���O
	constexpr int	MOVECHANGE_FASTTIME    = 80;   //1�i�K��
	constexpr int	MOVECHANGE_SECONDTIME  = 120;  //2�i�K��
	constexpr int	MOVECHANGE_THIRDTIME   = 150;  //3�i�K��
	constexpr int	MOVECHANGE_FOURTHTIME  = 240;  //4�i�K��
	//�������x
	constexpr float MOVESPEED_BACK = 0.1f; //�����鎞
	constexpr float MOVESPEED_RUSH = 0.2f; //�ːi���鎞
	//�X����Ƃ��̑��x
	constexpr float TILT_BACK_SPEED    = 0.005f; //���
	constexpr float TILT_FORWARD_SPEED = 0.01f;  //�O
	//�X����ő�l
	constexpr float TILT_BACK_MAX      = 0.5f;   //���
	constexpr float TILT_FORWARD_MAX   = 0.35f;  //�O
	//-------------

	//----�U��1----
	//�A�j���[�V�����I���^�C�~���O
	constexpr int FASTATTACK_ANIM_END = 300;
	//--------------
    
	//----�U��2----
	//�A�j���[�V�����I���^�C�~���O
	constexpr int SECONDATTACK_ANIM_END = 200;
	//-------------
	
	//----�G�t�F�N�g----
	//��]�Ɏg�������G�t�F�N�g
	const D3DXVECTOR3 TORNADE_POS      = { 0.3f, 0.3f, 0.3f };  //���W
	const D3DXVECTOR3 TORNADE_SCALE    = { 0.3f, 0.3f, 0.3f };  //�g�k
	constexpr int     TORNADE_PLAY     = 60;					//�Đ��^�C�~���O
	///�U���Ɏg�������G�t�F�N�g
	const D3DXVECTOR3 ATTACKTORNADE_SCALE    = { 0.5f, 0.5f, 0.5f }; //�g�k
	constexpr float   ATTACKTORNADE_ROTATE_Y = 90.0f;				 //�����ɂ���ĕς��Y���̉�]�l
	constexpr int     ATTACKTORNADE_PLAY     = 60;					 //�Đ��^�C�~���O
	//------------------
}
// =======================

//=====================================
//�@���C�N���X
//�@����ҁF�Γc�D��
//=====================================
class CYui
	:public CHeroBase
{
public:
	CYui();
    ~CYui();
private:

	//==================w
    //�\����
    //==================

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

	// =======================


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


	// =======================
	// �U���֐�
	// =======================
	
	//�U��1
	float PowerAttack() override { return CHeroBase::PowerAttack(); }
	//�U��2
	float MagicAttack() override { return CHeroBase::MagicAttack(); };

	// =======================

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
	//--------------------

	//========================

private:
	//----�A�j���[�V�����֘A----
	//�A�j���[�V�����Ɋւ��鏉����
	void AnimInit();
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }
	//�A�j���[�V�����؂�ւ��֐�
	void AnimChange(int animno) override;
	//-------------------------

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

