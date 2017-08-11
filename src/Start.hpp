# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"

struct Start : MyApp::Scene //start画面
{
    const Circle m_backButton = Circle(960,900,60);
    const Texture m_backIcon = Texture(Icon(0xf112,60));
    
    const Texture m_dataIcon = Texture(Icon(0xf0c9,45));//横３本

    const Font m_newsFont = Font(45);
    const Font m_newsPreviewFont = Font(20);
    
    //現在の時間,日付など
    const Font m_yearFont = Font(50);//何年かと何秒かのフォントの大きさ
    const Font m_dateFont = Font(80);
    const Font m_timeFont = Font(180);
    
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
        if (m_backButton.leftClicked())
        {
            changeScene(L"Title", RRYY::FadeTime);
        }
        
        const auto& articles = getData().articles;
        
        for (int i = 0; i < articles.size(); ++i)
        {
            const Rect rect(50,i * 100 + 50,1200,60);
            if(rect.leftClicked())
            {
                getData().articlesIndex = i;
                changeScene(L"News", RRYY::FadeTime);
            }
        }
    }
    
    void draw() const override
    {
        Graphics::SetBackground(getData().getBackgroundColor());
        
        const auto& articles = getData().articles;
        for (int i = 0; i < articles.size(); ++i)
        {
            const Rect rect(50,i * 100 + 50,1200,60);
            rect.draw(Palette::Gray);
            m_newsFont(articles[i].title).draw(rect.pos);
            m_newsPreviewFont(articles[i].getPreview()).draw(rect.x + 800,rect.y + 15);
            m_dataIcon.drawAt(rect.x + 1150,rect.center().y);
        }
        
        m_backButton.draw(Palette::Orange);
        m_backIcon.drawAt(m_backButton.center);
        
        //現在の時間など
        const DateTime now = DateTime::Now();
        m_yearFont(now.format(L"yyyy年")).draw(1300,150,Palette::Black);//年
        m_dateFont(now.format(L"MM月dd日(E)")).draw(1300,200,Palette::Black);//月/日(曜)
        m_timeFont(now.format(L"H:mm")).draw(1300,300,Palette::Black);//時,分
    }
};

