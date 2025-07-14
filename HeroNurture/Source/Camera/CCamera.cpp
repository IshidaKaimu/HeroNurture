#include "CCamera.h"
#include "Scene/CSceneManager.h"

CCamera::CCamera()
	: m_Camera	()
{
}

CCamera::~CCamera()
{
}

void CCamera::Update()
{

#if DEBUG
	//カメラ座標のデバックコマンド.
	float add_value = 0.1f;
	if (GetAsyncKeyState('W') & 0x8000) {
		m_Camera.Position.y += add_value;
		m_Camera.Look.y += add_value;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		m_Camera.Position.y -= add_value;
		m_Camera.Look.y -= add_value;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		m_Camera.Position.x -= add_value;
		m_Camera.Look.x -= add_value;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		m_Camera.Position.x += add_value;
		m_Camera.Look.x += add_value;
	}
	if (GetAsyncKeyState('Q') & 0x8000) {
		m_Camera.Position.z += add_value;
		m_Camera.Look.z += add_value;
	}
	if (GetAsyncKeyState('E') & 0x8000) {
		m_Camera.Position.z -= add_value;
		m_Camera.Look.z -= add_value;
	}
#endif
	//プロジェクションの計算
	Projection();

	//カメラ変換
	Camera();
}

void CCamera::Camera()
{
		D3DXVECTOR3	vUpVec(0.0f, 1.0f, 0.0f);	//上方（ベクトル）.

		//ビュー（カメラ）変換.
		D3DXMatrixLookAtLH(		//LH(Left Hand)
			&m_Camera.View,		//(out)ビュー計算結果.
			&m_Camera.Position, //位置情報
			&m_Camera.Look,		//注視点
			&vUpVec);			//上方ベクトル

}

void CCamera::Projection()
{
	//y方向の視野角。数値を大きくしたら視野が狭くなる.
	float fov_y = static_cast<FLOAT>(D3DXToRadian(45.0));	//ラジアン値.
	//アスペクト（幅÷高さ）.
	float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
	float near_z = 0.1f;	//手前0.1fまで表示
	float far_z = 200.0f;	//奥側100.0fまで表示(数値を大きくしすぎると重くなる)

	//プロジェクション（射影）変換.
	D3DXMatrixPerspectiveFovLH(
		&m_Camera.Proj,		//(out)プロジェクション計算結果.
		fov_y,				//視野角（FOV：Field of View）.
		aspect,				//アスペクト.
		near_z,				//近いビュー平面のz値.
		far_z);				//遠いビュー平面のz値.
}



