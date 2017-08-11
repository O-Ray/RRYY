# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"

struct Setting : MyApp::Scene //set画面
{
    const Circle m_backButton = Circle(960,900,60);
    const Texture m_backIcon = Texture(Icon(0xf112,60));
    
    const Font m_settingFont = Font(50);
    int m_choice = -1;
    int m_choice1 = -1;
    int m_choice2 = -1;
    
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
        
        for(auto p: step(Size(5,2)))
        {
            const Rect rect(100 + (p.x * 104),400 + (p.y * 110),100,100);
            if(rect.leftClicked())
            {
                getData().backgroundColorIndex = p.y * 5 + p.x;
                m_choice = p.y * 5 + p.x;

            }
        }
        
        for(auto p: step(Size(5,2)))
        {
            const Rect rect(650 + (p.x * 104),400 + (p.y * 110),100,100);
            if(rect.leftClicked())
            {
                getData().taxtColorIndex = p.y * 5 + p.x;
                m_choice1 = p.y * 5 + p.x;
            }
        }
        
        for(auto p: step(Size(5,2)))
        {
            const Rect rect(1200 + (p.x * 104),400 + (p.y * 110),100,100);
            if(rect.leftClicked())
            {
                getData().markerColorIndex = p.y * 5 + p.x;
                m_choice2 = p.y * 5 + p.x;
            }
        }
    }
    
    void draw() const override
    {
        Graphics::SetBackground(getData().getBackgroundColor());
        
        m_settingFont(L"背景色").drawAt(358,320,Palette::Black);
        for(auto p: step(Size(5,2)))
        {
            const Rect rect(100 + (p.x * 104),400 + (p.y * 110),100,100);
            
            if(m_choice == p.y * 5 + p.x)
            {
                rect.draw(getData().settingColors[p.y * 5 + p.x]).drawFrame(8,8,Palette::Black);
            }
            else{
                rect.draw(getData().settingColors[p.y * 5 + p.x]).drawFrame(1,1,Palette::Black);
            }
        }
        
        m_settingFont(L"文字の色").drawAt(908,320,Palette::Black);
        for(auto p: step(Size(5,2)))
        {
            const Rect rect(650 + (p.x * 104),400 + (p.y * 110),100,100);
            
            if(m_choice1 == p.y * 5 + p.x)
            {
                rect.draw(getData().settingColors[p.y * 5 + p.x]).drawFrame(8,8,Palette::Black);
            }
            else{
                rect.draw(getData().settingColors[p.y * 5 + p.x]).drawFrame(1,1,Palette::Black);
            }
        }
        
        m_settingFont(L"マーカーの色").drawAt(1458,320,Palette::Black);
        for(auto p: step(Size(5,2)))
        {
            const Rect rect(1200 + (p.x * 104),400 + (p.y * 110),100,100);
            
            if(m_choice2 == p.y * 5 + p.x)
            {
                rect.draw(getData().settingColors[p.y * 5 + p.x]).drawFrame(8,8,Palette::Black);
            }
            else{
                rect.draw(getData().settingColors[p.y * 5 + p.x]).drawFrame(1,1,Palette::Black);
            }
        }
        
        m_backButton.draw(Palette::Orange);
        m_backIcon.drawAt(m_backButton.center);
    }
};
