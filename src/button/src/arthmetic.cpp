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
            // this->positionText.x,  
            //this->positionText.y,
            this->getFrame().x + this->getFrame().width / 2,
            this->getFrame().y + this->getFrame().height / 2,
            this->fontSize,
            // this->color
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
    if (!this->isSuggest)
        DrawTexture(texture[tmpPath], rectangle.x, rectangle.y, WHITE);
    else
        DrawTexture(texturePress[tmpPath], rectangle.x, rectangle.y, WHITE);
}

void ButtonImage::handleEvents() {
    this->clicked = false;
    if (CheckCollisionPointRec(GetMousePosition(), this->rectangle)) {
        this->isSuggest = true;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            this->pressing = true;

        }
        else if (this->pressing) {
            this->pressing = false;
            this->clicked = true;
        }
    }
    else {
        this->color = WHITE;
        this->pressing = false;
        this->isSuggest = false;
    }

}

void ButtonImage::update() {
    if (this->isClicked())
    {
        this->tmpPath = (this->tmpPath + 1) % numpath;
    }
}

void ButtonImage::changeIndex(int newindex)
{
    tmpPath = newindex;
}

void ButtonImage::changePosition(Rectangle change)
{
    this->rectangle = change;
}

int ButtonImage::getClicked()
{
    return tmpPath;
}

bool ButtonImage::isClicked() const {
    return this->clicked;
}
