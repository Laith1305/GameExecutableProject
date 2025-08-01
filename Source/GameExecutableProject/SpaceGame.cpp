#include "SpaceGame.h"

#include "Core/Random.h"
#include "Scene.h"
#include "Math/Vector2.h"
#include "Player.h"
//#include "Renderer/Font.h"
#include "Model.h"
#include "Renderer/Renderer (2).h"
//#include "Renderer/Text.h"
#include "Engine.h"
#include "Input/InputSystem.h"

#include <vector>
#include "Enemy.h"
#include "GameData.h"
#include "ParticleSystem.h"

bool SpaceGame::Initialize() {
    scene = std::make_unique<viper::Scene>(this);

    titleFont = std::make_shared<viper::Font>();
    titleFont->Load(GameData::gameFont, 128);

    uiFont = std::make_shared<viper::Font>();
    uiFont->Load(GameData::gameFont, 48);

    titleText = std::make_unique<viper::Text>(titleFont);
    scoreText = std::make_unique<viper::Text>(uiFont);
    livesText = std::make_unique<viper::Text>(uiFont);

    return true;
}

void SpaceGame::Update(float dt) {

    switch (gameState) {
    case SpaceGame::GameState::Initialize:
        gameState = GameState::Title;
        break;
    case SpaceGame::GameState::Title:
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            gameState = GameState::StartGame;
        }
        break;
    case SpaceGame::GameState::StartGame:
        score = 0;
        lives = 3;
        gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::StartRound:
    {
        scene->RemoveAllActors();
        // CREATE PLAYER
        std::shared_ptr<viper::Model> ship_model = std::make_shared<viper::Model>(GameData::ship_points, viper::vec3{ 0.37f, 1, 0.16f });
        viper::Transform transform{ viper::vec2{ viper::GetEngine().GetRenderer().GetWidth() * 0.5f , viper::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 2 };
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, ship_model);

        player->speed = 500.0f;
        player->rotationRate = 180.0f;
        player->damping = 0.5f;
        player->name = "player";
        player->tag = "player";

        scene->AddActor(std::move(player));

        gameState = GameState::Game;
        break;
    }
    case SpaceGame::GameState::Game:
        enemySpawnTimer -= dt;
        if (enemySpawnTimer <= 0) {
            enemySpawnTimer = 2;

            // CREATE ENEMY
            SpawnEnemy();
        }
        break;
    case SpaceGame::GameState::PlayerDead:
        stateTimer -= dt;
        if (stateTimer <= 0) {
            lives--;
            if (lives == 0) { gameState = GameState::GameOver; stateTimer = 3; }
            else { gameState = GameState::StartRound; }
        }
        break;
    case SpaceGame::GameState::GameOver:
        stateTimer -= dt;
        if (stateTimer <= 0) {
            gameState = GameState::Title;
        }
        break;
    }
    scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer) {

    // CREATE TITLE TEXT
    if (gameState == GameState::Title) {
        titleText->Create(renderer, "PIT VIPER", viper::vec3{ 1,0,0 });
        titleText->Draw(renderer, 250, 400);
    }

    // CREATE GAME OVER TEXT
    if (gameState == GameState::GameOver) {
        titleText->Create(renderer, "GAME OVER", viper::vec3{ 1,0,0 });
        titleText->Draw(renderer, 250, 400);
    }

    // CREATE SCORE/LIVES TEXT
    if (gameState != GameState::GameOver && gameState != GameState::Title) {
        scoreText->Create(renderer, "SCORE  " + std::to_string(score), { 1,1,1 });
        scoreText->Draw(renderer, 20.0f, 20.0f);

        livesText->Create(renderer, "LIVES  " + std::to_string(lives), { 1,1,1 });
        livesText->Draw(renderer, (float)renderer.GetWidth() - 300, 20.0f);
    }

    scene->Draw(renderer);

    viper::GetEngine().GetParticleSystem().Draw(renderer);

    // DRAW TEXT
    //_text->Draw(viper::GetEngine().GetRenderer(), 40.0f, 40.0f);
    //viper::GetEngine()GetParticalSystem().Draw(renderer);
}

void SpaceGame::OnPlayerDead()
{
    gameState = GameState::PlayerDead;
    stateTimer = 2;
}

void SpaceGame::SpawnEnemy()
{
    Player* player = scene->GetActorByName<Player>("player");
    if (player) {

        std::shared_ptr<viper::Model> enemy_model = std::make_shared<viper::Model>(GameData::enemy_points, viper::vec3{ 1, 0.18f, 0.18f });

        // spawn at random position (not on player)
        viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
        viper::Transform enemy_transform{ position, viper::random::getReal(0.0f,360.0f), 5 };
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(enemy_transform, enemy_model);

        enemy->speed = (viper::random::getReal() * 100) + 100;
        enemy->damping = 0.5f;
        enemy->fireTime = 3;
        enemy->fireTimer = 5;
        enemy->name = "enemy";
        enemy->tag = "enemy";

        scene->AddActor(std::move(enemy));

    }
}

void SpaceGame::Shutdown() {

}