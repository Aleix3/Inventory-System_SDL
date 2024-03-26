#ifndef __INVENTORYMANAGER_H__
#define __INVENTORYMANAGER_H__

#include "Module.h"
#include "Entity.h"
#include "inventity.h"
#include "List.h"

class InventoryManager : public Module
{
public:

	InventoryManager();

	// Destructor
	virtual ~InventoryManager();

	// Called before render is available
	bool Awake(pugi::xml_node config);

	// Called after Awake
	bool Start();

	// Called every frame
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Additional methods
	Inventity* CreateEntity(InventityType type, int id, int ataque, int durabilidad, int magia, float peso);

	void DestroyEntity(Inventity* Inventity);

	void InventoryManager::DestroyEntity2(int entityId);

	void AddEntity(Inventity* Inventity);

public:

	int ataque = 100;
	int durabilidad; // Durabilidad de la espada
	int magia;
	float peso; // Peso de la espada

	List<Inventity*> inventities;

};

#endif // __INVENTORYMANAGER_H__
