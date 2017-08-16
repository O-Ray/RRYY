# pragma once
# include <Siv3D.hpp>
# include "Common.hpp"

bool IsNewsFile(const FilePath& path)
{
    return path.ends_with(L".txt");
}

struct Start : MyApp::Scene //start画面
{
    const Circle m_backButton = Circle(960,50,60);//バックボタン
    const Texture m_backIcon = Texture(Icon(0xf112,60));//バックボタンアイコン
    
    
    const Circle m_reloadButton = Circle(800,50,60);//リロードボタン
    const Texture m_reloadIcon = Texture(Icon(0xf01e,60));//リロードボタンアイコン
    
    const Texture m_dataIcon = Texture(Icon(0xf0c9,45));//横３本

    const Font m_newsFont = Font(45);
    const Font m_newsPreviewFont = Font(20);
    
    //現在の時間,日付など
    const Font m_yearFont = Font(50);//何年かと何秒かのフォントの大きさ
    const Font m_dateFont = Font(80);
    const Font m_timeFont = Font(180);
    
    const Rect m_dateBackRect = Rect(1260,0,660,600);
    
    int m_scroll = 0;//マウスのスクロールがどれくらいか？(!= "px")
    
    Start(const InitData& init)
    : IScene(init)
    {
        getData().articles.clear();
        const Array<FilePath> files = FileSystem::DirectoryContents(L"news/").filter(IsNewsFile);
        
        for(const FilePath& file:files)
        {
            getData().articles.push_back(LoadArticle(file));
        }
    }
    
    void update() override
    {
        if (m_backButton.leftClicked())
        {
            changeScene(L"Title", RRYY::FadeTime);
            return;
        }
        
        if (m_reloadButton.leftClicked())
        {
            changeScene(L"Start", RRYY::FadeTime);
            return;
        }
        
        const auto& articles = getData().articles;
        
        for (int i = 0; i < articles.size(); ++i)
        {
            const Rect rect(50,i * 100 + 200 - m_scroll,1200,60);
            if(rect.leftClicked())
            {
                getData().articlesIndex = i;
                changeScene(L"News", RRYY::FadeTime);
            }
        }
        
         m_scroll += (Mouse::Wheel() * 30);//スクロールした分を計算
    }
    
    void draw() const override
    {
        Graphics::SetBackground(getData().getBackgroundColor());
        
        const auto& articles = getData().articles;
        for (int i = 0; i < articles.size(); ++i)
        {
            const Rect rect(50,i * 100 + 200 - m_scroll,1200,60);
            rect.draw(Palette::Gray);
            m_newsFont(articles[i].title).draw(rect.pos);
            m_newsPreviewFont(articles[i].getPreview()).draw(rect.x + 800,rect.y + 15);
            m_dataIcon.drawAt(rect.x + 1150,rect.center().y);
        }
        
        //現在の時刻の背景の四角
        m_dateBackRect.draw(Palette::White);
        
        //現在の時間など
        const DateTime now = DateTime::Now();
        m_yearFont(now.format(L"yyyy年")).draw(1300,150,Palette::Black);//年
        m_dateFont(now.format(L"MM月dd日(E)")).draw(1300,200,Palette::Black);//月/日(曜)
        m_timeFont(now.format(L"H:mm")).draw(1300,300,Palette::Black);//時,分
        
        
        //バックボタン
        m_backButton.draw(Palette::Orange);
        m_backIcon.drawAt(m_backButton.center);
        
        //リロードボタン
        m_reloadButton.draw(Palette::Orange);
        m_reloadIcon.drawAt(m_reloadButton.center);
    }
};

