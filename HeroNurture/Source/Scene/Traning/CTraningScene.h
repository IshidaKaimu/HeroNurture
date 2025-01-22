#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Scene\Nature\CNatureScene.h"
#include "json.hpp"

//========================
// �O���錾
//=======================
//----�}�l�[�W���[�N���X----
//�q�[���[�}�l�[�W���[
class CHeroManager;
//UI�}�l�[�W���[
class CUIManager;

//========================
// �萔�錾
//=======================
//----�e�L�X�g�̈ʒu----
//�p�����[�^�̎��
const D3DXVECTOR2 PARAMTEXT_OFFSET  = { 80.0f,600.0f };
//�l
const D3DXVECTOR2 VALUETEXT_OFFSET  = { 275.0f,600.0f };
//�g���[�j���O����
const D3DXVECTOR2 RESULTTEXT_OFFSET = { 500.0f,100.0f };
//SE�̍Đ��^�C�~���O
const int PLAY_SE = 1;


//========================
//�㏸�����p�����[�^�̃��X�g
//�e�L�X�g�̕`�揇�����Ɏg��
//=======================
struct IncParam
{
	std::wstring ParamName;		 //�p�����[�^�̎��
	int IncValue;				 //�㏸��
	std::wstring ParamChangeText;//�㏸�܂��͌����̃e�L�X�g
};

//=====================================
//�g���[�j���O�V�[���N���X
//=====================================
class CTraningScene
	:public CNatureScene
{
public:
	CTraningScene();
	~CTraningScene();

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

private:
	////�g���[�j���O���Ƃ̃A�j���[�V����
	//void TraningAnimation();
	//�p�����[�^���㏸���Ă�����z��Ƀe�L�X�g��ǉ����鏈��
	void AddText();
	//�z��Ɋ��ɒǉ����Ă�����ł͂Ȃ����̊m�F
	bool AlreadyAddCheck(std::wstring paramname);
	//�g���[�j���O���ʃe�L�X�g�̕`��
	void DrawTraningText();
	//�p�����[�^�ω��̕`�揈��
	void DrawParamChange(const IncParam& param);

private:

	//�J�����}�l�[�W��
	CCameraManager* m_pCamera;

	//=====================================
	// �I�u�W�F�N�g�N���X
	//=====================================
	//----�X�^�e�B�b�N���b�V��----
	//�X�J�C�{�b�N�X
	std::unique_ptr<CSky> m_pSky;
	//�n��
	std::unique_ptr<CGround> m_pGround;

	//----UI----
	//�w�i
	std::unique_ptr<CUIObject> m_pBack;
	//�e�L�X�g�{�b�N�X
	std::unique_ptr<CUIObject> m_pTextBox;

	//----vector�z��----
	//�e�L�X�g�̕`�揇�����Ɏg���z��
	std::vector<IncParam> m_ParamInc;

	//�e�L�X�g�ԍ����\��������
	int m_TextNo;

	//SE�Đ��p�J�E���g
	int m_SECnt;

};