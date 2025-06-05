#pragma once
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Scene\CSceneBase.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "json.hpp"
#include <memory>
#include "Json\CJson.h"

// =======================
// �O���錾
// =======================		
//----�}�l�[�W���[�N���X----
//ImGui
class ImGuiManager;
//�V�[��
class CSceneManager;
//�琬���[�h
class CNurtureManager;
//���C�g
class CLightManager;
//�T�E���h
class CSoundManager;
//�����`��N���X
class WriteText;
//�ėp�N���X
class CUtility;


//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

// =======================
// �萔�錾
// =======================	
namespace Constant_NurtureScene
{
	//----�e�q�[���[���Ƃ̃J�����ʒu/�����_---
	//���C
	const D3DXVECTOR3 CAMERAPOS_YUI  = { 0.0, 5.0, -4.0 }; //���W
	const D3DXVECTOR3 CAMERALOOK_YUI = { 0.0, 5.0, 0.0 };  //�����_
	//�J�C�g
	const D3DXVECTOR3 CAMERAPOS_KAITO  = { 0.0, 5.0, -4.5 }; //���W
	const D3DXVECTOR3 CAMERALOOK_KAITO = { 0.0, 5.0, 0.0 };  //�����_

	//----UI���----
	//�p�����[�^�w�i
	const D3DXVECTOR3 PARAMBACK_POS   = { 330.0f,410.0f,0.0f }; //���W
	const D3DXVECTOR3 PARAMBACK_SCALE = { 0.8f,0.8f,0.8f };   //�g�k
	//�g���[�j���OUI
	const D3DXVECTOR3 TRANING_POS = { 200.0f,580.0f,0.0f };  //X���W
	constexpr float   TRANING_INTERVAL = 180.0f;	         //�z�u�Ԋu
	const D3DXVECTOR3 TRANING_SCALE = { 0.5f,0.5f,0.5f };    //�g�k
	//���l
	const D3DXVECTOR2 PARAMVALUE_POS = { 425.0f,430.0f };    //���W
	constexpr float PARAMVALUE_INTERVAL = 150.0f;			 //�z�u�Ԋu
	//�����N
	const D3DXVECTOR2 RANK_POS = { 350.0f,430.0f };     //���W
	constexpr float RANK_INTERVAL = 150.0f;				      //�z�u�Ԋu
	//�X�^�~�i�Q�[�W
	const D3DXVECTOR3 STAMINA_POS	   = { 670.0f, 7.0f, 0.0f }; //�Q�[�W�E�Q�[�W�w�i���W
	const D3DXVECTOR3 STAMINAFRAME_POS = { 575.0f, 0.0f, 0.0f }; //�Q�[�W�g���W
	//�^�[�����w�i
	const D3DXVECTOR3 TURNBACK_POS = { 0.0f, 0.0f, 0.0f };  //���W
	//�^�[����
	const D3DXVECTOR2 TURN_POS = { 180.0f,-10.0f };
	//�u�c��v�e�L�X�g
	const D3DXVECTOR2 REMAININGTEXT_POS = { 10.0f,-20.0f };
	//�u�^�[���v�e�L�X�g
	const D3DXVECTOR2 TURNTEXT_POS = { 240.0f, -20.0f };
	//����
	const D3DXVECTOR3 BASIC_SCALE   = { 1.0f, 1.0f, 1.0f }; //�g�k
	const D3DXVECTOR2 BASIC_DISPLAY = { 1.0f,1.0f };	    //��
	//�ʒu�̕␳�����錅��
	constexpr int CORRECTION_DIGIT = 3;
	//���s���w�i
	const D3DXVECTOR3 FAILUREBACK_POS   = { 30.0f, 350.0f, 0.0f }; //���W
	const D3DXVECTOR3 FAILUREBACK_SCALE = { 0.7f, 0.7f, 0.7f };	   //�g�k
	const D3DXVECTOR2 FAILUREBACK_DISP  = { 1.0f, 1.0f };		   //��
	constexpr float   FAILUREBACK_ALPHA = 1.0f;					   //���l
	//���s��
	const D3DXVECTOR3 FAILURERATE_POS   = { 95.0f, 430.0f, 0.0f };//���W
	//�u���s���v�e�L�X�g
	const D3DXVECTOR3 FAILURETEXT_POS   = { 55.0f, 370.0f, 0.0f }; //���W


	//���s����l
	constexpr int SAFE = 30;	//���S
	constexpr int ANXIETY = 70; //�x��

	//----�X�^�~�i�Q�[�W----
	//�X�^�~�i�̍ő�l
	constexpr float STAMINA_MAX = 100.0f;
}
//�q�[���[���\����
struct HeroName
{
	//���C
	std::string Yui = "Yui";
	//�J�C�g
	std::string Kaito = "Kaito";
};

