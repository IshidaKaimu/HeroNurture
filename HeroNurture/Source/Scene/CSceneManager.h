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
class CNurtureHeroSelectScene;
class CNurtureScene;
class CTraningScene;
class CTraningResultScene;
class CBattleHeroSelectScene;
class CYuiAppearanceScene;
class CBattleScene;
class CBattleResultScene;

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
		NurtureHeroSelect,
		Nurture,
		Training,
		NurtureResult,
		BattleHeroSelect,
		YuiAppearance,
		KaitoAppearance,
		Battle,
		UniqueAttack,
		BattleResult,
		Max_S,
		none,
	};

	//���s���X�g
	enum enBattleResultList
	{
		Win,
		Lose,
	};

public:
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
private:
	//������A�N�Z�X����邱�Ƃ��Ȃ��悤��
	CSceneManager();

public:
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
	//���[�U�[��
	std::wstring GetName() { return m_UserName; } //wstring�^
	std::string GetStringName() { return CUtility::GetInstance().WstringToString(m_UserName); } //string�^
	void SetName(std::wstring name) { m_UserName = name; }


private:
	//���j�[�N�|�C���^
	std::unique_ptr<CSceneBase> m_Scene;
	//�E�B���h�E�n���h��
    HWND        m_hWnd;
	//DirectX9
    CDirectX9*  m_pDx9;
	//DirectX11
    CDirectX11* m_pDx11;  
	
	//���[�U�[��
	std::wstring m_UserName;
};
