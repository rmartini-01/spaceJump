/**
*\file Player.h
*\brief Header des joueurs
*\author Reen MARTINI , Anna Beranger
*\date 05/11/2020
*/



#ifndef PLAYER_H
#define PLAYER_H

#include "Sdl2-light.h"
//#include "Textures.h"
#include <stdlib.h>
#include <stdio.h>


/**
 *\brief vitesse du joueur
 */
#define PLAYER_SPEED 0.1
#define PLAYER_STEP 1
#define PLAYER_HEIGHT 68
#define PLAYER_WIDTH 54
/**
 * \brief Largeur de l'écran
 */
#define SCREEN_WIDTH 700
/**
 * \brief Hauteur de l'écran
 */
#define SCREEN_HEIGHT 650 

/**
 * \brief Structure du joueur
 */
struct player {
	double x; /*!< abscisse*/
	double y; /*!< ordonnée*/
	int height; /*!< hauteur*/
	int width; /*!< largeur*/
	int speed;/*!< vitesse horizontale*/
    int is_on; /*!< 1 si le joueur est sur une plateforme, 2 si le joueur est sur un monstre*/
	int is_jumping;  /*!< 0 il saute pas , 1 saut déclenché, 2 ascension en cours */
	int diamonds; /*!< nombre de diamants attrapés */
    int lives; /*!< nombre de vies restantes */
	int collided_with_super; /*!< 1 si le joueur est en collision avec un monstre et il perd une vie s'il en a, sinon il meurt. 2 s'il le tue et gagne en score*/
	int power; /*!< 0: pas de pouvoir, 1: attire les diamants, 2: invincible*/
};
typedef struct player player_t;
/*Déclaration des fonctions*/

/**
 * \brief initialise un joueur
 * \param le joueur
 * \param x position x 
 * \param y position y
 * \param h hauteur 
 * \param w largeur
 * \param speed vitesse 
 * \param is_on_platform détécte la collision player-platform
 * \param is_jumping état du saut du joueur
 * \param diamonds nb de diamants attrapés
 * \param lives nb de vies du player
 * \param collided_with_super détécte la collision player-collision
 */ 

void init_player(player_t *player , double pos_x, double pos_y, int height, int width, int speed, int is_on_platform, int is_jumping, int diamonds, int lives , int collided_with_super, int power);


/**
 * \brief Le joueur se déplace vers la droite
 * \param player un joueur
 */

void move_right(player_t *player);

/**
 * \brief Le joueur se déplace vers la gauche
 * \param player un joueur
 */

void move_left(player_t *player); 

/**
 * \brief Fonction qui gère le saut du joueur 
 * \param player un joueur
 */
void jump(player_t* player);

/**
 * \brief mise à jour du placement du joueur, par défaut il tombe vers le bas
 * \param player un joueur
 */

void update_player(player_t* player);






#endif
