#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "raylib.h"

#define BOARD_SIZE 10
#define TILE_SIZE 42
#define TILE_TYPES 7

const char tile_chars[TILE_TYPES] = { '#', '!', '$', '@', '&', '%', '*' };

char board[BOARD_SIZE][BOARD_SIZE];

Vector2 grid_origin;
Texture2D background;

char random_tile() {
  return tile_chars[rand() % TILE_TYPES];
}

void init_board() {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      board[x][y] = random_tile();
    }
  }

  int grid_width = BOARD_SIZE * TILE_SIZE;
  int grid_height = BOARD_SIZE * TILE_SIZE;

  grid_origin = (Vector2) {
    (GetScreenWidth() - grid_width) / 2,
    (GetScreenHeight() - grid_height) / 2
  };
}

int main() {
  const int screen_width = 800;
  const int screen_height = 600;
  InitWindow(screen_width, screen_height, "Match3");
  SetTargetFPS(60);
  srand(time(NULL));
  
  background = LoadTexture("assets/background.png");

  init_board();

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(
      background,
      (Rectangle) { 0, 0, background.width, background.height },
      (Rectangle) { 0, 0, GetScreenWidth(), GetScreenHeight() },
      (Vector2) { 0, 0 },
      0.0f,
      WHITE
    );

    for (int y = 0; y < BOARD_SIZE; y++) {
      for (int x = 0; x < BOARD_SIZE; x++) {
        Rectangle rectangle = {
          grid_origin.x + (x * TILE_SIZE),
          grid_origin.y + (y * TILE_SIZE),
          TILE_SIZE,
          TILE_SIZE
        };

        DrawRectangleLinesEx(rectangle, 1, DARKGRAY);
        DrawTextEx(
          GetFontDefault(), 
          TextFormat("%c", board[x][y]), 
          (Vector2) { rectangle.x + 15, rectangle.y + 10 },
          20, 1, WHITE
        );
      }
    }

    EndDrawing();
  }
  
  UnloadTexture(background);

  CloseWindow();

  return 0;
}
