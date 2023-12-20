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
ButtonImage::ButtonImage(Frame* parrent, Rectangle rel) : Container(parrent, rel)
{
    // this->rectangle = rectangle;
}

std::string ButtonImage::linkContent(std::string path)
{
    
    return linkContentAbsolute(PATB::BUTTON_ + path);
}

std::string ButtonImage::linkContentAbsolute(std::string path)
{
    YAML::Node node = YAML_FILE::readFile(path);
    if(!loadName(node)) return "";
    
    if(node["textures"])
    {
        
        loadSprites(node["textures"]);
    }

    return getName();
}