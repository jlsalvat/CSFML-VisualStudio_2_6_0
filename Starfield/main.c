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
	sfRectangleShape* rect;
	sfVector2f position = { 0,0 };
	int dy = 10,dx=10;
	rect= sfRectangleShape_create();
	sfRectangleShape_setFillColor(rect, sfRed);
	sfRectangleShape_setSize(rect, (sfVector2f) { 50, 50 });
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
		sfRectangleShape_setPosition(rect, position);
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
	return 0;
}


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

//quatrième programme qui permet d'afficher du texte (click ou A) , une image et émettre un son

#define _CRT_SECURE_NO_WARNINGS //pour pouvoir utiliser sprintf
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
//Pour pouvoir lancer ce jeu vous devez installer https://www.openal.org/downloads/ sur votre PC

#define HAUTEUR 600
#define LARGEUR 800
int main()
{
	sfVideoMode mode = { LARGEUR, HAUTEUR, 32 };
	sfRenderWindow* window;
	sfTexture* texture;
	sfSprite* sprite;
	sfFont* font;
	sfText* text;
	sfMusic* music;
	sfEvent event;
	sfClock* clk;

	//mes variables
	char tabText[100] = "C'est parti : un clic pour voir";
	int cpt = 0;
	sfVector2f pos = { 100,100 }, posImage = { LARGEUR / 2,HAUTEUR / 2 };

	//Create the main window 
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	// open FONT 
	font = sfFont_createFromFile("ressources/arial.ttf");
	// Load a sprite to display 
	texture = sfTexture_createFromFile("ressources/sfmljl_icon.png", NULL);
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setPosition(sprite, posImage);
	// Create a graphical text to display 
	text = sfText_create();
	sfText_setFont(text, font);
	sfText_setCharacterSize(text, 20);
	pos.x = pos.x;
	pos.y = pos.y + 100;
	sfText_setPosition(text, pos);
	sfText_setString(text, tabText);

	// Load a music to play in loop
	music = sfMusic_createFromFile("ressources/sound.wav");
	if (!music) {
		printf("ERREUR : ouverture du fichier \'ressources/sound.wav\'");
		return EXIT_FAILURE;
	}
	sfTime dur = sfMusic_getDuration(music);
	sfTimeSpan timespan = { 0, dur };
	sfMusic_setLoopPoints(music, timespan);

	//lance timer pour le son
	clk = sfClock_create();
	// Start the game loop 
	while (sfRenderWindow_isOpen(window))
	{
		// Process events
		while (sfRenderWindow_pollEvent(window, &event))
		{
			// Close window : exit or Escape
			if (event.type == sfEvtClosed || event.key.code == sfKeyEscape)
				sfRenderWindow_close(window);
			//click on mouse 
			if (event.type == sfEvtMouseButtonPressed) {
				pos.x = event.mouseButton.x;
				pos.y = event.mouseButton.y;
				sprintf(tabText, "CLICK %d", cpt++);
				//on lance la musique
				sfMusic_play(music);
				sfClock_restart(clk);
			}
			//use of arrow for move the image
			if (event.key.code == sfKeyLeft)
				posImage.x -= 10;
			if (event.key.code == sfKeyRight)
				posImage.x += 10;
			if (event.key.code == sfKeyUp)
				posImage.y -= 10;
			if (event.key.code == sfKeyDown)
				posImage.y += 10;
		}
		sfSprite_setPosition(sprite, posImage);
		sfText_setString(text, tabText);
		sfText_setPosition(text, pos);
		//arrêt de la musique au bout de 2s
		sfTime temps = sfClock_getElapsedTime(clk);
		if (temps.microseconds > 1000000) {
			sfMusic_stop(music);
		}
		//Clear the screen 
		sfRenderWindow_clear(window, sfBlack);
		// Draw the sprite 
		sfRenderWindow_drawSprite(window, sprite, NULL);
		// Draw the texts 
		sfRenderWindow_drawText(window, text, NULL);
		// Update the window 
		sfRenderWindow_display(window);
		// temps de rafraichissement pour pas trop charger le GPU
		sfTime time_wait = { 20000 };// 20 ms
		sfSleep(time_wait);
	}
	// Cleanup resources 
	sfMusic_destroy(music);
	sfText_destroy(text);
	sfFont_destroy(font);
	sfSprite_destroy(sprite);
	sfTexture_destroy(texture);
	sfRenderWindow_destroy(window);
	return EXIT_SUCCESS;
}
*/

