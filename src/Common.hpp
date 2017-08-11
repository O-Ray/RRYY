# pragma once
# include <Siv3D.hpp>
# include "Scene.hpp"

namespace RRYY {
    const auto FadeTime = 0.1s;
}
struct Article
{
    String title;
    String preview;
    String body;
};

struct AppData
{
    Array<Article> articles;
    int articlesIndex = 0;
};

Article LoadArticle(const FilePath& path)
{
    TextReader reader(path);
    
    String title;
    reader.readLine(title);
    
    String body,line;
    while (reader.readLine(line))
    {
        body += line;
    }
    
    Article article;
    article.title = title;
    article.preview = body.substr(0,10);
    article.body = body;
    return article;
}

using MyApp = SceneManager<String, AppData>;
