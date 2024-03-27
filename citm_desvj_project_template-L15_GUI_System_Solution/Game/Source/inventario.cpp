#include "inventario.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Module.h"

Inventario::Inventario() : Module()
{
	
}

Inventario::~Inventario() {}

bool Inventario::Awake() {

	
	

	return true;
}

bool Inventario::Start() {


	texture = app->tex->Load("Assets/Textures/inventario.png");
	
	// L07 DONE 4: Add a physics to an item - initialize the physics body
	app->tex->GetSize(texture, texW, texH);
	

	

	return true;
}

bool Inventario::Update(float dt)
{
	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  

	

	
	return true;
}

bool Inventario::CleanUp()
{
	return true;
}

//void datos::agregarEspada(int ataque, int durabilidad, int magia, float peso)
//{
//	if (datosCreados.size() <= 10)
//	{
//		datos* dato;
//		int ide;
//		for (int i = 0; i <= datosCreados.size(); i++)
//		{
//			if (datosCreados.at(i)->id == 0)
//			{
//				ide = datosCreados.at(i - 1)->id;
//			}
//		}
//		dato = new datos(ide, ataque, durabilidad, magia, peso);
//
//		datosCreados.push_back(dato);
//	}
//	
//}
