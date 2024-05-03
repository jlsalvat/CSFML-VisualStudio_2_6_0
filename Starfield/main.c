#include <SFML/Graphics.h>
//premier programme qui affiche une fenêtre vide (gestion seulement de l'évènement de fermeture de fenêtre
int main(){
	sfRenderWindow* window;
	sfEvent event;
	window = sfRenderWindow_create((sfVideoMode) { 280, 280, 32 }, "Hello!", sfClose, NULL);
	while (sfRenderWindow_isOpen(window)) {
		// Process events 
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed || event.key.code == sfKeyEscape)
				sfRenderWindow_close(window);
		}
		sfRenderWindow_clear(window, sfWhite);
		// Update the window 
		sfRenderWindow_display(window);
		// temps de rafraichissement pour pas trop charger le GPU
		sfSleep((sfTime) { 20000 });
	}
	// Cleanup resources 
	sfRenderWindow_destroy(window);
	return 0;
}
/*
//deuxième programme qui affiche une fenêtre avec un rond rouge et qui gère les évènements liés à la souris et au clavier (flèches)
//permet de d'afficher un rond rouge et de le déplacer
#include <SFML/Graphics.h>
int main()
{
	sfRenderWindow* window;
	sfEvent event;
	sfCircleShape* rond;
	sfVector2f position = { 0,0 };
	int dy = 10,dx=10;
	rond= sfCircleShape_create();
	sfCircleShape_setFillColor(rond, sfRed);
	sfCircleShape_setRadius(rond, 30);
	window = sfRenderWindow_create((sfVideoMode) { 280, 280, 32 }, "Hello!",  sfClose, NULL);
	while (sfRenderWindow_isOpen(window)) {
		// Process events 
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed || event.key.code == sfKeyEscape)
				sfRenderWindow_close(window);
			if (event.type == sfEvtMouseButtonPressed) {
				position.x = event.mouseButton.x;
				position.y = event.mouseButton.y;
			}
			if (event.type == sfEvtKeyPressed) {
				if (event.key.code == sfKeyUp)
					position.y -= dy;
				if (event.key.code == sfKeyDown)
					position.y += dy;
				if (event.key.code == sfKeyLeft)
					position.x -= dx;
				if (event.key.code == sfKeyRight)
					position.x += dx;
			}
		}
		sfCircleShape_setPosition(rond, position);
		sfRenderWindow_clear(window, sfWhite);
		sfRenderWindow_drawCircleShape(window, rond, NULL);
		// Update the window 
		sfRenderWindow_display(window);
		// temps de rafraichissement pour pas trop charger le GPU
		sfSleep((sfTime) { 20000 });
	}
	// Cleanup resources 
	sfCircleShape_destroy(rond);
	sfRenderWindow_destroy(window);
	return 0;
}
*/
/*
//troisième programme qui permet d'afficher du texte (click ou A) ou un rond vert en fonction de la variable toggle.

#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.h>
#include <stdio.h>
//Pour pouvoir lancer ce jeu vous devez installer https://www.openal.org/downloads/ sur votre PC

#define HAUTEUR 600
#define LARGEUR 800
#define PAS 10

sfEvent event;
int main()
{
	sfRenderWindow* window;
	sfFont* font;
	sfText* textAffiche;
	int toggle = 1;
	sfCircleShape *rond= sfCircleShape_create();
	sfCircleShape_setFillColor(rond,sfGreen);
	sfCircleShape_setRadius(rond, 100);
	// Create the main window 
	window = sfRenderWindow_create((sfVideoMode){200, 200, 32 }, "SFML works!", sfResize | sfClose, NULL);
	font = sfFont_createFromFile("ressources/arial.ttf");
	// Create a graphical text to display 
	textAffiche = sfText_create();
	sfText_setFont(textAffiche, font);
	sfText_setCharacterSize(textAffiche, 20);
	sfText_setPosition(textAffiche, (sfVector2f){ 50,50 });
	sfText_setFillColor(textAffiche, sfWhite);
	// Start the game loop 
	while (sfRenderWindow_isOpen(window)){
		// Process events 
		while (sfRenderWindow_pollEvent(window, &event))
		{
			// Close window : exit or Escape
			if (event.type == sfEvtClosed || event.key.code == sfKeyEscape)
				sfRenderWindow_close(window);
			if (event.type == sfEvtMouseButtonPressed) {
				sfText_setString(textAffiche, "CLICK");
				toggle = !toggle;
			}
			if (event.type == sfEvtTextEntered && (event.text.unicode == 'A' || event.text.unicode == 'a')) {
				printf("A");
				sfText_setString(textAffiche, "A");
				toggle = !toggle;
			}
		}
		sfRenderWindow_clear(window, sfBlack);
		if (toggle)
			sfRenderWindow_drawCircleShape(window, rond, NULL);
		else
			sfRenderWindow_drawText(window, textAffiche, NULL);
		// Update the window 
		sfRenderWindow_display(window);
		// temps de rafraichissement pour pas trop charger le GPU
		sfSleep((sfTime){20000});
	}
	// Cleanup resources 
	sfCircleShape_destroy(rond);
	sfRenderWindow_destroy(window);
	return 0;
}
*/