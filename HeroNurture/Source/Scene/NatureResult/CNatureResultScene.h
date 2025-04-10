#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json\CJson.h"

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
// �萔�錾
//=====================================
namespace Constant_NatureResultScene 
{
	//-----�J�������----
	//�J�����ʒu
	const D3DXVECTOR3 CAMPOS = { 0.0f, 5.0f, -4.0f };
	//�J���������_
	const D3DXVECTOR3 CAMLOOK = { 2.0f, 5.0f, 3.0f };
	//----�琬�]���`��֘A----
	//�ŏI�����NX���W
	constexpr float RANK_POSX = 900.0f;
	//�ŏI�����NY���W
	constexpr float RANK_POSY = 30.0f;
	//�p�����[�^�����N�z�u�J�n�n�_X���W
	constexpr float PARAMRANK_POSX = 885.0f;
	//�p�����[�^�����N�z�u�J�n�n�_Y���W
	constexpr float PARAMRANK_POSY = 225.0f;
	//�e�p�����[�^�����N�z�u�Ԋu
	constexpr float PARAMRANK_INTERVAL = 130.0f;
	//�p�����[�^�w�i���W
	const D3DXVECTOR3 PARAMBACK_POS = { 840.0f, 205.0f, 0.0f };
	//�p�����[�^�w�i�g�k
	const D3DXVECTOR3 PARAMBACK_SCALE = { 1.1f, 1.1f , 1.1f };
	//�p�����[�^�̒lX���W
	const float PARAMVALUE_POSX = 930.0f;
	//�p�����[�^�̒lY���W
	const float PARAMVALUE_POSY = 225.0f;
	//�p�����[�^�̒l�z�u�Ԋu
	const float PARAMVALUE_INTERVAL = 130.0f;
	//�u�琬�����N�v�e�L�X�g���W
	const D3DXVECTOR2 RESULTTEXT_POS = { 895.0f,0.0f };
}
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