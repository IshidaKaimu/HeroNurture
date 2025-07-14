#include "Scene\CSceneBase.h"					//�V�[���x�[�X�N���X
#include "Camera\CameraManager\CCameraManager.h"//�J�����}�l�[�W���N���X
#include "WriteText\WriteText.h"				//�e�L�X�g�`��N���X
#include <filesystem>
#include <memory>
#include <Windows.h>

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
namespace Constant_LoginScene
{
	//----UI----
	//���O���̓X�y�[�X
	static D3DXVECTOR3 NAMESPACE_POS   = { 300.0f,300.0f,0.0f }; //���W
	static D3DXVECTOR3 NAMESPACE_SCALE = { 0.5f, 0.5f, 1.0f };   //�g�k
	static D3DXVECTOR2 NAMESPACE_DISP  = { 1.0f,1.0f };		     //��
	//�w�i
	static D3DXVECTOR3 BACK_POS   = { 0.0f,0.0f,0.0f };         //���W
	static D3DXVECTOR3 BACK_SCALE = { 1.0f, 1.0f, 1.0f };       //�g�k
	static D3DXVECTOR2 BACK_DISP  = { 1.0f,1.0f };		        //��
	//���O���͊J�n���W
	static D3DXVECTOR3 NAME_STARTPOS   = { 320.0f, 320.0f, 0.0f }; 
	//���O�ő啶����
	static const int NAME_MAXLENGTH    = 8;
	//�V�[�������W
	static const D3DXVECTOR2 SCENENAME_POS = { 0.0f, -20.0f };
	//-----------
}

//=====================================
// ���O�C���V�[���N���X
// �����:�Γc�D��
//=====================================
class CLoginScene
	:public CSceneBase
{
public:
	CLoginScene();
	~CLoginScene();

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
	//���݂̗L�����m�F�������t�H���_�̃p�X
	std::filesystem::path m_TargetPath;

	// =======================
	// �I�u�W�F�N�g�N���X
	// =======================		
	//----UI----
	//���[�U�[��
	std::wstring m_UserName;
	//���[�U�[�����̓X�y�[�X
	std::unique_ptr<CUIObject> m_pNameSpace;
	//�w�i
	std::unique_ptr<CUIObject> m_pBack;
	//---------

	//Json�N���X
	std::unique_ptr<CJson> m_pJson;
	
	//��v���閼�O�����݂��Ȃ����Ƃ�\������t���O
	bool m_NonExistent;
};
