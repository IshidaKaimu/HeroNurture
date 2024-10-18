#include "CCamera.h"
#include "CSceneManager.h"

CCamera::CCamera()
	: m_Camera	()
	, m_mView	()
	, m_mProj	()
	, m_ShakeAmp()
	, m_ShakeFre()
	, m_ShakeDuration()
	, m_ShakeTime()
	, m_Origin  ()
	, m_IsShaking(false)
{
}

CCamera::~CCamera()
{
}

void CCamera::Update()
{

	//カメラの揺れ
	if (m_IsShaking == true)
	{
		//経過時間を更新
		m_ShakeTime += 0.016f; //16ミリ秒

		//揺れの振動を計算
		float shakeX = m_ShakeAmp * sin(m_ShakeFre * m_ShakeTime);
		float shakeY = m_ShakeAmp * cos(m_ShakeFre * m_ShakeTime);

		m_ShakeOffset = D3DXVECTOR3(shakeX,shakeY,0);

		//元のカメラ位置に揺れを加える
		m_Camera.Position = m_Origin + m_ShakeOffset;
	}
	else
	{
		//シェイク終了後、元のカメラ位置に戻す
		m_IsShaking = false;
		m_ShakeOffset = D3DXVECTOR3(0, 0, 0);
		m_Camera.Position = m_Origin;
	}

	CSceneManager::GetInstance()->SetCameraPos(m_Camera.Position);

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

}

void CCamera::Camera(D3DXMATRIX& view, D3DXMATRIX& proj)
{
		D3DXVECTOR3 cam_pos		= m_Camera.Position;
		D3DXVECTOR3 cam_look	= m_Camera.Look;
		D3DXVECTOR3	vUpVec(0.0f, 1.0f, 0.0f);	//上方（ベクトル）.

		//ビュー（カメラ）変換.
		D3DXMatrixLookAtLH(		//LH(Left Hand)
			&view,	//(out)ビュー計算結果.
			&cam_pos, &cam_look, &vUpVec);

		
		//y方向の視野角。数値を大きくしたら視野が狭くなる.
		float fov_y = static_cast<FLOAT>(D3DXToRadian(45.0));	//ラジアン値.
		//アスペクト（幅÷高さ）.
		float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
		float near_z = 0.1f;	//手前0.1fまで表示
		float far_z = 200.0f;	//奥側100.0fまで表示(数値を大きくしすぎると重くなる)

		//プロジェクション（射影）変換.
		D3DXMatrixPerspectiveFovLH(
			&proj,		//(out)プロジェクション計算結果.
			fov_y,		//視野角（FOV：Field of View）.
			aspect,		//アスペクト.
			near_z,		//近いビュー平面のz値.
			far_z);		//遠いビュー平面のz値.
}

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
//揺れの実行
void CCamera::StartShake(float ampl, float fre, float duration, D3DXVECTOR3 origin)
{
	m_ShakeAmp = ampl;
	m_ShakeFre = fre;
	m_ShakeDuration = duration;
	m_ShakeTime = 0.0f;
	m_Origin =  origin;
	m_IsShaking = true;
}
D3DXVECTOR3 CCamera::GetCameraPosition(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 basePosition = pos;

	D3DXVECTOR3 shakeOffset = m_ShakeOffset;

	return basePosition + shakeOffset;
}
//カメラの揺れ
D3DXVECTOR3 CCamera::ApplyShake(const D3DXVECTOR3& origin )
{
	if (m_IsShaking)
	{
		return origin + m_ShakeOffset;
	}
	return origin;
}



