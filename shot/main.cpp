#include "raylib.h"
#include "game.h"


int main() {
	InitWindow(800, 600, "shot");
	SetTargetFPS(144);
	init();

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		update();
		draw();
		EndDrawing();
	}

	unload();

	CloseWindow();

	return 0;
}