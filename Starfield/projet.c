#define _CRT_SECURE_NO_WARNINGS //pour pouvoir utiliser scanf
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
//Pour pouvoir lancer ce jeu vous devez installer https://www.openal.org/downloads/ sur votre PC
//programme qui affiche une fenêtre avec un rectangle et qui déplace le rectangle avec les flèches.


#define INC_DEP_RECT 10
#define L_RECT 50
#define H_RECT 100
#define L_WIN 480
#define H_WIN 380

int main()
{
	sfRenderWindow* window;
	sfEvent event;
	sfRectangleShape* rect;
	sfVector2f posRect = { 0,0 };
	int dy = INC_DEP_RECT, dx = INC_DEP_RECT;
	rect = sfRectangleShape_create();
	sfRectangleShape_setFillColor(rect, sfRed);
	sfRectangleShape_setSize(rect, (sfVector2f) { L_RECT, H_RECT });
	window = sfRenderWindow_create((sfVideoMode) { L_WIN, H_WIN, 32 }, "Rectangle", sfClose, NULL);
	while (sfRenderWindow_isOpen(window)) {
		// Process events 
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed || event.key.code == sfKeyEscape)
				sfRenderWindow_close(window);
			if (event.type == sfEvtKeyPressed) {
				printf("sfEvtKeyPressed\n");
				if (event.key.code == sfKeyUp)
					posRect.y -= dy;
				if (event.key.code == sfKeyDown)
					posRect.y += dy;
				if (event.key.code == sfKeyLeft)
					posRect.x -= dx;
				if (event.key.code == sfKeyRight)
					posRect.x += dx;
			}
		}
		sfRectangleShape_setPosition(rect, posRect);
		sfRenderWindow_clear(window, sfWhite);
		sfRenderWindow_drawRectangleShape(window, rect, NULL);
		// Update the window 
		sfRenderWindow_display(window);
		// temps de rafraichissement pour pas trop charger le GPU
		sfSleep((sfTime) { 20000 });
	}
	// Cleanup resources 
	sfRectangleShape_destroy(rect);
	sfRenderWindow_destroy(window);
	return EXIT_SUCCESS;
}

