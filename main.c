#include "raylib.h"

int main() {
    // constants
    const int width = 500;
    const int height = 500;
    const char* title = "Move this circle";
    const float radius = 40.0f;

    // variables
    bool lockOnBall = false;
    Vector2 cursorTmpPos;
    Vector2 center = {
            (float) width/2,
            (float) height/2,
    };

    InitWindow(width, height, title);
    SetTargetFPS(120);

    // GAME LOOP
    while (!WindowShouldClose()) {
        // UPDATE
        {
            Vector2 cursorPos = GetMousePosition();
            if (CheckCollisionPointCircle(cursorPos, center, radius) || lockOnBall) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    cursorTmpPos = cursorPos;
                    lockOnBall = true;
                }

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    float deltaX = cursorPos.x - cursorTmpPos.x;
                    float deltaY = cursorPos.y - cursorTmpPos.y;

                    center.x = center.x + deltaX;
                    center.y = center.y + deltaY;

                    cursorTmpPos = cursorPos;
                }
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                lockOnBall = false;
            }
        }
        // UPDATE

        // DRAW
        BeginDrawing();
        {
            ClearBackground(BLACK);
            DrawCircle((int)center.x, (int)center.y, 40.0f, RED);
        }
        EndDrawing();
        // DRAW
    }
    // GAME LOOP

    CloseWindow();
    return 0;
}
