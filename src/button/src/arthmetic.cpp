#include <button.hpp>



void Button::draw() {
  
    DrawRectangleRoundedLines(
            {
                this->getFrame().x + 1,
                this->getFrame().y + 1,
                this->getFrame().width - 2,
                this->getFrame().height - 2
                },
            this->isSuggest ? 0 : CORNER_RADIUS,
            DPI,
            3,
            this->color
            );

    DrawRectangleRounded(
            this->getFrame(),
            CORNER_RADIUS,
            DPI,
            this->colorBG
            );

    DrawText(
            this->text.c_str(),
            this->getFrame().x + this->getFrame().width / 2,
            this->getFrame().y + this->getFrame().height / 2,
            this->fontSize,
            RED
            );
}

void Button::handleEvents() {
    this->clicked = false;
    this->colorBG = isSuggest ? WHITE : TRANSPARENT;

    if (CheckCollisionPointRec(GetMousePosition(), this->getFrame())) {
        this->colorBG = LIGHTGRAY;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            this->pressing = true;
            this->colorBG = GRAY;
        } else if (this->pressing) {
            this->pressing = false;
            this->clicked = true;
        }
    } else {
        this->colorBG = isSuggest ? WHITE : TRANSPARENT;
        this->pressing = false;
    }
}

void Button::update() {
    if (this->isChosen)
        this->colorBG = GRAY;
}

Action *Button::react()
{
    return nullptr;
}

bool Button::isClicked() const {
    return this->clicked;
}

void Button::setChosen(bool _isChosen) {
    this->isChosen = _isChosen;
}
void Button::setIsSuggest() {
    this->isSuggest = true;
}


// Button for image

void ButtonImage::draw() {
    if(!isVisible()) return;
    this->Container::draw();
}

Action* ButtonImage::react() {
   
    if (CheckCollisionPointRec(GetMousePosition(), rectangle)) {
        this->isHover = 1;
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) { // click -> pressing
            this->clicked = true;
            if(this->pressingID == -1)
                return nullptr;
            return actions[pressingID]->clone(); 
        }
        else if(this->clicked) { // release -> click
            
            this->clicked = false;
            if(this->clickedID == -1)
                return nullptr;
            return actions[clickedID]->clone();
        }
        if(this->hoverID == -1)
            return nullptr;
        return actions[hoverID]->clone();
    }
    if (this->isHover == 1)
    {
        this->isHover = 0;
        if(this->releaseID == -1)
            return nullptr;
        return actions[releaseID]->clone();
    }
    return nullptr;
}



void ButtonImage::changeIndex(int newindex)
{
    tmpPath = newindex;
}

int ButtonImage::getClicked()
{
    return tmpPath;
}

bool ButtonImage::isClicked() const {
    return this->clicked;
}
