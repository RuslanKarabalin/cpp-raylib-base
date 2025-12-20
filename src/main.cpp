#include <raylib.h>
#include <entt.hpp>

static int WINDOW_WIDTH = 1600;
static int WINDOW_HEIGHT = 900;

struct PlayerTag {};

struct Position {
    Vector2 vec2;
};

struct Velocity {
    Vector2 vec2;
};

struct RenderableCircle {
    int radius;
    Color color;
};

static void MovementSystem(entt::registry& world, float dt) {
    for (auto e : world.view<Position, Velocity>()) {
        auto& p = world.get<Position>(e).vec2;
        auto& v = world.get<Velocity>(e).vec2;
        p.x += v.x * dt;
        p.y += v.y * dt;
    }

    for (auto e : world.view<PlayerTag, Velocity>()) {
        auto& v = world.get<Velocity>(e).vec2;
        v.x *= 0.90f;
        v.y *= 0.90f;
    }
}

static void ClampPlayerToScreen(entt::registry& world, int w, int h) {
    for (auto e :
         world.view<PlayerTag, Position, RenderableCircle, Velocity>()) {
        auto& p = world.get<Position>(e).vec2;
        auto& r = world.get<RenderableCircle>(e).radius;
        auto& v = world.get<Velocity>(e).vec2;

        float minX = (float)r;
        float maxX = (float)w - r;
        float minY = (float)r;
        float maxY = (float)h - r;

        float newX = std::clamp(p.x, minX, maxX);
        float newY = std::clamp(p.y, minY, maxY);

        if (newX != p.x) {
            v.x = 0.0f;
        }
        if (newY != p.y) {
            v.y = 0.0f;
        }

        p.x = newX;
        p.y = newY;
    }
}

int main() {
    const int TARGET_FPS = 120;
    const float playerX = WINDOW_WIDTH / 2.0;
    const float playerY = 86 * WINDOW_HEIGHT / 90.0;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "WindowName");
    SetTargetFPS(TARGET_FPS);

    entt::registry world;

    auto player = world.create();
    world.emplace<PlayerTag>(player);
    world.emplace<Position>(player, Vector2{playerX, playerY});
    world.emplace<Velocity>(player, Vector2{0, 0});
    world.emplace<RenderableCircle>(player, 32, BLACK);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        float dt = GetFrameTime();
        auto& vel = world.get<Velocity>(player);
        if (IsKeyDown(KEY_W)) {
            vel.vec2.y = -700.0f;
        }
        if (IsKeyDown(KEY_A)) {
            vel.vec2.x = -700.0f;
        }
        if (IsKeyDown(KEY_S)) {
            vel.vec2.y = 700.0f;
        }
        if (IsKeyDown(KEY_D)) {
            vel.vec2.x = 700.0f;
        }
        MovementSystem(world, dt);
        ClampPlayerToScreen(world, WINDOW_WIDTH, WINDOW_HEIGHT);

        auto rederableCircles = world.view<Position, RenderableCircle>();
        for (auto [entity, pos, cc] : rederableCircles.each()) {
            DrawCircle(pos.vec2.x, pos.vec2.y, cc.radius, cc.color);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
