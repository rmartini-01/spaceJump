/**
 * \file World.h
 * \brief header du monde
 * \author Anna Béranger, Reen Martini
 * \date 5 novembre 2020
 */

#ifndef WORLD_H
#define WORLD_H

#include "Player.h"
#include "Textures.h"
#include "Platforms.h"
#include "Sdl2-light.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/**
 * \brief Largeur de l'écran
 */
#define SCREEN_WIDTH 700

/**
 * \brief Hauteur de l'écran
 */
#define SCREEN_HEIGHT 650

/**
 * \brief Nombre de plateformes à l'écran
 */
#define NB_PLATFORMS 19


/**
 *\brief Structure de l'univers du jeu
 */
struct world_s {
	player_t player;/*!< un joueur*/ // pas besoin du pointeur
	platform_t* platform[NB_PLATFORMS] ; /*!< des plateformes*/ //pas besoin de pointeur
	int gameover; /*!< variable indiquant l'état du jeu*/
	int score; /*!< score du joueur*/
	/*!< l'état de l'affichage du jeu
	 * 0 : menu 
	 * 1 : le jeu 
	 * 2 : victoire 
	 * 3 : perdu 
	 */
	int state;
    int power_mode; /*!< 0: aucun pouvoir enclenché, 1: pouvoir rich enclenché, 2:pouvoir warrior enclenché*/
    int chrono; /*!< le temps en millisecondes*/
    int before_start; /*!< temps avant de démarrer la partie*/
    int minutes; /*!< les minutes*/
    int secondes; /*!< les secondes*/
    int jump_time; /*!< le temps du saut*/
    int power_time;/*!<le le temps des pouvoirs*/
};
typedef struct world_s world_t;


/*
 * Déclaration des fonctions
 */

/**
 * \brief initialise un univers de jeu
 * \param w un monde
 */
void init_data(world_t* w);


/**
 * \brief fonction qui dit si le joueur est sur la plateforme
 * \param w un monde
 */
int is_on_platform(world_t* w);  //tester yBas du joueur avec yHaut de la platform

/**
 * \brief fonction pour placer le joueur sur la platforme s'ils sont en collision
 * \param w un monde
 */
void collision_player_platform(world_t* w);

/**
* \brief fonction qui gère la collision entre le joueur et les créatures super 
* \param world_t* w un monde de jeu.
*/
void handle_collision(world_t* w);
/**
 * \brief fonction qui met à jour l'état du jeu
 * \param w un monde
 */
void update_data(world_t* w); 

/**
 * \brief fonction qui nettoie les données du monde
 * \param w un monde
 */
void clean_data(world_t* w);

/**
 * \brief fonction qui gère les déplacements du personnage en fonciton du clavier
 * \param world un monde
 * \param event SDL_Event
 */
void handle_events(SDL_Event *event ,world_t *world);

/**
 * \brief La fonction gère les évènements ayant eu lieu en rapport avec le saut du joueur et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_jump(SDL_Event *event,world_t *world);

/**
 * \brief La fonction gère l'état du jeu si le joueur tombe
 * \param world les données du monde
 */
void fell(world_t *world);

/**
 * \brief La fonction gère l'état du jeu 
 * \param world les données du monde
 */
int is_gameover(world_t* world);

/**
 * \brief La fonction gère le score du joueur
 * \param world les données du monde
 */
void add_score(world_t* world);

/**
 * \brief La fonction gère l'état du jeu si le joueur gagne
 * \param world les données du monde
 */
void win(world_t* world);

#endif
