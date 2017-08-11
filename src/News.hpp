# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"


struct News : MyApp::Scene //開いた画面
{
    Circle m_backButton = Circle(960,900,60);
    const Texture m_zoomInIcon = Texture(Icon(0xf00e,60));
    const Texture m_zoomOutIcon = Texture(Icon(0xf010,60));
    const Circle m_zoomInButton = Circle(300,60,35);
    const Circle m_zoomOutButton = Circle(450,60,35);
    const Texture m_backIcon = Texture(Icon(0xf112,60));
    const Rect m_scrollBar = Rect(1800,0,50,100);
    int m_fontSize = 40;
    int m_readIndex = 0;
    int m_clickCount = 0;
    double m_scroll = 0;
    Font m_newsFont = Font(m_fontSize);
    
    News(const InitData& init)
    : IScene(init)
    {
        
    }
    
    void update() override
    {
        if(MouseL.down())
        {
            ++m_clickCount;
        }
        
        if (m_backButton.leftClicked())
        {
            changeScene(L"Start", RRYY::FadeTime);
        }
        
        if (m_zoomInButton.leftClicked())
        {
            m_fontSize += 5;
            m_newsFont = Font(m_fontSize);
        }
        else if (m_zoomOutButton.leftClicked())
        {
            m_fontSize -= 5;
            m_newsFont = Font(m_fontSize);
        }
        
        m_scroll += (Mouse::Wheel() * 30);
        
        Vec2 penPos(50,100 - m_scroll);
        int i = 0;//下のループした回数
        for (auto glyph : m_newsFont(getData().getArticle().body))
        {
            ++i;
            
            if(penPos.x + glyph.xAdvance > m_scrollBar.x - 40)
            {
                penPos.x = 50;
                penPos.y += m_newsFont.height() + 5;
            }
            
            const RectF area(penPos,glyph.xAdvance,m_newsFont.height());
            if(area.leftPressed() && m_clickCount != 0)
            {
                m_readIndex = i;
            }
            
            penPos.x += glyph.xAdvance;
        }
             
        m_backButton = Circle(960,penPos.y + m_newsFont.height() + 100,60);
    }
    
    void draw() const override
    {
        Graphics::SetBackground(getData().getBackgroundColor());
        
        Vec2 penPos(50,100 - m_scroll);
        int i = 0;//下のループした回数
        for (auto glyph : m_newsFont(getData().getArticle().body))
        {
            ++i;
            
            if(penPos.x + glyph.xAdvance > m_scrollBar.x - 40)
            {
                penPos.x = 50;
                penPos.y += m_newsFont.height() + 5;
            }
            
            if(i <= m_readIndex)
            {
                const RectF area(penPos,glyph.xAdvance,m_newsFont.height());
                area.draw(getData().getMarkerColor());
            }
            
            glyph.texture.draw(penPos + glyph.offset,getData().getTaxtColor());
            
            penPos.x += glyph.xAdvance;
        }
        
        m_zoomInButton.draw(Palette::White).drawFrame(1,1,Palette::Black);
        m_zoomInIcon.drawAt(m_zoomInButton.center,Palette::Black);
        
        m_zoomOutButton.draw(Palette::White).drawFrame(1,1,Palette::Black);
        m_zoomOutIcon.drawAt(m_zoomOutButton.center,Palette::Black);
        
        m_backButton.draw(Palette::Orange);
        m_backIcon.drawAt(m_backButton.center);
        
        m_scrollBar.draw(Palette::Gray);
    }
};



