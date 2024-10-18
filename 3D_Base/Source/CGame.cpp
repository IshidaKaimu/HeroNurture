#include "CGame.h"
#include "CSoundManager.h"
#include "CMeshManager.h"
#include "CSceneManager.h"
#include "CSkinMeshManager.h"
#include "CUIManager.h"
#include "CSceneBase.h"

//Effekseerを使うためのクラス
#include "CEffect.h"

//コンストラクタ.
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
	//ライト情報.
	m_Light.vDirection	= D3DXVECTOR3( 1.5f, 1.0f, -1.0f );	//ライト方向.
}


//デストラクタ.
CGame::~CGame()
{
	//ザコ複数
	//rbegin() :末尾を指す逆イテレータを取得
	//rend()   :戦闘を指す逆イテレータを取得

	for (auto it = m_Zako.rbegin(); it != m_Zako.rend(); ++it)
	{
		SAFE_DELETE(*it);
	}

	
	//弾の破棄.
	SAFE_DELETE( m_pShot );

	//地面の破棄.
	SAFE_DELETE( m_pGround );

	SAFE_DELETE( m_pEnemy );

	//プレイヤーの破棄.
	SAFE_DELETE( m_pPlayer );

	//スタティックメッシュオブジェクトの破棄.
	SAFE_DELETE( m_pStcMeshObj );


	//爆発の破棄.
	SAFE_DELETE( m_pExplosion );

	//スタティックメッシュの破棄.
	SAFE_DELETE( m_pStaticMeshBSphere );
	SAFE_DELETE( m_pStaticMeshGround );
	SAFE_DELETE( m_pStaticMeshFighter );

	//スプライト2Dの解放.
	SAFE_DELETE( m_pSprite2DPmon );

	//爆発スプライトの解放.
	SAFE_DELETE( m_pSpriteExplosion );
	//プレイヤースプライトの解放.
	SAFE_DELETE( m_pSpritePlayer );
	//地面スプライトの解放.
	SAFE_DELETE( m_pSpriteGround );

	//カメラクラスの破棄
	SAFE_DELETE(m_pCamera);

	//レイ表示クラスの破棄
	SAFE_DELETE( m_pRayY );

	//外部で作成しているので、ここで破棄しない.
	m_hWnd = nullptr;
	m_pDx11 = nullptr;
	m_pDx9 = nullptr;
}

//構築.
void CGame::Create()
{

	//レイ表示クラスのインスタンス生成
	m_pRayY = new CRay();

	//カメラクラス
	m_pCamera = new CCamera();

	m_pExplosion = new CExplosion();

	//スタティックメッシュのインスタンス作成.
	m_pStaticMeshGround		= new CStaticMesh();
	m_pStaticMeshBSphere	= new CStaticMesh();

	//スプライトオブジェクトクラスのインスタス作成.
	m_pExplosion= new CExplosion();
	m_pSpriteExplosion = new CSprite3D();

	//スタティックメッシュオブジェクトクラスのインスタンス作成.
	m_pStcMeshObj = new CStaticMeshObject();

	//テキストクラスにDirectXの情報を渡す
	WriteText::GetInstance()->SetDx11(*m_pDx11);

	//地面クラスのインスタンス作成.
	m_pGround = new CGround();
	m_pGround->SetPlayer(*m_pPlayer);

	//Effectクラス
	CEffect::GetInstance()->Create( m_pDx11->GetDevice(), m_pDx11->GetContext() );

}

//ロードデータ関数.
HRESULT CGame::LoadData()
{
	
	//サウンドデータの読み込み.
	if( CSoundManager::GetInstance()->Load( m_hWnd ) == false ){
		return E_FAIL;
	}


	//Effectクラス
	if (FAILED(CEffect::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}


	//メッシュデータの読み込み
	if (CMeshManager::GetInstance()->Load(m_pDx9, m_pDx11)) {
		return E_FAIL;
	}

	//スキンメッシュデータのよみこみ
	if (CSkinMeshManager::GetInstance()->Load(m_pDx9, m_pDx11)) {
		return E_FAIL;
	}

	//UIデータの読み込み
	if (CUIManager::GetInstance()->Load(m_pDx11)) {
		return E_FAIL;
	}


	//SceneManagerクラスのクリエイト
	CSceneManager::GetInstance()->Create();


	//SceneManagerのLoadData
	CSceneManager::GetInstance()->LoadData();



	//バウンディングスフィア(当たり判定用).
	m_pStaticMeshBSphere->Init( *m_pDx9, *m_pDx11,
		_T("Data\\Collision\\Sphere.x" ) );

	//爆発スプライトの構造体
	CSprite3D::SPRITE_STATE SSExplosion = { 1.0f, 1.0f, 400.0f, 40.0f, 40.0f, 40.0f };

	m_pSpriteExplosion->Init(*m_pDx11,
		_T("Data\\Texture\\explosion.png"), SSExplosion);


	//カメラを合わせる
	CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


	//爆発スプライトを設定.
	m_pExplosion->AttachSprite( *m_pSpriteExplosion );

	//スタティックメッシュを設定.
	m_pStcMeshObj->AttachMesh( *m_pStaticMeshFighter );
	m_pGround->AttachMesh( CMeshManager::GetInstance()->GetMesh(CMeshManager::Ground));

	CSceneManager::GetInstance()->SetDx11(*m_pDx11);

	CSceneManager::GetInstance()->SetWnd(m_hWnd);


	return S_OK;
}

//解放関数.
void CGame::Release()
{
}


//更新処理.
void CGame::Update()
{
	//BGMのループ再生.

	CSceneManager::GetInstance()->Update();

	//カメラの座標セット
    //シーンマネージャーでカメラの座標を作ってその座標を各シーンのカメラ座標(シーンベースで作った)をセットした値をここに入れている
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

//描画処理.
void CGame::Draw()
{
	//カメラ
	m_pCamera->Camera(m_mView, m_mProj);

	//地面の描画
	m_pGround->Draw( m_mView, m_mProj, m_Light, m_pCamera->m_Camera );

	CSceneManager::GetInstance()->Draw(m_mView, m_mProj, m_Light, m_pCamera->m_Camera);

	//Effectクラス
	CEffect::GetInstance()->Draw(m_mView, m_mProj, m_Light, m_pCamera->m_Camera);


}

