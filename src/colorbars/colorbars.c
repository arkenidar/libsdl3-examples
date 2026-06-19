// colorbars example: cycles through a palette as vertical bars, one added every
// half second, with a small button in the corner that quits when clicked. No
// assets required.
//
// Lean and self-contained: ensure(), a minimal quit/escape event loop, plus the
// in_rect() hit-test and draw_colors() helper this example uses.

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

static int in_rect(float x, float y, const SDL_FRect *r)
{
    return (x >= r->x) && (y >= r->y) &&
           (x < r->x + r->w) && (y < r->y + r->h);
}

static int rgb[][3] = {
    {203, 203, 203}, // Gray
    {254, 254, 31},  // Yellow
    {0, 255, 255},   // Cyan
    {0, 0, 0},       // Black
    {0, 254, 30},    // Green
    {255, 16, 253},  // Magenta
    {253, 3, 2},     // Red
    {18, 14, 252}    // Blue
};
static int rgb_size = sizeof rgb / sizeof rgb[0];

static void draw_colors(SDL_Renderer *renderer, int i_current, int view_width, int view_height)
{

    SDL_FRect colorBar;
    colorBar.x = 0;
    colorBar.y = 0;
    colorBar.w = view_width / rgb_size;
    colorBar.h = view_height;

    int *color;
    SDL_FRect rectangle;

    int background_color[] = {50, 50, 50};
    for (int i = -1; i <= i_current; i++)
    {
        if (i == -1)
        {
            color = background_color;
            SDL_FRect view = {.x = 0, .y = 0, .w = view_width, .h = view_height};
            rectangle = view;
        }
        else
        {
            color = rgb[i];
            colorBar.x = i * colorBar.w;
            rectangle = colorBar;
        }
        SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
        SDL_RenderFillRect(renderer, &rectangle);
    }
}

int main(int argc, char *argv[])
{
    ensure(SDL_Init(SDL_INIT_VIDEO));
    int view_width = 400, view_height = 300;
    SDL_Window *window;
    SDL_Renderer *renderer;
    ensure(SDL_CreateWindowAndRenderer("colorbars", view_width, view_height, SDL_WINDOW_RESIZABLE, &window, &renderer));

    int i = -1;
    Uint64 lastTime = SDL_GetTicks(), currentTime;
    while (events())
    {

        SDL_GetWindowSize(window, &view_width, &view_height);

        draw_colors(renderer, i, view_width, view_height);

        int button_color[] = {0, 50, 50};
        SDL_FRect button = {.x = 10, .y = 10, .w = 50, .h = 50};
        SDL_SetRenderDrawColor(renderer, button_color[0], button_color[1], button_color[2], 255);
        SDL_RenderFillRect(renderer, &button);

        float x, y;
        SDL_MouseButtonFlags buttons;
        SDL_PumpEvents();
        buttons = SDL_GetMouseState(&x, &y);
        if ((buttons & SDL_BUTTON_LMASK) != 0 && in_rect(x, y, &button))
        {
            SDL_Event quit_event;
            quit_event.type = SDL_EVENT_QUIT;
            SDL_PushEvent(&quit_event);
        }

        SDL_RenderPresent(renderer);

        currentTime = SDL_GetTicks();
        if (currentTime >= lastTime + 500)
        {
            i += 1;
            lastTime = currentTime;
        }
        if (i >= rgb_size)
            i = -1;
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
