#include "CGame.h"
#include "CSoundManager.h"
#include "CMeshManager.h"
#include "CSceneManager.h"
#include "CSkinMeshManager.h"
#include "CUIManager.h"
#include "CSceneBase.h"

//Effekseer���g�����߂̃N���X
#include "CEffect.h"

//�R���X�g���N�^.
CGame::CGame( CDirectX9& pDx9, CDirectX11& pDx11, HWND hWnd )
	: m_pDx9				( &pDx9 )
	, m_pDx11				( &pDx11 )
	, m_pDbgText			( nullptr )
	, m_pRayY				( nullptr )
	, m_hWnd				( hWnd )
	, m_mView				()
	, m_mProj				()
	, m_Light				()

	, m_pSpriteGround		( nullptr )
	, m_pSpritePlayer		( nullptr )
	, m_pSpriteExplosion	( nullptr )

	, m_pSprite2DPmon		( nullptr )

	, m_pStaticMeshFighter	( nullptr )
	, m_pStaticMeshGround	( nullptr )
	, m_pStaticMeshBSphere	( nullptr )

	, m_ZakoAnimNo			()
	, m_ZakoAnimTime		()
	, m_ZakoBonePos			()
	
	, m_pExplosion			( nullptr )

	, m_pStcMeshObj			( nullptr )
	, m_pPlayer				( nullptr )
	, m_pEnemy				( nullptr )
	, m_pEnemies			()
	, m_ppEnemies			( nullptr )
	, m_EnemyMax			( 0 )

	, m_pGround				( nullptr )

	, m_pShot				( nullptr )
	, m_Zako				()
{
	//���C�g���.
	m_Light.vDirection	= D3DXVECTOR3( 1.5f, 1.0f, -1.0f );	//���C�g����.
}


//�f�X�g���N�^.
CGame::~CGame()
{
	//�U�R����
	//rbegin() :�������w���t�C�e���[�^���擾
	//rend()   :�퓬���w���t�C�e���[�^���擾

	for (auto it = m_Zako.rbegin(); it != m_Zako.rend(); ++it)
	{
		SAFE_DELETE(*it);
	}

	
	//�e�̔j��.
	SAFE_DELETE( m_pShot );

	//�n�ʂ̔j��.
	SAFE_DELETE( m_pGround );

	SAFE_DELETE( m_pEnemy );

	//�v���C���[�̔j��.
	SAFE_DELETE( m_pPlayer );

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�̔j��.
	SAFE_DELETE( m_pStcMeshObj );


	//�����̔j��.
	SAFE_DELETE( m_pExplosion );

	//�X�^�e�B�b�N���b�V���̔j��.
	SAFE_DELETE( m_pStaticMeshBSphere );
	SAFE_DELETE( m_pStaticMeshGround );
	SAFE_DELETE( m_pStaticMeshFighter );

	//�X�v���C�g2D�̉��.
	SAFE_DELETE( m_pSprite2DPmon );

	//�����X�v���C�g�̉��.
	SAFE_DELETE( m_pSpriteExplosion );
	//�v���C���[�X�v���C�g�̉��.
	SAFE_DELETE( m_pSpritePlayer );
	//�n�ʃX�v���C�g�̉��.
	SAFE_DELETE( m_pSpriteGround );

	//�J�����N���X�̔j��
	SAFE_DELETE(m_pCamera);

	//���C�\���N���X�̔j��
	SAFE_DELETE( m_pRayY );

	//�O���ō쐬���Ă���̂ŁA�����Ŕj�����Ȃ�.
	m_hWnd = nullptr;
	m_pDx11 = nullptr;
	m_pDx9 = nullptr;
}

//�\�z.
void CGame::Create()
{

	//���C�\���N���X�̃C���X�^���X����
	m_pRayY = new CRay();

	//�J�����N���X
	m_pCamera = new CCamera();

	m_pExplosion = new CExplosion();

	//�X�^�e�B�b�N���b�V���̃C���X�^���X�쐬.
	m_pStaticMeshGround		= new CStaticMesh();
	m_pStaticMeshBSphere	= new CStaticMesh();

	//�X�v���C�g�I�u�W�F�N�g�N���X�̃C���X�^�X�쐬.
	m_pExplosion= new CExplosion();
	m_pSpriteExplosion = new CSprite3D();

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X�̃C���X�^���X�쐬.
	m_pStcMeshObj = new CStaticMeshObject();

	//�e�L�X�g�N���X��DirectX�̏���n��
	WriteText::GetInstance()->SetDx11(*m_pDx11);

	//�n�ʃN���X�̃C���X�^���X�쐬.
	m_pGround = new CGround();
	m_pGround->SetPlayer(*m_pPlayer);

	//Effect�N���X
	CEffect::GetInstance()->Create( m_pDx11->GetDevice(), m_pDx11->GetContext() );

}

