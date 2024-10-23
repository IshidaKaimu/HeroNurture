#pragma once
#include "Global/Global.h"

class CCamera
{
public :
	//インスタンス取得(唯一のアクセス経路).
	static CCamera* GetInstance()
	{
		//唯一のインスタンス生成.
		static CCamera s_Instance;
		return &s_Instance;
	}

	~CCamera();

	void Update();
	void Camera();

	void ThirdPersonCamera(CAMERA* pCamera, const D3DXVECTOR3& TargetPos, float TargetRotY);
  
	//プロジェクション関数
	void Projection();

	//位置情報の設定
	void SetPos(D3DXVECTOR3 pos) { m_Camera.Position = pos; }
	//注視点の設定
	void SetLook(D3DXVECTOR3 Look) { m_Camera.Look = Look; }

	//カメラ情報の取得
	D3DXMATRIX  GetViewMatrix() { return m_mView; }
	D3DXMATRIX  GetProjection() { return m_mProj; }
	CAMERA	    GetCamera() { return m_Camera; }


	//カメラ情報.
	CAMERA			m_Camera;

private:
	CCamera();
	//コピーコンストラクタによるコピーを禁止できる
	//「=delete」で関数の定義を削除できる
	CCamera(const CCamera& rhs) = delete;
	//代入演算子によるコピーを禁止する
	//operator(オペレータ):演算子のオーバーロードで、演算の中身を拡張できる
	CCamera& operator = (const CCamera& rhs) = delete;

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
