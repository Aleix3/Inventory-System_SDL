#include "espada.h"
#include "armadura.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

Armadura::Armadura(EntityType type, int id, int durabilidad, int magia, float peso, int defensa)
	: type(type), defensa(defensa), durabilidad(durabilidad), magia(magia), peso(peso), Entity(EntityType::ARMADURA)
{
	name.Create("armadura");
}

Armadura::~Armadura() {}

bool Armadura::Awake() {

	
	 

	return true;
}

bool Armadura::Start() {

	//initilize textures
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texture = app->tex->Load("Assets/Textures/armadura.png");
	
	// L07 DONE 4: Add a physics to an item - initialize the new physics body
	app->tex->GetSize(texture, texW, texH);
	pbody = app->physics->CreateCircle(position.x, position.y, 11, bodyType::STATIC);
	pbody->id = id;

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::ARMADURA;

	return true;
}

bool Armadura::Update(float dt)
{
	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
	
	b2Transform pbodyPos = pbody->body->GetTransform();
	position.x = METERS_TO_PIXELS(pbodyPos.p.x) - 11;
	position.y = METERS_TO_PIXELS(pbodyPos.p.y) - 11;

	app->render->DrawTexture(texture, position.x, position.y);
	
	return true;
}

bool Armadura::CleanUp()
{
	return true;
}


