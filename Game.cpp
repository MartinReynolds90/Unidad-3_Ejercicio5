#include "Game.h"
#include "Box2DHelper.h"


// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
    // Inicialización de la ventana de renderizado
    wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
    wnd->setVisible(true);
    fps = 60;
    wnd->setFramerateLimit(fps);
    frameTime = 1.0f / fps;
    SetZoom(); // Configuración del zoom de la cámara
    InitPhysics(); // Inicialización del mundo físico
    Vector2i coordenadas_mouse;



}

// Método principal que maneja el bucle del juego
void Game::Loop()
{
    while (wnd->isOpen())
    {
        wnd->clear(clearColor); // Limpia la ventana con un color especificado
        DoEvents(); // Procesa los eventos del sistema


        UpdatePhysics(); // Actualiza la simulación física
        DrawGame(); // Dibuja el juego en la ventana
        wnd->display(); // Muestra la ventana renderizada
    }
}

// Actualiza la simulación física
void Game::UpdatePhysics()
{
    phyWorld->Step(frameTime, 8, 8); // Avanza la simulación física
    phyWorld->ClearForces(); // Limpia las fuerzas aplicadas a los cuerpos
    phyWorld->DebugDraw(); // Dibuja el mundo físico (para depuración)
}

// Dibuja los elementos del juego en la ventana
void Game::DrawGame()
{
    // Dibujamos el suelo
    sf::RectangleShape groundShape(sf::Vector2f(500, 5));
    groundShape.setFillColor(sf::Color::Red);
    groundShape.setPosition(0, 95);
    wnd->draw(groundShape);

    // Dibujamos las paredes
    sf::RectangleShape leftWallShape(sf::Vector2f(10, alto)); // Alto de la ventana
    leftWallShape.setFillColor(sf::Color::Red);
    leftWallShape.setPosition(100, 0); // X = 100 para que comience donde termina el suelo
    wnd->draw(leftWallShape);

    sf::RectangleShape rightWallShape(sf::Vector2f(10, alto)); // Alto de la ventana
    rightWallShape.setFillColor(sf::Color::Cyan);
    rightWallShape.setPosition(90, 0); // X = 90 para que comience donde termina el suelo
    wnd->draw(rightWallShape);



    //firstBodyAvatar->Actualizar(); // Actualiza la posición del avatar
    //firstBodyAvatar->Dibujar(*wnd); // Dibuja el avatar en la ventana
    //secondBodyAvatar->Actualizar();
    //secondBodyAvatar->Dibujar(*wnd);
}

// Procesa los eventos del sistema
void Game::DoEvents()
{
    Event evt;
    while (wnd->pollEvent(evt))
    {
        switch (evt.type)
        {
        case Event::Closed:
            wnd->close(); // Cierra la ventana
            break;
        case Event::MouseButtonPressed: //si se presiona un boton del mouse

            break;
        }
    }

    // Mueve el cuerpo controlado por el teclado
    firstBody->SetAwake(true); // Activa el cuerpo para que responda a fuerzas y colisiones
    if (Keyboard::isKeyPressed(Keyboard::Left))
        firstBody->SetLinearVelocity(b2Vec2(-50.0f, 0.0f));
    if (Keyboard::isKeyPressed(Keyboard::Right))
        firstBody->SetLinearVelocity(b2Vec2(50.0f, 0.0f));
    if (Keyboard::isKeyPressed(Keyboard::Down))
        firstBody->SetLinearVelocity(b2Vec2(0.0f, 50.0f));
    if (Keyboard::isKeyPressed(Keyboard::Up))
        firstBody->SetLinearVelocity(b2Vec2(0.0f, -50.0f));

}

// Configura el área visible en la ventana de renderizado
void Game::SetZoom()
{
    View camara;
    camara.setSize(100.0f, 100.0f); // Tamaño del área visible
    camara.setCenter(50.0f, 50.0f); // Centra la vista en estas coordenadas
    wnd->setView(camara); // Asigna la vista a la ventana
}

// Inicializa el mundo físico y los elementos estáticos del juego
void Game::InitPhysics()
{
    // Inicializa el mundo físico con la gravedad por defecto
    phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

    // Inicializa el renderizador de depuración para el mundo físico
    debugRender = new SFMLRenderer(wnd);
    debugRender->SetFlags(UINT_MAX); // Configura el renderizado para que muestre todo
    phyWorld->SetDebugDraw(debugRender);

    // Crea los elementos estáticos del juego (suelo y paredes)
    b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
    groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

    b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
    leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

    b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
    rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

    // Crea un cuerpo de círculo controlado por el teclado
    firstBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 10, 10, 1.0f, 0.5, 0.3f);
    firstBody->SetTransform(b2Vec2(20.0f, 20.0f), 0.0f);
    secondBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 5, 1.0f, 0.5, 0.3f);
    secondBody->SetTransform(b2Vec2(20.0f, 12.0f), 0.0f);

    thirdBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 10, 2, 1.0f, 0.5f, 0.3f);
    thirdBody->SetTransform(b2Vec2(8.0f, 15.0f), 0.0f);

    fourthBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 10, 2, 1.0f, 0.5f, 0.3f);
    fourthBody->SetTransform(b2Vec2(32.0f, 15.0f), 0.0f);

    fifthBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 3, 12, 1.0f, 0.5f, 0.3f);
    fifthBody->SetTransform(b2Vec2(15.0f, 32.0f), 0.0f);

    sixthBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 3, 12, 1.0f, 0.5f, 0.3f);
    sixthBody->SetTransform(b2Vec2(25.0f, 32.0f), 0.0f);

    revolute_head.Initialize(firstBody, secondBody, b2Vec2(20.0f, 12.0f));
    revolute_head.upperAngle = (0.4);
    revolute_head.lowerAngle = (0.1);
    revolute_head.collideConnected = true;
    b2RevoluteJoint* revoluteHead = (b2RevoluteJoint*)phyWorld->CreateJoint(&revolute_head);

    revolute_armR.Initialize(firstBody, thirdBody, b2Vec2(15.0f, 15.0f));
    revolute_armR.upperAngle = (0.1);
    revolute_armR.lowerAngle = (0.3);
    revolute_armR.collideConnected = true;
    b2RevoluteJoint* revoluteArmR = (b2RevoluteJoint*)phyWorld->CreateJoint(&revolute_armR);

    revolute_armL.Initialize(firstBody, fourthBody, b2Vec2(25.0f, 15.0f));
    revolute_armL.upperAngle = (0.1);
    revolute_armL.lowerAngle = (0.3);
    revolute_armL.collideConnected = true;
    b2RevoluteJoint* revoluteArmL = (b2RevoluteJoint*)phyWorld->CreateJoint(&revolute_armL);

    revolute_legR.Initialize(firstBody, fifthBody, b2Vec2(17.0f, 25.0f));
    revolute_legR.upperAngle = (0.1);
    revolute_legR.lowerAngle = (0.15);
    revolute_legR.collideConnected = true;
    b2RevoluteJoint* revoluteLegR = (b2RevoluteJoint*)phyWorld->CreateJoint(&revolute_legR);

    revolute_legL.Initialize(firstBody, sixthBody, b2Vec2(23.0f, 25.0f));
    revolute_legL.upperAngle = (0.1);
    revolute_legL.lowerAngle = (0.15);
    revolute_legL.collideConnected = true;
    b2RevoluteJoint* revoluteLegL = (b2RevoluteJoint*)phyWorld->CreateJoint(&revolute_legL);
 
}
