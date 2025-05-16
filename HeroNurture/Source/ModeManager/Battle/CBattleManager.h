#pragma once
#include "CDirectX11.h"
#include "CDirectX9.h"
#include "Singleton\CSingleton.h"
#include "Utility\CUtility.h"
#include <memory>

//=====================================
//�o�g���}�l�[�W���[�N���X
//����ҁF�Γc�D��
//=====================================
class CBattleManager
	: public CSingleton<CBattleManager>
{
private:
	//�t�����h�錾
	//�A�N�Z�X����^����
	friend class CSingleton<CBattleManager>;
	~CBattleManager();
public:

	//���s���X�g
	enum enBattleResultList
	{
		Win,
		Lose,
	};

private:
	CBattleManager();
public:
	
	//---�Q�b�^�[�E�Z�b�^�[---
	//���s
	enBattleResultList GetBattleResult() { return m_BattleResult; }
	void SetBattleResult(enBattleResultList result) { m_BattleResult = result; }

private:

	//----�񋓌^----
	//���s���X�g
	enBattleResultList m_BattleResult;
};
