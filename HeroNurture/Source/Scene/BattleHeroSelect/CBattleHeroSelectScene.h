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
//------------------------

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

//=====================================
//  �萔�錾
//=====================================
namespace Constant_BattleHeroSelectScene 
{
	//�J����
	const D3DXVECTOR3 CAMPOS  = { 0.0f, 5.0f, -4.0f };			  //���W
	const D3DXVECTOR3 CAMLOOK = { 2.0f, 5.0f, 3.0f };			  //�����_

	//----UI----
	//�p�����[�^�̔w�i
	const D3DXVECTOR3 PARAMBACK_POS   = { 840.0f, 165.0f, 0.0f }; //���W
	const D3DXVECTOR3 PARAMBACK_SCALE = { 1.1f, 1.1f, 1.1f };	  //�����_
	//�p�����[�^�̐��l
	const D3DXVECTOR2 PARAMVALUE_POS    = { 955.0f,185.0f };	  //���W
	constexpr float PARAMVALUE_INTERVAL = 130.0f;				  //�z�u�Ԋu
	//�p�����[�^�����N											  
	const D3DXVECTOR2 PARAMRANK_POS    = { 860.0f, 185.0f };	  //���W
	constexpr float PARAMRANK_INTERVAL = 130.0f;				  //�z�u�Ԋu
	//�琬�����N												  	 
	const D3DXVECTOR2 RANK_POS = { 900.0f,-5.0f };				  //���W
	//�u�琬�����N�v�e�L�X�g									   
	const D3DXVECTOR2 RESULTTEXT_POS = { 895.0f,-20.0f };		  //���W
	//���݂̑I��ԍ�											   
	const D3DXVECTOR2 SELECTNO_POS = { 1140.0f, 0.0f };			  //���W
	//�琬�f�[�^�̍ő吔										     
	const D3DXVECTOR2 NurtureDATA_MAX_POS = { 1200.0f, 0.0f };	  //���W
	//�uA�ED �I���v�e�L�X�g									   	  
	const D3DXVECTOR2 SELECTTEXT_POS = { 800.0f, 675.0f };		  //���W
	//�w�i													   	  
	static D3DXVECTOR3 BACK_POS   = { 0.0f,0.0f,0.0f };			  //���W
	static D3DXVECTOR3 BACK_SCALE = { 1.0f, 1.0f, 1.0f };		  //�g�k
	static D3DXVECTOR2 BACK_DISP  = { 1.0f,1.0f };				  //��
	//----------
}
//==============================
// �o�g���q�[���[�I���N���X
//==============================
class CBattleHeroSelectScene
	:public CSceneBase
{
private:
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

public:

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

	//�ۑ�����Ă��閼�O���Ƃ̃q�[���[�̕`��
	void DrawHero();

	//���̕`��
	void DrawArrow();

	//�p�����[�^UI�̕`��
	void DrawParamUI(float paramvalue, int no);

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
	//----�X�L�����b�V��----
	//���C
	std::unique_ptr<CYui>	m_pYui;
	//�J�C�g
	std::unique_ptr<CKaito> m_pKaito;
	//----------------------

	//----UI----
	//�p�����[�^�w�i
	std::unique_ptr<CUIObject> m_pParamBack;
	//���
	std::unique_ptr<CUIObject> m_pLeftArrow;
	//���E
	std::unique_ptr<CUIObject> m_pRightArrow;
	//----------


	//�O�̃V�[���ɖ߂��ꍇ�̃t���O
	bool m_BackSceneFlag;

};