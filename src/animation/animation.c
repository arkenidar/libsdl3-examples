// animation example: two translucent rectangles sliding across the window at
// different speeds, using frame delta time. No assets required.
//
// Lean and self-contained: only ensure() and a minimal quit/escape event loop.

#include <SDL3/SDL.h>
#include <stdio.h>

// Log an SDL error when a bool-returning SDL call reports failure.
static void ensure(bool ok)
{
    if (!ok)
        printf("SDL error: %s\n", SDL_GetError());
}

// Pump SDL events. Returns 0 to quit (window closed or Escape), 1 otherwise.
static int events(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            return 0;
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    ensure(SDL_Init(SDL_INIT_VIDEO));
    int view_width = 400, view_height = 300;
    SDL_Window *window;
    SDL_Renderer *renderer;
    ensure(SDL_CreateWindowAndRenderer("animation", view_width, view_height, SDL_WINDOW_RESIZABLE, &window, &renderer));

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    double x1 = 0;
    double x2 = 0;

    Uint64 lastTime = SDL_GetTicks(), currentTime;
    while (events())
    {
        currentTime = SDL_GetTicks();
        Uint64 dt = currentTime - lastTime;
        lastTime = currentTime;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        x1 += dt * 0.02;
        if (x1 > 150)
            x1 = 0;
        SDL_FRect button1 = {.x = x1, .y = 10, .w = 50, .h = 50};
        int button_color[] = {0, 50, 50};
        SDL_SetRenderDrawColor(renderer, button_color[0], button_color[1], button_color[2], 100);
        SDL_RenderFillRect(renderer, &button1);

        x2 += dt * 0.08;
        if (x2 > 150)
            x2 = 0;
        SDL_FRect button2 = {.x = x2, .y = 10 + 50 + 10, .w = 50, .h = 50};
        // int button_color[] = { 0, 50, 50 };
        SDL_SetRenderDrawColor(renderer, button_color[0], button_color[1], button_color[2], 50);
        SDL_RenderFillRect(renderer, &button2);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
