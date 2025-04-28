#pragma once
#include "CSceneBase.h"
#include "CDirectX11.h"
#include "CDirectX9.h"
#include "Singleton\CSingleton.h"
#include "Utility\CUtility.h"
#include <memory>


//----�O���錾---
class CTitleScene;
class CModeSelect;
class CNatureHeroSelectScene;
class CNatureScene;
class CTraningScene;
class CTraningResultScene;
class CBattleHeroSelectScene;
class CAppearanceScene;
class CBattleScene;
class CBattleResultScene;

//�琬�^�[����
constexpr int MAX_TURN = 50;

//=====================================
//�V�[���}�l�[�W���[�N���X
//����ҁF�Γc�D��
//=====================================
class CSceneManager
	: public CSceneBase
	, public CSingleton<CSceneManager>
{
private:
	//�t�����h�錾
	//�A�N�Z�X����^����
	friend class CSingleton<CSceneManager>;
	~CSceneManager();
public:
	//�V�[�����X�g
	enum enSceneList :char
	{
		Title,
		CreateAcount,
		Login,
		ModeSelect,
		NatureHeroSelect,
		Nature,
		Training,
		NatureResult,
		BattleHeroSelect,
		Appearance,
		Battle,
		UniqueAttack,
		BattleResult,
		Max_S,
		none,
	};

	//�������X�g
	enum enRoleList :char
	{
		Hero,
		EnemyHero,
	};

	//���s���X�g
	enum enBattleResultList
	{
		Win,
		Lose,
	};

public:
	static CSceneManager* GetInstance() {
		static CSceneManager s_Instance;
		return &s_Instance;
	}

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
    CDirectX9* GetDx9()			 { return m_pDx9; }
	void SetDx9( CDirectX9& Dx9) { m_pDx9 = &Dx9; }
    //DirectX11
	CDirectX11* GetDx11()		   { return m_pDx11; }
	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }
    //�E�B���h�E�n���h��
    HWND GetWnd()			{ return m_hWnd; }
    void SetWnd(HWND m_wnd) { m_hWnd = m_wnd; }
	//�ǂݍ��݉񐔐����t���O
	bool GetIsDataLoaded() { return m_IsDataLoaded; }
	//�^�[����
	int GetRemainingTurn() { return m_Turn; }
	//�X�^�~�i�Q�[�W�̕�
	float GetStaminaWidth()			   { return m_GageWidth; }
	void  SetStaminaWidth(float width) { m_GageWidth = width; }
	//���[�U�[��
	std::wstring GetName()			{ return m_UserName; } //wstring�^
	std::string GetStringName()		{ return CUtility::GetInstance().WstringToString(m_UserName); } //string�^
	void SetName(std::wstring name) { m_UserName = name; }
	//�x���t���O
	bool GetRestFlag()			{ return m_Rest; }
	void SetRestFlag(bool rest) { m_Rest = rest; }
	//����
	enRoleList GetRole()		  { return m_RoleList; }
	void SetRole(enRoleList role) { m_RoleList = role; }
	//���s
	enBattleResultList GetBattleResult()			  { return m_BattleResult; }
	void SetBattleResult( enBattleResultList result ) { m_BattleResult = result; }

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
	int         m_Turn;
	//���[�U�[��
	std::wstring m_UserName;
	//�X�^�~�i�Q�[�W�̕�
	float m_GageWidth;

	//----�񋓌^----
	//�������X�g
	enRoleList  m_RoleList;
	//���s���X�g
	enBattleResultList m_BattleResult;

	//----�񋓌^----
	//�x����I���������̃t���O
	bool m_Rest;
	//�f�[�^�ǂݍ��݂����񂩂ǂ����̃t���O
	bool m_IsDataLoaded;
};
