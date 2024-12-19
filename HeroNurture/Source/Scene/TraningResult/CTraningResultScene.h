#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json.hpp"
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

//=====================================
// �萔�錾
//=====================================
//-----�J�������----
//�J�����ʒu
const D3DXVECTOR3 RESULT_CAMPOS  = { 0.0, 5.0, -4.0 };
//�J���������_
const D3DXVECTOR3 RESULT_CAMLOOK = { 2.0, 5.0, 3.0 };
//----�琬�]���`��֘A----
//�����NX���W
constexpr float RANK_POSX = 900.0f;
//�����NY���W
constexpr float RANK_POSY = 30.0f;
//�p�����[�^�w�iX���W
const float PARAMBACK_POSX = 850.0f;
//�p�����[�^�w�iY���W
const float PARAMBACK_POSY = 600.0f;
//�p�����[�^�w�i�g�k
const D3DXVECTOR3 PARAMBACK_SCALE = { 0.3f,0.3f,0.3f };

//=====================================
// �琬���ʃV�[���N���X
//=====================================
class CTraningResultScene
	:public CSceneBase
{
public:
	CTraningResultScene();
	~CTraningResultScene();

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
	//�琬���ʂ̕`��
	void DrawResult();
	//�p�����[�^�̍��v�l��Ԃ�
	float ParamTotal();
	//�p�����[�^�w�iUI�̏����ݒ�
	void ParamBackUIInit(std::unique_ptr<CUIObject>& param, int no);
	//�p�����[�^UI�̕`��
	void DrawParamUI(std::unique_ptr<CUIObject>& param, float paramvalue, int no);


private:
	//�J�����}�l�[�W��
	CCameraManager* m_pCamera;

	//�ؗ̓p�����[�^�w�i
	std::unique_ptr<CUIObject> m_pPowerParam;
	//���̓p�����[�^�w�i
	std::unique_ptr<CUIObject> m_pMagicParam;
	//�f�����p�����[�^�w�i
	std::unique_ptr<CUIObject> m_pSpeedParam;
	//�̗̓p�����[�^�w�i
	std::unique_ptr<CUIObject> m_pHpParam;
	//�X�^�~�i�Q�[�W
	std::unique_ptr<CUIObject> m_pStaminaGage;
	//�X�^�~�i�Q�[�W�Q�[�W�w�i
	std::unique_ptr<CUIObject> m_pStaminaBack;
	//�X�^�~�i�Q�[�W�̕�
	float m_GageWidth;

};