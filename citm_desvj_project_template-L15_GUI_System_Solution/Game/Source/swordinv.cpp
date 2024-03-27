#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "inventity.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "SwordInv.h"

Swordinv::Swordinv() : Inventity(InventityType::ESPADA)
{
	name.Create("swordinv");
}

Swordinv::~Swordinv() {}

bool Swordinv::Awake() {

	

	return true;
}

bool Swordinv::Start() {

	//initilize textures
	/*icon = app->tex->Load();*/

	return true;
}


bool Swordinv::Update(float dt)
{
	/*app->render->DrawTexture(icon, position.x, position.y);*/

	return true;
}

bool Swordinv::PostUpdate()
{



	return false;
}

bool Swordinv::CleanUp()
{
	return true;
}