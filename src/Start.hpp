# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"

struct Start : MyApp::Scene //start画面
{
    const Circle back_button = Circle(960,900,60);
    const Texture back_icon = Texture(Icon(0xf112,60));
    const Texture detail_icon = Texture(Icon(0xf0c9,45));
    const Font news_font = Font(45);
    const Font news_preview_font = Font(20);
    
    Start(const InitData& init)
    : IScene(init)
    {
        getData().articles.clear();
        getData().articles.push_back(LoadArticle(L"news/news0.txt"));
        getData().articles.push_back(LoadArticle(L"news/news1.txt"));
        getData().articles.push_back(LoadArticle(L"news/news2.txt"));
        getData().articles.push_back(LoadArticle(L"news/news3.txt"));
        getData().articles.push_back(LoadArticle(L"news/news4.txt"));
    }
    
    void update() override
    {
        if (back_button.leftClicked())
        {
            changeScene(L"Title", 2s);
        }
        
        const auto& articles = getData().articles;
        for (int i = 0; i < articles.size(); ++i)
        {
            Rect rect(50,i * 100 + 50,1200,60);
            if(rect.leftClicked())
            {
                getData().articlesIndex = i;
                changeScene(L"News", 2s);
            }
        }
        
    }
    
    void draw() const override
    {
        const auto& articles = getData().articles;
        for (int i = 0; i < articles.size(); ++i)
        {
            Rect rect(50,i * 100 + 50,1200,60);
            rect.draw(Palette::Gray);
            news_font(articles[i].title).draw(rect.pos);
            news_preview_font(articles[i].preview).draw(rect.x + 800,rect.y + 15);
            detail_icon.drawAt(rect.x + 1150,rect.center().y);
        }
        
        back_button.draw(Palette::Orange);
        back_icon.drawAt(back_button.center);
    }
};

