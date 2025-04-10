#include "Scene\CSceneBase.h"					//シーンベースクラス
#include "Camera\CameraManager\CCameraManager.h"//カメラマネージャクラス
#include "WriteText\WriteText.h"				//テキスト描画クラス
#include <memory>
#include <Windows.h>

// =======================
// 前方宣言
// =======================		
class CJson;
class CKeyManager;
class CSoundManager;
class CUIManager;

// =======================
// 定数宣言
// =======================
namespace Constant_LoginScene
{
	//名前入力スペースの位置
	static D3DXVECTOR3 NAMESPACE_POS   = { 300.0f,300.0f,0.0f };
	//名前入力スペースのスケール
	static D3DXVECTOR3 NAMESPACE_SCALE = { 0.5f, 0.5f, 1.0f };
	//名前入力スペースの幅
	static D3DXVECTOR2 NAMESPACE_DISP  = { 1.0f,1.0f };
	//名前入力開始位置
	static D3DXVECTOR3 NAME_STARTPOS   = { 320.0f, 320.0f, 0.0f };
}

//=====================================
// タイトルシーンクラス
//=====================================
class CLoginScene
	:public CSceneBase
{
public:
	CLoginScene();
	~CLoginScene();

	//構築関数
	void Create()	  override;
	//破棄関数
	void Releace()	  override;
	//データ設定関数
	void LoadData()	  override;
	//初期化関数
	void Initialize() override;
	//更新関数
	void Update()     override;
	//描画関数
	void Draw()		  override;

private:
	//文字の動き
	float Easing(float x);
	//アカウント名入力処理
	void  InputName();
	//UIの描画
	void DrawUI();

	//wstringからstringへの変換
	std::string WstringToString(std::wstring owstring);

private:

	//カメラクラス
	CCameraManager* m_pCamera;

	// =======================
	// オブジェクトクラス
	// =======================		
	//----UI----
	//ユーザー名入力
	std::wstring m_UserName;
	//ユーザー名入力スペース
	std::unique_ptr<CUIObject> m_pNameSpace;

	//Jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//表示ヒーロー
	int m_HeroNo;

};
