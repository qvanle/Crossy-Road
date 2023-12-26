#include <inputbox.hpp>

void InputBox::draw()
{
    DrawRectangleRec(this->getFrame(), LIGHTGRAY); // can change by texture in yaml file

    if (isActivated) DrawRectangleLines((int)this->getFrame().x, (int)this->getFrame().y, (int)this->getFrame().width, (int)this->getFrame().height, RED);
    else DrawRectangleLines((int)this->getFrame().x, (int)this->getFrame().y, (int)this->getFrame().width, (int)this->getFrame().height, DARKGRAY);

    DrawText(rawText.c_str(), (int)this->getFrame().x + 5, (int)this->getFrame().y + 8, this->fontSize, MAROON);
    if (isActivated)
    {
        if (letterCount < MAX_LENGTH)
        {
            // Draw blinking underscore char
            if (((framesCounter/20)%2) == 0) DrawText("_", (int)this->getFrame().x + 8 + MeasureText(rawText.c_str(), this->fontSize), (int)this->getFrame().y + 12, this->fontSize, MAROON);
        }
    }
    //std::cout<<rawText<<std::endl; // for debug
}

void InputBox::handle()
{
    if (CheckCollisionPointRec(GetMousePosition(), this->getFrame())) isActivated = true;
        else isActivated = false;

        if (isActivated)
        {
            // Set the window's cursor to the I-Beam
            //SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_LENGTH))
                {
                    rawText[letterCount] = (char)key;
                    rawText[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                rawText[letterCount] = '\0';
            }
        }
        //else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (isActivated) framesCounter++;
        else framesCounter = 0;
}

void InputBox::update()
{
    // int head = rawText.length() - MAX_VISIBLE;
    // if(head < 0) head = 0;
    // showText = rawText.substr(head, MAX_VISIBLE); // why it not work?
    // if(head > 0)
    //     showText = "..." + showText;
    // std::cout<<showText<<std::endl; // for debug
}

    