#pragma once
#include "Global.h"

class CCamera
{
public :
	CCamera();
	~CCamera();

	void Update();
	void Camera(D3DXMATRIX& view, D3DXMATRIX& proj);

	void ThirdPersonCamera(CAMERA* pCamera, const D3DXVECTOR3& TargetPos, float TargetRotY);
  
	void SetPos(D3DXVECTOR3 pos) { m_Camera.Position = pos; }
	void SetLook(D3DXVECTOR3 Look) { m_Camera.Look = Look; }

	void StartShake(float ampl, float fre, float duration, D3DXVECTOR3 origin);

	D3DXVECTOR3 GetCameraPosition(D3DXVECTOR3 pos);

	//カメラの揺れ関数
	D3DXVECTOR3 ApplyShake( const D3DXVECTOR3& origin);

	//カメラ情報.
	CAMERA			m_Camera;

private:

private:
	D3DXMATRIX		m_mView;	//ビュー(カメラ)行列.
	D3DXMATRIX		m_mProj;	//射影（プロジェクション）行列.

	float			m_ShakeTimer;//振動時間
	float           m_ShakePos;

	//カメラの揺れ関連
	D3DXVECTOR3 m_ShakeOffset;
	float m_ShakeAmp;		//揺れの振れ幅
	float m_ShakeFre;		//揺れの周波数(速さ、頻度)
	float m_ShakeDuration;  //揺れの持続時間
	float m_ShakeTime;		//揺れ開始からの経過時間
	D3DXVECTOR3 m_Origin;	//元のカメラ位置に戻すための変数

	bool m_IsShaking;		

};
