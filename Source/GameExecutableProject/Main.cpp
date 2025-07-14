#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "math.h"
#include <eTime.h>
#include "Math/Vector2.h"
#include "../Engine/Core/Random.h"
#include "../Engine/Renderer/Renderer (2).h"
#include "../Engine/Input/InputSystem.h"
#include <fmod.hpp>
#include "Input/InputSystem.h"


int main(int argc, char* argv[]) {
    //viper::InputSystem inputSystem;
    
    viper::Time time;
    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Screen", 1280, 1024);

    //SDL_Init(SDL_INIT_VIDEO);
    viper::InputSystem input;
    input.Initialize();

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    SDL_Event e;
    bool quit = false;
    
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
       

    }
    
    
    FMOD::Sound* sound = nullptr;
    audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);
    std::vector<FMOD::Sound*> sounds;
    audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    // Define a rectangle
    
    

    audio->playSound(sound, 0, false, nullptr);

    std::vector<viper::vec2> points;

    while (!quit) {
        time.Tick();
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        
        audio->update();

        input.Update();
        if (input.getKeyReleased(SDL_SCANCODE_A)) {

            std::cout << "Pressed \n";
        }


        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = input.GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }
  
        for (int i = 0; i < (int)points.size() - 1; i++) {
            // set color or random color
            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        

        viper::vec2 speed{ -140.0f, 0.0f };
        float length = speed.Length();

        viper::vec2 mouse = input.GetMousePosition();
        std::cout << mouse.x << " " << mouse.y << std::endl;

        /*renderer.SetColor(0, 0, 0);
        renderer.Clear();*/

        if (input.getKeyDown(SDL_SCANCODE_Q) && !input.getPrevKeyDown(SDL_SCANCODE_Q)) {
        
            audio->playSound(sounds[0], nullptr, false, nullptr);
        
        }
        if (input.getKeyDown(SDL_SCANCODE_W) && !input.getPrevKeyDown(SDL_SCANCODE_Q)) {
        
            audio->playSound(sounds[1], nullptr, false, nullptr);
        
        }
        if (input.getKeyDown(SDL_SCANCODE_E) && !input.getPrevKeyDown(SDL_SCANCODE_Q)) {
        
            audio->playSound(sounds[2], nullptr, false, nullptr);
        
        }
      
    
    }

        


        /*renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
        renderer.DrawLine(viper::random::getRandomInt(1280), viper::random::getRandomInt(1280), viper::random::getRandomInt(1280), viper::random::getRandomInt(1280));
        renderer.Present();*/


        
        /*for (auto& star : stars) {
            star += speed * time.GetDeltaTime();


            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(star.x, star.y);

        }*/
        

        renderer.Present();
        renderer.ShutDown();
        //SDL_Quit();

        return 0;
}








    //for (int i = 0; i < 10; i++) {

    //    SDL_SetRenderDrawColor(renderer, viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256)); // Set render draw color to black
    //    //SDL_RenderClear(renderer); // Clear the renderer
    //    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set render draw color to green
    //    SDL_RenderLine(renderer, viper::random::getRandomInt(1280), viper::random::getRandomInt(1280), viper::random::getRandomInt(1280), viper::random::getRandomInt(1280));

    //    SDL_RenderPoint(renderer, viper::random::getRandomInt(1280), viper::random::getRandomInt(1280));
    //    SDL_RenderPoint(renderer, viper::random::getRandomInt(1280), viper::random::getRandomInt(1280));

    //    SDL_RenderPresent(renderer); // Render the screen
    //}
    //

    /*SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);*/
   
   