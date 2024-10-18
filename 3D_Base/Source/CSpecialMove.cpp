#include "CSpecialMove.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CSkinMeshManager.h" 
#include "CEffect.h"
#include "CUIManager.h"
#include "CMeshManager.h"
#include "CSoundManager.h"

CSpecialMove::CSpecialMove()
    : m_pKaito      ()
    , m_pBoss       ()
    , m_pSky        ()
    , m_pBlack      ()
    , m_CameraPosZ  ()
    , m_CameraPosY  ()
    , m_CameraPosX  ()
    , m_Alpha       (0.0)
    , m_EndChange   ()
    , m_CameraChange()
{
    Create();
    LoadData();
}

CSpecialMove::~CSpecialMove()
{
    SAFE_DELETE(m_pBlack);
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pWhiteFade);
    SAFE_DELETE(m_pBoss);
    SAFE_DELETE(m_pKaito);
}

void CSpecialMove::Create()
{
    m_pKaito = new CKaito();
    m_pBoss = new CBoss();
    m_pWhiteFade = new CUIObject();
    m_pSky = new CSky();
    m_pBlack = new CSky();
}

void CSpecialMove::LoadData()
{
    //スキンメッシュマネージャのインスタンスを変数に代入
    CSkinMeshManager* SkMng = CSkinMeshManager::GetInstance();

    //メッシュマネージャーのインスタンスを変数に代入
    CMeshManager* MMng = CMeshManager::GetInstance();

    //UIマネージャのインスタンスを変数に代入
    CUIManager* UiMng = CUIManager::GetInstance();


    //Kaitoにメッシュを設定
    m_pKaito->AttachMesh(SkMng->GetMesh(CSkinMeshManager::Player));
    m_pKaito->SpInit();

    //変身後ボス
    m_pBoss->AttachMesh(SkMng->GetMesh(CSkinMeshManager::Boss));
    m_pBoss->SpInit();

    //白フェード
    m_pWhiteFade->AttachSprite(UiMng->GetSprite(CUIManager::WhiteFade));
    m_pWhiteFade->SetAlpha(m_Alpha);

    //スカイボックス
    m_pSky->AttachMesh(MMng->GetMesh(CMeshManager::Sky));

    //黒
    m_pBlack->AttachMesh(MMng->GetMesh(CMeshManager::Black));


    //シーンマネージャーのインスタンスを変数に代入
    CSceneManager* SMng = CSceneManager::GetInstance();

    D3DXVECTOR3 KPos = m_pKaito->GetPosition();

    SMng->SetCameraPos(D3DXVECTOR3(KPos.x, KPos.y + 3.0f, KPos.z - 9.0f));
    SMng->SetCameraLook(D3DXVECTOR3(KPos.x, KPos.y + 3.0f, KPos.z));

}

