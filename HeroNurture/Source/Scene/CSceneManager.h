#pragma once
#include "CSceneBase.h"
#include "CDirectX11.h"
#include "CDirectX9.h"
#include <memory>

//----�O���錾---
class CTitleScene;
class CNatureHeroSelectScene;
class CNatureScene;
class CTraningScene;
class CTraningResult;

//�琬�^�[����
constexpr int MAX_TURN = 10;

//=====================================
//�V�[���}�l�[�W���[�N���X
//����ҁF�Γc�D��
//=====================================
class CSceneManager
	: public CSceneBase
{
public:
	//�V�[�����X�g�񋓌^
	enum enSceneList :char
	{
		Login,
		HeroSelect,
		Nature,
		Training,
		TrainingResult,
		BattleHeroSelect,
		Battle,
		Max_S,
		none,
	};

public:
	static CSceneManager* GetInstance() {
		static CSceneManager s_Instance;
		return &s_Instance;
	}

	~CSceneManager() ;

	//�\�z�֐�
    void Create(CDirectX9& pDx9, CDirectX11& pDx11, HWND hwnd);

	//�j���֐�
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

	//----�琬�o�߃^�[���֘A�֐�----
	//�^�[�����̌o��
	void TurnProgress() { m_Turn--; }
	//�^�[�����̏�����
	void InitTurn() { m_Turn = MAX_TURN; }

	//�X�^�~�i�Q�[�W�̕��̏�����
	void InitStaminaWidth() { m_GageWidth = 1.0f; }

	//���t�F�[�h�֘A�̏�����
	void InitWhiteFade() { m_Scene->InitWhiteFade(); }

	//���t�F�[�h�̍Đ�
	void PlayWhiteFade(int max, float speed, float alpha) { m_Scene->PlayWhiteFade(max, speed, alpha); }

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
	//�ǂݍ��݉񐔐����t���O
	bool GetIsDataLoaded() { return m_IsDataLoaded; }
	//�^�[����
	int GetRemainingTurn() { return m_Turn; }
	//�X�^�~�i�Q�[�W�̕�
	float GetStaminaWidth() { return m_GageWidth; }
	void  SetStaminaWidth(float width) { m_GageWidth = width; }
	//�x���t���O
	bool GetRestFlag() { return m_Rest; }
	void SetRestFlag(bool rest) { m_Rest = rest; }

private:
	CSceneManager();
	CSceneManager(const CSceneManager& rhs) = delete;
	CSceneManager& operator = (const CSceneManager& rhs) = delete;
private:
	//���j�[�N�|�C���^
	std::unique_ptr<CSceneBase> m_Scene;	
	//�E�B���h�E�n���h��
    HWND        m_hWnd;
	//DirectX9
    CDirectX9*  m_pDx9;
	//DirectX11
    CDirectX11* m_pDx11;  

	//�c��^�[����
	int        m_Turn;

	// =======================
	// �t���O
	// =======================		
	//�x����I���������̃t���O
	bool m_Rest;
	//�f�[�^�ǂݍ��݂����񂩂ǂ����̃t���O
	bool m_IsDataLoaded;


	//�X�^�~�i�Q�[�W�̕�
	float m_GageWidth;

};