//���[�h�f�[�^�֐�.
HRESULT CGame::LoadData()
{
	
	//�T�E���h�f�[�^�̓ǂݍ���.
	if( CSoundManager::GetInstance()->Load( m_hWnd ) == false ){
		return E_FAIL;
	}


	//Effect�N���X
	if (FAILED(CEffect::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}


	//���b�V���f�[�^�̓ǂݍ���
	if (CMeshManager::GetInstance()->Load(m_pDx9, m_pDx11)) {
		return E_FAIL;
	}

	//�X�L�����b�V���f�[�^�̂�݂���
	if (CSkinMeshManager::GetInstance()->Load(m_pDx9, m_pDx11)) {
		return E_FAIL;
	}

	//UI�f�[�^�̓ǂݍ���
	if (CUIManager::GetInstance()->Load(m_pDx11)) {
		return E_FAIL;
	}


	//SceneManager�N���X�̃N���G�C�g
	CSceneManager::GetInstance()->Create();


	//SceneManager��LoadData
	CSceneManager::GetInstance()->LoadData();



	//�o�E���f�B���O�X�t�B�A(�����蔻��p).
	m_pStaticMeshBSphere->Init( *m_pDx9, *m_pDx11,
		_T("Data\\Collision\\Sphere.x" ) );

	//�����X�v���C�g�̍\����
	CSprite3D::SPRITE_STATE SSExplosion = { 1.0f, 1.0f, 400.0f, 40.0f, 40.0f, 40.0f };

	m_pSpriteExplosion->Init(*m_pDx11,
		_T("Data\\Texture\\explosion.png"), SSExplosion);


	//�J���������킹��
	CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


	//�����X�v���C�g��ݒ�.
	m_pExplosion->AttachSprite( *m_pSpriteExplosion );

	//�X�^�e�B�b�N���b�V����ݒ�.
	m_pStcMeshObj->AttachMesh( *m_pStaticMeshFighter );
	m_pGround->AttachMesh( CMeshManager::GetInstance()->GetMesh(CMeshManager::Ground));

	CSceneManager::GetInstance()->SetDx11(*m_pDx11);

	CSceneManager::GetInstance()->SetWnd(m_hWnd);


	return S_OK;
}

//����֐�.
void CGame::Release()
{
}


//�X�V����.
void CGame::Update()
{
	//BGM�̃��[�v�Đ�.

	CSceneManager::GetInstance()->Update();

	//�J�����̍��W�Z�b�g
    //�V�[���}�l�[�W���[�ŃJ�����̍��W������Ă��̍��W���e�V�[���̃J�������W(�V�[���x�[�X�ō����)���Z�b�g�����l�������ɓ���Ă���
	m_pCamera->SetPos(CSceneManager::GetCameraPos());
	m_pCamera->SetLook(CSceneManager::GetCameraLook());


	m_pGround->Update();

#if 1
	for( int No = 0; No < m_EnemyMax; No++ ){
		m_ppEnemies[No]->Update();
	}
#else
	for( int No = 0; No < ENEMY_MAX; No++ ){
		m_pEnemies[No]->Update();
	}
#endif

	m_pExplosion->Update();


}

//�`�揈��.
void CGame::Draw()
{
	//�J����
	m_pCamera->Camera(m_mView, m_mProj);

	//�n�ʂ̕`��
	m_pGround->Draw( m_mView, m_mProj, m_Light, m_pCamera->m_Camera );

	CSceneManager::GetInstance()->Draw(m_mView, m_mProj, m_Light, m_pCamera->m_Camera);

	//Effect�N���X
	CEffect::GetInstance()->Draw(m_mView, m_mProj, m_Light, m_pCamera->m_Camera);


}

