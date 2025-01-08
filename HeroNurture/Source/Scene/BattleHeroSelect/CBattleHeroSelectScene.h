#pragma once
#include "Scene\CSceneBase.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json\CJson.h"
#include "Utility\CUtility.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"

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
//�ėp�N���X
class CUtility;

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

//=====================================
//  �萔�錾 (_BS = �g���[�j���O���ʃV�[���ŗp���邱�Ƃ�����)
//=====================================
//----�e�q�[���[�̃J�����z�u�E�����_----
//-----�J�������----
//�J�����ʒu
const D3DXVECTOR3 CAMPOS_BS = { 0.0, 5.0, -4.0 };
//�J���������_
const D3DXVECTOR3 CAMLOOK_BS = { 2.0, 5.0, 3.0 };

//----UI���----
//�p�����[�^�̔w�iUI
const D3DXVECTOR3 PARAMBACK_POS_BS = { 725.0f,125.0f, 0.0f };
const D3DXVECTOR3 PARAMBACK_SCALE_BS = { 1.1f,1.1f,1.1f };
//�p�����[�^�̐��l
constexpr float PARAMVALUE_POSX_BS = 900.0f; //X���W
constexpr float PARAMVALUE_POSY_BS = 225.0f; //Y���W
constexpr float PARAMVALUE_INTERVAL_BS = 130.0f; //�z�u�Ԋu
//�p�����[�^�����N
constexpr float PARAMRANK_POSX_BS = 855.0f; //X���W
constexpr float PARAMRANK_POSY_BS = 225.0f; //Y���W
constexpr float PARAMRANK_INTERVAL_BS = 130.0f; //�z�u�Ԋu
//�琬�����N
constexpr float RANK_POSX_BS = 900.0f; //X���W
constexpr float RANK_POSY_BS = 30.0f; //Y���W
//�u�琬�����N�v�e�L�X�g���W
const D3DXVECTOR2 RESULTTEXT_POS_BS = { 895.0f,0.0f };
//���݂̑I��ԍ�
const D3DXVECTOR2 SELECTNO_POS = { 1140.0f, 0.0f };
//�琬�f�[�^�̍ő吔
const D3DXVECTOR2 NATUREDATA_MAX_POS = { 1200.0f, 0.0f };

//==============================
// �o�g���q�[���[�I���N���X
//==============================
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

	//�琬�f�[�^�̊e�v�f�`�揈��
	void DrawResultData();

	//�ۑ�����Ă���q�[���[�̃p�����[�^��\������
	void DrawSaveParameter(const json& jsondata, int number);

private:
	//�o�߃^�[����
	int m_BattleTurn;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//�ۑ�����Ă���琬���ʂ̃t�@�C���f�[�^
	json m_ResultData;
	//�o�g���Ɏg�p����f�[�^���i�[���A�������݂ɗp����ϐ�
	json m_BattleDataWriter;

	//�J�����}�l�[�W���N���X
	CCameraManager* m_pCamera;

	// =======================
	// �I�u�W�F�N�g�N���X
	// =======================	
	//----UI----
	std::unique_ptr<CUIObject> m_pParamBack;

	//----�X�L�����b�V��----
	//���C
	std::unique_ptr<CYui>	m_pYui;
	//�J�C�g
	std::unique_ptr<CKaito> m_pKaito;

};