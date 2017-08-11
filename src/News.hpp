# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"

struct News : MyApp::Scene //開いた画面
{
    Circle m_backButton = Circle(960,900,60);
    const Texture m_newsFontSizeUpIcon = Texture(Icon(0xf00e,60));
    const Texture m_newsFontSizeDownIcon = Texture(Icon(0xf010,60));
    const Circle m_newsFontSizeUpButton = Circle(300,60,35);
    const Circle m_newsFontSizeDownButton = Circle(450,60,35);
    const Texture m_backIcon = Texture(Icon(0xf112,60));
    int m_newsFontSize = 40;
    double m_scroll = 0;
    Font m_newsFont = Font(m_newsFontSize);
    
    News(const InitData& init)
    : IScene(init)
    {
        
    }
    
    void update() override
    {
        if (m_backButton.leftClicked())
        {
            changeScene(L"Start", RRYY::FadeTime);
        }
        if (m_newsFontSizeUpButton.leftClicked())
        {
            m_newsFontSize += 5;
            m_newsFont = Font(m_newsFontSize);
        }
        else if (m_newsFontSizeDownButton.leftClicked())
        {
            m_newsFontSize -= 5;
            m_newsFont = Font(m_newsFontSize);
        }
        m_scroll += (Mouse::Wheel() * 2);
        Vec2 penPos(50,100 - m_scroll);
        for (auto glyph:m_newsFont(getData().articles[getData().articlesIndex].body))
        {
            penPos.x += glyph.xAdvance;
            if(penPos.x > 1800){
                penPos.x = 50;
                penPos.y += m_newsFont.height() + 5;
            }
        }
        m_backButton = Circle(960,penPos.y + m_newsFont.height() + 100,60);
    }
    
    void draw() const override
    {
        Vec2 penPos(50,100 - m_scroll);
        for (auto glyph:m_newsFont(getData().articles[getData().articlesIndex].body))
        {
            glyph.texture.draw(penPos + glyph.offset,Palette::Black);
            penPos.x += glyph.xAdvance;
            if(penPos.x > 1800){
                penPos.x = 50;
                penPos.y += m_newsFont.height() + 5;
            }
        }
        m_backButton.draw(Palette::Orange);
        m_newsFontSizeUpButton.draw(Palette::White).drawFrame(1,1,Palette::Black);
        m_newsFontSizeDownButton.draw(Palette::White).drawFrame(1,1,Palette::Black);
        m_newsFontSizeUpIcon.drawAt(m_newsFontSizeUpButton.center,Palette::Black);
        m_newsFontSizeDownIcon.drawAt(m_newsFontSizeDownButton.center,Palette::Black);
        m_backIcon.drawAt(m_backButton.center);
    }
};



