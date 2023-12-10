#include <button.hpp>
Button::Button(std::string text, int fontSize, Color color, Frame* parrent, Rectangle rel) : Container(parrent, rel) {
    this->text = std::move(text);
    this->fontSize = fontSize;
    this->color = color;
    // this->rectangle = rectangle;
    this->colorBG = WHITE;

    // Calculate text width and height
    float textWidth = MeasureText(this->text.c_str(), fontSize);
    float textHeight = fontSize; // Assuming font size is 20, you can change this accordingly

    // Calculate the position to center the text in the rectangle
    float posX = rectangle.x + (rectangle.width - textWidth) / 2.0;
    float posY = rectangle.y + (rectangle.height - textHeight) / 2.0;

    this->positionText = {posX, posY};

    
}

// Button for Image
ButtonImage::ButtonImage(std::vector<std::string> path, std::vector <std::string> pathPress, Frame* parrent, Rectangle rel) : Container(parrent, rel)
{
    this->path = path;
    this->pathPress = pathPress;
    // this->rectangle = rectangle;
    this->numpath = path.size();
    this->tmpPath = 0;
    this->color = WHITE;
    for (int i = 0; i < numpath; i++)
    {
        Texture tmp = LoadTextureFromImage(LoadImage(path[i].c_str()));
        this->texture.push_back(tmp);
        Texture tmpPress = LoadTextureFromImage(LoadImage(pathPress[i].c_str()));
        this->texturePress.push_back(tmpPress);
    }
}