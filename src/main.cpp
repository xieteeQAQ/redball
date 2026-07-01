#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <math.h>
#include <deque>

constexpr int fps = 90;
constexpr int width = 800;
constexpr int height = 600;
constexpr float radius = 20.0f;
constexpr float mass = 10.0f;
constexpr float G = 1000.0f;
constexpr float PI = 3.1415926535f;
int a = 40;
int b = 0;

struct State
{
    SDL_Window *win;
    SDL_Renderer *render;
};

struct Circle
{
    Circle() = default;
    Circle(float rudius, float mass, float x, float y, int r, int g, int b, int a) : _radius(rudius), _mass(mass), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a) {};

    void draw_circle(SDL_Renderer *renderer);
    void refresh(float dt);

    float _radius = 0;
    float _mass = 1.0f;
    float _veloc_x = 0;
    float _veloc_y = 0;
    float _acceler_x = 0;
    float _acceler_y = G;
    float _x = 0;
    float _y = 0;
    int _r = 0;
    int _g = 0;
    int _b = 0;
    int _a = 0;
};

std::deque<Circle> shadow;

void free_window(State state);

int main(int argc, char *argv[])
{

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    State state{SDL_CreateWindow("window", width, height, 0), SDL_CreateRenderer(state.win, nullptr)};
    if (!state.win)
    {
        std::cerr << "SDL_Window failed: " << SDL_GetError() << std::endl;
        free_window(state);
        return 1;
    }
    if (!state.render)
    {
        std::cerr << "SDL_Render failed: " << SDL_GetError() << std::endl;
        free_window(state);
        return 1;
    }

    Circle circle{radius, mass, width / 2.0f, height / 2.0f + 50.0f, 180, 0, 0, 255};

    const float dt = 1.0f / fps;
    bool running = true;
    const bool* keyboard = SDL_GetKeyboardState(nullptr);
    while (running)
    {
        SDL_Event event{0};
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            }
            if (keyboard[SDL_SCANCODE_W])
                a += 5;
            if (keyboard[SDL_SCANCODE_A])
                b -= 5;
            if (keyboard[SDL_SCANCODE_D])
                b += 5;
        }

        SDL_SetRenderDrawColor(state.render, 25, 25, 25, 255);
        SDL_RenderClear(state.render);
        circle.refresh(dt);
        for (int i = 0; i < shadow.size(); ++i)
        {
            shadow[i]._r -= 15;
            shadow[i]._b += 8;
            shadow[i].draw_circle(state.render);
        }
        if (shadow.size() < 4)
        {
            shadow.push_back(circle);
        }
        else
        {
            shadow.pop_front();
        }
        circle.draw_circle(state.render);
        SDL_RenderPresent(state.render);

        std::cout << "\rv_x: " << circle._veloc_x << ", v_y: " << circle._veloc_y << std::flush;

        SDL_Delay(static_cast<Uint32>(dt * 1000.0f));
    }

    free_window(state);

    return 0;
}

void free_window(State state)
{
    SDL_DestroyWindow(state.win);
    SDL_DestroyRenderer(state.render);
    SDL_Quit();
}

void Circle::draw_circle(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if (dx * dx + dy * dy <= radius * radius)
            {
                SDL_RenderPoint(renderer, _x + dx, _y + dy);
            }
        }
    }
}

void Circle::refresh(float dt)
{
    float Acc_y = 1500.0f;
    float Acc_x = 600.0f;
    if (a < 0)
        Acc_y = 0.0f;
    else
        --a;
    if (b < -5)
    {
        Acc_x = Acc_x < 0 ? Acc_x : -Acc_x;
        ++b;
    }
    else if (b > 5)
    {
        Acc_x = Acc_x > 0 ? Acc_x : -Acc_x;
        --b;
    }
    else
        Acc_x = 0.0f;

    float area = PI * _radius * _radius * 0.0001f;
    float speed_y = _veloc_y;
    float speed_x = _veloc_x;
    float drag_x = 0.5f * 0.1225f * 0.047f * area * speed_x * speed_x;
    float drag_y = 0.5f * 0.1225f * 0.047f * area * speed_y * speed_y;
    float dragAcc_x = _veloc_x > 0 ? -(drag_x / _mass) : (drag_x / _mass);
    float dragAcc_y = _veloc_y > 0 ? -(drag_y / _mass) : (drag_y / _mass);

    _acceler_y = G + dragAcc_y - Acc_y;
    _veloc_y += _acceler_y * dt;
    _y += _veloc_y * dt;

    if (_y > height - _radius)
    {
        _y = height - _radius;
        _veloc_y = -_veloc_y * 0.90f;
    }
    else if (_y < _radius)
    {
        _y = _radius;
        _veloc_y = -_veloc_y * 0.90f;
    }

    _acceler_x = Acc_x + dragAcc_x;
    _veloc_x += _acceler_x * dt;
    _x += _veloc_x * dt;

    if (_x > width - _radius)
    {
        _x = width - _radius;
        _veloc_x = -_veloc_x * 0.90f;
    }
    else if (_x < _radius)
    {
        _x = _radius;
        _veloc_x = -_veloc_x * 0.90f;
    }
}
