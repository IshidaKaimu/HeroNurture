#include "CSoundManager.h"
#include "MyMacro/MyMacro.h"

CSoundManager::CSoundManager()
	: m_pSound	()
{
	//�C���X�^���X����.
	for( int i = 0; i < enList::max; i++ )
	{
		m_pSound[i] = new CSound();
	}
}

CSoundManager::~CSoundManager()
{
	Release();

	//�C���X�^���X�j��.
	for( int i = enList::max - 1; i >= 0; i-- )
	{
		SAFE_DELETE( m_pSound[i] );
	}
}

//�T�E���h�f�[�^�Ǎ��֐�.
bool CSoundManager::Load( HWND hWnd )
{
	struct SoundList
	{
		int listNo;				//enList�񋓌^��ݒ�.
		const TCHAR path[256];	//�t�@�C���̖��O(�p�X�t��).
		const TCHAR alias[32];	//�G�C���A�X��.
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
	//�z��̍ő�v�f�����Z�o (�z��S�̂̃T�C�Y/�z��1���̃T�C�Y).
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

//�T�E���h�f�[�^����֐�.
void CSoundManager::Release()
{
	//�J�������Ƌt���ŕ���.
	for( int i = enList::max - 1; i >= 0; i-- )
	{
		if( m_pSound[i] != nullptr )
		{
			m_pSound[i]->Close();
		}
	}
}
