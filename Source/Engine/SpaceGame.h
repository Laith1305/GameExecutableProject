#pragma once
#pragma once
#include "Game.h"
#include <Font.h>
#include "Text.h"
#include "Renderer/Renderer (2).h"

class SpaceGame : public viper::Game {
public:
	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver,
	};
	SpaceGame() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;

	void Draw(class viper::Renderer& renderer) override;

	void OnPlayerDead();

private:
	void SpawnEnemy();

private:
	GameState gameState = GameState::Initialize;
	float enemySpawnTimer = { 0 };
	float stateTimer = { 0 };

	std::shared_ptr<viper::Font> titleFont;
	std::shared_ptr<viper::Font> uiFont;

	std::unique_ptr<viper::Text> titleText;
	std::unique_ptr<viper::Text> scoreText;
	std::unique_ptr<viper::Text> livesText;
};