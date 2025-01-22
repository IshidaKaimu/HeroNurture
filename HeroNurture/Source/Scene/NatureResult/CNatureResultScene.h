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

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

//=====================================
// �萔�錾 (_NR = �g���[�j���O���ʃV�[���ŗp���邱�Ƃ�����)
//=====================================
//-----�J�������----
//�J�����ʒu
const D3DXVECTOR3 CAMPOS_NR  = { 0.0f, 5.0f, -4.0f };
//�J���������_
const D3DXVECTOR3 CAMLOOK_NR = { 2.0f, 5.0f, 3.0f };
//----�琬�]���`��֘A----
//�ŏI�����NX���W
constexpr float RANK_POSX_NR = 900.0f;
//�ŏI�����NY���W
constexpr float RANK_POSY_NR = 30.0f;
//�p�����[�^�����N�z�u�J�n�n�_X���W
constexpr float PARAMRANK_POSX_NR = 885.0f;
//�p�����[�^�����N�z�u�J�n�n�_Y���W
constexpr float PARAMRANK_POSY_NR = 225.0f;
//�e�p�����[�^�����N�z�u�Ԋu
constexpr float PARAMRANK_INTERVAL_NR = 130.0f;
//�p�����[�^�w�i���W
const D3DXVECTOR3 PARAMBACK_POS_NR = { 840.0f, 205.0f, 0.0f };
//�p�����[�^�w�i�g�k
const D3DXVECTOR3 PARAMBACK_SCALE_NR = { 1.1f, 1.1f , 1.1f };
//�p�����[�^�̒lX���W
const float PARAMVALUE_POSX_NR = 930.0f;
//�p�����[�^�̒lY���W
const float PARAMVALUE_POSY_NR = 225.0f;
//�p�����[�^�̒l�z�u�Ԋu
const float PARAMVALUE_INTERVAL_NR = 130.0f;
//�u�琬�����N�v�e�L�X�g���W
const D3DXVECTOR2 RESULTTEXT_POS_NR = { 895.0f,0.0f };
 
//=====================================
// �琬���ʃV�[���N���X
//=====================================
class CNatureResultScene
	:public CSceneBase
{
public:
	CNatureResultScene();
	~CNatureResultScene();

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
	//�琬���ʂ̕ۑ�
	void SaveResult(const std::string& heroname);


private:
	//�J�����}�l�[�W��
	CCameraManager* m_pCamera;

	//�p�����[�^�w�iUI
	std::unique_ptr<CUIObject> m_pParamList;

	// =======================
	// json�֘A
	// =======================	
	//json�N���X
	std::unique_ptr<CJson> m_pJson;
	//�琬���ʏ������ݗp
	json m_ResultWriter;
};