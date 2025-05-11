#pragma once
#include "CSound.h"		//サウンドクラス.

//=====================================
// サウンドマネージャークラス
// 制作者:石田櫂夢
// ※授業内制作
//=====================================
class CSoundManager
{
public:
	//サウンドリスト列挙型.
	enum enList
	{
		BGM_Title,	          //タイトル
		BGM_ModeSelect,       //モード選択
		BGM_NatureHeroSelect, //育成ヒーロー選択
		BGM_Nature,			  //育成
		BGM_BattleHeroSelect, //戦闘ヒーロー選択
		BGM_Battle,			  //戦闘
		BGM_NatureResult,     //育成結果
		BGM_Win,	          //戦闘結果(勝利)
		BGM_Lose,			  //戦闘結果(敗北)
		
		SE_Slash,			  //斬撃.		
		SE_Damage,			  //ダメージ		
		SE_Select,			  //選択.		
		SE_Enter,			  //決定.		
		SE_Tornade,			  //竜巻.		
		SE_Start,			  //スタート.		
		SE_FireBall,		  //火球.
		SE_Thunder,           //電気
		SE_TPose,             //T字ポーズ
		SE_Up,                //ステータス(上昇)
		SE_Miss,              //ステータス(失敗)
		SE_RaccoonChange,     //タヌキの変身
		SE_RaccoonCollision,  //タヌキの衝突
		SE_MagicSircle,       //魔法陣出現
		SE_Laser,			  //光エフェクト
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
	static void PlaySE( enList list )   { CSoundManager::GetInstance()->m_pSound[list]->PlaySE();  }
	//ループ再生する.
	static void PlayLoop( enList list ) { CSoundManager::GetInstance()->m_pSound[list]->PlayLoop();}
	//停止する.
	static void Stop( enList list )     { CSoundManager::GetInstance()->m_pSound[list]->Stop();    }

	//音量の操作
	static void Volume(enList list, int volume) { CSoundManager::GetInstance()->m_pSound[list]->SetVolume(volume); }


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