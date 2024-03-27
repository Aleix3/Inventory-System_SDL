#include "EntityManager.h"
#include "InventoryManager.h"
#include "Player.h"
#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Scene.h"
#include "espada.h"
#include "inventity.h"
#include "SwordInv.h"
#include "Defs.h"
#include "Log.h"

InventoryManager::InventoryManager() : Module()
{
	name.Create("iventorymanager");
}

// Destructor
InventoryManager::~InventoryManager()
{}

// Called before render is available
bool InventoryManager::Awake(pugi::xml_node config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	//Iterates over the entities and calls the Awake
	ListItem<Inventity*>* item;
	Inventity* pEntity = NULL;

	for (item = inventities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Awake();
	}

	return ret;

}

bool InventoryManager::Start() {

	Backtexture = app->tex->Load("Assets/Textures/inventario.png");

	bool ret = true; 

	//Iterates over the entities and calls Start
	ListItem<Inventity*>* item;
	Inventity* pEntity = NULL;

	for (item = inventities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Start();
	}

	return ret;
}

// Called before quitting
bool InventoryManager::CleanUp()
{
	bool ret = true;
	ListItem<Inventity*>* item;
	item = inventities.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	inventities.Clear();

	return ret;
}
int highestId = -1;
Inventity* InventoryManager::CreateItem(EntityType type, int id, int ataque, int durabilidad, int magia, float peso)
{
	Inventity* entity = nullptr;

	//L03: DONE 3a: Instantiate entity according to the type and add the new entity to the list of Entities
	switch (type)
	{
	

	case EntityType::ESPADA:
	{
		
		for (ListItem<Inventity*>* item = inventities.start; item != NULL; item = item->next)
		{
			if (item->data->id > highestId)
			{
				highestId = item->data->id;
			}
		}
		Swordinv* sword = new Swordinv();
		sword->id = highestId+1;
		sword->type = InventityType::ESPADA;
		sword->damage = ataque;
		sword->durability = durabilidad;
		sword->weight = peso;
		sword->icon = app->tex->Load("Assets/Textures/espmadIcon.png");
		entity = sword;
		break;
	}
	case EntityType::ESPADA2:

		
		break;
	default:
		break;
	}

	inventities.Add(entity);

	return entity;
}

void InventoryManager::DestroyItem(Inventity* entity)
{
	ListItem<Inventity*>* item;

	for (item = inventities.start; item != NULL; item = item->next)
	{
		if (item->data == entity) inventities.Del(item);
	}
}

void InventoryManager::DestroyItem2(int entityId)
{
	ListItem<Inventity*>* item;

	for (item = inventities.start; item != NULL; item = item->next)
	{
		if (item->data->id != 0)
		{
			if (item->data->id == entityId && entityId > 0) // Comprueba si el ID coincide
			{
				inventities.Del(item);
				delete item->data; // Libera la memoria de la espada eliminada
				break; // Termina el bucle después de eliminar la espada
			}
		}
		
	}
}

void InventoryManager::UseItemSelected()
{
}

void InventoryManager::RemoveItemSelected()
{
}

void InventoryManager::OnMovePointer()
{
}

void InventoryManager::AddItem(Inventity* entity)
{
	if ( entity != nullptr) inventities.Add(entity);
}

bool InventoryManager::Update(float dt)
{
	bool ret = true;
	ListItem<Inventity*>* item;
	Inventity* pEntity = NULL;

	for (item = inventities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Update(dt);
	}

	return ret;
}

bool InventoryManager::PostUpdate()
{
	bool ret = true;
	app->tex->GetSize(Backtexture, texW, texH);

	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {
		mostrar = !mostrar;
	}




	if (mostrar == true)
	{
		ListItem<Inventity*>* item;
		Inventity* pEntity = NULL;
		app->render->DrawTexture(Backtexture, texW / 8, texH / 8 - 200);
		for (item = inventities.start; item != NULL && ret == true; item = item->next)
		{
			pEntity = item->data;
			app->render->DrawTexture(pEntity->icon, 445 + pEntity->id*75, 300);
			
			

		}

		
	}



	return ret;
}
