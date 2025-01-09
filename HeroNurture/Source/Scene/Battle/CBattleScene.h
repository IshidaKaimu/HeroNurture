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

//=====================================
// �萔�錾(_B = �o�g���V�[���ŗp���邱�Ƃ�����)
//=====================================
//----�J�������----
//�������W
const D3DXVECTOR3 INIT_CAMPOS_B  = { -1.0f,2.0f,-6.0f };
const D3DXVECTOR3 INIT_CAMLOOK_B = { -1.0f,2.0f,-0.0f };

//=====================================
// �o�g���V�[���N���X
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

private:
	//�������g���q�[���[
	CHeroManager* m_pHero;
	//�G�̃q�[���[
	CEnemyHeroManager* m_pEnemyHero;

	//�J�����}�l�[�W���[
	CCameraManager* m_pCamera;

	//�I�u�W�F�N�g�N���X
	//----�X�^�e�B�b�N���b�V��----
	//�n��
	std::unique_ptr<CGround> m_pGround;
	//��
	std::unique_ptr<CSky> m_pSky;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//�o�g���Ɏg�p����f�[�^
	json m_BattleData;

	//�o�߃^�[����
	int m_BattleTurn;
};