void CSpecialMove::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

    CKeyManager::GetInstance()->Update();

    CSceneManager* SMng = CSceneManager::GetInstance();

    D3DXVECTOR3 KPos = m_pKaito->GetPosition();
    D3DXVECTOR3 BPos = m_pBoss->GetPosition();
    //カイトのアニメーション
    m_pKaito->SpAnim();

    //ボスのアニメーション
    m_pBoss->SpAnim();

    m_pWhiteFade->SetAlpha(m_Alpha);

    //最初のシーン後から
    if (m_Cut != KaitoUp)
    {
        //BGMの停止、音量
        CSoundManager::PlayLoop(CSoundManager::BGM_Special);
        CSoundManager::Volume(CSoundManager::BGM_Special, 50);
    }

    switch (m_Cut)
    {
    case CSpecialMove::KaitoUp:
        m_AnimCnt++;

        if (m_CameraPosY <= 4.0f) {
            m_CameraPosY += 0.04;
        }

        SMng->SetCameraPos(D3DXVECTOR3(KPos.x, KPos.y + 3.0f, KPos.z - 9.0f));
        SMng->SetCameraLook(D3DXVECTOR3(KPos.x,KPos.y + 3.0f, KPos.z));
        
        if (m_pKaito->WhiteStart())
        {
            m_Cut = Fade;
            m_AnimCnt = 0.0f;
            m_CameraPosY = 0.0f;
        }

        break;
    case CSpecialMove::Fade:
        PlayWhiteFade();
        if (m_EndChange == true)
        {
            m_Cut = Fast;
            m_CameraPosZ = 4.0f;
            m_pKaito->AnimNoChange(3);
        }
        break;
    case CSpecialMove::Fast:
        PlayWhiteFade();


        if (m_CameraPosY <= 3.0)
        {
            m_CameraPosY += 0.05;
        }

        //前撮り
        SMng->SetCameraPos(D3DXVECTOR3(KPos.x + 1.0f, KPos.y + m_CameraPosY, KPos.z - m_CameraPosZ));
        SMng->SetCameraLook(D3DXVECTOR3(KPos.x, KPos.y + m_CameraPosY, KPos.z));

        if (m_CameraPosY >= 3.0f)
        {
            m_AnimCnt++;
            if (m_AnimCnt > 60) 
            {
                m_CameraPosY = 0.0;
                m_Cut = Second;
                m_AnimCnt = 0;
            }
        }

        break;
    case CSpecialMove::Second:

        m_pKaito->Magic(true);

        if (m_CameraPosY <= 3.0)
        {
            m_CameraPosY += 0.05;
        }
    
        //後ろ撮り
        SMng->SetCameraPos(D3DXVECTOR3(KPos.x - 2.0f, KPos.y + m_CameraPosY, KPos.z + 6.0f));
        SMng->SetCameraLook(D3DXVECTOR3(KPos.x, KPos.y + m_CameraPosY, KPos.z));

        if (m_CameraPosY >= 3.0)
        {
            m_AnimCnt++;
            if (m_AnimCnt > 60)
            {
                m_Cut = Third;
                m_AnimCnt = 0;
            }
            
        }

        break;
    case CSpecialMove::Third:
        //魔法
        m_pKaito->Magic(true);
        //走り出す
        m_pKaito->Run(true);
        //軌道再生
        m_pKaito->Root();

        SMng->SetCameraPos(D3DXVECTOR3(KPos.x - 20.0f, KPos.y + 3.0, KPos.z - 8.0f));
        SMng->SetCameraLook(D3DXVECTOR3(KPos.x, KPos.y + 3.0f, KPos.z - 8.0f));

        if (m_pKaito->GetPosition().z < -10.0f)
        {
            //斬る
            m_pKaito->Slash();
            m_pBoss->AnimNoChange(2);
            m_AnimCnt++;
            if (m_AnimCnt > 60)
            {
                m_Cut = fource;
                m_AnimCnt = 0;
            }
        }

        break;
    case CSpecialMove::fource:

        SMng->SetCameraPos(D3DXVECTOR3(KPos.x, KPos.y + 3.0, KPos.z - 7.0f));
        SMng->SetCameraLook(D3DXVECTOR3(KPos.x, KPos.y + 3.0f, KPos.z));

        //ボスから離れたら
        if (m_pKaito->GetPosition().z < -23.0f)
        {
            //進むのをやめさせる
            m_pKaito->Run(false);
            //魔法陣追加ストップ
            m_pKaito->Magic(false);
            //ボス爆発
            m_pBoss->Death();
        }
        break;
    default:
         break;
    }


    if (m_pBoss->AfterDeath())
    {
        CEffect::StopAll();
        m_SceneTransitionFlg = true;    //シーン遷移フラグ有効化
    }

    if (m_SceneTransitionFlg && FadeOut())
    {
        CSceneManager::GetInstance()->LoadCreate(CSceneManager::SceneSelect);
        //カメラを合わせる
        CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
        CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
    }

}

void CSpecialMove::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{

    if (m_pBoss->AfterDeath() == false) {
        m_pBoss->Draw(View, Proj, Light, Camera);
    }

    m_pKaito->Draw(View, Proj, Light, Camera);

    if (m_Cut == KaitoUp) {
        m_pSky->Draw(View, Proj, Light, Camera);
    }
    else
    {
        m_pBlack->Draw(View, Proj, Light, Camera);
    }

    if (m_Cut == Fade || m_Cut == Fast)
    {
        m_pWhiteFade->Draw();
    }

    WriteText::GetInstance()->Draw_Text(L"Special", WriteText::Select, D3DXVECTOR2(0, 0));

}

void CSpecialMove::PlayWhiteFade()
{
    if (m_AlphaChange == false)
    {
        m_Alpha += 0.01f;

        if (m_Alpha >= 1.0f)
        {
            m_AlphaChange = true;
            m_EndChange = true;
        }
    }
    else
    {
        m_Alpha -= 0.01f;

        if (m_Alpha <= 0.0f)
        {
            m_Alpha = 0.0f;
        }
    }

}



