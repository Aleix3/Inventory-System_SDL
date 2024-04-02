#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include"inventario.h"
#include "InventoryManager.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	//L03: DONE 2: Initialize Player parameters
	position = iPoint(config.attribute("x").as_int(), config.attribute("y").as_int());

	return true;
}

bool Player::Start() {

	texture = app->tex->Load(config.attribute("texturePath").as_string());

	//initialize audio effect
	pickCoinFxId = app->audio->LoadFx(config.attribute("coinfxpath").as_string());
	app->tex->GetSize(texture, texW, texH);
	pbody = app->physics->CreateCircle(position.x, position.y, texW / 2, bodyType::DYNAMIC);

	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this;

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::PLAYER;

	pbody->body->SetGravityScale(0.0f);



	return true;
}

bool Player::Update(float dt)
{
	//L03: DONE 4: render the player texture and modify the position of the player using WSAD keys and render the texture

	b2Vec2 velocity = b2Vec2(0, -GRAVITY_Y);

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		velocity.x += -0.2*dt;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		velocity.x += 0.2*dt;
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		velocity.y += -0.2 * dt;
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		velocity.y += 0.2 * dt;
	}

	pbody->body->SetLinearVelocity(velocity);
	b2Transform pbodyPos = pbody->body->GetTransform();
	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - texH / 2;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - texH / 2;

	

	if (espadaMadera == true && espadaHierro == false)
	{
		
		app->render->DrawTexture(app->tex->Load("Assets/Textures/playeresp1.png"), position.x, position.y);
		manollena = true;
	}

	if (espadaHierro == true && espadaMadera == false)
	{
		
		app->render->DrawTexture(app->tex->Load("Assets/Textures/playeresp2.png"), position.x, position.y);
		manollena = true;
	}

	if(espadaMadera == false && espadaHierro == false)
	{
		app->render->DrawTexture(texture, position.x, position.y);
	}
	return true;
}

bool Player::CleanUp()
{
	return true;
}

// L07 DONE 6: Define OnCollision function for the player. 
void Player::OnCollision(PhysBody* physA, PhysBody* physB) {
	switch (physB->ctype)
	{
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		break;
	case ColliderType::ITEM:
		LOG("Collision ITEM");
		/*app->audio->PlayFx(pickCoinFxId);*/
		break;
	case ColliderType::ESPADA:
		if (app->inventoryManager->IsFull() == false)
		{
			espadaid = (app->scene->GetEspadaId(physB));
			if (app->entityManager->FindEspadaById(espadaid) != nullptr)
			{
				app->inventoryManager->CreateItem(app->entityManager->FindEspadaById(espadaid)->type, app->entityManager->FindEspadaById(espadaid)->id, app->entityManager->FindEspadaById(espadaid)->ataque, app->entityManager->FindEspadaById(espadaid)->durabilidad, app->entityManager->FindEspadaById(espadaid)->magia, app->entityManager->FindEspadaById(espadaid)->peso);

			}
			

			app->entityManager->DestroyEntity2(espadaid);
			/*app->inventoryManager->CreateItem()*/
			espadas = 1;
		}
		
		LOG("Collision PLATFORM");
		break;
	case ColliderType::ESPADA2:
		if (app->inventoryManager->IsFull() == false)
		{
			espadaid = (app->scene->GetEspada2Id(physB));
			if (app->entityManager->FindEspada2ById(espadaid) != nullptr)
			{
				app->inventoryManager->CreateItem(app->entityManager->FindEspada2ById(espadaid)->type, app->entityManager->FindEspada2ById(espadaid)->id, app->entityManager->FindEspada2ById(espadaid)->ataque, app->entityManager->FindEspada2ById(espadaid)->durabilidad, app->entityManager->FindEspada2ById(espadaid)->magia, app->entityManager->FindEspada2ById(espadaid)->peso);

			}
			app->entityManager->DestroyEntity2(espadaid);
			/*app->inventoryManager->CreateItem()*/
			espadas = 2;
		}
		

		
		LOG("Collision PLATFORM");
		break;

	case ColliderType::ARMADURA:
	{
		if (app->inventoryManager->IsFull() == false)
		{
			armaduraid = (app->scene->GetArmaduraId(physB));
			if (app->entityManager->FindArmaduraById(armaduraid) != nullptr)
			{
				app->inventoryManager->CreateItem(app->entityManager->FindArmaduraById(armaduraid)->type, app->entityManager->FindArmaduraById(armaduraid)->id, app->entityManager->FindArmaduraById(armaduraid)->ataque, app->entityManager->FindArmaduraById(armaduraid)->durabilidad, app->entityManager->FindArmaduraById(armaduraid)->magia, app->entityManager->FindArmaduraById(armaduraid)->peso, app->entityManager->FindArmaduraById(armaduraid)->defensa);

			}
			app->entityManager->DestroyEntity2(armaduraid);

		}
	}
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	default:
		break;
	}
}