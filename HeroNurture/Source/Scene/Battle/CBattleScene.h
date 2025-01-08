#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json\CJson.h"
#include "Utility\CUtility.h"

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
//ImGui
class ImGuiManager;

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;


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
	//�q�[���[�}�l�[�W���[�N���X
	std::unique_ptr<CHeroManager> m_pHero;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//�o�g���Ɏg�p����f�[�^
	json m_BattleData;

	//�o�߃^�[����
	int m_BattleTurn;
};