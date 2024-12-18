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
//�O���錾
//=======================
class CHeroManager;

//========================
//�萔�錾
//=======================
//----�e�L�X�g�̈ʒu----
//�p�����[�^�̎��
const D3DXVECTOR2 PARAMTEXT_OFFSET  = { 0.0f,600.0f };
//�l
const D3DXVECTOR2 VALUETEXT_OFFSET  = { 195.0f,600.0f };
//�g���[�j���O����
const D3DXVECTOR2 RESULTTEXT_OFFSET = { 500.0f,100.0f };


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
//����ҁF�Γc�D��
//=====================================
class CTraning
	:public CNatureScene
{
public:
	CTraning();
	~CTraning();

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

	//----�I�u�W�F�N�g�N���X----
	// �X�^�e�B�b�N���b�V��
	//�X�J�C�{�b�N�X
	std::unique_ptr<CSky> m_pSky;
	//�n��
	std::unique_ptr<CGround> m_pGround;

	//----vector�z��----
	//�e�L�X�g�̕`�揇�����Ɏg���z��
	std::vector<IncParam> m_ParamInc;

	//�e�L�X�g�ԍ����\��������
	int m_TextNo;

};