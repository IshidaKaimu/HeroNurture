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

#if _DEBUG
	//カメラ座標のデバックコマンド.
	float add_value = 0.1f;
	if (GetAsyncKeyState('W') & 0x8000) {
		m_Camera.Position.y += add_value;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		m_Camera.Position.y -= add_value;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		m_Camera.Position.x -= add_value;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		m_Camera.Position.x += add_value;
	}
	if (GetAsyncKeyState('Q') & 0x8000) {
		m_Camera.Position.z += add_value;
	}
	if (GetAsyncKeyState('E') & 0x8000) {
		m_Camera.Position.z -= add_value;
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

//3人称カメラ
void CCamera::ThirdPersonCamera(CAMERA* pCamera, const D3DXVECTOR3& TargetPos, float TargetRotY)
{
	//Z軸ベクトル
	D3DXVECTOR3 vecAxisZ(0.0f, 0.0f, 1.0f);

	//Y方向の回転行列
	D3DXMATRIX mRotationY;
	//Y軸回転行列を作成
	D3DXMatrixRotationY(
		&mRotationY,	//(out行列)
		TargetRotY); //対象のY方向の回転値

	//Y軸回転行列を使ってZ軸ベクトルを座標変換している
	D3DXVec3TransformCoord(
		&vecAxisZ,		//(out)Z軸ベクトル
		&vecAxisZ,		//(in)Z軸ベクトル
		&mRotationY);	//Y軸回転行列

	//カメラの位置、注視点を対象にそろえる
	pCamera->Position = TargetPos;
	pCamera->Look = TargetPos;

	//カメラの位置、注視点をZ軸ベクトルを用いて調整
	pCamera->Position -= vecAxisZ * 4.0f;//対象の背中側
	pCamera->Look += vecAxisZ * 3.0f;//対象を挟んで向こう側

	//カメラの位置、注視点の高さをそれぞれ微調整
	pCamera->Position.y += 2.0f;
	pCamera->Look.y += 0.5f;

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



