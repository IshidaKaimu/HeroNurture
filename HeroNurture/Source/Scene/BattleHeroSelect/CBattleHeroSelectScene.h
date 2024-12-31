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
//�L�[����
class CKeyManager;
//�e�L�X�g�`��N���X
class WriteText;

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

// =======================
// �萔�錾
// =======================	
	
//----UI���(_BS = BattleHeroSelectScene�ł̎d�l��\��)----
//�p�����[�^�̐��l
constexpr float PARAMVALUE_POSX_BS = 425.0f; //X���W
constexpr float PARAMVALUE_POSY_BS = 430.0f; //Y���W
constexpr float PARAMVALUE_INTERVAL_BS = 150.0f; //�z�u�Ԋu
//�琬�f�[�^�̍ő吔
const D3DXVECTOR2 NATUREDATA_MAX_POS = { 1000.0f, 0.0f };

//=====================================
// �o�g���q�[���[�I���N���X
//=====================================
class CBattleHeroSelectScene
	:public CSceneBase
{
public:
	//�p�����[�^�\���X�V�p�\����
	struct enParamWriter
	{
		//�ؗ�
		float Power;
		//����
		float Magic;
		//�f����
		float Speed;
		//�̗�
		float Hp;
	};

	CBattleHeroSelectScene();
	~CBattleHeroSelectScene();

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
	//�ۑ�����Ă���q�[���[�̃p�����[�^��\������
	void DrawSaveParameter(const json& jsondata, int number);

private:
	//�o�߃^�[����
	int m_BattleTurn;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//�ۑ�����Ă���琬���ʂ̃t�@�C���f�[�^
	json m_ResultData;

};