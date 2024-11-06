#pragma once
#include "CSceneBase.h"
#include "CDirectX11.h"
#include "CDirectX9.h"
#include <memory>

class COpening;
class CAppearance;
class CTitle;
class CBossEvolution;
class CSpecialMove;
class CBossDeath;

class CSceneManager
	: public CSceneBase
{
public:
	//�V�[�����X�g�񋓌^
	enum enSceneList
	{
		SceneSelect = 0,
		GameMain,
		Max,
		none = -1,
	};

public:
	static CSceneManager* GetInstance() {
		static CSceneManager s_Instance;
		return &s_Instance;
	}

	~CSceneManager() ;


	void Initialize();

    void Create(CDirectX9& pDx9, CDirectX11& pDx11, HWND hwnd);

	void Update();
	void Draw();

	//�e�V�[���̍\�z�A�f�[�^�ǂݍ���
	void LoadCreate(enSceneList List);	

	//�V�[����
	void LoadScene() override;

	void Release();

	static std::unique_ptr<CSceneBase> Create(enSceneList List);


	//�J�����֘A�̃Z�b�^�[�ƃQ�b�^�[
	static D3DXVECTOR3 GetCameraPos() { return CSceneManager::GetInstance()->m_Camera.Position; };	//�ʒu���擾
	static D3DXVECTOR3 GetCameraLook() { return CSceneManager::GetInstance()->m_Camera.Look; };		//�����_���擾
	static void SetCameraPos(D3DXVECTOR3 pos)		{ CSceneManager::GetInstance()->m_Camera.Position = pos; };	//�ʒu
	static void SetCameraLook(D3DXVECTOR3 Look)	{ CSceneManager::GetInstance()->m_Camera.Look = Look; };		//�����_

	//x,y,Z���̃J�����Z�b�g
	static void SetCameraPosX(float x) { CSceneManager::GetInstance()->m_Camera.Position.x = x; }
	static void SetCameraPosY(float y) { CSceneManager::GetInstance()->m_Camera.Position.y = y; }
	static void SetCameraPosZ(float z) { CSceneManager::GetInstance()->m_Camera.Position.z = z; }

    //---�Q�b�^�[,�Z�b�^�[---
    //DirectX9
    CDirectX9* GetDx9() { return m_pDx9; }
	void SetDx9( CDirectX9& Dx9) { m_pDx9 = &Dx9; }
    //DirectX11
	CDirectX11* GetDx11() { return m_pDx11; }
	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }
    //�E�B���h�E�n���h��
    HWND GetWnd() { return m_hWnd; }
    void SetWnd(HWND m_wnd) { m_hWnd = m_wnd; }

private:

	CSceneManager();
	CSceneManager(const CSceneManager& rhs) = delete;
	CSceneManager& operator = (const CSceneManager& rhs) = delete;
private:
	std::unique_ptr<CSceneBase> m_Scene;	//���j�[�N�|�C���^

    HWND        m_hWnd;    //�E�B���h�E�n���h��
    CDirectX9*  m_pDx9;
    CDirectX11* m_pDx11;

};
