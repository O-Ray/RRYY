# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"//共通の変数を読み込む
//ここのファイルは、ニュースを開く時にその画面を表示している。

//禁則処理
bool TextProhibition(char32_t c)
{
    const String ProhibitionList = L"」』）｝】＞≫］ぁぃぅぇぉっゃゅょァィゥェォッャュョ、。,.ゝ々！？：；／ー-";
    return ProhibitionList.includes(c);
}

struct News : MyApp::Scene //開いた画面
{
    Circle m_backButton = Circle(960,20,60);//戻るボタンの後ろの円
    const Texture m_backIcon = Texture(Icon(0xf112,60));//戻るボタンのアイコン
    
    Circle m_settingButton = Circle(810,20,60);//設定に飛ぶボタンの後ろの円
    const Texture m_settingIcon = Texture(Icon(0xf013,60));//設定に飛ぶボタンのアイコン
    
    Circle m_homeButton = Circle(660,20,60);//ホーム画面に飛ぶボタンの後ろの円
    const Texture m_humeIcon = Texture(Icon(0xf015,60));//ホーム画面に飛ぶボタンのアイコン
    
    const Texture m_zoomInIcon = Texture(Icon(0xf00e,60));//文字の大きさを大きくするボタンのアイコン
    const Texture m_zoomOutIcon = Texture(Icon(0xf010,60));//文字の大きさを小さくするボタンのアイコン
    const Circle m_zoomInButton = Circle(300,60,35);//文字の大きさを大きくするボタンの後ろの円
    const Circle m_zoomOutButton = Circle(450,60,35);//文字の大きさを小さくするボタンの後ろの円
    
    const Rect m_scrollBar = Rect(1800,0,50,100);//スクロールバーの四角
    int m_fontSize = 40;//ニュースの文字の大きさ（27行目で指定する時の変数）
    int m_readIndex = 0;//マーカーを引くのが何文字目までか
    int m_clickCount = 0;//この画面に来てからのクリックした回数をカウントしている。
    double m_scroll = 0;//スクロールした時に記事の画面を動かす分の大きさ(!= "px")
    Font m_newsFont = Font(m_fontSize);//ニュースの文字の大きさを指定する。
    
    News(const InitData& init)
    : IScene(init)
    {
//        FileSystem::Remove(getData().articles[getData().articlesIndex].path);
    }
    
    void update() override
    {
        if(MouseL.down())//もし左クリックされたら、
        {
            ++m_clickCount;//『m_clickCount』という変数を１増やす。(『m_clickCount』は25行目)
        }
        
        if(m_homeButton.leftClicked()){//もしホームボタンを左クリックしたら、
            changeScene(L"Title", RRYY::FadeTime);//ホーム(タイトル)画面に行く
        }
        
        if(m_settingButton.leftClicked()){//もし設定ボタンを左クリックしたら、
            getData().beforeDisplay = getData().articlesIndex;//今の記事の番号を保存
            changeScene(L"Setting", RRYY::FadeTime);//設定画面に行く
        }
        
        if (m_backButton.leftClicked())//もしバックボタンを左クリックしたら、
        {
            changeScene(L"Start", RRYY::FadeTime);//ニュースの一覧(Start)画面に行く
        }
        
        if (m_zoomInButton.leftClicked())//もしズームインボタンを左クリックしたら
        {
            m_fontSize += 5;//フォントのサイズを5px大きくする(『m_fontSize』は23行目)
            m_newsFont = Font(m_fontSize);//ニュースの文字の大きさを変更し、指定する。
        }
        else if (m_zoomOutButton.leftClicked())//もしズームアウトボタンを左クリックしたら
        {
            m_fontSize -= 5;//フォントのサイズを5px小さくする(『m_fontSize』は23行目)
            m_newsFont = Font(m_fontSize);//ニュースの文字の大きさを変更し、指定する。
        }
        
        m_scroll += (Mouse::Wheel() * 30);//スクロールした分を計算
        
        Vec2 penPos(50,100 - m_scroll);//一文字分の後ろのマーカーの範囲のx,y座標を指定。
        int i = 0;//下のループした回数
        for (auto glyph : m_newsFont(getData().getArticle().body))
        {
            ++i;//70行目で指定した、ループした回数を1増やす。
            if(!TextProhibition(glyph.codePoint))
            {
                if(penPos.x + glyph.xAdvance > m_scrollBar.x - 40)
                {
                    penPos.x = 50;//x座標を50pxにする
                    penPos.y += m_newsFont.height() + 5;//y座標を個数×縦幅5pxにする
                }
            }

            
            const RectF area(penPos,glyph.xAdvance,m_newsFont.height());//マーカー用の四角を表示
            if(area.leftPressed() && m_clickCount != 0)//もしこの画面に来てから初めてのクリックだったら、
            {
                m_readIndex = i;//クリックされたのが何文字かを『m_readIndex』に代入
            }
            
            penPos.x += glyph.xAdvance;//四角のy座標を計算
        }
    }
    
    void draw() const override
    {
        Graphics::SetBackground(getData().getBackgroundColor());//背景色を設定
        //ここから、116行目までは、69~88行目までと同じ(改良は少しある)
        Vec2 penPos(50,100 - m_scroll);
        int i = 0;//下のループした回数
        for (auto glyph : m_newsFont(getData().getArticle().body))
        {
            ++i;
            
            if(!TextProhibition(glyph.codePoint))
            {
                if(penPos.x + glyph.xAdvance > m_scrollBar.x - 40)
                {
                    penPos.x = 50;//x座標を50pxにする
                    penPos.y += m_newsFont.height() + 5;//y座標を個数×縦幅5pxにする
                }
            }

            
            if(i <= m_readIndex)
            {
                const RectF area(penPos,glyph.xAdvance,m_newsFont.height());
                area.draw(getData().getMarkerColor());
            }
            
            glyph.texture.draw(penPos + glyph.offset,getData().getTaxtColor());//改: マーカーを表示
            
            penPos.x += glyph.xAdvance;
        }
        
        m_zoomInButton.draw(Palette::White).drawFrame(1,1,Palette::Black);//ズームインボタンを表示
        m_zoomInIcon.drawAt(m_zoomInButton.center,Palette::Black);//ズームインアイコンを表示
        
        m_zoomOutButton.draw(Palette::White).drawFrame(1,1,Palette::Black);//ズームアウトボタンを表示
        m_zoomOutIcon.drawAt(m_zoomOutButton.center,Palette::Black);//ズームアウトアイコンを表示
        
        m_backButton.draw(Palette::Orange);//バックボタンを表示
        m_backIcon.drawAt(m_backButton.center);//バックアイコンを表示
        
        m_homeButton.draw(Palette::Orange);//ホームボタンを表示
        m_humeIcon.drawAt(m_homeButton.center);//ホームアイコンを表示
        
        m_settingButton.draw(Palette::Orange);//設定ボタンを表示
        m_settingIcon.drawAt(m_settingButton.center);//設定アイコンを表示
        
        m_scrollBar.draw(Palette::Gray);//スクロールバーの四角を表示
    }
};



