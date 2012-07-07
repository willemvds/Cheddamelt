#include "Game.h"

Game::Game() {
  running = true;
  displaySurface = NULL;
  testSurface = NULL;
}

int Game::OnExecute() {
  if (OnInit() == false) {
    return -1;
  }

  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      OnEvent(&event);
    }

    OnLoop();
    OnRender();
  }

  OnCleanup();

	return 0;
}

bool Game::OnInit() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  if ((displaySurface = SDL_SetVideoMode(WINDOWWIDTH, WINDOWHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }

  if ((testSurface = Surface::Load("C:\\Users\\Willem\\Documents\\Visual Studio 11\\Projects\\Cheddamelt\\Debug\\yoshi.png")) == NULL) {
    return false;
  }

  yoshiAnim.maxFrames = 8;
  //yoshiAnim.oscillate = true;

  if (entity1.Load("C:\\Users\\Willem\\Documents\\Visual Studio 11\\Projects\\Cheddamelt\\Debug\\yoshi.png", 64, 64, 8) == false) {
    return false;
  }

  if (entity2.Load("C:\\Users\\Willem\\Documents\\Visual Studio 11\\Projects\\Cheddamelt\\Debug\\yoshi.png", 64, 64, 8) == false) {
    return false;
  }
  entity2.x = 100;

  Entity::entityList.push_back(&entity1);
  Entity::entityList.push_back(&entity2);

  if (Area::areaControl.Load("C:\\Cheddamelt\\maps\\1.area") == false) {
    return false;
  }

  SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

  return true;
}

void Game::OnEvent(SDL_Event* event) {
  /*if (event->type == SDL_QUIT) {
    running = false;
  }*/
  Event::OnEvent(event);
}

void Game::OnExit() {
  running = false;
}

void Game::OnLoop() {
  yoshiAnim.OnAnimate();

  for (int i = 0; i < Entity::entityList.size(); i++) {
    if (!Entity::entityList[i])
      continue;

    Entity::entityList[i]->OnLoop();
  }
}

void Game::OnRender() {
  //Surface::Draw(displaySurface, testSurface, 0, 0);
  //Surface::DrawRegion(displaySurface, testSurface, 400, 0, 0, 0, 198, 140);
  Area::areaControl.OnRender(displaySurface, Camera::cameraControl.getX(), Camera::cameraControl.getY());
  
  Surface::DrawRegion(displaySurface, testSurface, 290, 220, 0, yoshiAnim.GetCurrentFrame() * 64, 64, 64);

  for (int i = 0; i < Entity::entityList.size(); i++) {
    if (!Entity::entityList[i])
      continue;

    Entity::entityList[i]->OnRender(displaySurface);
  }

  SDL_Flip(displaySurface);
}

void Game::OnCleanup() {
  SDL_FreeSurface(testSurface);
  SDL_FreeSurface(displaySurface);

  for (int i = 0; i < Entity::entityList.size(); i++) {
    if (!Entity::entityList[i])
      continue;

    Entity::entityList[i]->OnCleanup();
  }
  Entity::entityList.clear();

  Area::areaControl.OnCleanup();

  SDL_Quit();
}

void Game::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
  switch (sym) {
    case SDLK_UP:
      Camera::cameraControl.OnMove(0, -5);
      break;
    case SDLK_DOWN:
      Camera::cameraControl.OnMove(0, 5);
      break;
    case SDLK_LEFT:
      Camera::cameraControl.OnMove(-5, 0);
      break;
    case SDLK_RIGHT:
      Camera::cameraControl.OnMove(5, 0);
      break;
  }
}