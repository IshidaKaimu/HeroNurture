#pragma once
#include "CDirectX9.h"
#include "CDirectX11.h"
#include "DebugText/CDebugText.h"
#include "Sprite3D/CSprite3D.h"
#include "Sprite2D/CSprite2D.h"
#include "SpriteObject/CSpriteObject.h"
#include "StaticMeshObject/Character/CCharacter.h"
#include "SkinMeshObject/Player/CPlayer.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "StaticMeshObject/Shot/CShot.h"
#include "UIObject/CUIObject.h"
#include "StaticMesh/CStaticMesh.h"
#include "StaticMeshObject/CStaticMeshObject.h"
#include "SkinMesh/CSkinMesh.h"
#include "SkinMeshObject/Zako/CZako.h"
#include "Ray/CRay.h"
#include "Camera/CCamera.h"
#include "Scene/Title/CSceneSelect.h"

#include <vector> //可変長配列


/********************************************************************************
*	ゲームクラス.
**/
class CGame
{
public:
	static constexpr int ENEMY_MAX = 3;	//エネミーの最大数.

	CGame( CDirectX9& pDx9, CDirectX11& pDx11, HWND hWnd );
	~CGame();

	void Create();
	HRESULT LoadData();
	void Release();

	void Update();
	void Draw();


private:
	CDirectX9*		m_pDx9;
	CDirectX11*		m_pDx11;

	CDebugText*		m_pDbgText;	//デバッグテキスト.

	//レイ表示クラス
	CRay*			m_pRayY;	//Y方向(垂直)

	//ウィンドウハンドル.
	HWND			m_hWnd;

	//カメラ情報.
	CCamera*		m_pCamera;
	//ライト情報.
	LIGHT			m_Light;

	//行列.
	D3DXMATRIX		m_mView;	//ビュー(カメラ)行列.
	D3DXMATRIX		m_mProj;	//射影（プロジェクション）行列.

	//ゲームで扱うスプライトデータ(使いまわす資源).
	CSprite3D*		m_pSpriteGround;
	CSprite3D*		m_pSpritePlayer;
	CSprite3D*		m_pSpriteExplosion;

	//スプライト2Dデータ(使いまわす資源).
	CSprite2D*		m_pSprite2DPmon;

	//スキンメッシュ(使いまわす資源)
	int            m_ZakoAnimNo;			//ザコ:アニメーション番号
	double         m_ZakoAnimTime;			//ザコ:アニメーション経過時間
	D3DXVECTOR3    m_ZakoBonePos;			//ザコ:ボーン座標

	//スタティックメッシュ(使いまわす資源).
	CStaticMesh*	m_pStaticMeshFighter;	//自機.
	CStaticMesh*	m_pStaticMeshGround;	//地面.
	CStaticMesh*	m_pStaticMeshBSphere;	//バウンディングスフィア(当たり判定用).

	//スプライトオブジェクトクラス.
	CSpriteObject*		m_pExplosion;
	

	//スタティックメッシュオブジェクトクラス.
	CStaticMeshObject*	m_pStcMeshObj;

	//キャラクタークラス.
	CCharacter*			m_pPlayer;
	CCharacter*			m_pEnemy;
	CCharacter*			m_pEnemies[ENEMY_MAX];
	CCharacter**		m_ppEnemies;
	int					m_EnemyMax;

	//地面クラス.
	CGround*			m_pGround;

	//弾クラス.
	CShot*				m_pShot;

	//std::vector<宣言したい型名> 変数名
	std::vector<CZako*> m_Zako;

private:
	//=delete「削除定義」と呼ばれる機能.
	//指定された場合、その関数は呼び出せなくなる.
	CGame() = delete;	//デフォルトコンストラクタ禁止.
	CGame( const CGame& ) = delete;
	CGame& operator = (const CGame& rhs ) = delete;
};