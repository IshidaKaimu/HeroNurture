#include "CGameMain.h"
#include "Scene/CSceneManager.h"
#include "KeyManager/CKeyManager.h"
#include "StaticMesh/MeshManager/CMeshManager.h"
#include "Sound/CSoundManager.h"
#include <cmath>
#include <fstream>
#include <sstream>

CGameMain::CGameMain()
    : m_pSky()
    , m_pGround()
    , m_Opening(false)
    , m_BossApp(false)
    , m_BossEvo(false)
    , m_Special(false)
    , m_Time(-10.0f)
{
    m_Camera.Position = D3DXVECTOR3(0.0, 10.0, 0.0);
    m_Camera.Look = D3DXVECTOR3(0.0, 0.0, 0.0);

    //ライト情報
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
}

CGameMain::~CGameMain()
{
}

//構築関数
void CGameMain::Create()
{
    m_pSky = new CSky();
    m_pGround = new CGround();
}

//データ設定関数
void CGameMain::LoadData()
{
    //メッシュマネージャーのインスタンスを変数に代入
    CMeshManager* MMng = CMeshManager::GetInstance();
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

//破棄関数
void CGameMain::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
}

//更新関数
void CGameMain::Update()
{


    //フェードイン処理
    if (!FadeIn()) { return; }

    m_Camera.Look = D3DXVECTOR3(m_pGround->GetPosition());

    CKeyManager::GetInstance()->Update();

    //シーン遷移(仮)
    if (CKeyManager::GetInstance()->IsDown('1'))
    {
        //オープニングシーンへ
        m_SceneTransitionFlg = true;
        m_Opening = true;
    }

    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
        if (m_Opening == true) {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::SceneSelect);
        }
    }


}

//描画関数
void CGameMain::Draw()
{
    m_mProj = CCamera::GetInstance()->GetProjection();
    m_mView = CCamera::GetInstance()->GetViewMatrix();


    if (m_Time <= 5.0f) {
        m_Time += 0.1f;
    }


    float x = Easing(m_Time);

    m_pSky->Draw(m_mView, m_mProj, m_Light, m_Camera);
    m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);
}

//イージング
float CGameMain::Easing(float x)
{
    const float c1 = 1.70158;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}
