#include "CSoundManager.h"
#include "MyMacro/MyMacro.h"

CSoundManager::CSoundManager()
	: m_pSound	()
{
	//インスタンス生成.
	for( int i = 0; i < enList::max; i++ )
	{
		m_pSound[i] = new CSound();
	}
}

CSoundManager::~CSoundManager()
{
	Release();

	//インスタンス破棄.
	for( int i = enList::max - 1; i >= 0; i-- )
	{
		SAFE_DELETE( m_pSound[i] );
	}
}

//サウンドデータ読込関数.
bool CSoundManager::Load( HWND hWnd )
{
	struct SoundList
	{
		int listNo;				//enList列挙型を設定.
		const TCHAR path[256];	//ファイルの名前(パス付き).
		const TCHAR alias[32];	//エイリアス名.
	};
	SoundList SList[] =
	{
		{ enList::BGM_Opening,		_T( "Data\\Sound\\BGM\\Opening.mp3" ),				_T( "BGM_Opening" )		},
		{ enList::BGM_BossApe,		_T( "Data\\Sound\\BGM\\BossApe.mp3" ),				_T( "BGM_BossAp" )		},
		{ enList::BGM_BossEvo,		_T( "Data\\Sound\\BGM\\BossEvo.mp3" ),				_T( "BGM_BossEvo" )		},
		{ enList::BGM_Special,		_T( "Data\\Sound\\BGM\\Special.mp3" ),				_T( "BGM_Special" )		},
		{ enList::BGM_BossDeath,    _T( "Data\\Sound\\BGM\\BossDeath.mp3" ),			_T( "BGM_BossDeath" )	},
		{ enList::SE_Slash,			_T( "Data\\Sound\\SE\\Slash.mp3" ),				    _T( "SE_Slash" )		},
		{ enList::SE_Root,			_T( "Data\\Sound\\SE\\Root.mp3" ),				    _T( "SE_Root" )			},
		{ enList::SE_Charge,		_T( "Data\\Sound\\SE\\Charge.mp3" ),				_T( "SE_Charge" )		},
		{ enList::SE_Sp,			_T( "Data\\Sound\\SE\\BeforeSp.mp3" ),				_T( "SE_BeforeSp" )		},
		{ enList::SE_EvoAf,			_T( "Data\\Sound\\SE\\BossEvoAfter.mp3" ),	        _T( "SE_BossEvoAfter" )	},
		{ enList::SE_EvoNow,		_T( "Data\\Sound\\SE\\EvoNow.mp3" ),				_T( "SE_EvoNow" )		},
		{ enList::SE_BossVo,		_T( "Data\\Sound\\SE\\BossVoice.mp3" ),				_T( "SE_BossVoice" )	},
		{ enList::SE_BossDeath,		_T( "Data\\Sound\\SE\\BossDeath.mp3" ),				_T( "SE_BossDeath" )	},
		{ enList::SE_DeathNow,		_T( "Data\\Sound\\SE\\DeathNow.mp3" ),				_T( "SE_DeathNow" )		},
		{ enList::SE_BossLoss,		_T( "Data\\Sound\\SE\\BossLoss.mp3" ),				_T( "SE_BossLoss" )		},
		{ enList::SE_BeforeDeath,   _T( "Data\\Sound\\SE\\BeforeDeath.mp3" ),		    _T( "SE_BeforeDeath" )	},
	};
	//配列の最大要素数を算出 (配列全体のサイズ/配列1つ分のサイズ).
	int list_max = sizeof( SList ) / sizeof( SList[0] );
	for( int i = 0; i < list_max; i++ )
	{
		if( m_pSound[SList[i].listNo]->Open(
			SList[i].path,
			SList[i].alias,
			hWnd ) == false )
		{
			return false;
		}
	}

	return true;
}

//サウンドデータ解放関数.
void CSoundManager::Release()
{
	//開いた時と逆順で閉じる.
	for( int i = enList::max - 1; i >= 0; i-- )
	{
		if( m_pSound[i] != nullptr )
		{
			m_pSound[i]->Close();
		}
	}
}
