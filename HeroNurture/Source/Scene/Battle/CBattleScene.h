#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json\CJson.h"
#include "Utility\CUtility.h"

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

//=====================================
// �O���錾
//=====================================
//----�}�l�[�W���[�N���X----
//�V�[��
class CSceneManager;
//�o�g�����[�h
class CBattleManager;
//UI
class CUIManager;
//�X�L�����b�V��
class CSkinMeshManager;
//�T�E���h
class CSoundManager;
//ImGui
class ImGuiManager;
//�J����
class CCameraManager;
//�q�[���[
class CHeroManager;
//�G�̃q�[���[
class CEnemyHeroManager;
//�L�[����
class CKeyManager;
//�G�t�F�N�g
class CEffect;

//=====================================
// �萔�錾
//=====================================
namespace Constant_BattleScene 
{
	//----�J�������----
	const D3DXVECTOR3 INIT_CAMPOS	= { -1.0f,2.0f,-7.0f };		//�������W
	const D3DXVECTOR3 INIT_CAMLOOK  = { -1.0f,2.0f,0.0f };		//���������_
	const D3DXVECTOR3 ATTACK_CAMPOS = { -1.0f,2.0f,0.0f };		//�U�������W(����)
	const D3DXVECTOR3 ATTACK_CAMLOOK	   = { -2.0f,2.0f,0.0f }; //�U���������_(����)
	const D3DXVECTOR3 ENEMY_ATTACK_CAMPOS  = { -1.0f,2.0f,0.0f }; //�U�������W(�G)
	const D3DXVECTOR3 ENEMY_ATTACK_CAMLOOK = { 2.0f,2.0f,0.0f };  //�U���������_(�G)
	//----�Q�[�W���----
	//HP
	const D3DXVECTOR3 HPGAGE_POS = { 0.0f, 16.0f, 0.0f }; //���W
	const D3DXVECTOR3 HPGAGE_SCALE = { 0.8f, 0.8f, 0.8f };//�g�k
	const D3DXVECTOR2 HPGAGE_DISPLAY = { 1.0f, 1.0f };	  //��
	//HP�̘g
	const D3DXVECTOR3 HPFRAME_POS = { 0.0f, 10.0f, 0.0f };
	//�G��HP
	const D3DXVECTOR3 ENEMY_HPGAGE_POS  = { 800.0f, 16.0f, 0.0f };  //���W
	//�G��HP�̘g
	const D3DXVECTOR3 ENEMY_HPFRAME_POS = { 800.0f, 10.0f, 0.0f }; //���W
	//----�s���I��----
	//�͍ؗU���A�C�R��
	const D3DXVECTOR3 POWER_ATTACK_POS = { 420.0f, 540.0f, 0.0f }; //���W
	//���@�U���A�C�R��
	const D3DXVECTOR3 MAGIC_ATTACK_POS = { 620.0f, 540.0f, 0.0f }; //���W
	//����
	const D3DXVECTOR3 ATTACK_SCALE = { 0.5f, 0.5f, 0.5f };	//�g�k
	const D3DXVECTOR2 ATTACK_DISP  = { 1.0f, 1.0f };		//��
	const float ATTACK_ALPHA = 1.0f;
	//�U���A�C�R���ɔ킹��摜
	constexpr float ATTACK_COVER_ALPHA = 0.8f;
	//----�^�[����----
	const D3DXVECTOR2 HERO_TURNTEXT_POS  = { 450.0f, 50.0f };	//���W(����)
	const D3DXVECTOR2 ENEMY_TURNTEXT_POS = { 340.0f, 50.0f };	//���W(�G)
}

