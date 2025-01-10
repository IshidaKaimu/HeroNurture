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

//=====================================
// �萔�錾(_B = �o�g���V�[���ŗp���邱�Ƃ�����)
//=====================================
//----�J�������----
const D3DXVECTOR3 INIT_CAMPOS_B  = { -1.0f,2.0f,-6.0f }; //�������W
const D3DXVECTOR3 INIT_CAMLOOK_B = { -1.0f,2.0f,-0.0f }; //���������_
//----�Q�[�W���----
//HP
const D3DXVECTOR3 HPGAGE_POS     = { 0.0f, 16.0f, 0.0f }; //���W
const D3DXVECTOR3 HPGAGE_SCALE   = { 0.8f, 0.8f, 0.8f };  //�g�k
const D3DXVECTOR2 HPGAGE_DISPLAY = { 1.0f, 1.0f };
//HP�̘g
const D3DXVECTOR3 HPFRAME_POS = { 0.0f, 10.0f, 0.0f };
//�G��HP
const D3DXVECTOR3 ENEMY_HPGAGE_POS  = { 800.0f, 16.0f, 0.0f }; //���W

//=====================================
// �o�g���V�[���N���X
// �����:�Γc�D��
//=====================================
class CBattleScene
	:public CSceneBase
{
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

	//----�̗̓Q�[�W�֘A----
	//���ꂼ��̗̑̓Q�[�W�̕`��
	void DrawHpGage();
	//�̗̓Q�[�W/�w�i�̏����ݒ�
	void InitHpGage();
	//�̗̓Q�[�W�̃A�j���[�V����
	void HpGageAnim(std::unique_ptr<CUIObject>& gage, float& hp, float maxhp, float& width);

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

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//�o�g���Ɏg�p����p�����[�^�̃f�[�^
	json m_BattleData;
	//�G�̃p�����[�^�̃f�[�^
	json m_EnemyHeroData;

	//----�̗͊֘A�̕ϐ�----
	//���݂̗̑�
	float m_Hp;		//����
	float m_EnemyHp;//�G
	//�̗̓Q�[�W�̕ϓ����镝
	float m_HpWidth;    //����
	float m_EnemyHpWidth;//�G

	//�o�߃^�[����
	int m_BattleTurn;
};