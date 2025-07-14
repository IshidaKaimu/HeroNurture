#include "Scene\CSceneBase.h"					//シーンベースクラス
#include "Camera\CameraManager\CCameraManager.h"//カメラマネージャクラス
#include "WriteText\WriteText.h"				//テキスト描画クラス
#include <filesystem>
#include <memory>
#include <Windows.h>

// =======================
// 前方宣言
// =======================		
class CJson;
class CKeyManager;
class CSoundManager;
class CUIManager;
class CUtility;

// =======================
// 定数宣言
// =======================
namespace Constant_LoginScene
{
	//----UI----
	//名前入力スペース
	static D3DXVECTOR3 NAMESPACE_POS   = { 300.0f,300.0f,0.0f }; //座標
	static D3DXVECTOR3 NAMESPACE_SCALE = { 0.5f, 0.5f, 1.0f };   //拡縮
	static D3DXVECTOR2 NAMESPACE_DISP  = { 1.0f,1.0f };		     //幅
	//背景
	static D3DXVECTOR3 BACK_POS   = { 0.0f,0.0f,0.0f };         //座標
	static D3DXVECTOR3 BACK_SCALE = { 1.0f, 1.0f, 1.0f };       //拡縮
	static D3DXVECTOR2 BACK_DISP  = { 1.0f,1.0f };		        //幅
	//名前入力開始座標
	static D3DXVECTOR3 NAME_STARTPOS   = { 320.0f, 320.0f, 0.0f }; 
	//名前最大文字数
	static const int NAME_MAXLENGTH    = 8;
	//シーン名座標
	static const D3DXVECTOR2 SCENENAME_POS = { 0.0f, -20.0f };
	//-----------
}

//=====================================
// ログインシーンクラス
// 制作者:石田櫂夢
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
	//存在の有無を確認したいフォルダのパス
	std::filesystem::path m_TargetPath;

	// =======================
	// オブジェクトクラス
	// =======================		
	//----UI----
	//ユーザー名
	std::wstring m_UserName;
	//ユーザー名入力スペース
	std::unique_ptr<CUIObject> m_pNameSpace;
	//背景
	std::unique_ptr<CUIObject> m_pBack;
	//---------

	//Jsonクラス
	std::unique_ptr<CJson> m_pJson;
	
	//一致する名前が存在しないことを表示するフラグ
	bool m_NonExistent;
};
