#include "Game.h"

Game::Game() {
  running = true;
  displaySurface = NULL;
  testSurface = NULL;
}

char* Game::getCwd() {
  return cwd;
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
  char tempPath[255];
  if ((cwd = _getcwd(NULL, 0)) == NULL) {
    return false;
  }
  strcpy(tempPath, cwd);
  strcat(cwd, "/../Debug/");
  

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  if ((displaySurface = SDL_SetVideoMode(WINDOWWIDTH, WINDOWHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }

  strcpy(tempPath, getCwd());
  strcat(tempPath, "yoshi.png");
  if ((testSurface = Surface::Load(tempPath)) == NULL) {
    return false;
  }

  yoshiAnim.maxFrames = 8;
  //yoshiAnim.oscillate = true;

  if (entity1.Load(tempPath, 64, 64, 8) == false) {
    return false;
  }

  if (entity2.Load(tempPath, 64, 64, 8) == false) {
    return false;
  }
  entity2.x = 100;

  Entity::entityList.push_back(&entity1);
  Entity::entityList.push_back(&entity2);

  if (player1.Load(tempPath, 64, 64, 8) == false) {
    return false;
  }

  if (player2.Load(tempPath, 64, 64, 8) == false) {
    return false;
  }

  player1.x = 200;
  player2.x = 300;

  Entity::entityList.push_back(&player1);
  Entity::entityList.push_back(&player2);

  Camera::cameraControl.targetMode = TARGET_MODE_CENTER;
  Camera::cameraControl.setTarget(&player1.x, &player1.y);

  strcpy(tempPath, getCwd());
  strcat(tempPath, "maps\\1.area");
  if (Area::areaControl.Load(tempPath) == false) {
  //if (Area::areaControl.Load("C:\\Cheddamelt\\maps\\1.area") == false) {
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

  FPS::fpsControl.OnLoop();
}

void Game::OnRender() {
  //Surface::Draw(displaySurface, testSurface, 0, 0);
  //Surface::DrawRegion(displaySurface, testSurface, 400, 0, 0, 0, 198, 140);
  Area::areaControl.OnRender(displaySurface, -Camera::cameraControl.getX(), -Camera::cameraControl.getY());
  
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
    case SDLK_LEFT:
      player1.moveLeft = true;
      break;
    case SDLK_RIGHT:
      player1.moveRight = true;
      break;
    /*case SDLK_UP:
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
      break;*/
  }
}

void Game::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
  switch (sym) {
    case SDLK_LEFT:
      player1.moveLeft = false;
      break;
    case SDLK_RIGHT:
      player1.moveRight = false;
      break;
  }
}