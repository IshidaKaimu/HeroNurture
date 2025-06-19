#include "CSoundManager.h"
#include <tchar.h>
#include "MyMacro\MyMacro.h"

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
		{ enList::BGM_Title,		    _T( "Data\\Sound\\BGM\\Title.mp3" ),				_T( "BGM_Title" )		},
		{ enList::BGM_ModeSelect,		_T( "Data\\Sound\\BGM\\ModeSelect.mp3" ),			_T( "BGM_ModeSelect" )	},
		{ enList::BGM_NurtureHeroSelect,_T( "Data\\Sound\\BGM\\NurtureHeroSelect.mp3" ),	_T( "BGM_NurtureHeroSelect" )},
		{ enList::BGM_Nurture,		    _T( "Data\\Sound\\BGM\\Nurture.mp3" ),				_T( "BGM_Nurture" )		},
		{ enList::BGM_BattleHeroSelect,	_T( "Data\\Sound\\BGM\\BattleHeroSelect.mp3" ),	    _T( "BGM_BattleHeroSelect" )},
		{ enList::BGM_Battle,		    _T( "Data\\Sound\\BGM\\Battle.mp3" ),				_T( "BGM_Battle" )		},
		{ enList::BGM_NurtureResult,    _T( "Data\\Sound\\BGM\\NurtureResult.mp3" ),		_T( "BGM_NurtureResult" )},
		{ enList::BGM_Win,		        _T( "Data\\Sound\\BGM\\Win.mp3" ),				    _T( "BGM_Win" )		    },
		{ enList::BGM_Lose,		        _T( "Data\\Sound\\BGM\\Lose.mp3" ),				    _T( "BGM_Lose" )		},
		{ enList::SE_Slash,				_T( "Data\\Sound\\SE\\Slash.mp3" ),				    _T( "SE_Slash" )		},
		{ enList::SE_Damage,		    _T( "Data\\Sound\\SE\\Damage.mp3" ),				_T( "SE_Damege" )		},
		{ enList::SE_Select,		    _T( "Data\\Sound\\SE\\Select.mp3" ),				_T( "SE_Select" )		},
		{ enList::SE_Enter,			    _T( "Data\\Sound\\SE\\Enter.mp3" ),				    _T( "SE_Enter" )		},
		{ enList::SE_Tornade,		    _T( "Data\\Sound\\SE\\Tornade.mp3" ),			    _T( "SE_Tornde" )		},
		{ enList::SE_Start,				_T( "Data\\Sound\\SE\\Start.mp3" ),				    _T( "SE_Start" )		},
		{ enList::SE_FireBall,			_T( "Data\\Sound\\SE\\FireBall.mp3" ),			    _T( "SE_FireBall" )		},
		{ enList::SE_Thunder,			_T( "Data\\Sound\\SE\\Thunder.mp3" ),			    _T( "SE_Thunder" )		},
		{ enList::SE_TPose,			    _T( "Data\\Sound\\SE\\TPose.mp3" ),			        _T( "SE_TPose" )		},
		{ enList::SE_Up,			    _T( "Data\\Sound\\SE\\Up.mp3" ),			        _T( "SE_Up" )			},
		{ enList::SE_Miss,			    _T( "Data\\Sound\\SE\\Miss.mp3" ),			        _T( "SE_Miss" )			},
		{ enList::SE_RaccoonChange,	    _T( "Data\\Sound\\SE\\RaccoonChange.mp3" ),	        _T( "SE_RaccoonChange " )	},
		{ enList::SE_RaccoonCollision,	_T( "Data\\Sound\\SE\\RaccoonCollision.mp3" ),		_T( "SE_RaccoonCollision" )	},
		{ enList::SE_MagicSircle,	    _T( "Data\\Sound\\SE\\MagicSircle.mp3" ),			_T( "SE_MagicSircle" )		},
		{ enList::SE_Laser,			    _T( "Data\\Sound\\SE\\Laser.mp3" ),			        _T( "SE_Laser" )			},
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
