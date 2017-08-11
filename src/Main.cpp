# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Common.hpp"
# include "Title.hpp"
# include "Setting.hpp"
# include "Start.hpp"
# include "News.hpp"

void Main()
{
    for(auto output: Graphics::EnumOutputs())
    {
        for(auto mode : output.displayModes)
        {
//            Print << mode.size;
        }
    }
    
    ScalableWindow::SetBaseSize(1920, 1080);
    //    Graphics::SetFullScreen(true, Size(1440, 900));
    Graphics::SetFullScreen(true, Size(1920, 1080));
    Graphics::SetBackground(Palette::White);
    
    MyApp manager;
    manager
    .add<Title>(L"Title")
    .add<Setting>(L"Setting")
    .add<Start>(L"Start")
    .add<News>(L"News");

    manager.setFadeColor(Palette::White);
    
    while (System::Update())
    {
        auto t = ScalableWindow::CreateTransformer();
        
        if (!manager.update())
        {
            break;
        }
    }
}

