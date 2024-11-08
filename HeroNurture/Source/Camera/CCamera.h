#pragma once
#include "Global\Global.h"


//カメラ情報構造体.
struct CAMERA
{
	D3DXVECTOR3	Position;	//視点.
	D3DXVECTOR3 Look;		//注視点.

	D3DXMATRIX	View;	    //ビュー情報
	D3DXMATRIX  Proj;		//プロジェクション情報
};

class CCamera
{
public :
	CCamera();
	~CCamera();

	void Update();
	void Camera();

	void ThirdPersonCamera(CAMERA* pCamera, const D3DXVECTOR3& TargetPos, float TargetRotY);
  
	//初期化関数
	void Initialize();

	//プロジェクション関数
	void Projection();

	//----カメラ座標の設定----
	void SetPos(D3DXVECTOR3 pos) { m_Camera.Position = pos; }
	void SetPos(float x, float y, float z) { m_Camera.Position = D3DXVECTOR3( x, y, z ); }
	void SetPosX(float x) { m_Camera.Position.x = x; }
	void SetPosY(float y) { m_Camera.Position.y = y; }
	void SetPosZ(float z) { m_Camera.Position.z = z; }


	//----カメラ注視点の設定----
	void SetLook(D3DXVECTOR3 look) { m_Camera.Look = look; }
	void SetLook(float x, float y, float z) { m_Camera.Look = D3DXVECTOR3(x, y, z); }
	void SetLookX(float x) { m_Camera.Look.x = x; }
	void SetLookY(float y) { m_Camera.Look.y = y; }
	void SetLookZ(float z) { m_Camera.Look.z = z; }


	//カメラ情報の取得
	CAMERA	GetCamera() const { return m_Camera; }

protected:
	//カメラ情報.
	CAMERA			m_Camera;

};
