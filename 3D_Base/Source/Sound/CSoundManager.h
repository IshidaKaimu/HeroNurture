#pragma once
#include "CSound.h"		//サウンドクラス.

/**************************************************
*	サウンドマネージャークラス.
*	Manager(マネージャー)：管理者.
*		Singleton(シングルトン：デザインパターンの１つ)で作成.
**/
class CSoundManager
{
public:
	//サウンドリスト列挙型.
	enum enList
	{
		BGM_Opening,	//オープニングシーン.
		BGM_BossApe,	//ボス登場シーン.
		BGM_BossEvo,	//ボス進化シーン.
		BGM_Special,	//必殺技シーン.
		BGM_BossDeath,	//ボス撃破シーン.
		
		SE_Slash,		//斬撃.
		SE_Root,	    //必殺の軌道.
		SE_Sp,			//必殺発動時
		SE_Charge,	    //必殺中貯め
		SE_EvoNow,		//ボス変身中
		SE_EvoAf,		//変身後カメラの動き
		SE_BossVo,		//ボスの声
		SE_BossDeath,	//ボス死亡
		SE_DeathNow,	//死亡中フェード
		SE_BossLoss,	//ボス消滅
		SE_BeforeDeath,	//ボス爆発前
		
		

		//音が増えたら「ここ」に追加してください.
		max,		//最大数.
	};

public:
	//インスタンス取得(唯一のアクセス経路).
	//※関数の前にstaticを付けることでインスタンス生成しなくても使用できる.
	static CSoundManager* GetInstance()
	{
		//唯一のインスタンスを作成する.
		//※staticで作成されたので2回目以降は、下の1行は無視される.
		static CSoundManager s_Instance;	//s_:staticの意味.
		return &s_Instance;
	}


	~CSoundManager();

	//サウンドデータ読込関数.
	bool Load( HWND hWnd );
	//サウンドデータ解放関数.
	void Release();

	//SEを再生する.
	static void PlaySE( enList list ) {
		CSoundManager::GetInstance()->m_pSound[list]->PlaySE();
	}
	//ループ再生する.
	static void PlayLoop( enList list ) {
		CSoundManager::GetInstance()->m_pSound[list]->PlayLoop();
	}
	//停止する.
	static void Stop( enList list ) {
		CSoundManager::GetInstance()->m_pSound[list]->Stop();
	}

	//音量の操作
	static void Volume(enList list,int volume) {
		CSoundManager::GetInstance()->m_pSound[list]->SetVolume(volume);
	}


private://外部からアクセス不可能.
	//外部からコンストラクタへのアクセスを禁止する.
	CSoundManager();
	//コピーコンストラクタによるコピーを禁止する.
	//「=delete」で関数の定義を削除できる.
	CSoundManager( const CSoundManager& rhs ) = delete;
	//代入演算子によるコピーを禁止する.
	//operator(オペレータ):演算子のオーバーロードで、演算の中身を拡張できる.
	CSoundManager& operator = ( const CSoundManager& rhs ) = delete;

private:
	CSound*		m_pSound[enList::max];
};