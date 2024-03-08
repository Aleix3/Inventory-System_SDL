#ifndef __INVENTARIO_H__
#define __INVENTARIO_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include <vector>
#include "espada.h"
#include "Module.h"

struct SDL_Texture;

class Inventario : public Module
{
public:


	Inventario();

	virtual ~Inventario();

	void agregarEspada(const Espada& espada) {
		espadas.push_back(espada);
	}

	void mostrarEspadas() {
		
		
	}

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();


public:

	std::vector<Espada> espadas;
	std::vector<Espada2> espadas2;
	bool isPicked = false;

	int ataque = 100;
	PhysBody* pbody;
	SDL_Texture* texture;

	bool mostrar;
private:

	
	const char* texturePath;
	uint texW, texH;

	//L07 DONE 4: Add a physics to an item
	
};

#endif // __ITEM_H__