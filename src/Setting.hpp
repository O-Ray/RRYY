# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"

struct Setting : MyApp::Scene //set画面
{
    const Circle back_button = Circle(960,900,60);
    const Texture back_icon = Texture(Icon(0xf112,60));
    
    Setting(const InitData& init)
    : IScene(init)
    {
        
    }
    
    void update() override
    {
        if (back_button.leftClicked())
        {
            changeScene(L"Title", 2s);
        }
    }
    
    void draw() const override
    {
        back_button.draw(Palette::Orange);
        back_icon.drawAt(back_button.center);
    }
};
