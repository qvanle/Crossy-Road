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
	std::ifstream fi;
	fi.open(path);
	if (fi.is_open())
	{
		std::string name;
		int score;
		std::string line;
		while (getline(fi, line))
		{
			std::stringstream ss(line);
			ss >> score;
			char space;
			//ss >> space;
			getline(ss, name);
			if(name[0] = ' ') name.erase(0, 1);
			list.push_back(std::make_pair(score, name));
		}
	}
	fi.close();
}