#pragma once
#include "CSceneBase.h"
#include "CDirectX11.h"
#include "CDirectX9.h"
#include <memory>

//----�O���錾---
class CTitle;
class CHeroSelect;
class CNatureScene;
class CTraning;

//�琬�^�[����
constexpr int MAX_TURN = 5;

class CSceneManager
	: public CSceneBase
{
public:
	//�V�[�����X�g�񋓌^
	enum enSceneList
	{
		SceneSelect = 0,
		GameMain,
		Nature,
		Training,
		Max,
		none = -1,
	};

public:
	static CSceneManager* GetInstance() {
		static CSceneManager s_Instance;
		return &s_Instance;
	}

	~CSceneManager() ;

	//�\�z�֐�
    void Create(CDirectX9& pDx9, CDirectX11& pDx11, HWND hwnd);

	void Release();

	//�������֐�
	void Initialize();

	//�X�V�֐�
	void Update();
	
	//�`��֐�
	void Draw();

	//�e�V�[���̍\�z�A�f�[�^�ǂݍ���
	void LoadCreate(enSceneList List);	

	//�V�[���\�z�֐�
	static std::unique_ptr<CSceneBase> Create(enSceneList List);

public:
	//�ǂݍ��݉񐔐����t���O�̑���
	void SetIsDataLoaded(bool loaded) { m_IsDataLoaded = loaded; }

	//�^�[�����̌o��
	void TurnProgress() { m_Turn--; }

	//�^�[�����̏�����
	void InitTurn() { m_Turn = MAX_TURN; }

    //---�Q�b�^�[�E�Z�b�^�[---
    //DirectX9
    CDirectX9* GetDx9() { return m_pDx9; }
	void SetDx9( CDirectX9& Dx9) { m_pDx9 = &Dx9; }
    //DirectX11
	CDirectX11* GetDx11() { return m_pDx11; }
	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }
    //�E�B���h�E�n���h��
    HWND GetWnd() { return m_hWnd; }
    void SetWnd(HWND m_wnd) { m_hWnd = m_wnd; }
	//�ǂݍ��݉񐔐����t���O�̎擾
	bool GetIsDataLoaded() { return m_IsDataLoaded; }
	//�c��^�[�����̎擾
	int GetRemainingTurn() { return m_Turn; }

private:
	CSceneManager();
	CSceneManager(const CSceneManager& rhs) = delete;
	CSceneManager& operator = (const CSceneManager& rhs) = delete;
private:
	std::unique_ptr<CSceneBase> m_Scene;	//���j�[�N�|�C���^

    HWND        m_hWnd;    //�E�B���h�E�n���h��
    CDirectX9*  m_pDx9;	   //DirectX9
    CDirectX11* m_pDx11;   //DirectX11

	//�c��^�[����
	int        m_Turn;

	//----�t���O----
	//�f�[�^�ǂݍ��݂����񂩂ǂ����̃t���O
	bool       m_IsDataLoaded;


};
