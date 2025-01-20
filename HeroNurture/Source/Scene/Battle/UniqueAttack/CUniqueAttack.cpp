#include "CUniqueAttack.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Scene\CSceneManager.h"

CUniqueAttack::CUniqueAttack()
    : m_pHero     ( &CHeroManager::GetInstance() )
    , m_pEnemyHero( &CEnemyHeroManager::GetInstance() )
    , m_pCamera   ( &CCameraManager::GetInstance() )
{
}

CUniqueAttack::~CUniqueAttack()
{
}

void CUniqueAttack::Create()
{
}

void CUniqueAttack::Releace()
{
}

void CUniqueAttack::LoadData()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    switch (SceneMng->GetRole())
    {
    case CSceneManager::Hero:
        m_pHero->LoadMeshData();
        break;
    case CSceneManager::EnemyHero:
        m_pEnemyHero->LoadMeshData();
        break;
    default:
        break;
    }
}

void CUniqueAttack::Initialize()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    switch (SceneMng->GetRole())
    {
    case CSceneManager::Hero:
        if (m_pHero->GetBattleHeroName() == "Yui")
        {
            m_pCamera->SetPos(YUI_CAMPOS);
            m_pCamera->SetLook(YUI_CAMPOS);
        }
        else if(m_pHero->GetBattleHeroName() == "Kaito")
        {
            m_pCamera->SetPos(KAITO_CAMPOS);
            m_pCamera->SetLook(KAITO_CAMPOS);
        }
        break;
    case CSceneManager::EnemyHero:
        if (m_pEnemyHero->GetBattleHeroName() == "Yui")
        {
            m_pCamera->SetPos(YUI_CAMPOS);
            m_pCamera->SetLook(YUI_CAMPOS);
        }
        else if (m_pEnemyHero->GetBattleHeroName() == "Kaito")
        {
            m_pCamera->SetPos(KAITO_CAMPOS);
            m_pCamera->SetLook(KAITO_CAMPOS);
        }
        break;
    default:
        break;
    }


}

void CUniqueAttack::Update()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    switch (SceneMng->GetRole())
    {
    case CSceneManager::Hero:
        m_pHero->UniqueAttackAnim();
        break;
    case CSceneManager::EnemyHero:
        m_pEnemyHero->UniqueAttackAnim();
        break;
    default:
        break;
    }
}

void CUniqueAttack::Draw()
{
  CSceneManager* Scene = CSceneManager::GetInstance();

  //カメラの動作
  m_pCamera->CameraUpdate();

  switch (Scene->GetRole())
  {
  case CSceneManager::Hero:
      m_pHero->Draw();
      break;
  case CSceneManager::EnemyHero:
      m_pEnemyHero->Draw();
      break;
  default:
	  break;
  }
}

void CUniqueAttack::Debug()
{
}

//ユイの固有攻撃アニメーション中のカメラワーク
void CUniqueAttack::YuiCameraWork()
{

}

//カイトの固有攻撃アニメーション中のカメラワーク
void CUniqueAttack::KaitoCameraWork()
{

}
