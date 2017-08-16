# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"//共通の変数を読み込む
//ここのファイルは、設定画面を表示している。

struct Setting : MyApp::Scene //set画面
{
    const Circle m_backButton = Circle(960,900,60);//戻るボタンの後ろの円
    const Texture m_backIcon = Texture(Icon(0xf112,60));//戻るボタンのアイコン
    const Rect m_settingBackRect = Rect(0,200,1920,800);
    
    const int m_paletteNumX = 4;
    const int m_paletteNumY = 3;
    
    const Font m_settingFont = Font(50);//設定の種類の文字のフォントサイズ
    int m_choice = -1;//今選択している色の配列の何番目か(背景色)
    int m_choice1 = -1;//今選択している色の配列の何番目か(文字の色)
    int m_choice2 = -1;//今選択している色の配列の何番目か(マーカーの色)
    
    Setting(const InitData& init)
    : IScene(init)
    {
    
    }
    
    void update() override
    {
        if (m_backButton.leftClicked())//もしバックボタンが左クリックされたら、
        {
            if(getData().beforeDisplay != -1)//前の画面がニュースだったら、
            {
                getData().beforeDisplay = -1;
                changeScene(L"News", RRYY::FadeTime);//ニュース画面に飛ぶ
            }else//それ以外だったら、
            {
                changeScene(L"Title", RRYY::FadeTime);//ホーム(タイトル)画面に飛ぶ
            }
        }
        //背景色
        for(auto p: step(Size(m_paletteNumX,m_paletteNumY)))//for文で、表を作る
        {
            const Rect rect(265 + (p.x * 110),400 + (p.y * 120),100,100);//四角を作成
            if(rect.leftClicked())//もし四角をクリックしたら、
            {
                getData().backgroundColorIndex = p.y * m_paletteNumX + p.x;//それが何個目かを取得
                m_choice = p.y * m_paletteNumX + p.x;//それが何個目かを計算

            }
        }
        //文字の色(35~45までと同じ)
        for(auto p: step(Size(m_paletteNumX,m_paletteNumY)))
        {
            const Rect rect(745 + (p.x * 110),400 + (p.y * 120),100,100);
            if(rect.leftClicked())
            {
                getData().taxtColorIndex = p.y * m_paletteNumX + p.x;
                m_choice1 = p.y * m_paletteNumX + p.x;
            }
        }
        //マーカーの色(35~45までと同じ)
        for(auto p: step(Size(m_paletteNumX,m_paletteNumY)))
        {
            const Rect rect(1225 + (p.x * 110),400 + (p.y * 120),100,100);
            if(rect.leftClicked())
            {
                getData().markerColorIndex = p.y * m_paletteNumX + p.x;
                m_choice2 = p.y * m_paletteNumX + p.x;
            }
        }
    }
    
    void draw() const override
    {
        Graphics::SetBackground(getData().getBackgroundColor());//背景色を表示
        
        m_settingBackRect.draw(Palette::White);//設定の表の背景に白い四角を作成
        
        //背景色の設定の表を表示
        m_settingFont(L"背景色").drawAt(480,320,Palette::Black);//『背景色』と文字を表示
        for(auto p: step(Size(m_paletteNumX,m_paletteNumY)))
        {
            const Rect rect(265 + (p.x * 110),400 + (p.y * 120),100,100);
            
            if(m_choice == p.y * m_paletteNumX + p.x)//もし選択している四角だったら、
            {
                rect.draw(getData().settingBackColors[p.y * m_paletteNumX + p.x]).drawFrame(4,4,Palette::Black);//その四角を表示し、枠をつける
            }
            else{//それ以外だったら、
                rect.draw(getData().settingBackColors[p.y * m_paletteNumX + p.x]).drawFrame(1,1,Palette::Black);//四角だけを表示
            }
        }
        //文字の色の設定の表を表示(71~84)
        m_settingFont(L"文字の色").drawAt(960,320,Palette::Black);
        for(auto p: step(Size(m_paletteNumX,m_paletteNumY)))
        {
            const Rect rect(745 + (p.x * 110),400 + (p.y * 120),100,100);
            
            if(m_choice1 == p.y * m_paletteNumX + p.x)
            {
                rect.draw(getData().settingTextColors[p.y * m_paletteNumX + p.x]).drawFrame(4,4,Palette::Black);
            }
            else{
                rect.draw(getData().settingTextColors[p.y * m_paletteNumX + p.x]).drawFrame(1,1,Palette::Black);
            }
        }
        //マーカーの色の設定の表を表示(71~84)
        m_settingFont(L"マーカーの色").drawAt(1440,320,Palette::Black);
        for(auto p: step(Size(m_paletteNumX,m_paletteNumY)))
        {
            const Rect rect(1225 + (p.x * 110),400 + (p.y * 120),100,100);
            
            if(m_choice2 == p.y * m_paletteNumX + p.x)
            {
                rect.draw(getData().settingColors[p.y * m_paletteNumX + p.x]).drawFrame(4,4,Palette::Black);
            }
            else{
                rect.draw(getData().settingColors[p.y * m_paletteNumX + p.x]).drawFrame(1,1,Palette::Black);
            }
        }
        
        m_backButton.draw(Palette::Orange);//バックボタンを表示
        m_backIcon.drawAt(m_backButton.center);//バックアイコンを表示
    }
};
