# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"

struct Setting : MyApp::Scene //set画面
{
    const Circle m_backButton = Circle(960,900,60);
    const Texture m_backIcon = Texture(Icon(0xf112,60));
    
    Setting(const InitData& init)
    : IScene(init)
    {
        
    }
    
    void update() override
    {
        if (m_backButton.leftClicked())
        {
            changeScene(L"Title", RRYY::FadeTime);
        }
    }
    
    void draw() const override
    {
        m_backButton.draw(Palette::Orange);
        m_backIcon.drawAt(m_backButton.center);
    }
};
