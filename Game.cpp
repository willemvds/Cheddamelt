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

  if ((displaySurface = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }

  if ((testSurface = Surface::Load("C:\\Users\\Willem\\Documents\\Visual Studio 11\\Projects\\Cheddamelt\\Debug\\yoshi.bmp")) == NULL) {
    return false;
  }

  yoshiAnim.maxFrames = 8;
  //yoshiAnim.oscillate = true;

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
}

void Game::OnRender() {
  //Surface::Draw(displaySurface, testSurface, 0, 0);
  //Surface::DrawRegion(displaySurface, testSurface, 400, 0, 0, 0, 198, 140);
  Surface::DrawRegion(displaySurface, testSurface, 290, 220, 0, yoshiAnim.GetCurrentFrame() * 64, 64, 64);
  SDL_Flip(displaySurface);
}

void Game::OnCleanup() {
  SDL_FreeSurface(testSurface);
  SDL_FreeSurface(displaySurface);
  SDL_Quit();
}