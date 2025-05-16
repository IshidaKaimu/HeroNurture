#pragma once
#include "Sprite3D\CSprite3D.h"
#include "CDirectX11.h"

class CSprite3DManager
{
public:
	//スプライト3Dリスト
	enum Sprite3DList
	{
		BackGround,

		Max,
	};

	//シングルトン化
	static CSprite3DManager* GetInstance() {
		static CSprite3DManager s_Instance;
		return &s_Instance;
	}

public:
	~CSprite3DManager();

	HRESULT Load(CDirectX11* dx11);

	void SetDx11(CDirectX11& dx11) { m_pDx11 = &dx11; }

	static CSprite3D& GetSprite(Sprite3DList list) { return *GetInstance()->m_pSprite3D[list]; }

private:
	//シングルトン化
	CSprite3DManager();
	CSprite3DManager(const CSprite3DManager& rhs) = delete;
	CSprite3DManager& operator = (const CSprite3DManager& rhs) = delete;

private:
	CDirectX11* m_pDx11;

	CSprite3D* m_pSprite3D[Sprite3DList::Max];

};