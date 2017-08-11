# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"

struct News : MyApp::Scene //開いた画面
{
    const Circle back_button = Circle(960,900,60);
    const Texture back_icon = Texture(Icon(0xf112,60));
    const Font news_font = Font(40);
    News(const InitData& init)
    : IScene(init)
    {
        
    }
    
    void update() override
    {
        if (back_button.leftClicked())
        {
            changeScene(L"Start", 2s);
        }
    }
    
    void draw() const override
    {
        news_font(getData().articles[getData().articlesIndex].body).draw(0,0,Palette::Black);
        back_button.draw(Palette::Orange);
        back_icon.drawAt(back_button.center);
    }
};



