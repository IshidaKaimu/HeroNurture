#pragma once
//=====================================
// シングルトンクラス
//=====================================

template<typename T>

class CSingleton
{
public:
    //シングルトンインスタンスを取得する
    static T& GetInstance() {
        static T Instance;
        return Instance;
    }

    //コピーコンストラクタと代入演算子を削除して一つしか作られないようにする
    CSingleton(const CSingleton& rhs) = delete;
    CSingleton& operator = (const CSingleton& rhs) = delete;

protected:
    //継承関係でない外部からのコンストラクタへの干渉を禁止する
    CSingleton() = default;
    virtual ~CSingleton() = default;

};

