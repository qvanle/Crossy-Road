#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <raylib.h>

#include <frame.hpp>
#include <container.hpp>

#define TRANSPARENT Color {127, 127, 127, 0}
#define rectangle this->getFrame()

class Button : public Container {
private:
    static constexpr int DPI = 500;
    static constexpr float CORNER_RADIUS = 0.3;

    std::string text;
    Vector2 positionText;
    int fontSize;

    Color color, colorBG;
    // Rectangle rectangle;

    bool isSuggest = false;
    bool pressing = false, clicked = false, isChosen = false;

public:
    Button(std::string text, int fontSize, Color color, Frame* parrent, Rectangle rel);

    void draw();
    void handleEvents();
    void update();

    [[nodiscard]] bool isClicked() const;
    [[nodiscard]] bool isPressing() const;

    void setChosen(bool isChosen);
    void setIsSuggest();
    void setBG(Color colorBG);
};

class ButtonImage : public Container
{
private:
    static constexpr int DPI = 500;
    static constexpr float CORNER_RADIUS = 0.3;

    std::vector <std::string> path;
    std::vector <std::string> pathPress;

    int numpath;
    int tmpPath;

    // Rectangle rectangle;
    Color color;

    bool isHover = false;
    bool pressing = false, clicked = false;

    std::vector <Texture> texture;
    std::vector <Texture> texturePress;

public:
    ButtonImage(std::vector <std::string> path, std::vector <std::string> pathPress, Rectangle rec);
    void draw();
    void handleEvents();
    void update();
    void changeIndex(int newindex);
    void changePosition(Rectangle change);
    [[nodiscard]] bool isClicked() const;
    [[nodiscard]] bool isPressing() const;
    int getClicked();
};

#endif 
