#include "./consts.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int game_running = FALSE;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int last_frame_time = 0;

struct Rect {
  int x, y, w, h;
} rect;

int init_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return FALSE;
  }

  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
  if (!window) {
    printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
    return FALSE;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
    return FALSE;
  }

  return TRUE;
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    game_running = FALSE;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
      game_running = FALSE;
    break;
  }
}

void setup(void) {
  rect.x = 20;
  rect.y = 20;
  rect.w = 20;
  rect.h = 20;
}

void update(void) {
  int wait_time = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
  if (wait_time > 0 && wait_time <= FRAME_TARGET_TIME) {
    SDL_Delay(wait_time);
  }
  
  float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
  last_frame_time = SDL_GetTicks();

  rect.x += 100 * delta_time;
  rect.y += 100 * delta_time;
}

void render(void) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderClear(renderer);

  SDL_Rect rect_test = {
      rect.x,
      rect.y,
      rect.w,
      rect.h,
  };

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &rect_test);

  SDL_RenderPresent(renderer);
}

void destroy(void) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char const *argv[]) {
  game_running = init_window();

  setup();

  while (game_running) {
    process_input();
    update();
    render();
  }

  destroy();

  printf("Hello, World!\n");
  return 0;
}
