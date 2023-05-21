#include "mvc/game.h"
#include "game/gameplay_scene.h"
#include "utils/size.h"

const int SCREEN_WIDTH = 400 * 1.5;
const int SCREEN_HEIGHT = 400 * 1.5;

int main(int argc, char *argv[])
{
    Game game("Moon Patrol", Size(SCREEN_WIDTH, SCREEN_HEIGHT), 60);
    game.setScene(new GameplayScene(&game));
    game.run();
    return 0;
}