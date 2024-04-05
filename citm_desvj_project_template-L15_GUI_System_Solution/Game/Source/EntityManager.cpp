#include "EntityManager.h"
#include "Player.h"
#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Scene.h"
#include "espada.h"
#include "armadura.h"
#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager() : Module()
{
	name.Create("entitymanager");
}

// Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	//Iterates over the entities and calls the Awake
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Awake();
	}

	return ret;

}

bool EntityManager::Start() {

	bool ret = true; 

	//Iterates over the entities and calls Start
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Start();
	}

	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	entities.Clear();

	return ret;
}

Entity* EntityManager::CreateEntity(EntityType type, int id, int ataque, int durabilidad, int magia, float peso,int defensa)
{
	Entity* entity = nullptr; 

	//L03: DONE 3a: Instantiate entity according to the type and add the new entity to the list of Entities
	switch (type)
	{
	case EntityType::PLAYER:
		entity = new Player();
		break;
	case EntityType::ITEM:
		entity = new Item();
		break;
	case EntityType::ESPADA:
		entity = new Espada(type,id, ataque, durabilidad, magia, peso); 
		break;
	case EntityType::ESPADA2:
		entity = new Espada2(type, ataque, durabilidad, magia, peso);
		break;
	case EntityType::ARMADURA:
		entity = new Armadura(type, id, durabilidad, magia, peso, defensa);
		break;
	default:
		break;
	}

	entities.Add(entity);

	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data == entity) entities.Del(item);
	}
}

void EntityManager::DestroyEntity2(int entityId)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data->id != 0)
		{
			if (item->data->id == entityId && entityId > 0) // Comprueba si el ID coincide
			{
				entities.Del(item); //elimina el item de la lista
				delete item->data; // Libera la memoria del item
				break; 
			}
		}
		
	}
}

Espada* EntityManager::FindEspadaById(int entityId)
{
	ListItem<Entity*>* item;
	
	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data->id != 0)
		{
			if (item->data->id == entityId && entityId > 0) // Comprueba si el ID coincide
			{
				switch (item->data->type)
				{
				case EntityType::ESPADA:
					Espada* espada = dynamic_cast<Espada*>(item->data); // convertimos un item a espada
					return espada;
					break;
				}
				 // Devuelve el elemento si encuentra el ID
			}
		}
	}

	return NULL; // Devuelve NULL si no se encuentra el ID
}

Espada2* EntityManager::FindEspada2ById(int entityId)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data->id != 0)
		{
			if (item->data->id == entityId && entityId > 0) // Comprueba si el ID coincide
			{
				switch (item->data->type)
				{
				case EntityType::ESPADA2:
					Espada2* espada = dynamic_cast<Espada2*>(item->data);
					return espada;
					break;
				}
				// Devuelve el elemento si encuentra el ID
			}
		}
	}

	return NULL; // Devuelve NULL si no se encuentra el ID
}

Armadura* EntityManager::FindArmaduraById(int entityId)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data->id != 0)
		{
			if (item->data->id == entityId && entityId > 0) // Comprueba si el ID coincide
			{
				switch (item->data->type)
				{
				case EntityType::ARMADURA:
					Armadura* armadura = dynamic_cast<Armadura*>(item->data);
					return armadura;
					break;
				}
				// Devuelve el elemento si encuentra el ID
			}
		}
	}

	return NULL; // Devuelve NULL si no se encuentra el ID
}

void EntityManager::AddEntity(Entity* entity)
{
	if ( entity != nullptr) entities.Add(entity);
}

bool EntityManager::Update(float dt)
{
	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Update(dt);
	}

	return ret;
}