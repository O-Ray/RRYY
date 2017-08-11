# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"

struct Title : MyApp::Scene  //タイトル画面
{
    const Font m_fontTitle = Font(140);
    
    const Size m_buttonSize = Size(570,324);
    const double m_buttonR = 30;
    
    const RoundRect m_settingButton = RoundRect(Rect(Arg::center(320,700),m_buttonSize),m_buttonR);
    const Texture m_settingIcon = Texture(Icon(0xf013,300));
    
    const RoundRect m_startButton = RoundRect(Rect(Arg::center(960,700),m_buttonSize),m_buttonR);
    const Texture m_startIcon = Texture(Icon(0xf1ea,300));
    
    const RoundRect m_exitButton = RoundRect(Rect(Arg::center(1600,700),m_buttonSize),m_buttonR);
    const Texture m_exitIcon = Texture(Icon(0xf2d4,300));
    
    Title(const InitData& init)
    : IScene(init)
    {
        
    }
    
    void update() override
    {
        if (m_settingButton.leftClicked())
        {
            changeScene(L"Setting", RRYY::FadeTime);
        }
        else if (m_startButton.leftClicked())
        {
            changeScene(L"Start", RRYY::FadeTime);
        }
        else if (m_exitButton.leftClicked())
        {
            System::Exit();//終了する
        }
    }
    
    void draw() const override
    {
        Graphics::SetBackground(getData().getBackgroundColor());
        
        m_fontTitle(L"らくらく読み読み").drawAt(960,260,Palette::Black);
        
        m_settingButton.draw(Palette::Lightgreen);
        m_settingIcon.drawAt(m_settingButton.center());
        
        m_startButton.draw(Palette::Lightgreen);
        m_startIcon.drawAt(m_startButton.center());
        
        m_exitButton.draw(Palette::Lightgreen);
        m_exitIcon.drawAt(m_exitButton.center());
    }
};
