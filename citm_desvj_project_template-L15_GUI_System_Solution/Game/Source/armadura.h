#ifndef __ARMADURA_H__
#define __ARMADURA_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class Armadura : public Entity
{
public:
	/*Armadura() : Entity(EntityType::ESPADA, 0, 100, 0, 0, 0) {}*/

	Armadura(EntityType type, int id, int durabilidad, int magia, float peso, int defensa); // Constructor con parámetros
	virtual ~Armadura();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();


public:

	bool isPicked = false;

	
	EntityType type;
	int ataque;
	int defensa;
	int durabilidad; // Durabilidad de la espada
	int magia;
	float peso; // Peso de la espada
	PhysBody* pbody;
	SDL_Texture* texture;
	iPoint position;
	pugi::xml_node config;
private:

	
	const char* texturePath;
	uint texW, texH;

	//L07 DONE 4: Add a physics to the item
	
};
#endif // __ITEM_H__