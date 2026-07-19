#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <cmath>

#include <raylib.h>

void drawOutline(Rectangle rect)
{
  DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, WHITE);
}

int main(int, char *[])
{
  InitWindow(720, 720, "Chess 2.0");
  SetTargetFPS(60);

  Texture2D
    hand_texture = LoadTexture("asset/hand.png"),
    item_texture = LoadTexture("asset/default.png");

  float hand_rotation = 0.f, item_rotation = -45.f;
  bool swing_animation = false;

  Rectangle player = { static_cast<float>(GetScreenWidth()) / 2.f - 16.f, static_cast<float>(GetScreenHeight()) / 2.f - 32.f, 32.f, 64.f };

  while(!WindowShouldClose())
  {
    Vector2 mouse_position = GetMousePosition();
    

    item_rotation = hand_rotation - 45.f;

    if(IsKeyDown(KEY_D))
    {
      player.x += 4;
    }
    if(IsKeyDown(KEY_A))
    {
      player.x -= 4;
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
      if(!swing_animation)
        hand_rotation = -110.f;
      swing_animation = true;
    }

    if(swing_animation)
    {
      hand_rotation += 1.f;

      if(hand_rotation >= 70.f)
      {
        hand_rotation = 0.f;
        swing_animation = false;
      }
    }

    hand_rotation += GetMouseWheelMove() * 10.f;
    float rad = hand_rotation * DEG2RAD;
    float cos_r = std::cosf(rad);
    float sin_r = std::sinf(rad);

    Rectangle hand = { player.x, player.y, 32.f, 32.f };
    hand.x += std::cosf(hand_rotation * DEG2RAD) * 30.f;
    hand.y += std::sinf(hand_rotation * DEG2RAD) * 30.f;

    Vector2 item_offset = { -2.f, -14.f };

    Rectangle item = {
      hand.x + (item_offset.x * cos_r - item_offset.y * sin_r),
      hand.y + (item_offset.x * sin_r + item_offset.y * cos_r),
      32.f, 32.f
    };


    BeginDrawing();
    ClearBackground(BLACK);
    









    
    DrawRectanglePro(player, Vector2 { 0.f, 0.f }, 0.f, GRAY);
    DrawTexturePro(item_texture,
      Rectangle { 8.f * 5.f, 8.f * 7.f, 8.f, 8.f }, item,
      Vector2 { 0.f, 0.f }, item_rotation, WHITE
    );
    DrawTexturePro(hand_texture,
      Rectangle { 0.f, 0.f, 32.f, 32.f }, hand,
      Vector2 { 0.f, 0.f }, hand_rotation, WHITE
    );

    drawOutline(hand);

    DrawText(("hand-angle: " + std::to_string(hand_rotation)).c_str(), 4, 4, 32, WHITE);

    EndMode2D();
    EndDrawing();
  }

  UnloadTexture(hand_texture);
  CloseWindow();

  return EXIT_SUCCESS;
}