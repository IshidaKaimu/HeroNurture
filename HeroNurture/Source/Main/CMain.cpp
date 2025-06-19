#include "CMain.h"
#include "CDirectX9.h"
#include "CDirectX11.h"
#include "Scene\CSceneManager.h"
#include "Sound\CSoundManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Effect\CEffect.h"	
#include <tchar.h>

#ifdef DEBUG
#include "ImGui\ImGuiManager\ImGuiManager.h"
#endif // DEBUG


//�E�B���h�E����ʒ����ŋN����L���ɂ���.
//#define ENABLE_WINDOWS_CENTERING

//=================================================
//	�萔.
//=================================================
const TCHAR WND_TITLE[] = _T( "HeroNurture" );
const TCHAR APP_NAME[]	= _T( "HeroNurture" );


/********************************************************************************
*	���C���N���X.
**/
//=================================================
//	�R���X�g���N�^.
//=================================================
CMain::CMain()
	//���������X�g.
	: m_hWnd	( nullptr )
	, m_pDx9	( nullptr )
	, m_pDx11	( nullptr )
{
	m_pDx9  = new CDirectX9();
	m_pDx11 = new CDirectX11();
}


//=================================================
//	�f�X�g���N�^.
//=================================================
CMain::~CMain()
{
	SAFE_DELETE( m_pDx11 );
	SAFE_DELETE( m_pDx9 );

	DeleteObject( m_hWnd );
}


void CMain::Init()
{
	CSceneManager::GetInstance().Initialize();
}

//�X�V����.
void CMain::Update()
{
#ifdef DEBUG
	//ImGui�̍X�V
	CImGuiManager::ImGui_NewFrame();
#endif // DEBUG


	//�X�V����.
	CSceneManager::GetInstance().Update();


	//�o�b�N�o�b�t�@���N���A�ɂ���.
	m_pDx11->ClearBackBuffer();

	//�`�揈��.
	CSceneManager::GetInstance().Draw();

	//�G�t�F�N�g�̕`��
	CEffect::GetInstance()->Draw();

#ifdef DEBUG
	//ImGui�̕`��
	CImGuiManager::Render();
#endif // DEBUG


	//��ʂɕ\��.
	m_pDx11->Present();

}


//�\�z����.
HRESULT CMain::Create()
{
	//DirectX9�\�z.
	if (FAILED(m_pDx9->Create( m_hWnd ) ) )
	{
		return E_FAIL;
	}

	//DirectX11�\�z.
	if( FAILED( m_pDx11->Create( m_hWnd ) ) )
	{
		return E_FAIL;
	}

#ifdef DEBUG
	//ImGui�̏�����
	CImGuiManager::Init(m_hWnd, *m_pDx11);
#endif // DEBUG
	CUIManager* UIMng = &CUIManager::GetInstance();
	CMeshManager* MMng = CMeshManager::GetInstance();
	CSkinMeshManager* SMMng = &CSkinMeshManager::GetInstance();
	CEffect* Effect = CEffect::GetInstance();

	//�摜�f�[�^�̓ǂݍ���
	UIMng->Load(m_pDx11);
	MMng->Load(m_pDx9, m_pDx11);
	SMMng->Load(m_pDx9, m_pDx11);

	//Effect�N���X
	CEffect::GetInstance()->Create(m_pDx11->GetDevice(), m_pDx11->GetContext());
	//�G�t�F�N�g�̓ǂݍ���
	Effect->LoadData();

	//�V�[���̍\�z�iLoad���܂߂�j.
	CSceneManager::GetInstance().Create(*m_pDx9, *m_pDx11, m_hWnd);

	//�V�[���̏�����
	CSceneManager::GetInstance().Initialize();

	return S_OK;
}

//�f�[�^���[�h����.
HRESULT CMain::LoadData()
{
	//�T�E���h�f�[�^�̓ǂݍ���
	if (CSoundManager::GetInstance()->Load(m_hWnd) == false) {
		return E_FAIL;
	}

	return S_OK;
}


//�������.
void CMain::Release()
{
	CSceneManager::GetInstance().Release();
	
	if( m_pDx11 != nullptr ){
		m_pDx11->Release();
	}

	if (m_pDx9 != nullptr) {
		m_pDx9->Release();
	}

}


//���b�Z�[�W���[�v.
void CMain::Loop()
{
	//�f�[�^���[�h.
	if( FAILED( LoadData() )){
		return;
	}

	//------------------------------------------------
	//	�t���[�����[�g��������.
	//------------------------------------------------
	float Rate = 0.0f;	//���[�g.
	DWORD sync_old = timeGetTime();			//�ߋ�����.
	DWORD sync_now;							//���ݎ���.

	//���ԏ����̂��߁A�ŏ��P�ʂ�1�~���b�ɕύX.
	timeBeginPeriod( 1 );
	Rate = 1000.0f / static_cast<float>(FPS); //���z���Ԃ��Z�o.

	//���b�Z�[�W���[�v.
	MSG msg = { 0 };
	ZeroMemory( &msg, sizeof( msg ) );

	while( msg.message != WM_QUIT )
	{
		sync_now = timeGetTime();	//���݂̎��Ԃ��擾.

		if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else if( sync_now - sync_old >= Rate )
		{
			sync_old = sync_now;	//���ݎ��Ԃɒu������.

			//�X�V����.
			Update();
		}
	}
	//�A�v���P�[�V�����̏I��.
	Release();
}

