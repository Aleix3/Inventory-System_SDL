#ifndef __INVENTORYMANAGER_H__
#define __INVENTORYMANAGER_H__

#include "Module.h"
#include "Entity.h"
#include "inventity.h"
#include "List.h"
#include "Textures.h"

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

	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Additional methods
	Inventity* InventoryManager::CreateItem(EntityType type, int id, int ataque, int durabilidad, int magia, float peso);

	void AddItem(Inventity* Inventity);

	void DestroyItem(Inventity* Inventity);

	void InventoryManager::DestroyItem2(int entityId);

	void UseItemSelected();

	void RemoveItemSelected();

	void OnMovePointer();

	bool InventoryManager::IsFull();

	

public:



	List<Inventity*> inventities;
	iPoint PointerPosition = { 125,-75 };
	int PointerId = 0;
	iPoint selected = { -1000,-1000 };
	int selectedId = -1;
	iPoint InventorySize;
	SDL_Texture* InventoryBackground;
	SDL_Texture* SelectItemText;
	SDL_Texture* SelectedItemText;
	SDL_Texture* EquipedItemText;

	SDL_Texture* Backtexture;
	uint texW, texH;
	bool mostrar = false;


	int highestIde = -1;


};

#endif // __INVENTORYMANAGER_H__
