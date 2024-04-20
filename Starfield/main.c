#define _CRT_SECURE_NO_WARNINGS //pour pouvoir utiliser scanf
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
/*Pour pouvoir lancer ce jeu vous devez installer https://www.openal.org/downloads/ sur votre PC*/

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
	sfText* debug;
	sfMusic* music;
	sfEvent event;
	sfRectangleShape *rectangle;
	sfCircleShape* cercle;

//mes variables
	char tab[100];
	char tabDebug[100];
	int cpt = 0;
	int state_son = 0;
	int state_jeu = 0;
	
	/* Create the main window */
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	if (!window) {
		printf("impossible de créer la fenêtre graphique");
		return EXIT_FAILURE;
	}
	/* Load a sprite to display */
	texture = sfTexture_createFromFile("ressources/sfmljl_icon.png", NULL);
	if (!texture) {
		printf("ERREUR : ouverture de l'image \'ressources/sfmljl_icon.png\'");
		return EXIT_FAILURE;
	}
	sfVector2u size = sfTexture_getSize(texture);
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue); 
	sfVector2f pos = { 100.0,100.0 };
	sfSprite_setPosition(sprite, pos);
	
	/* open FONT */
	font = sfFont_createFromFile("ressources/arial.ttf");
	if (!font) {
		printf("ERREUR : ouverture de la font \'ressources/arial.ttf\'");
		return EXIT_FAILURE;
	}

	/* Create a graphical text to display */
	text = sfText_create();
	sfText_setFont(text, font);
	sfText_setCharacterSize(text, 50);
	sfVector2f posText;
	posText.x = pos.x + 100;
	posText.y = pos.y;
	sfText_setPosition(text, posText);
	sfText_setString(text, "Cliquer pour démarrer");
	
	/* Create a graphical text DEBUG bottom of display */
	debug = sfText_create();
	sfText_setFont(debug, font);
	sfText_setCharacterSize(debug, 13);
	sfVector2f posDebug = { 0,HAUTEUR-17 };
	sfText_setPosition(debug, posDebug);
	sfText_setColor(debug,sfMagenta);
	
	/* Create a graphical shape circle for clic zone */
	cercle = sfCircleShape_create();
	sfCircleShape_setFillColor(cercle, sfBlue);
	sfCircleShape_setRadius(cercle,5);
	sfCircleShape_setOutlineThickness(cercle,2);
	sfCircleShape_setOutlineColor(cercle, sfWhite);

	/* Create a graphical shape rectangle for debug zone */
	rectangle=sfRectangleShape_create();
	sfColor color = { 0x16,0x5a,0x72 };//autre solution de couleur en RGB
	sfRectangleShape_setFillColor(rectangle, sfColor_fromInteger(0xC71585A0));//RGBA 32 hexa
	sfRectangleShape_setPosition(rectangle, posDebug);
	sfVector2f sizeRect = { LARGEUR,20 };
	sfRectangleShape_setSize(rectangle, sizeRect);

	// Load a music to play en boucle
	music = sfMusic_createFromFile("ressources/sound.wav");
	if (!music) {
		printf("ERREUR : ouverture du fichier \'ressources/sound.wav\'");
		return EXIT_FAILURE;
	}
	sfTime dur = sfMusic_getDuration(music);
	sfTimeSpan timespan = { 0, dur };
	sfMusic_setLoopPoints(music, timespan);

	/* Start the game loop */
	while (sfRenderWindow_isOpen(window))
	{
		/* Process events */
		while (sfRenderWindow_pollEvent(window, &event))
		{
			/* Close window : exit or Escape*/
			if (event.type == sfEvtClosed || event.key.code == sfKeyEscape)
				sfRenderWindow_close(window);
			/*click on mouse */
			if (event.type == sfEvtMouseButtonPressed) {
				state_jeu = 1; //pour détecter le premier clic
				posText.x = event.mouseButton.x;
				posText.y = event.mouseButton.y;
				sprintf(tab, "CLICK %d", cpt++);
				sfText_setString(text, tab);
				sfText_setPosition(text, posText);
				sfCircleShape_setPosition(cercle, posText);
				printf("click\n");

			}
			/*use of arrow for move the image*/
			if (event.key.code == sfKeyLeft) {
				pos.x -= 10;
				sfSprite_setPosition(sprite, pos);
			}
	
			if (event.key.code == sfKeyRight) {
				pos.x += 10;
				sfSprite_setPosition(sprite, pos);
			}
			if (event.key.code == sfKeyUp) {
				pos.y -= 10;
				sfSprite_setPosition(sprite, pos);
			}
			if (event.key.code == sfKeyDown) {
				pos.y += 10;
				sfSprite_setPosition(sprite, pos);
			}
			/*collision detection */
			sfVector2f vectorText = sfText_getPosition(text); 
			sfVector2f vectorSpritePos = sfSprite_getPosition(sprite);
			float leftText = vectorText.x;
			float rightText = vectorText.x + 180;
			float topText = vectorText.y;
			float bottomText = vectorText.y + 50;
			float leftSprite = vectorSpritePos.x;
			float rightSprite = vectorSpritePos.x + size.x;
			float topSprite = vectorSpritePos.y;
			float bottomSprite = vectorSpritePos.y + size.y;
			if(((bottomText <= topSprite) || (topText >= bottomSprite) || (rightText <= leftSprite) || (leftText >= rightSprite)) == 0){
				sfText_setString(text, "COLLISION");
				sfText_setColor(text, sfRed);
				if (state_son == 0) {
					state_son = 1;
					sfMusic_play(music);
				}
			}
			else {
				state_son = 0;
				if (state_jeu) { // au premier clic on change le texte
					sfText_setString(text, tab);
					sfText_setColor(text, sfWhite);
					sfMusic_stop(music);
				}
			}
		}
		/*update text DEBUG*/
		sprintf(tabDebug, "utiliser les flèches pour déplacer le logo, attention COLLISION possible avec le texte", cpt);
		sfText_setString(debug, tabDebug);
		/* Clear the screen */
		sfRenderWindow_clear(window, sfBlack);
		/* draw rectangle */
		sfRenderWindow_drawRectangleShape(window,rectangle,NULL);
		/* Draw the sprite */
		sfRenderWindow_drawSprite(window, sprite, NULL);
		/*Draw Circle au premier clic*/
		if(state_jeu)
			sfRenderWindow_drawCircleShape(window, cercle, NULL);
		/* Draw the texts */
		sfRenderWindow_drawText(window, text, NULL);
		sfRenderWindow_drawText(window, debug, NULL);
		/* Update the window */
		sfRenderWindow_display(window);
		/* temps de rafraichissement*/
		sfTime time_wait = { 20000 };// 20 ms
		sfSleep(time_wait);
	}
	/* Cleanup resources */
	sfMusic_destroy(music);
	sfText_destroy(text);
	sfFont_destroy(font);
	sfSprite_destroy(sprite);
	sfTexture_destroy(texture);
	sfRenderWindow_destroy(window);
	return EXIT_SUCCESS;
}