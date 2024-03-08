#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Entity.h"
#include "List.h"

class EntityManager : public Module
{
public:

	EntityManager();

	// Destructor
	virtual ~EntityManager();

	// Called before render is available
	bool Awake(pugi::xml_node config);

	// Called after Awake
	bool Start();

	// Called every frame
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Additional methods
	Entity* CreateEntity(EntityType type, int id, int ataque, int durabilidad, int magia, float peso);

	void DestroyEntity(Entity* entity);

	void EntityManager::DestroyEntity2(int entityId);

	void AddEntity(Entity* entity);

public:

	int ataque = 100;
	int durabilidad; // Durabilidad de la espada
	int magia;
	float peso; // Peso de la espada

	List<Entity*> entities;

};

#endif // __ENTITYMANAGER_H__
