#include "Enemy.h"
#include "Engine.h"
#include "Scene.h"
#include "Player.h"
#include "Game.h"
#include "Rocket.h"
#include "GameData.h"
#include <Vector3.h>
#include <Math/Vector2.h>
#include "Model.h"
#include "ParticleSystem.h"
#include "Core/Random.h"
#include <Core/Math.h>
using namespace viper;
void Enemy::Update(float dt)
{
	bool playerSeen = false;

	
	Player* player = scene->GetActorByName<Player>("player");
	if (player) {
		vec2 direction{ 0, 0 };
		direction = player->transform.position - transform.position;

		direction = direction.Normalized();
		viper::vec2 forward = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(transform.rotation));

		float angle = viper::vec2::AngleBetween(forward, direction);
		playerSeen = angle <= 30;


		if (playerSeen) {
			float angle = vec2::SignedAngleBetween(direction, forward);
			angle = viper::math::sign(angle);
			transform.rotation = math::radToDeg(angle * 5 * dt); // Adjust rotation to face the player
		}


	}

	// ROTATION
	vec2 direction{ 1, 0 };
	vec2 force = vec2{ 1,0 }.Rotate(math::degToRad(transform.rotation)) * speed;
	velocity += force * dt;

	// WRAP POSITION
	transform.position.x = math::wrap(transform.position.x, 0.0f, (float)GetEngine().GetRenderer().GetWidth());
	transform.position.y = math::wrap(transform.position.y, 0.0f, (float)GetEngine().GetRenderer().GetHeight());

	// ENEMY ROCKETS
	fireTimer -= dt;
	if (fireTimer <= 0 && playerSeen) {
		fireTimer = fireTime;
		std::shared_ptr<viper::Model> rocket_model = std::make_shared<viper::Model>(GameData::rocket_points, viper::vec3{ 1, 0, 0 });
		viper::Transform transform{ this->transform.position,this->transform.rotation , 2 };
		auto rocket = std::make_unique<Rocket>(transform, rocket_model);

		rocket->speed = 500.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "enemy";

		scene->AddActor(std::move(rocket));
	}

	// UPDATE PARENT
	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
	if (other->tag != tag) {
		destroyed = true;
		scene->GetGame()->AddPoints(100);
		for (int i = 0; i < 100; i++) {

			// CREATE PARTICAL EXPLOSION
			viper::Particle particle;
			particle.position = transform.position;
			particle.velocity = viper::random::onUnitCircle() * random::getReal(10.0f, 200.0f);
			particle.color = vec3{ 1,1,1 };
			particle.lifespan = 2;

			viper::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}