//=====================================
// �o�g���V�[���N���X
// �����:�Γc�D��
//=====================================
class CBattleScene
	:public CSceneBase
{
private:
	//�U���̎��
	enum enAttackList :char
	{
		PowerAttack,
		MagicAttack,
		Max,
	};

	//�o�g���̃t�F�[�Y
	enum enBattlePhase
	{
		MoveSelectPhase, //�U���̑I��������t�F�[�Y
		AttackPhase,	 //���݂��ɍU������t�F�[�Y
		SetUpPhase,		 //���̃^�[���̏���������t�F�[�Y
	};

public:
	CBattleScene();
	~CBattleScene();

	//�\�z�֐�
	void Create()	  override;
	//�j���֐�
	void Releace()	  override;
	//�f�[�^�ݒ�֐�
	void LoadData()	  override;
	//�������֐�
	void Initialize() override;
	//�X�V�֐�
	void Update()     override;
	//�`��֐�
	void Draw()		  override;

	//�f�o�b�O����
	void Debug();

private:
	//�o�g���Ɏg�p����f�[�^�̓ǂݍ���
	void LoadBattleData();

	//�U���A�C�R���̕`��
	void DrawAttack(std::unique_ptr<CUIObject>& icon,D3DXVECTOR3 pos,float alpha);

	//----�̗̓Q�[�W�֘A----
	//���ꂼ��̗̑̓Q�[�W�̕`��
	void DrawHpGage();
	//�̗̓Q�[�W/�w�i�̏����ݒ�
	void InitHpGage();
	//�̗̓Q�[�W�̃A�j���[�V����
	void HpGageAnim(std::unique_ptr<CUIObject>& gage, float hp, float maxhp, float& width);

	//�s���I���t�F�[�Y���̏���
	void MoveSelect();
	//�U���t�F�[�Y���̏���
	void Attack();
	//���̃^�[���������̏���
	void SetUpToNextTurn();

	//----���ꂼ��̃^�[���ɍs������----
	//����
	void HeroTurn();     //�s������
	void DrawHeroTurn(); //UI���`�揈��
	//�G
	void EnemyHeroTurn();     //�s������
	void DrawEnemyHeroTurn(); //UI���`�揈��

	//�^�[�����Ƃ̍U���̐ݒ�
	void SettingAttack(int no , enAttackList& attacklist);

private:
	//�������g���q�[���[
	CHeroManager* m_pHero;
	//�G�̃q�[���[
	CEnemyHeroManager* m_pEnemyHero;

	//�J�����}�l�[�W���[
	CCameraManager* m_pCamera;

	// =======================
	// �I�u�W�F�N�g�N���X
	// =======================		
	//----�X�^�e�B�b�N���b�V��----
	//�n��
	std::unique_ptr<CGround> m_pGround;
	//��
	std::unique_ptr<CSky> m_pSky;
	//----UI----
	//�����̗̑̓Q�[�W
	std::unique_ptr<CUIObject> m_pHpGage;	   //�Q�[�W
	std::unique_ptr<CUIObject> m_pHpGageBack;  //�w�i
	std::unique_ptr<CUIObject> m_pHpGageFrame; //�g
	//�G�̗̑̓Q�[�W
	std::unique_ptr<CUIObject> m_pEnemyHpGage;	  //�Q�[�W
	std::unique_ptr<CUIObject> m_pEnemyHpGageBack;//�w�i
	std::unique_ptr<CUIObject> m_pEnemyHpGageFrame;//�g
	//�͍ؗU���A�C�R��
	std::unique_ptr<CUIObject> m_pPowerAttack;
	//���͍U���A�C�R��
	std::unique_ptr<CUIObject> m_pMagicAttack;
	//�I������Ă��Ȃ��U���A�C�R���ɂ��Ԃ���摜
	std::unique_ptr<CUIObject> m_pAttackCover;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//�o�g���Ɏg�p����p�����[�^�̃f�[�^
	json m_BattleData;
	//�G�̃p�����[�^�̃f�[�^
	json m_EnemyHeroData;

	//�̗̓Q�[�W�̕ϓ����镝
	float m_HpWidth;    //����
	float m_EnemyHpWidth;//�G

	//�o�߃^�[����
	int m_BattleTurn;

	//�^�[���̏������߂�t���O
	bool m_IsHeroTurn;

	//���݂ǂ���̃^�[�����𔻒f����t���O
	bool m_CurrentTurn;

	//�s����I���ς݂ł��邩�̔��f
	bool m_SelectAttack;

	//�������I������U���̃��X�g
	enAttackList m_Attack;

	//�G�̍s�������߂�ԍ�
	int m_EnemyAttackNo;

	//�G�̑I������U���̃��X�g
	enAttackList m_EnemyAttack;

	//�o�g���̃t�F�[�Y
	enBattlePhase m_BattlePhase;

};