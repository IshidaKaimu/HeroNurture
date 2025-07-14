#pragma once
#include "Global\Global.h"
#include "Singleton\CSingleton.h"

//=====================================
// ライトマネージャークラス
// 制作者:石田櫂夢
//=====================================

class CLightManager
	: public CSingleton<CLightManager>
{
private:
	//フレンド宣言でアクセス権を与える.
	friend class CSingleton<CLightManager>;
	~CLightManager();

public:
	//情報の取得
	LIGHT GetLight() { return m_Light; }
	
	//位置の設定
	void SetPos(const D3DXVECTOR3& pos) { m_Light.Position = pos; }
	void SetPos(float x, float y,float z)
	{
		m_Light.Position.x = x;
		m_Light.Position.y = y;
		m_Light.Position.z = z;
	}
	void SetPosX(float x){ m_Light.Position.x = x; }
	void SetPosY(float y){ m_Light.Position.y = y; }
	void SetPosZ(float z){ m_Light.Position.z = z; }
	
	//方向の設定
	void SetDir(const D3DXVECTOR3& dir) { m_Light.vDirection = dir; }
	void SetDir(float x, float y, float z)
	{
		m_Light.vDirection.x = x;
		m_Light.vDirection.y = y;
		m_Light.vDirection.z = z;
	}
	void SetDirX(float x) { m_Light.vDirection.x = x; }
	void SetDirY(float y) { m_Light.vDirection.y = y; }
	void SetDirZ(float z) { m_Light.vDirection.z = z; }

	//ライトのデバッグ処理
	void Debug();

private:
	//他からアクセスされることがないように
	CLightManager();

private:
	//ライト情報
	LIGHT m_Light;

	//デバッグ用変数
	//位置
	D3DXVECTOR3 m_DebugDirection;
};

