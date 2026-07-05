#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>

#include <raylib.h>

constexpr float SLOT_SIZE = 64;
Texture2D
  king_black,
  bishop_black,
  knight_black,
  queen_black,
  pawn_black,
  rook_black,
  king_white,
  bishop_white,
  knight_white,
  queen_white,
  pawn_white,
  rook_white;

enum class Piece : std::uint8_t
{
  NONE,
  BPAWN,
  BBISHOP,
  BKING,
  BQUEEN,
  BKNIGHT,
  BROOK,
  WPAWN,
  WBISHOP,
  WKING,
  WQUEEN,
  WKNIGHT,
  WROOK
};

struct Board
{
  Board(int width = 8, int height = 8)
    : width { width }, height { height }
  {
    this->clear();
  }
  
  void clear()
  {
    slots.resize(width, std::vector<Piece>(height, Piece::NONE));
  }

  std::vector<std::vector<Piece>> slots;
  int width, height;
};

struct GrabedPice
{
  Piece piece = Piece::NONE;
  int last_x, last_y;
} grabed_piece;

bool isValidBoardPosition(int grid_x, int grid_y, const Board &board)
{
  return grid_x < board.width && grid_x >= 0 && grid_y < board.height && grid_y >= 0;
}

void drawBoard(const Board &board)
{
  for(int x = 0; x < board.width; x++)
  {
    for(int y = 0; y < board.height; y++)
    {
      Color color = (x + y) % 2 == 0 ? Color { 234, 237, 209, 255 } : Color { 118, 149, 87, 255 };

      DrawRectangle(SLOT_SIZE * x, SLOT_SIZE * y, SLOT_SIZE, SLOT_SIZE, color);
    }

  }
}

Texture2D getTextureByPiece(Piece piece)
{
  switch (piece)
  {
  case Piece::WQUEEN: return queen_white; break;
  case Piece::WBISHOP: return bishop_white; break;
  case Piece::WKING: return king_white; break;
  case Piece::WKNIGHT: return knight_white; break;
  case Piece::WPAWN: return pawn_white; break;
  case Piece::WROOK: return rook_white; break;
  case Piece::BQUEEN: return queen_black; break;
  case Piece::BBISHOP: return bishop_black; break;
  case Piece::BKING: return king_black; break;
  case Piece::BKNIGHT: return knight_black; break;
  case Piece::BPAWN: return pawn_black; break;
  case Piece::BROOK: return rook_black; break;
  default: return queen_white; break;
  }
}

void drawBoardPieces(const Board &board)
{
  for(int x = 0; x < board.width; x++)
  {
    for(int y = 0; y < board.height; y++)
    {
      const Piece &piece = board.slots[y][x];
      const Texture2D texture = getTextureByPiece(piece);

      if(piece == Piece::NONE) continue;

      DrawTexturePro(
        texture,
        Rectangle { 0.f, 0.f, static_cast<float>(texture.width), static_cast<float>(texture.height) },
        Rectangle { static_cast<float>(SLOT_SIZE * x), static_cast<float>(SLOT_SIZE * y), static_cast<float>(SLOT_SIZE), static_cast<float>(SLOT_SIZE) },
        Vector2 { 0.f, 0.f },
        0.f, WHITE
      );
    }
  } 
}

void drawSlotOverlay(Vector2 global_mouse_position, Board &board)
{
  int 
    grid_x = std::floorf(global_mouse_position.x / static_cast<float>(SLOT_SIZE)),
    grid_y = std::floorf(global_mouse_position.y / static_cast<float>(SLOT_SIZE));

  Rectangle overlay_slot = {
    static_cast<float>(grid_x) * static_cast<float>(SLOT_SIZE),
    static_cast<float>(grid_y) * static_cast<float>(SLOT_SIZE),
    SLOT_SIZE, SLOT_SIZE
  };

  if(isValidBoardPosition(grid_x, grid_y, board))
  {
    DrawRectangleRec(overlay_slot, Color { 255, 255, 255, 80});
  }
}

void updateBoard(Board &board, Vector2 global_mouse_position)
{
  int
    grid_x = std::floorf(global_mouse_position.x / SLOT_SIZE),
    grid_y = std::floorf(global_mouse_position.y / SLOT_SIZE);

  if(!isValidBoardPosition(grid_x, grid_y, board)) return;

  Piece piece = board.slots[grid_y][grid_x];

  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    if(piece != Piece::NONE && grabed_piece.piece == Piece::NONE)
    {
      grabed_piece.piece = piece;
      grabed_piece.last_x = grid_x;
      grabed_piece.last_y = grid_y;
      
      board.slots[grid_y][grid_x] = Piece::NONE;
    }
    else if(piece == Piece::NONE && grabed_piece.piece != Piece::NONE)
    {
      board.slots[grid_y][grid_x] = grabed_piece.piece;
      grabed_piece.piece = Piece::NONE;
    }
  }
}

