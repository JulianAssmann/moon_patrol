#ifndef EXIT_GAME_CONTROLLER_H
#define EXIT_GAME_CONTROLLER_H

#include <functional>

class ExitGameController : public Controller
{
public:
    /// @brief Constructor
    ExitGameController(std::shared_ptr<Model> model, std::function<void()> callback)
        : Controller(model), exitGameCallback(callback) {};

    /// @brief Handle input
    /// @param model The model to update
    /// @param dt The delta time since the last update
    void update(SDL_Event &event, float dt) override
    {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)))
        {
            exitGameCallback();
        }
    }

private:
    std::function<void()> exitGameCallback;
};

#endif // EXIT_GAME_CONTROLLER_H