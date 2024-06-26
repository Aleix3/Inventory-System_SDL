#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

Item::Item() : Entity(EntityType::ITEM)
{
	name.Create("item");
}

Item::~Item() {}

bool Item::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Item::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 11, bodyType::KINEMATIC);
	pbody->id = id;
	pbody->ctype = ColliderType::ITEM;
	pbody->listener = this;

	return true;
}

bool Item::Update(float dt)
{
	app->render->DrawTexture(texture, position.x, position.y);

	return true;
}

bool Item::CleanUp()
{
	return true;
}