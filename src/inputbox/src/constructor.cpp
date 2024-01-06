#include <inputbox.hpp>

InputBox::InputBox(int fontSize, Rectangle relative, Frame* root, Font* font) : Interface(root, relative)
{
	
	this->fontSize = fontSize;
	this->font = font;
	this->showText= "";
	this->rawText = "";
	this->framesCounter = 0;
	this->isActivated = false;
	this->isFlicked = false;
	this->letterCount = 0;
}	

highScore::highScore(std::string path)
{
	list = std::vector<std::vector<std::pair<int, std::string>>>();
	linkContent(path);
	tmpName = "easy";
	tmpScore = 0;
}

