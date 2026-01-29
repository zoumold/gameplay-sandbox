#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]){
    SDL_Window* window;
    bool running = true;
    SDL_Event event;
    SDL_Renderer* render;
    SDL_Rect rect{100,100,50,50};
    const Uint8* keyboard;
    Uint32 lastTick, currentTick;
    float deltaTime, speed = 200.0f;

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "DSL_Init error:" << SDL_GetError() << std::endl;
        return 1;
    }

    //Create window
    window = SDL_CreateWindow("Sandbox Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
    
    if(!window){
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    //Create Render
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!render){
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    lastTick = SDL_GetTicks();

    //Main loop
    while(running){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
        }

        currentTick = SDL_GetTicks();
        float deltaTime = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;

        SDL_SetRenderDrawColor(render, 20, 20, 20, 255);
        SDL_RenderClear(render);

        SDL_SetRenderDrawColor(render,200,50,50,255);
        SDL_RenderFillRect(render, &rect);

        keyboard = SDL_GetKeyboardState(nullptr);

        if (keyboard[SDL_SCANCODE_W]) rect.y -= speed * deltaTime;
        if (keyboard[SDL_SCANCODE_S]) rect.y += speed * deltaTime;
        if (keyboard[SDL_SCANCODE_A]) rect.x -= speed * deltaTime;
        if (keyboard[SDL_SCANCODE_D]) rect.x += speed * deltaTime;

        SDL_RenderPresent(render);

        SDL_Delay(1);
    }    

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    return 0;
}