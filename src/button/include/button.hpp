#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <raylib.h>

#include <frame.hpp>
#include <container.hpp>
#include <request.hpp>
#include <const/request.hpp>
#define TRANSPARENT Color {127, 127, 127, 0}
#define rectangle this->getFrame()

/**
 * @class ButtonImage
 *
 * @brief manages the appearance and behavior of a button
 * 
**/
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

class popInfRequest : public Request
{
public:
    popInfRequest();
    popInfRequest(popInfRequest*);
    ~popInfRequest() = default;
    int isRequest() override;
    Action* clone() override;
};

class popThenChangeInfRequest : public Request
{
public:
    popThenChangeInfRequest(std::string s);
    popThenChangeInfRequest(popThenChangeInfRequest*);
    ~popThenChangeInfRequest() = default;
    int isRequest() override;
    Action* clone() override;
    ARGS& getArgs() override;
};

class loadGameRequest : public Request 
{
public:
    loadGameRequest() = default;
    ~loadGameRequest() = default;
    int isRequest() override;
    Action* clone() override;
};

class toggleMusicRequest : public Request
{
public:
    toggleMusicRequest() = default;
    ~toggleMusicRequest() = default;
    int isRequest() override;
    Action* clone() override;
};

class closeInputboxRequest : public Request
{
public:
    closeInputboxRequest();
    closeInputboxRequest(closeInputboxRequest*);
    ~closeInputboxRequest() = default;
    int isRequest() override;
    Action* clone() override;
};

class openInputboxRequest : public Request
{
public:
    openInputboxRequest();
    openInputboxRequest(openInputboxRequest*);
    ~openInputboxRequest() = default;
    int isRequest() override;
    Action* clone() override;
};

#endif 
