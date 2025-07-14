#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Utility/CUtility.h"
#include "json\CJson.h"

//=====================================
// �O���錾
//=====================================
//----�}�l�[�W���[�N���X----
//�V�[��
class CSceneManager;
//�琬���[�h
class CNurtureManager;
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
//--------------------------


//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

//=====================================
// �萔�錾
//=====================================
namespace Constant_NurtureResultScene 
{
	//-----�J�������----
	//�J�����ʒu
	const D3DXVECTOR3 CAMPOS	= { 0.0f, 5.0f, -4.0f };
	//�J���������_
	const D3DXVECTOR3 CAMLOOK	= { 2.0f, 5.0f, 3.0f };
	//-------------------

	//----�琬�]���`��֘A----
	//�ŏI�����N
	const D3DXVECTOR2 RANK_POS			  = { 900.0f,-5.0f };	//���W
	//�p�����[�^�����N 
	const D3DXVECTOR2 PARAMRANK_POS		  = { 860.0f, 185.0f };	//����W
	constexpr float	  PARAMRANK_INTERVAL  = 130.0f;				//�z�u�Ԋu
	//�p�����[�^�w�i					 
	const D3DXVECTOR3 PARAMBACK_POS		  = { 840.0f, 165.0f, 0.0f };	//���W
	const D3DXVECTOR3 PARAMBACK_SCALE	  = { 1.1f, 1.1f , 1.1f };		//�g�k
	//�p�����[�^�̒l					 
	const D3DXVECTOR3 PARAMVALUE_POS	  = { 955.0f,185.0f,0.0f };	//���W
	constexpr float   PARAMVALUE_INTERVAL = 130.0f;					//�z�u�Ԋu
	//�u�琬�����N�v�e�L�X�g
	const D3DXVECTOR2 RESULTTEXT_POS	  = { 895.0f,-20.0f }; //���W
	//-------------------------

	//----����w��----

	//������@�w���uEnter ���[�h�I���ցv�e�L�X�g�̕`��
	const D3DXVECTOR2 NEXTSCENE_TEXT_POS = { 800.0f, 675.0f };

	//----------------
}
//=====================================
// �琬���ʃV�[���N���X
// �����:�Γc�D��
//=====================================
class CNurtureResultScene
	:public CSceneBase
{
public:
	CNurtureResultScene();
	~CNurtureResultScene();

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
	//========================
};