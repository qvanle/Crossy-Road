#include <iostream>

#include <window.hpp>

int main()
{
    // Window win("window.yaml");
    // win.run();
    highScore hs("saving/highscore.txt");
    std::cout << "Origin high score:" << std::endl;
    std::vector<std::pair<int, std::string>> list = hs.getList();
    for (auto i : list)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
    hs.add("Huy", 100);
    hs.add("linh chi", 300);
    std::cout << "New high score:" << std::endl;
    std::vector<std::pair<int, std::string>> list2 = hs.getList();
    for (auto i : list2)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
    // hs.save("saving/highscore.txt");
    return 0;
}
