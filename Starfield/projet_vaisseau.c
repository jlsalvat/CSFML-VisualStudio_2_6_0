#define _CRT_SECURE_NO_WARNINGS //pour pouvoir utiliser scanf
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
//Pour pouvoir lancer ce jeu vous devez installer https://www.openal.org/downloads/ sur votre PC


//programme qui affiche une fenêtre avec un rectangle et qui déplace le rectangle avec les flèches.

#include <SFML/Graphics.h>

#define INC_DEP_RECT 10
#define L_RECT 50
#define H_RECT 100
#define L_WIN 480
#define H_WIN 380
#define INC_DEP_BALLE 5
#define R_BALLE 10
#define SIZE_IMAGE 64
#define INC_ANGLE 5

int main()
{
	int collision = 0, tireBalle = 0;
	int angleImage = -90, angleBalle;
	angleBalle = angleImage;
	sfRenderWindow* window;
	sfEvent event;
	sfRectangleShape* rect;
	sfCircleShape** balle;
	sfTexture* texture;
	sfSprite* sprite;
	sfVector2f posRect = { 0,0 };
	sfVector2f posImage = { (L_WIN - SIZE_IMAGE),(H_WIN / 2) };
	sfVector2f posBalle = posImage;
	//Création rectangle
	rect = sfRectangleShape_create();
	sfRectangleShape_setFillColor(rect, sfRed);
	sfRectangleShape_setSize(rect, (sfVector2f) { L_RECT, H_RECT });
	//Création vaisseau
	texture = sfTexture_createFromFile("ressources/vaisseau.png", NULL);
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setPosition(sprite, posImage);
	sfVector2u sizeImage = sfTexture_getSize(texture);
	//déplacement de l'origine pour qu'elle soit au cendre de l'image
	sfSprite_setOrigin(sprite, (sfVector2f) { sizeImage.x / 2, sizeImage.y / 2 });
	sfSprite_rotate(sprite, angleImage);
	//l'image du vaisseau est 4 fois trop grande on la réduit.
	sfSprite_setScale(sprite, (sfVector2f) { 0.25, 0.25 });
	//Création balle
	balle = sfCircleShape_create();
	sfCircleShape_setFillColor(balle, sfRed);
	sfCircleShape_setRadius(balle, R_BALLE);
	sfCircleShape_setPosition(balle, posBalle);
	//Création fenêtre graphique
	window = sfRenderWindow_create((sfVideoMode) { L_WIN, H_WIN, 32 }, "Rectangle", sfClose, NULL);
	while (sfRenderWindow_isOpen(window)) {
		// Process events 
		while (sfRenderWindow_pollEvent(window, &event))		{
			if (event.type == sfEvtClosed || event.key.code == sfKeyEscape)
				sfRenderWindow_close(window);
			if (event.type == sfEvtKeyPressed) {
				if (event.key.code == sfKeyW) {
					angleImage += INC_ANGLE;
					sfSprite_rotate(sprite, INC_ANGLE);

				}
				if (event.key.code == sfKeyX) {
					angleImage -= INC_ANGLE;
					sfSprite_rotate(sprite, -INC_ANGLE);
				}
				if (event.key.code == sfKeyB) {
					tireBalle = 1;
					angleBalle = angleImage;
				}
			}
		}
		if (tireBalle == 1) {
			// calcul de la position de la balle qui se déplace selon un angle en x,y
			posBalle.x = posBalle.x - INC_DEP_BALLE * cos(M_PI / 180.0 * (angleBalle + 90));
			posBalle.y = posBalle.y - INC_DEP_BALLE * sin(M_PI / 180.0 * (angleBalle + 90));
			printf("%.2lf %.2lf\n", posBalle.x, posBalle.y);
// si la balle disparait de l'écran on replace la position de la balle pour un prochain tir (reset tireBalle)
			if (posBalle.x < -100 || posBalle.y < -100 || posBalle.x > L_WIN+10 || posBalle.y > H_WIN +10) {
				tireBalle = 0;
				posBalle = posImage;
			}
		}	
//mise à jour des positions des 3 objets
		sfRectangleShape_setPosition(rect, posRect);
		sfSprite_setPosition(sprite, posImage);
		sfCircleShape_setPosition(balle, posBalle);
//préparation des éléments graphique à afficher
		sfRenderWindow_clear(window, sfWhite);
		sfRenderWindow_drawRectangleShape(window, rect, NULL);
		sfRenderWindow_drawCircleShape(window, balle, NULL);
		sfRenderWindow_drawSprite(window, sprite, NULL);
//switch buffer video (affichage de la nouvelle image)
		sfRenderWindow_display(window);
		sfSleep((sfTime) { 20000 });
	}
	sfRectangleShape_destroy(rect);
	sfSprite_destroy(sprite);
	sfCircleShape_destroy(balle);
	sfRenderWindow_destroy(window);
	return EXIT_SUCCESS;
}

