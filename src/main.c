#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "raylib.h"

#define BOARD_SIZE 10
#define TILE_SIZE 45
#define TILE_TYPES 7

const char tile_chars[TILE_TYPES] = { '#', '!', '$', '@', '&', '%', '*' };

char board[BOARD_SIZE][BOARD_SIZE];
bool matched[BOARD_SIZE][BOARD_SIZE] = { 0 };

int score = 0;
Vector2 grid_origin;
Texture2D background;
Font font;
Vector2 selected_tile = { -1, -1 };

char random_tile() {
  return tile_chars[rand() % TILE_TYPES];
}

bool find_matches() {
  bool found = false;
  
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      matched[y][x] = false;
    }
  }

  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE - 2; x++) {
      char t = board[y][x];
      
      if (t == board[y][x + 1] && t == board[y][x + 2]) {
        matched[y][x] = matched[y][x + 1] = matched[y][x + 2] = true;
        score += 10;
        found = true;
      }
    }
  }

  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE - 2; y++) {
      char t = board[y][x];
      
      if (t == board[y + 1][x] && t == board[y + 2][x]) {
        matched[y][x] = matched[y + 1][x] = matched[y + 2][x] = true;
        score += 10;
        found = true;
      }
    }
  }

  return found;
}

void resolve_matches() {

}

void init_board() {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      board[y][x] = random_tile();
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
  font = LoadFont("assets/font/Px437_Philips_YES_T.ttf");

  init_board();

  Vector2 mouse = { 0, 0 };

  while (!WindowShouldClose()) {
    mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      int x = (mouse.x - grid_origin.x) / TILE_SIZE;
      int y = (mouse.y - grid_origin.y) / TILE_SIZE;

      if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        selected_tile = (Vector2) { x, y };
      }
    }

    find_matches();

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

        DrawRectangleLinesEx(rectangle, 1.0f, DARKGRAY);
        DrawTextEx(
          font, 
          TextFormat("%c", board[y][x]), 
          (Vector2) { rectangle.x + 15, rectangle.y + 12 },
          20, 
          1.0f,
          matched[y][x] ? GREEN : WHITE
        );
      }
    }

    if (selected_tile.x >= 0) {
      DrawRectangleLinesEx(
        (Rectangle) {
          grid_origin.x + (selected_tile.x * TILE_SIZE),
          grid_origin.y + (selected_tile.y * TILE_SIZE),
          TILE_SIZE,
          TILE_SIZE
        }, 
        2.0f,
        PURPLE
      );
    }

    DrawTextEx(
      font,
      TextFormat("SCORE: %d", score),
      (Vector2) { 20, 20 },
      24,
      1.0f,
      PURPLE
    );

    EndDrawing();
  }
  
  UnloadTexture(background);
  UnloadFont(font);

  CloseWindow();

  return 0;
}
