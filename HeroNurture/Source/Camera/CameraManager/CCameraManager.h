#pragma once
#include "Singleton\CSingleton.h"
#include "Camera\CCamera.h"
#include <memory>

//=====================================
// カメラマネージャークラス
//=====================================

class CCameraManager
	: public CCamera
	, public CSingleton<CCameraManager>
{
public:
	//フレンド宣言
	friend class CSingleton<CCameraManager>;

public:

	~CCameraManager();

	//カメラの更新
	void CameraUpdate();

	//カメラ情報の取得
	CAMERA GetCamera() { return GetInstance().m_pCamera.get()->GetCamera(); }

	// =======================
	// ゲッター・セッター関数
	// =======================
	//座標
	D3DXVECTOR3 GetPos() { return m_pCamera->GetPos(); }
	void SetPos( D3DXVECTOR3 pos ) { m_pCamera->SetPos(pos); }
	void SetPos( float x, float y, float z ) { m_pCamera->SetPos(x,y,z); }
	void SetPosX( float x ) { m_pCamera->SetPosX(x); }
	void SetPosY( float y ) { m_pCamera->SetPosY(y); }
	void SetPosZ( float z ) { m_pCamera->SetPosZ(z); }
	//注視点
	D3DXVECTOR3 GetLook() { return m_pCamera->GetLook(); }
	void SetLook(D3DXVECTOR3 look) { m_pCamera->SetLook(look); }
	void SetLook(float x, float y, float z) { m_pCamera->SetLook (x, y, z); }
	void SetLookX(float x) { m_pCamera->SetLookX(x); }
	void SetLookY(float y) { m_pCamera->SetLookY(y); }
	void SetLookZ(float z) { m_pCamera->SetLookZ(z); }

private:
	//アクセスされることがないようにprivate
	CCameraManager();

private:
	//カメラクラス
	std::unique_ptr<CCamera> m_pCamera;

};
