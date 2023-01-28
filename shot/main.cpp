#include "raylib.h"
#include "game.h"
#define WIDTH 1600
#define HEIGHT 900


int main() {
	InitWindow(WIDTH, HEIGHT, "shot");
	InitAudioDevice();
	SetTargetFPS(144);
	init();

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground({40,40,40,255});
		update();
		draw();
		EndDrawing();
	}

	StopSoundMulti();

	unload();

	CloseAudioDevice();
	CloseWindow();

	return 0;
}