#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include <list>
#include "Avatar.h"

using namespace std;
using namespace sf;
class Game
{
private:
	//Propiedades de la ventana
	int alto;
	int ancho;
	RenderWindow* wnd;
	Color clearColor;

	//objetos de box2d
	b2World* phyWorld;
	SFMLRenderer* debugRender;

	//tiempo de frame
	float frameTime;
	int fps;

	//cuerpo de box2d 
	b2Body* firstBody;
	b2Body* secondBody;
	b2Body* thirdBody;
	b2Body* fourthBody;
	b2Body* fifthBody;
	b2Body* sixthBody;

	//Avatar* firstBodyAvatar;
	//Avatar* secondBodyAvatar;

	/*b2DistanceJointDef jointDef;/////////Para el resorte
	b2PrismaticJointDef prismaticJDCabeza;
	b2PrismaticJointDef prismaticJDBrazo;
	b2PrismaticJointDef prismaticJDBrazoDos;
	b2PrismaticJointDef prismaticJDPierna;
	b2PrismaticJointDef prismaticJDPiernaDos;*/


	b2RevoluteJointDef revolute_head;
	b2RevoluteJointDef revolute_armL;
	b2RevoluteJointDef revolute_armR;
	b2RevoluteJointDef revolute_legL;
	b2RevoluteJointDef revolute_legR;


	//b2MouseJointDef MouseDef;


	//sf::Texture texturaPelota;



public:

	//Constructores, destructores e inicializadores
	Game(int ancho, int alto, std::string titulo);
	void CreateEnemy(int x, int y);
	void InitPhysics();

	//Main game loop
	void Loop();
	void DrawGame();
	void UpdatePhysics();
	void DoEvents();
	void SetZoom();



};


