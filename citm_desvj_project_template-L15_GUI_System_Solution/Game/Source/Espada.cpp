#include "espada.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

Espada::Espada(EntityType type, int id, int ataque, int durabilidad, int magia, float peso)
	: type(type), ataque(ataque), durabilidad(durabilidad), magia(magia), peso(peso), Entity(EntityType::ESPADA)
{
	name.Create("espada");
}

Espada::~Espada() {}

bool Espada::Awake() {

	
	 

	return true;
}

bool Espada::Start() {

	//initilize textures
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texture = app->tex->Load("Assets/Textures/espmad.png");
	
	// L07 DONE 4: Add a physics to an item - initialize the physics body
	app->tex->GetSize(texture, texW, texH);
	pbody = app->physics->CreateCircle(position.x, position.y, 11, bodyType::STATIC);
	pbody->id = id;

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::ESPADA;

	return true;
}

bool Espada::Update(float dt)
{
	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
	if (pbody->id == 1)
	{
		position = { 0,0 };
	}
	b2Transform pbodyPos = pbody->body->GetTransform();
	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - 11;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - 11;

	app->render->DrawTexture(texture, position.x, position.y);
	
	return true;
}

bool Espada::CleanUp()
{
	return true;
}
Espada2::Espada2(EntityType type, int ataque, int durabilidad, int magia, float peso)
	: type(type), ataque(ataque), durabilidad(durabilidad), magia(magia), peso(peso), Entity(EntityType::ESPADA2)
{
	
}

Espada2::~Espada2() {}

bool Espada2::Awake() {

	position.x = 200;
	position.y = 672;


	return true;
}

bool Espada2::Start() {

	//initilize textures
	position.x = 70;
	position.y = 672;
	texture = app->tex->Load("Assets/Textures/esphier.png");

	// L07 DONE 4: Add a physics to an item - initialize the physics body
	app->tex->GetSize(texture, texW, texH);
	pbody = app->physics->CreateCircle(position.x + texH / 2, position.y + texH / 2, texH / 2, bodyType::STATIC);

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::ESPADA2;



	return true;
}

bool Espada2::Update(float dt)
{
	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  

	b2Transform pbodyPos = pbody->body->GetTransform();
	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - texH / 2;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - texH / 2;

	app->render->DrawTexture(texture, position.x, position.y);

	return true;
}

bool Espada2::CleanUp()
{
	return true;
}

