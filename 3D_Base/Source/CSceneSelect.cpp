#include "CSceneSelect.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CMeshManager.h"
#include "CSoundManager.h"
#include <cmath>

CSceneSelect::CSceneSelect()
    : m_pSky    ()
    , m_Opening(false)
    , m_BossApp(false)
    , m_BossEvo(false)
    , m_Special(false)
    , m_Time   (-10.0f)
{
    Create();
    LoadData();
}

CSceneSelect::~CSceneSelect()
{
}

void CSceneSelect::Create()
{
    m_pSky = new CSky();
}

void CSceneSelect::LoadData()
{
    //メッシュマネージャーのインスタンスを変数に代入
    CMeshManager* MMng = CMeshManager::GetInstance();
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
}

void CSceneSelect::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

    //各BGMの停止
    CSoundManager::Stop(CSoundManager::BGM_Opening);    //オープニング
    CSoundManager::Stop(CSoundManager::BGM_BossApe);    //ボス登場シーン
    CSoundManager::Stop(CSoundManager::BGM_BossEvo);    //ボス進化シーン
    CSoundManager::Stop(CSoundManager::BGM_Special);    //必殺技シーン
    CSoundManager::Stop(CSoundManager::BGM_BossDeath);  //ボス撃破シーン

    CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
    CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


    CKeyManager::GetInstance()->Update();


    

    //シーン遷移(仮)
    if (CKeyManager::GetInstance()->IsDown('1'))
    {
        //オープニングシーンへ
        m_SceneTransitionFlg = true;
        m_Opening = true;
    }
    if (CKeyManager::GetInstance()->IsDown('2'))
    {
        //ボス登場シーンへ
        m_SceneTransitionFlg = true;
        m_BossApp = true;
    }

    if (CKeyManager::GetInstance()->IsDown('3'))
    {
        //ボス進化シーンへ
        m_SceneTransitionFlg = true;
        m_BossEvo = true;
    }

    if (CKeyManager::GetInstance()->IsDown('4'))
    {
        //必殺技シーンへ
        m_SceneTransitionFlg = true;
        m_Special = true;
    }

    if (CKeyManager::GetInstance()->IsDown('5'))
    {
        //ボス撃破シーンへ
        m_SceneTransitionFlg = true;
        m_BossDeath = true;
    }

    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        if (m_Opening == true) {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::Opening);
        }
        else if(m_BossApp == true)
        {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::BossApp);
        }
        else if (m_BossEvo == true)
        {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::BossEvo);
        }
        else if (m_Special == true)
        {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::Special);
        }
        else if (m_BossDeath == true)
        {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::BossDeath);
        }
    }


}

void CSceneSelect::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    if (m_Time <= 5.0f) {
        m_Time += 0.1f;
    }

    m_pSky->Draw(View, Proj, Light, Camera);

    float x = Easing(m_Time);
    WriteText::GetInstance()->Draw_Text(L"1 Opening", WriteText::Select, D3DXVECTOR2(x, 0));
    WriteText::GetInstance()->Draw_Text(L"2 Boss Appearance", WriteText::Select, D3DXVECTOR2(x, 80));
    WriteText::GetInstance()->Draw_Text(L"3 Boss Evolution", WriteText::Select, D3DXVECTOR2(x, 160));
    WriteText::GetInstance()->Draw_Text(L"4 Special", WriteText::Select, D3DXVECTOR2(x, 240));
    WriteText::GetInstance()->Draw_Text(L"5 Boss Destroy", WriteText::Select, D3DXVECTOR2(x, 320));

}

//イージング
float CSceneSelect::Easing(float x)
{
    const float c1 = 1.70158;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}
