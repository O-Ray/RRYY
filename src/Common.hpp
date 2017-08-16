# pragma once
# include <Siv3D.hpp>

//ここのファイルは、他のファイルに共通する変数や定数を入れている。
namespace RRYY
{
    //シーン切り替え時間
    const auto FadeTime = 0.1s;
}

struct Article
{
    String title;//記事のタイトル
    String body;//記事の全体
    String getPreview()const//記事の最初の10字
    {
        return body.substr(0,10);
    }
    String path;
};

struct AppData
{
    Array<Article> articles;//記事一覧
    int articlesIndex = 0;//何番目の記事を読んでいるか？
    int beforeDisplay = -1;//ニュースから、設定画面に戻った時に元の記事の番号を入れる。
    int fontSize = 40;
    const Article& getArticle()const
    {
        return articles[articlesIndex];
    }
    
    const Array<ColorF> settingColors =//マーカーの色のカラー配列
    {
        Color(L"#51A7F9"),
        Color(L"#70BF41"),
        Color(L"#F5D328"),
        Color(L"#F39019"),
        Color(L"#EC5D57"),
        Color(L"#FFFFFF"),
        Color(L"#DCDEE0"),
        Color(L"#A6AAA9"),
        Color(L"#53585F"),
        Color(L"#000000"),
        Color(L"#ffffff"),
        Color(L"#ffffff"),
    };
    const Array<ColorF> settingTextColors =//テキストの色のカラー配列
    {
        Color(L"#152B40"),
        Color(L"#253F15"),
        Color(L"#2D1A05"),
        Color(L"#472A59"),
        Color(L"#FFF9D8"),
        Color(L"#FFFFFF"),
        Color(L"#DCDEE0"),
        Color(L"#A6AAA9"),
        Color(L"#53585F"),
        Color(L"#000000"),
        Color(L"#ffffff"),
        Color(L"#ffffff"),
    };
    const Array<ColorF> settingBackColors =//背景色のカラー配列
    {
        Color(L"#FFFFFF"),
        Color(L"#FFE8F3"),
        Color(L"#FFFED8"),
        Color(L"#EBEBEB"),
        Color(L"#E6FFFF"),
        Color(L"#E5FEE6"),
        Color(L"#F1E3FF"),
        Color(L"#35350A"),
        Color(L"#000035"),
        Color(L"#000000"),
        Color(L"#ffffff"),
        Color(L"#ffffff"),
    };
    int backgroundColorIndex = 5;//背景色のカラー配列index(現在配列の何個目を指定しているか。０〜９)
    int taxtColorIndex = 9;//記事のテキストのカラー配列index(現在配列の何個目を指定しているか。０〜９)
    int markerColorIndex = 5;//記事に引くマーカーのカラー配列index(現在配列の何個目を指定しているか。０〜９)
    ColorF getBackgroundColor()const//現在の背景色を返す(表示する)
    {
        return settingBackColors[backgroundColorIndex];//『return』とは、要素を返すこと。
    }
    
    ColorF getTaxtColor()const//現在の記事のテキストのカラーを返す(表示する)
    {
        return settingTextColors[taxtColorIndex];//『return』とは、要素を返すこと。
    }
    
    ColorF getMarkerColor()const//現在の記事に引くマーカーのカラーを返す(表示する)
    {
        return settingColors[markerColorIndex];//『return』とは、要素を返すこと。
    }
};

Article LoadArticle(const FilePath& path)
{
    Article article;
    
    article.path = path;
    TextReader reader(path);
    
    //タイトルをプログラムに追加
    reader.readLine(article.title);//タイトルにtxtの１行目を追加
    
    //本文をプログラムに追加
    String line;//bodyを作成
    while (reader.readLine(line))//ループして、本文を読み取っている。
    {
        article.body += line;//bodyにtxtの全体を追加
    }
    return article;//『return』とは、要素を返すこと。
}

using MyApp = SceneManager<String, AppData>;//アプリ化している。
