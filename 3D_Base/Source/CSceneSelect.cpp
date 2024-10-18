#include "CSceneSelect.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CMeshManager.h"
#include "CSoundManager.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include "ImGuiManager.h"
CSceneSelect::CSceneSelect()
    : m_pSky    ()
    , m_pGround ()
    , m_Opening(false)
    , m_BossApp(false)
    , m_BossEvo(false)
    , m_Special(false)
    , m_Time   (-10.0f)
{
    CCamera::GetInstance()->SetPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
    CCamera::GetInstance()->SetLook(D3DXVECTOR3(0.0f, 0.0f, 4.0f));

    //ライト情報
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
}

CSceneSelect::~CSceneSelect()
{
}

//構築関数
void CSceneSelect::Create()
{
    m_pSky = new CSky();
    m_pGround = new CGround();

    //ファイル読み込みのテスト
    std::wfstream file("Data\\Status\\Test3.txt",std::ios::in);
    
    //ファイル
    if (file.is_open())
    {
        while (std::getline(file, m_Line)) 
        {
            m_Lines.push_back(m_Line);
        }
        file.close();

        m_Statuses = std::move(m_Lines);
    }
}

//データ設定関数
void CSceneSelect::LoadData()
{
    //メッシュマネージャーのインスタンスを変数に代入
    CMeshManager* MMng = CMeshManager::GetInstance();
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

//破棄関数
void CSceneSelect::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
}

//更新関数
void CSceneSelect::Update()
{

    
    //フェードイン処理
    if (!FadeIn()) { return; }

    CKeyManager::GetInstance()->Update();

    //D3DXVECTOR3 skyPos = m_pSky->GetPosition();
    //ImGui::InputFloat3(JAPANESE("空座標"), skyPos);
    //m_pSky->SetPosition(skyPos);

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
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::GameMain);
        }
    }


}

//描画関数
void CSceneSelect::Draw()
{

    CCamera::GetInstance()->Projection();
    CCamera::GetInstance()->Update();
    m_mProj = CCamera::GetInstance()->GetProjection();
    m_mView = CCamera::GetInstance()->GetViewMatrix();


    if (m_Time <= 5.0f) {
        m_Time += 0.1f;
    }

    //スカイボックスの描画
    m_pSky->Draw(m_mView, m_mProj, m_Light, m_Camera);

    //地面の描画
    m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);

    float x = Easing(m_Time);

    for (int i = 0; i < m_Statuses.size(); i++)
    {
        WriteText::GetInstance()->Draw_Text(m_Statuses[i], WriteText::Select, D3DXVECTOR2(x, 80 * i));
    }

}

//イージング
float CSceneSelect::Easing(float x)
{
    const float c1 = 1.70158;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}
