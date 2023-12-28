#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <raylib.h>

#include <frame.hpp>
#include <container.hpp>
#include <request.hpp>
#define TRANSPARENT Color {127, 127, 127, 0}
#define rectangle this->getFrame()



class ButtonImage : public Container
{
private:
    static constexpr int DPI = 500;
    static constexpr float CORNER_RADIUS = 0.3;

    int numpath;
    int tmpPath;
    int releaseID;
    int hoverID;
    int pressingID;
    int clickedID;

    // Rectangle rectangle;
    Color color;

    bool isHover = false;
    bool pressing = false, clicked = false;

    std::vector <Action*> actions;
    Request* request;

protected:
    void loadEvent(YAML::Node node);
    void loadAction(YAML::Node node);

public:
    ButtonImage(Frame* parrent, Rectangle relative);
    ~ButtonImage();
    void draw();
    PacketAction* react();

    void changeIndex(int newindex);
    void changePosition(Rectangle change);
    [[nodiscard]] bool isClicked() const;
    [[nodiscard]] bool isPressing() const;
    int getClicked();

    std::string linkContent(std::string);
    std::string linkContentAbsolute(std::string);

};

#endif 
