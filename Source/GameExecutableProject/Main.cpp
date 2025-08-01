#include "AudioSystem.h"
#include "Core/Random.h"
#include "eTime.h"
#include "File.h"
#include "Input/InputSystem.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Transform.h"
#include "Actor.h"
#include "Scene.h"
#include "Renderer/Renderer (2).h"
#include "Model.h"
#include "Font.h"
#include "Text.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Engine.h"
#include <fmod.hpp>  
#include <vector>
#include <SDL3/SDL.h>
#include <memory>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;
using namespace viper;



int main(int argc, char* argv[]) {

   
    viper::file::SetCurrentDirectory("Assets");

    
    GetEngine().Initialize();

    
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    
    SDL_Event e;
    bool quit = false;

   
    GetEngine().GetAudio().AddSound("bass.wav", "bass");
    GetEngine().GetAudio().AddSound("snare.wav", "snare");
    GetEngine().GetAudio().AddSound("open-hat.wav", "openhat");
    GetEngine().GetAudio().AddSound("clap.wav", "clap");
    GetEngine().GetAudio().AddSound("cowbell.wav", "cowbell");
    GetEngine().GetAudio().AddSound("close-hat.wav", "closehat");

    
    vector<vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(vec2{ random::getRandomFloat() * GetEngine().GetRenderer().GetWidth(), random::getRandomFloat() * GetEngine().GetRenderer().GetHeight() });
    }


    
    while (!quit) {
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        GetEngine().Update();
        game->Update(GetEngine().GetTime().GetDeltaTime());

        if (GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

       

        vec3 color{ 0,0,0 };
        GetEngine().GetRenderer().SetColor(color.x, color.y, color.z);
        GetEngine().GetRenderer().Clear();

       
       
        game->Draw(GetEngine().GetRenderer());

       


        
        vec2 star_speed{ -140.0f,0.0f };
        float length = star_speed.Length();

        for (auto& star : stars) {
            star += star_speed * GetEngine().GetTime().GetDeltaTime();
            

            if (star[0] > GetEngine().GetRenderer().GetWidth()) star[0] = 0;
            if (star[0] < 0) star[0] = GetEngine().GetRenderer().GetWidth();
            GetEngine().GetRenderer().SetColor((uint8_t)(random::getRandomInt(256)), random::getRandomInt(256), random::getRandomInt(256));
            GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }

        

        GetEngine().GetRenderer().Present();
    }

   
    game->Shutdown();
    game.release();
    GetEngine().Shutdown();

    return 0;
}