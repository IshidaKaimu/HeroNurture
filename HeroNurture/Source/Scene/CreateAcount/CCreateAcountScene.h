#include "Scene\CSceneBase.h"					//�V�[���x�[�X�N���X
#include "Camera\CameraManager\CCameraManager.h"//�J�����}�l�[�W���N���X
#include "WriteText\WriteText.h"				//�e�L�X�g�`��N���X
#include <memory>
#include <Windows.h>
#include <filesystem>

// =======================
// �O���錾
// =======================		
class CJson;
class CKeyManager;
class CSoundManager;
class CUIManager;
class CUtility;

// =======================
// �萔�錾
// =======================
namespace Constant_CreateAcountScene
{
	//----UI----
	//���O���̓X�y�[�X
	static D3DXVECTOR3 NAMESPACE_POS   = { 300.0f,300.0f,0.0f }; //���W
	static D3DXVECTOR3 NAMESPACE_SCALE = { 0.5f, 0.5f, 1.0f };   //�g�k
	static D3DXVECTOR2 NAMESPACE_DISP  = { 1.0f,1.0f };			 //��
	//�w�i
	static D3DXVECTOR3 BACK_POS   = { 0.0f,0.0f,0.0f };			//���W
	static D3DXVECTOR3 BACK_SCALE = { 1.0f, 1.0f, 1.0f };	    //�g�k
	static D3DXVECTOR2 BACK_DISP  = { 1.0f,1.0f };				//��
	//---------

	//----BGM/SE�̉���----
	//BGM
	constexpr int BGM_VOLUME = 200;
	//SE
	constexpr int SELECT_VOLUME = 200; //�I��
	constexpr int ENTER_VOLUME  = 200; //����
	//--------------------



	//���O���͊J�n���W
	static D3DXVECTOR3 NAME_STARTPOS = { 320.0f, 320.0f, 0.0f };
	//���O�ő啶����
	static const int NAME_MAXLENGTH = 8;
	//�V�[�������W
	static const D3DXVECTOR2 SCENENAME_POS = { 0.0f, -20.0f };

}

//=====================================
// �A�J�E���g�쐬�V�[���N���X
//=====================================
class CCreateAcountScene
	:public CSceneBase
{
public:
	CCreateAcountScene();
	~CCreateAcountScene();

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

	//�J�����N���X
	CCameraManager* m_pCamera;

	//----�t�H���_----
	//�R�s�[���t�@�C���̃p�X
	std::filesystem::path m_SorceDir;
	//�R�s�[��t�@�C���̃p�X
	std::filesystem::path m_DestDir;

	// =======================
	// �I�u�W�F�N�g�N���X
	// =======================		
	//----UI----
	//���[�U�[������
	std::wstring m_UserName;
	//���[�U�[�����̓X�y�[�X
	std::unique_ptr<CUIObject> m_pNameSpace;
	//�w�i
	std::unique_ptr<CUIObject> m_pBack;

	//Json�N���X
	std::unique_ptr<CJson> m_pJson;

	//���O���d�����邱�Ƃ�\������t���O
	bool m_Duplication;

};
