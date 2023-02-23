#include <raylib.h>
#include <iostream>
#include <vector>

int main(void)
{
	InitWindow(840, 540, "Big Juicy Window :)");

	Rectangle a = { 0, 0, 100, 100 };
	Rectangle b = { 0, 540-100/2, 840/2, 100 };
	Rectangle c = { 150, 540-100, 100, 100 };

	std::vector<Rectangle*> rects = {&a, &b, &c};

	int i = 0;

	int ac = 1;
	int vel = 0;

	bool grounded = false;

	std::string debug_info = " a_x : " + 
		std::to_string(a.x) + ", a_y : " + 
		std::to_string(a.y) + " c_x : " + 
		std::to_string(c.x) + ", c_y : " + std::to_string(c.y) + " grounded : " + std::to_string(grounded) +  '\n';

	while (!WindowShouldClose())
	{
		if (CheckCollisionRecs(a, b))
		{
			//a.y -= 1;
			vel = 0;
			grounded = true;
		}

		if (!CheckCollisionRecs(a, b))
			grounded = false;

		debug_info = " a_x : " + 
		std::to_string(a.x) + ", a_y : " + 
		std::to_string(a.y) + " c_x : " + 
		std::to_string(c.x) + ", c_y : " + std::to_string(c.y) + " grounded : " + std::to_string(grounded) +  '\n';

		if (!grounded)
		{
			vel += ac;
			a.y += vel * GetFrameTime();
		}

		BeginDrawing();
		
		ClearBackground(RAYWHITE);

		for (int i = 0; i < rects.size(); i++)
		{
			if (i % 2 == 0)
				DrawRectangleRec(*rects[i], GREEN);
			else
				DrawRectangleRec(*rects[i], SKYBLUE);
		}

		DrawText(debug_info.c_str(), 840/2, 50, 10, BLACK);

		DrawLine(a.x, a.y, a.x+100, a.y+100, DARKGREEN);

		if (IsKeyPressed(KEY_SPACE))
		{
			a.y -= 1;
			grounded = false;
			vel -= 1000;
		}

		if (IsKeyDown(KEY_W))
		{
			if (!CheckCollisionRecs(a, b))
				a.y -= .1;

			if (CheckCollisionRecs(a, b))
				a.y += 1;
		}
		if (IsKeyDown(KEY_S))
		{
			if (!CheckCollisionRecs(a, b))
				a.y += .1;

			if (CheckCollisionRecs(a, b))
				a.y -= 1;
		}

		if (IsKeyDown(KEY_A))
		{
			//if (!CheckCollisionRecs(a, b))
				a.x -= .1;
		}
		if (a.x > c.x && CheckCollisionRecs(a, c))
		{
			a.x += 1;
		}

		if (a.y < c.y+100 && CheckCollisionRecs(a, c))
		{
			a.y -= 1;
		}

		if (CheckCollisionRecs(a, c))
			grounded = true;

		DrawRectangleLines(c.x, c.y, 100, 100, RED);
		if (IsKeyDown(KEY_D))
		{
			//if (!CheckCollisionRecs(a, b))
				a.x += .1;

			// if (CheckCollisionRecs(a, b))
			// 	a.x -= 1;
		}

		EndDrawing();
	}

	return 0;
}