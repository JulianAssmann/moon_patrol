#include "game.h"

Game::Game(const char* title, Size screenSize, uint targetFps) {
    this->title = title;
    this->screen_size = screenSize;

    this->targetFps = targetFps;
    this->targetFrameTime = 1000 / targetFps;

    init_sdl();
}

void Game::exitGame() { 
    is_running = false; 
}

Size Game::getScreenSize() {
    return screen_size;
}

void Game::init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    // Window and renderer creation
    this->window = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                         screen_size.width, screen_size.height, SDL_WINDOW_SHOWN),
        [](SDL_Window *w) { if (w) SDL_DestroyWindow(w); });

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    this->renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
        [](SDL_Renderer *r) { if (r) SDL_DestroyRenderer(r); });

    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(1);
    }
}

void Game::clearScreen() {
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer.get());
}

void Game::run() {
    std::cout << "Running game" << std::endl;

    is_running = true;

    uint32_t currentTime = SDL_GetTicks();

    // Accumulator for fixed timestep updates
    uint32_t accumulator = 0;

    while (is_running) {
        // Calculate the time since the last frame
        uint32_t newTime = SDL_GetTicks();
        uint32_t frameTime = newTime - currentTime;
        currentTime = newTime;

        // Update the accumulator
        accumulator += frameTime;

        // Perform fixed timestep updates until the accumulator is empty
        // If the game is lagging, we will perform multiple updates per frame to catch up
        // This is to prevent the game from "freezing" when the framerate is low
        while (accumulator >= targetFrameTime) {
            float dt = (targetFrameTime) / 1000.0;

            // Perform game logic updates
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    exitGame();
                }
                handleEvent(event, dt);
            }
            update(dt);

            // Update the accumulator
            accumulator -= targetFrameTime;
        }

        // Render the game
        clearScreen();
        render();

        // Present the rendered frame
        SDL_RenderPresent(renderer.get());
    }
}

void Game::handleEvent(SDL_Event event, float dt) {
    currentScene->handleEvent(event, dt);
}

void Game::update(float dt) {
    currentScene->update(dt);
}

void Game::render() {
    currentScene->render();
}

Game::~Game() {
    delete currentScene;
    SDL_Quit();
    IMG_Quit();
}

void Game::setScene(Scene *scene)
{
    delete currentScene;
    currentScene = scene;
    currentScene->init();
}
