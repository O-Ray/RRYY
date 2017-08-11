# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"

struct Title : MyApp::Scene  //タイトル画面
{
    const Font font_title = Font(140);
    const Texture setting_icon = Texture(Icon(0xf013,300));
    const Texture start_icon = Texture(Icon(0xf1ea,300));
    const Texture exit_icon = Texture(Icon(0xf2d4,300));
    const Size button_size = Size(570,324);
    const double button_r = 30;
    const RoundRect setting_button = RoundRect(Rect(Arg::center(320,700),button_size),button_r);
    const RoundRect start_button = RoundRect(Rect(Arg::center(960,700),button_size),button_r);
    const RoundRect exit_button = RoundRect(Rect(Arg::center(1600,700),button_size),button_r);
    
    Title(const InitData& init)
    : IScene(init)
    {
        
    }
    
    void update() override
    {
        if (setting_button.leftClicked())
        {
            changeScene(L"Setting", 2s);
        }
        else if (start_button.leftClicked())
        {
            changeScene(L"Start", 2s);
        }
        else if (exit_button.leftClicked())
        {
            System::Exit();//終了する
        }
    }
    
    void draw() const override
    {
        font_title(L"らくらく読み読み").drawAt(960,260,Palette::Black);
        setting_button.draw(Palette::Lightgreen);
        setting_icon.drawAt(setting_button.center());
        start_button.draw(Palette::Lightgreen);
        start_icon.drawAt(start_button.center());
        exit_button.draw(Palette::Lightgreen);
        exit_icon.drawAt(exit_button.center());
    }
};
