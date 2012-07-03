#include "Game.h"

Game::Game() {
  running = true;
  displaySurface = NULL;
  gridSurface = NULL;
  xSurface = NULL;
  oSurface = NULL;
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

  if ((displaySurface = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }

  if ((gridSurface = Surface::Load("C:\\Users\\Willem\\Documents\\Visual Studio 11\\Projects\\Cheddamelt\\Debug\\grid.bmp")) == NULL) {
    return false;
  }

  if ((xSurface = Surface::Load("C:\\Users\\Willem\\Documents\\Visual Studio 11\\Projects\\Cheddamelt\\Debug\\x.bmp")) == NULL) {
    return false;
  }

  if ((oSurface = Surface::Load("C:\\Users\\Willem\\Documents\\Visual Studio 11\\Projects\\Cheddamelt\\Debug\\o.bmp")) == NULL) {
    return false;
  }

  Surface::Transparent(xSurface, 255, 0, 255);
  Surface::Transparent(oSurface, 255, 0, 255);

  Reset();

  return true;
}

void Game::OnEvent(SDL_Event* event) {
  Event::OnEvent(event);
}

void Game::OnExit() {
  running = false;
}

void Game::OnLButtonDown(int x, int y) {
  int id = x / 200;
  id = id + ((y / 200) * 3);

  if (grid[id] != GRID_TYPE_NONE) {
    return;
  }

  if (currentPlayer == 0) {
    SetCell(id, GRID_TYPE_X);
    currentPlayer = 1;
  }
  else {
    SetCell(id, GRID_TYPE_O);
    currentPlayer = 0;
  }
}

void Game::OnLoop() {
}

void Game::OnRender() {
  Surface::Draw(displaySurface, gridSurface, 0, 0);

  for (int i = 0; i < 9; i++) {
    int x = (i % 3) * 200;
    int y = (i / 3) * 200;

    if (grid[i] == GRID_TYPE_X) {
      Surface::Draw(displaySurface, xSurface, x, y);
    }
    else if (grid[i] == GRID_TYPE_O) {
      Surface::Draw(displaySurface, oSurface, x, y);
    }
  }

  SDL_Flip(displaySurface);
}

void Game::OnCleanup() {
  SDL_FreeSurface(oSurface);
  SDL_FreeSurface(xSurface);
  SDL_FreeSurface(gridSurface);
  SDL_FreeSurface(displaySurface);
  SDL_Quit();
}

void Game::Reset() {
  currentPlayer = 0;
  for (int i = 0; i < 9; i++) {
    grid[i] = GRID_TYPE_NONE;
  }
}

void Game::SetCell(int id, int type) {
  if (id < 0 || id >= 9) return;
  if (type < GRID_TYPE_NONE || type > GRID_TYPE_O) return;

  grid[id] = type;
}
