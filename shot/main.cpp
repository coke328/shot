#include "raylib.h"
#include "game.h"

int main() {
	InitWindow(800, 600, "shot");
	
	init();

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		update();
		draw();
		EndDrawing();
	}

	unload();

	CloseWindow();

	return 0;
}