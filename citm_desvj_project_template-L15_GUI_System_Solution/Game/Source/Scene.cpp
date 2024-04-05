#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Item.h"
#include "espada.h"
#include "Defs.h"
#include "Log.h"
#include "GuiControl.h"
#include "GuiManager.h"
#include <vector>

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node config)
{
	LOG("Loading Scene");
	bool ret = true;

	//L03: DONE 3b: Instantiate the player using the entity manager
	//L04 DONE 7: Get player paremeters
	player = (Player*) app->entityManager->CreateEntity(EntityType::PLAYER,0,0,0,0,0,0);
	
	//Assigns the XML node to a member in player
	player->config = config.child("player");

	//Get the map name from the config file and assigns the value in the module
	app->map->name = config.child("map").attribute("name").as_string();
	app->map->path = config.child("map").attribute("path").as_string();

	// iterate all items in the scene
	// Check https://pugixml.org/docs/quickstart.html#access
	for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM,0,0,0,0,0,0);
		item->parameters = itemNode;
	}

	int a = 1;
	for (pugi::xml_node itemNode = config.child("espada"); itemNode; itemNode = itemNode.next_sibling("espada"))
	{
		espada = (Espada*)app->entityManager->CreateEntity(EntityType::ESPADA, 1, 20, 100, 30, 2, 0);
		espada->parameters = itemNode;
		
		espada->id = a;
		
		espadas.push_back(espada);
		a++;
	}
	
	int b = 200;
	for (pugi::xml_node itemNode = config.child("armadura"); itemNode; itemNode = itemNode.next_sibling("armadura"))
	{
		armadura = (Armadura*)app->entityManager->CreateEntity(EntityType::ARMADURA, 100,0 , 300, 300, 50, 200);
		armadura->parameters = itemNode;

		armadura->id = b;

		armaduras.push_back(armadura);
		b++;
	}
	
	
	espada2 = (Espada2*)app->entityManager->CreateEntity(EntityType::ESPADA2,100, 100, 200, 20, 5, 0);
	espada2->id = 100;
	espadas2.push_back(espada2);

	

	
	
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// NOTE: We have to avoid the use of paths in the code, we will move it later to a config file
	img = app->tex->Load("Assets/Textures/test.png");
	
	//Music is commented so that you can add your own music
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

	//Get the size of the window
	app->win->GetWindowSize(windowW, windowH);

	//Get the size of the texture
	app->tex->GetSize(img, texW, texH);

	textPosX = (float)windowW / 2 - (float)texW / 2;
	textPosY = (float)windowH / 2 - (float)texH / 2;

	// Texture to highligh mouse position 
	mouseTileTex = app->tex->Load("Assets/Maps/tileSelection.png");

	// L15: DONE 2: Instantiate a new GuiControlButton in the Scene

	SDL_Rect btPos = { windowW / 2 - 60, windowH / 2 - 10, 120,20};
	gcButtom = (GuiControlButton*) app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos, this);

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	//L02 DONE 3: Make the camera movement independent of framerate
	float camSpeed = 1; 

	//if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	//	app->render->camera.y -= (int)ceil(camSpeed * dt);

	//if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	//	app->render->camera.y += (int)ceil(camSpeed * dt);

	//if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	//	app->render->camera.x -= (int)ceil(camSpeed * dt);

	//if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	//	app->render->camera.x += (int)ceil(camSpeed * dt);

	// L09 DONE 6: Implement a method that repositions the player in the map with a mouse click

	// Get the mouse position and obtain the map coordinate
	iPoint mousePos;
	app->input->GetMousePosition(mousePos.x, mousePos.y);
	iPoint mouseTile = app->map->WorldToMap(mousePos.x - app->render->camera.x,
										    mousePos.y - app->render->camera.y);
	
	// Render a texture where the mouse is over to highlight the tile, use the texture 'mouseTileTex'
	iPoint highlightedTileWorld = app->map->MapToWorld(mouseTile.x, mouseTile.y);
	app->render->DrawTexture(mouseTileTex, highlightedTileWorld.x, highlightedTileWorld.y);

	iPoint origin = iPoint(2, 2);

	//If mouse button is pressed modify player position
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
		player->position = iPoint(highlightedTileWorld.x, highlightedTileWorld.y);
		app->map->pathfinding->CreatePath(origin, mouseTile);
	}

	// L13: Get the latest calculated path and draw
	const DynArray<iPoint>* path = app->map->pathfinding->GetLastPath();
	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		app->render->DrawTexture(mouseTileTex, pos.x, pos.y);
	}
	
	// L14: DONE 3: Request App to Load / Save when pressing the keys F5 (save) / F6 (load)
	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) app->SaveRequest();
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) app->LoadRequest();

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

iPoint Scene::GetPLayerPosition() {
	return player->position;
}

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	// L15: DONE 5: Implement the OnGuiMouseClickEvent method
	LOG("Press Gui Control: %d", control->id);

	return true;
}
Espada* Scene::GetEspada()
{
	return espada;
}
Espada2* Scene::GetEspada2()
{
	return espada2;
}
Player* Scene::GetPlayer()
{
	return player;
}

int Scene::GetEspadaId(PhysBody* physBody) const {
	// Itera sobre todas las espadas 2 en la escena
	for (const auto& espadas : espadas) {
		// Comprueba si el cuerpo físico de la espada 2 coincide con el pasado como argumento
		if (espadas->pbody == physBody) {
			// Si coincide, devuelve el identificador único de la espada 2
			return espadas->id;
		}
	}

	// Si no se encuentra el cuerpo físico, devuelve un valor que indique que no se encontró la espada
	return -1;
}

int Scene::GetEspada2Id(PhysBody* physBody) const {
	// Itera sobre todas las espadas 2 en la escena
	for (const auto& espadas2 : espadas2) {
		// Comprueba si el cuerpo físico de la espada 2 coincide con el pasado como argumento
		if (espadas2->pbody == physBody) {
			// Si coincide, devuelve el identificador único de la espada 2
			return espadas2->id;
		}
	}

	// Si no se encuentra el cuerpo físico, devuelve un valor que indique que no se encontró la espada
	return -1;
}

int Scene::GetArmaduraId(PhysBody* physBody) const {
	// Itera sobre todas las espadas 2 en la escena
	for (const auto& armaduras : armaduras) {
		// Comprueba si el cuerpo físico de la espada 2 coincide con el pasado como argumento
		if (armaduras->pbody == physBody) {
			// Si coincide, devuelve el identificador único de la espada 2
			return armaduras->id;
		}
	}

	// Si no se encuentra el cuerpo físico, devuelve un valor que indique que no se encontró la espada
	return -1;
}
