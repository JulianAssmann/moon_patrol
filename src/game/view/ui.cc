#include "ui.h"

GameplayUI::GameplayUI() : 
    container(Rect(0.0f, 0.0f, 1.0f, uiHeight)),
    subcontainer(Rect(0.33f, 0.1f * uiHeight, 0.5f, 0.6 * uiHeight)),
    progressBarBackground(Rect(0.33f, 0.85 * uiHeight, 0.5f, 0.1f * uiHeight)),
    progressBarForeground(Rect(0.33f, 0.85 * uiHeight, 0.25f, 0.1f * uiHeight)) {
    
}

void GameplayUI::render(std::shared_ptr<SDL_Renderer> renderer, const Camera& camera) const {
    SDL_Rect rect;

    // Render main UI container
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 255, 255);
    rect = camera.cameraToScreen(container).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render subcontainer
    SDL_SetRenderDrawColor(renderer.get(), 97, 255, 255, 255);
    rect = camera.cameraToScreen(subcontainer).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render progress bar background
    SDL_SetRenderDrawColor(renderer.get(), 97, 255, 255, 255);
    rect = camera.cameraToScreen(progressBarBackground).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);

    // Render progress bar foreground
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
    rect = camera.cameraToScreen(progressBarForeground).toSDLRect();
    SDL_RenderFillRect(renderer.get(), &rect);
}