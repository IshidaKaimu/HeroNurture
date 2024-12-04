#pragma once
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Scene\CSceneBase.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "json.hpp"
#include <memory>

//----�O���錾----
class WriteText;
class CJson;

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

//----�萔�錾----
//�e�q�[���[���Ƃ̃J�����ʒu/�����_
//���C
const D3DXVECTOR3 CAMERAPOS_YUI  = { 0.0, 5.0, -6.0 };
const D3DXVECTOR3 CAMERALOOK_YUI = { 0.0, 5.0, 0.0 };
//�J�C�g
const D3DXVECTOR3 CAMERAPOS_KAITO  =  { 0.0, 5.0, -4.5 };
const D3DXVECTOR3 CAMERALOOK_KAITO =  { 0.0, 5.0, 0.0 };

//�p�����[�^UI���
//�A�C�R���E�p�����[�^��
constexpr float PARAM_POSX = 225.0f;
constexpr float PARAM_POSY = 450.0f;
//���l
constexpr float PARAMVALUE_POSX = 230.0f;

//�q�[���[���\����
struct HeroName
{
	//���C
	std::string Yui = "Yui";
	//�J�C�g
	std::string Kaito = "Kaito";
};

//----------------
//�琬�V�[���N���X
//----------------
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

public:
	//�e�q�[���[�p�t�@�C���̍쐬�E�ǂݍ���
	void LoadHeroData( const std::string& heroname );

	//�p�����[�^���̏�������
	void WriteParam( const std::string& heroname );

	//�p�����[�^UI�̐ݒ�
	void ParamInit(CUIObject* param, int no);

	//�p�����[�^�̕`��
	void DrawParam();

	//�c��^�[�����̕`��
	void DrawRemainingTurn();

public:
	//�J�����}�l�[�W���N���X
	CCameraManager* m_pCamera;

	//�q�[���[�}�l�[�W���N���X
	CHeroManager* m_pHero;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//���O�\����
	HeroName m_Name;

	//----�I�u�W�F�N�g�N���X----
	//�X�^�e�B�b�N���b�V��
	//�n�ʃN���X
	std::unique_ptr<CGround> m_pGround;
	//�X�J�C�{�b�N�X�N���X
	std::unique_ptr<CSky>	 m_pSky;
	
	//UI
	//�e�p�����[�^�\��
	//�ؗ�
	CUIObject* m_pPowerParam;
	//����
	CUIObject* m_pMagicParam;
	//�f����
	CUIObject* m_pSpeedParam;
	//�̗�
	CUIObject* m_pHpParam;

	//----json�֘A----
    //�p�����[�^���̏������ݗp
	json m_ParamWriter;
	//�p�����[�^�f�[�^�i�[�p
	json m_ParamData;

};

