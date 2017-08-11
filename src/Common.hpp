# pragma once
# include <Siv3D.hpp>
# include "Scene.hpp"

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
};

struct AppData
{
    Array<Article> articles;//記事一覧
    int articlesIndex = 0;//何番目の記事を読んでいるか？
    const Article& getArticle()const
    {
        return articles[articlesIndex];
    }
    
    const Array<ColorF> settingColors =//カラー配列
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
        Color(L"#000000")
    };
    int backgroundColorIndex = 5;//背景色のカラー配列index
    int taxtColorIndex = 5;//記事のテキストのカラー配列index
    int markerColorIndex = 5;//記事に引くマーカーのカラー配列index
    
    ColorF getBackgroundColor()const//現在の背景色を返す
    {
        return settingColors[backgroundColorIndex];
    }
    
    ColorF getTaxtColor()const//現在の記事のテキストのカラーを返す
    {
        return settingColors[taxtColorIndex];
    }
    
    ColorF getMarkerColor()const//現在の記事に引くマーカーのカラーを返す
    {
        return settingColors[markerColorIndex];
    }
};

Article LoadArticle(const FilePath& path)
{
    Article article;
    
    TextReader reader(path);
    
    //タイトルをプログラムに追加
    reader.readLine(article.title);//タイトルにtxtの１行目を追加
    
    //本文をプログラムに追加
    String line;//bodyを作成
    while (reader.readLine(line))
    {
        article.body += line;//bodyにtxtの全体を追加
    }
    return article;
}

using MyApp = SceneManager<String, AppData>;
