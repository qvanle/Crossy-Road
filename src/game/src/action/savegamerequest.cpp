#include <game.hpp>
#include <const/request.hpp>

int saveGameRequest::isRequest()
{
    return REQUEST::ID::SAVE_GAME;
}
