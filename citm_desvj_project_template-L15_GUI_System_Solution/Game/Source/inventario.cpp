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

	app->tex->GetSize(texture, texW, texH);

	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {	
		mostrar = !mostrar;
	}

	//if (isPicked) // Si se ha recogido una espada
	//{
	//	// Añade la espada al inventario
	//	espadas.push_back(Espada(/*datos de la espada*/));

	//	// Desactiva la espada en el mundo del juego
	//	// Supongamos que tienes un método para desactivar una espada en el mundo del juego
	//	// que se llama DesactivarEspada() en la clase Scene
	//	app->scene->DesactivarEspada(/*datos de la espada*/);

	//	// Vuelve a poner isPicked a false para esperar a que se recoja otra espada
	//	isPicked = false;
	//}
	
	

	if (mostrar == true)
	{

		app->render->DrawTexture(texture, texW / 8, texH / 8 - 200);
	}


	
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