//=====================================
//�琬�V�[���N���X
//����ҁF�Γc�D��
//=====================================
class CNurtureScene
	:public CSceneBase
{
public:
	CNurtureScene();
	~CNurtureScene();

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
	//�f�o�b�O�p�֐�
	void Debug();

protected:
	// =======================
    // �琬�֘A�̃V�[���ŌŒ肷��UI�֘A�̊֐�
    // =======================		
    //�C���X�^���X����
	void CreateNurtureUI(
		std::unique_ptr<CUIObject>& gage, 
		std::unique_ptr<CUIObject>& back,
		std::unique_ptr<CUIObject>& frame,
		std::unique_ptr<CUIObject>& turnback);
	//�f�[�^�̃��[�h
	void LoadNurtureUI(
		std::unique_ptr<CUIObject>& gage,
		std::unique_ptr<CUIObject>& back,
		std::unique_ptr<CUIObject>& frame,
		std::unique_ptr<CUIObject>& turnback);
	//������
	void InitNurtureUI(
		std::unique_ptr<CUIObject>& gage, 
		std::unique_ptr<CUIObject>& back, 
		std::unique_ptr<CUIObject>& frame,
		std::unique_ptr<CUIObject>& turnback);
	//�`��
	void DrawNurtureUI(
		std::unique_ptr<CUIObject>& gage, 
		std::unique_ptr<CUIObject>& back, 
		std::unique_ptr<CUIObject>& frame,
		std::unique_ptr<CUIObject>& turnback);
	//=========================

public:
	//�e�q�[���[�p�t�@�C���̍쐬�E�ǂݍ���
	void LoadHeroData(const std::string& heroname);

	//�g���[�j���O�I������
	void SelectTraning();

	//�e�g���[�j���OUI�̏����ݒ�
	void UIInit(std::unique_ptr<CUIObject>& traning, D3DXVECTOR3 pos, float interval, D3DXVECTOR3 scale, int no);

	//�e���s���w�i�̏����ݒ�
	void FailureRateBackInit(std::unique_ptr<CUIObject>& back, D3DXVECTOR3 pos);

	// =======================
	// �p�����[�^�֘A�֐�
	// =======================		
	//�q�[���[�̂��Ƃ̃p�����[�^���̏�������
	void SaveParam();
	//�p�����[�^�̕`��
	void DrawParam();

	//�e�g���[�j���O�̕`��
	void DrawTraning();

	//�c��^�[�����̕`��
	void DrawRemainingTurn();

	//�Q�[�W�A�j���[�V����
	void StaminaGageAnim();
public:
	//�J�����}�l�[�W���N���X
	CCameraManager* m_pCamera;

	//�q�[���[�}�l�[�W���N���X
	CHeroManager* m_pHero;

	//���O�\����
	HeroName m_Name;

	// =======================
	// �I�u�W�F�N�g�N���X
	// =======================		
	//----�X�^�e�B�b�N���b�V��----
	//�n��
	std::unique_ptr<CGround> m_pGround;
	//----------------------------

	//----UI----	
	//�p�����[�^�w�i
	std::unique_ptr<CUIObject>  m_pParamBack;
	//�ؗ̓g���[�j���OUI
	std::unique_ptr<CUIObject> m_pPowerTraning;
	//���̓g���[�j���OUI
	std::unique_ptr<CUIObject> m_pMagicTraning;
	//�f�����g���[�j���OUI
	std::unique_ptr<CUIObject> m_pSpeedTraning;
	//�̗̓g���[�j���OUI
	std::unique_ptr<CUIObject> m_pHpTraning;
	//�x��UI
	std::unique_ptr<CUIObject> m_pRest;
	//�X�^�~�i�Q�[�W
	std::unique_ptr<CUIObject> m_pStaminaGage;
	//�X�^�~�i�Q�[�W�w�i
	std::unique_ptr<CUIObject> m_pStaminaBack;
	//�X�^�~�i�Q�[�W�g
	std::unique_ptr<CUIObject> m_pStaminaFrame;
	//�X�^�~�i�Q�[�W�̕�
	float m_GageWidth;
	//�^�[�����̔w�i
	std::unique_ptr<CUIObject> m_pTurnBack;
	//���s���w�i(30%�ȉ�)
	std::unique_ptr<CUIObject> m_pSafeBack;
	//���s���w�i(30%�ȏ�70%�ȉ�)
	std::unique_ptr<CUIObject> m_pAnxietyBack;
	//���s���w�i(70%�ȏ�)
	std::unique_ptr<CUIObject> m_pDangerBack;
	//----------

	//===================================

	// =======================
	// json�֘A
	// =======================	
	//json�N���X
	std::unique_ptr<CJson> m_pJson;
	//�p�����[�^���̏������ݗp
	json m_ParamWriter;
	//�p�����[�^�f�[�^�i�[�p
	json m_ParamData;
};

