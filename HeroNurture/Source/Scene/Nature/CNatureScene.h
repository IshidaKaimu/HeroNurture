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
//�V�[��
class CSceneManager;
//���C�g
class CLightManager;
//�����`��N���X
class WriteText;
//�ėp�N���X
class CUtility;

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

// =======================
// �萔�錾
// =======================		
//----�e�q�[���[���Ƃ̃J�����ʒu/�����_---
//���C
const D3DXVECTOR3 CAMERAPOS_YUI  = { 0.0, 5.0, -4.0 };
const D3DXVECTOR3 CAMERALOOK_YUI = { 0.0, 5.0, 0.0 };
//�J�C�g
const D3DXVECTOR3 CAMERAPOS_KAITO  =  { 0.0, 5.0, -4.5 };
const D3DXVECTOR3 CAMERALOOK_KAITO =  { 0.0, 5.0, 0.0 };

//----UI���(_N = �琬�V�[���ŗp���邱�Ƃ�����)----
//�p�����[�^�w�i
constexpr float PARAMBACK_POSX_N     = 330.0f; //X���W
constexpr float PARAMBACK_POSY_N     = 410.0f; //Y���W
const D3DXVECTOR3 PARAMBACK_SCALE_N = { 0.8f,0.8f,0.8f }; //�g�k
//�g���[�j���OUI
constexpr float TRANING_POSX_N     = 300.0f; //X���W
constexpr float TRANING_POSY_N     = 580.0f; //Y���W
constexpr float TRANING_INTERVAL_N = 180.0f; //�z�u�Ԋu
const D3DXVECTOR3 TRANING_SCALE_N  = { 0.5f,0.5f,0.5f }; //�g�k
//���l
constexpr float PARAMVALUE_POSX_N = 425.0f; //X���W
constexpr float PARAMVALUE_POSY_N = 430.0f; //Y���W
constexpr float PARAMVALUE_INTERVAL_N = 150.0f; //�z�u�Ԋu
//�����N
constexpr float RANK_POSX_N = 350.0f; //X���W
constexpr float RANK_POSY_N = 430.0f; //Y���W
constexpr float RANK_INTERVAL_N = 150.0f;//�z�u�Ԋu
//�ʒu�̕␳�����錅��
constexpr int   CORRECTION_DIGIT = 3;

//----�X�^�~�i�Q�[�W----
//�X�^�~�i�̍ő�l
constexpr float STAMINA_MAX = 100.0f;

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
class CNatureScene
	:public CSceneBase
{
public:
	CNatureScene();
	~CNatureScene();

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
	void CreateNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back);
	//�f�[�^�̃��[�h
	void LoadNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back);
	//������
	void InitNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back);
	//�`��
	void DrawNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back);

public:
	//�e�q�[���[�p�t�@�C���̍쐬�E�ǂݍ���
	void LoadHeroData(const std::string& heroname);

	//�g���[�j���O�I������
	void SelectTraning();

	//UI�̏����ݒ�
	void UIInit(std::unique_ptr<CUIObject>& traning,float x, float y, float interval, D3DXVECTOR3 scale, int no);

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
	void GageAnim();
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
	//�n�ʃN���X
	std::unique_ptr<CGround> m_pGround;
	//�X�J�C�{�b�N�X�N���X
	std::unique_ptr<CSky>	 m_pSky;
	
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
	//�X�^�~�i�Q�[�W�̕�
	float m_GageWidth;

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