//�E�B���h�E�������֐�.
HRESULT CMain::InitWindow(
	HINSTANCE hInstance,	//�C���X�^���X.
	INT x, INT y,			//�E�B���h�Ex,y���W.
	INT width, INT height)	//�E�B���h�E��,����.
{
	//�E�B���h�E�̒�`.
	WNDCLASSEX wc;
	ZeroMemory( &wc, sizeof( wc ) );//������(0��ݒ�).

	wc.cbSize			= sizeof( wc );
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= MsgProc;//WndProc;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon( nullptr, IDI_APPLICATION );
	wc.hCursor			= LoadCursor( nullptr, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH)GetStockObject( LTGRAY_BRUSH );
	wc.lpszClassName	= APP_NAME;
	wc.hIconSm			= LoadIcon( nullptr, IDI_APPLICATION );

	//�E�B���h�E�N���X��Windows�ɓo�^.
	if( !RegisterClassEx( &wc ) ) {
		_ASSERT_EXPR( false, _T( "�E�B���h�E�N���X�̓o�^�Ɏ��s" ) );
		return E_FAIL;
	}

	//--------------------------------------.
	//	�E�B���h�E�\���ʒu�̒���.
	//--------------------------------------.
	//���̊֐����ł̂ݎg�p����\���̂������Œ�`.
	struct RECT_WND
	{
		INT x, y, w, h;
		RECT_WND() : x(), y(), w(), h() {}
	} rectWindow;//�����ɕϐ��錾������.

#ifdef ENABLE_WINDOWS_CENTERING
	//�f�B�X�v���C�̕��A�������擾.
	HWND hDeskWnd = nullptr;
	RECT recDisplay;
	hDeskWnd = GetDesktopWindow();
	GetWindowRect( hDeskWnd, &recDisplay );

	//�Z���^�����O.
	rectWindow.x = ( recDisplay.right - width ) / 2;	//�\���ʒux���W.
	rectWindow.y = ( recDisplay.bottom - height ) / 2;	//�\���ʒuy���W.
#endif//ENABLE_WINDOWS_CENTERING

	//--------------------------------------.
	//	�E�B���h�E�̈�̒���.
	//--------------------------------------.
	RECT	rect;		//��`�\����.
	DWORD	dwStyle;	//�E�B���h�E�X�^�C��.
	rect.top = 0;			//��.
	rect.left = 0;			//��.
	rect.right = width;		//�E.
	rect.bottom = height;	//��.
	dwStyle = WS_OVERLAPPEDWINDOW;	//�E�B���h�E���.

	if( AdjustWindowRect(
		&rect,			//(in)��ʃT�C�Y����������`�\����.(out)�v�Z����.
		dwStyle,		//�E�B���h�E�X�^�C��.
		FALSE ) == 0 )	//���j���[�������ǂ����̎w��.
	{
		MessageBox(
			nullptr,
			_T( "�E�B���h�E�̈�̒����Ɏ��s" ),
			_T( "�G���[���b�Z�[�W" ),
			MB_OK );
		return 0;
	}

	//�E�B���h�E�̕���������.
	rectWindow.w = rect.right - rect.left;
	rectWindow.h = rect.bottom - rect.top;

	//�E�B���h�E�̍쐬.
	m_hWnd = CreateWindow(
		APP_NAME,					//�A�v����.
		WND_TITLE,					//�E�B���h�E�^�C�g��.
		dwStyle,					//�E�B���h�E���(����).
		rectWindow.x, rectWindow.y,	//�\���ʒux,y���W.
		rectWindow.w, rectWindow.h,	//�E�B���h�E��,����.
		nullptr,					//�e�E�B���h�E�n���h��.
		nullptr,					//���j���[�ݒ�.
		hInstance,					//�C���X�^���X�ԍ�.
		nullptr );					//�E�B���h�E�쐬���ɔ�������C�x���g�ɓn���f�[�^.
	if( !m_hWnd ) {
		_ASSERT_EXPR( false, _T( "�E�B���h�E�쐬���s" ) );
		return E_FAIL;
	}

	//�E�B���h�E�̕\��.
	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );

	return S_OK;
}

#ifdef DEBUG
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif // DEBUG


//�E�B���h�E�֐��i���b�Z�[�W���̏����j.
LRESULT CALLBACK CMain::MsgProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam )
{

#ifdef DEBUG
	// ImGui�E�B���h�E�̏���������(�h���b�O��X�N���[���Ȃ�).
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
#endif // DEBUG
	switch( uMsg ) {
	case WM_DESTROY://�E�B���h�E���j�����ꂽ�Ƃ�.
		//�A�v���P�[�V�����̏I����Windows�ɒʒm����.
		PostQuitMessage( 0 );
		break;
	}
	//���C���ɕԂ����.
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}