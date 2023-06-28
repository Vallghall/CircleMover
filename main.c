#include "raylib.h"

float limit(float value) {
    const float speed_limit = 10.0f;

    if (value > speed_limit)
        return speed_limit;

    if (value < -speed_limit)
        return -speed_limit;

    return value;
}

int main() {
    // constants
    const int width = 500;
    const int height = 500;
    const char* title = "Move this circle";
    const float radius = 40.0f;
    const float decoy = 0.995f;

    // variables
    bool isHeld = false;
    Vector2 speed = {
        0.0f,
        0.0f,
    };
    Vector2 center = {
            (float) width/2,
            (float) height/2,
    };

    InitWindow(width, height, title);
    SetTargetFPS(60);

    // GAME LOOP
    while (!WindowShouldClose()) {
        // UPDATE
        {
            // logic for holding and moving a circle with a mouse
            Vector2 cursorPos = GetMousePosition();
            if (CheckCollisionPointCircle(cursorPos, center, radius) || isHeld) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    isHeld = true;
                    speed.x = 0.0f;
                    speed.y = 0.0f;
                }

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    Vector2 delta = GetMouseDelta();

                    center.x = center.x + delta.x;
                    center.y = center.y + delta.y;
                }
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && isHeld) {
                isHeld = false;

                Vector2 delta = GetMouseDelta();
                speed.x = limit(0.8f * delta.x);
                speed.y = limit(0.8f * delta.y);
            }

            // logic for circle movement when it's free
            if (!isHeld) {
                // Check collision with borders
                {
                    if (center.x <= radius || center.x >= width  - radius) speed.x *= -1.0f;
                    if (center.y <= radius || center.y >= height - radius) speed.y *= -1.0f;
                }

                center.x += speed.x;
                center.y += speed.y;

                speed.x *= decoy;
                speed.y *= decoy;
            }

        }
        // UPDATE

        // DRAW
        BeginDrawing();
        {
            ClearBackground(BLACK);
            DrawCircleV(center, 40.0f, RED);
        }
        EndDrawing();
        // DRAW
    }
    // GAME LOOP

    CloseWindow();
    return 0;
}
