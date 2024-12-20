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
//----�琬�]���`��֘A(_TR = �g���[�j���O���ʃV�[���ŗp���邱�Ƃ�����)----
//�ŏI�����NX���W
constexpr float RANK_POSX = 900.0f;
//�ŏI�����NY���W
constexpr float RANK_POSY_TR = 30.0f;
//�e�p�����[�^�����NX���W
constexpr float PARAMRANK_POSX_TR = 830.0f;
//�e�p�����[�^�����NY���W
constexpr float PARAMRANK_POSY_TR = 230.0f;
//�e�p�����[�^�����N�z�u�Ԋu
constexpr float PARAMRANK_INTERVAL_TR = 125.0f;
//�p�����[�^�w�iX���W
const float PARAMBACK_POSX_TR = 725.0f;
//�p�����[�^�w�iY���W
const float PARAMBACK_POSY_TR = 125.0f;
//�p�����[�^�w�i�g�k
const D3DXVECTOR3 PARAMBACK_SCALE_TR = { 1.1f, 1.1f , 1.1f };
//�p�����[�^�̒lX���W
const float PARAMVALUE_POSX_TR = 725.0f;
//�p�����[�^�̒lY���W
const float PARAMVALUE_POSY_TR = 200.0f;
//�p�����[�^�̒l�z�u�Ԋu
const float PARAMVALUE_INTERVAL_TR = 200.0f;
//�u�ŏI�]���v�e�L�X�gX���W
const D3DXVECTOR2 RESULTTEXT_POS = { 890.0f,0.0f };
 
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
	//�p�����[�^UI�̕`��
	void DrawParamUI(float paramvalue, int no);


private:
	//�J�����}�l�[�W��
	CCameraManager* m_pCamera;

	//�p�����[�^�w�iUI
	std::unique_ptr<CUIObject> m_pParamList;

	//�X�^�~�i�Q�[�W�̕�
	float m_GageWidth;

};