void drawGrabedPiece(Vector2 global_mouse_position)
{
  if(grabed_piece.piece != Piece::NONE)
  {
    const Texture2D texture = getTextureByPiece(grabed_piece.piece);

    DrawTexturePro(
      texture,
      Rectangle { 0.f, 0.f, static_cast<float>(texture.width), static_cast<float>(texture.height) },
      Rectangle { global_mouse_position.x, global_mouse_position.y, static_cast<float>(SLOT_SIZE), static_cast<float>(SLOT_SIZE) },
      Vector2 { 0.f, 0.f },
      0.f, WHITE
    );
  }
}

void loadTextures()
{
  king_black = LoadTexture("asset/modern/bk.png");
  bishop_black = LoadTexture("asset/modern/bb.png");
  knight_black = LoadTexture("asset/modern/bn.png");
  queen_black = LoadTexture("asset/modern/bq.png");
  pawn_black = LoadTexture("asset/modern/bp.png");
  rook_black = LoadTexture("asset/modern/br.png");
  king_white = LoadTexture("asset/modern/wk.png");
  bishop_white = LoadTexture("asset/modern/wb.png");
  knight_white = LoadTexture("asset/modern/wn.png");
  queen_white = LoadTexture("asset/modern/wq.png");
  pawn_white = LoadTexture("asset/modern/wp.png");
  rook_white = LoadTexture("asset/modern/wr.png");
}

void unloadTextures()
{
  UnloadTexture(king_black);
  UnloadTexture(bishop_black);
  UnloadTexture(knight_black);
  UnloadTexture(queen_black);
  UnloadTexture(pawn_black);
  UnloadTexture(rook_black);
  UnloadTexture(king_white);
  UnloadTexture(bishop_white);
  UnloadTexture(knight_white);
  UnloadTexture(queen_white);
  UnloadTexture(pawn_white);
  UnloadTexture(rook_white);
}

void setupBoardPieces(Board &board)
{
  board.slots[7][0] = Piece::WROOK;
  board.slots[7][7] = Piece::WROOK;
  board.slots[7][6] = Piece::WKNIGHT;
  board.slots[7][1] = Piece::WKNIGHT;
  board.slots[7][5] = Piece::WBISHOP;
  board.slots[7][2] = Piece::WBISHOP;
  board.slots[7][3] = Piece::WQUEEN;
  board.slots[7][4] = Piece::WKING;
  for(int i = 0; i < 8; i++)
    board.slots[6][i] = Piece::WPAWN;

  board.slots[0][0] = Piece::BROOK;
  board.slots[0][7] = Piece::BROOK;
  board.slots[0][6] = Piece::BKNIGHT;
  board.slots[0][1] = Piece::BKNIGHT;
  board.slots[0][5] = Piece::BBISHOP;
  board.slots[0][2] = Piece::BBISHOP;
  board.slots[0][4] = Piece::BKING;
  board.slots[0][3] = Piece::BQUEEN;
  for(int i = 0; i < 8; i++)
    board.slots[1][i] = Piece::BPAWN;
}

int main(int, char *[])
{
  InitWindow(720, 720, "Chess 2.0");
  loadTextures();

  Board board;
  Camera2D camera = {
    .offset = { static_cast<float>(GetScreenWidth()) / 2.f, static_cast<float>(GetScreenHeight()) / 2.f },
    .target = { static_cast<float>(board.width * SLOT_SIZE) / 2.f, static_cast<float>(board.height * SLOT_SIZE) / 2.f },
    .rotation = 0.f,
    .zoom = 1.f
  };

  setupBoardPieces(board);

  while(!WindowShouldClose())
  {
    Vector2 mouse_position = GetMousePosition();
    Vector2 global_mouse_position = GetScreenToWorld2D(mouse_position, camera);
    
    updateBoard(board, global_mouse_position);

    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(camera);
    
    
    drawBoard(board);
    drawBoardPieces(board);
    drawSlotOverlay(global_mouse_position, board);
    drawGrabedPiece(global_mouse_position);


    EndMode2D();

    EndDrawing();
  }

  unloadTextures();

  CloseWindow();

  return EXIT_SUCCESS;
}