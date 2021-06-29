/**
 * \file Platforms.h
 * \brief header des plateformes
 * \author Anna Béranger, Reen Martini
 * \date 5 novembre 2020
 */

#ifndef PLATFORMS_H
#define PLATFORMS_H

#include "Sdl2-light.h"
//#include "Textures.h"
#include <stdlib.h>
#include <stdio.h>
#include "Player.h"

/**
 * \brief Représentation des monstres et diamants
 */
struct super_s{
    float x; /*abscisse du coin en haut à gauche de l'objet */
    float y; /*ordonnée du coin en haut à gauche de l'objet */
    float h; /*Hauteur de l'objet */
    float w; /*Largeur de l'objet */
    float v; /*Vitesse horizontale de l'objet */
    int type; /*Type de l'objet 0: rien 1: monster, 2: diamant, 3: monster sur plateforme, 4: pouvoir rich, 5: pouvoir warrior */
    char direction; /*d: droite (par défaut) g: gauche */
};

/**
 * \brief Type qui correspond aux données des diamants et monstres
 */
typedef struct super_s super_t;

/**
 * \brief Représentation des plateformes
 */
struct platform_s{
    
    float x; /*abscisse du coin en haut à gauche de la plateforme */
    float y; /*ordonnée du coin en haut à gauche de la plateforme */
    float h; /*Hauteur de la plateforme */
    float w; /*Largeur de la plateforme */
    float v; /*Vitesse verticale de la plateforme */
    super_t super; /*monster ou diamond */
};

/**
 * \brief Type qui correspond aux données des plateformes
 */
typedef struct platform_s platform_t;

/**
 * \brief initialise une plateforme en haut de l'écran
 * \param p structure platform_t 
 */

void init_platform(platform_t* p);

/**
 * \brief initialise les plateformes du début du jeu
 *  \param p tableau de platform_t
 * \param nb_p nb de plateformes dans le jeu
 */

void init_platforms(platform_t** p, int nb_p);

/**
 * \brief met à jour les plateformes
 * \param p tableau de platform_t
 * \param nb_p nb de plateformes dans le jeu
 * \param player joueur qui saute sur le plateformes
 */

void update_platforms(platform_t** p, int nb_p, player_t* player);

/**
 * \brief Largeur d'une plateforme
 */
#define PLATFORM_WIDTH 94

/**
 * \brief Hauteur d'une plateforme
 */
#define PLATFORM_HEIGHT 21

/**
 * \brief Vitesse d'une plateforme
 */
#define PLATFORM_SPEED 0.2

/**
 * \brief Vitesse d'un monstre
 */
#define MONSTER_SPEED 0.06

/**
 * \brief Largeur d'un monstre
 */
#define MONSTER_WIDTH 45

/**
 * \brief Hauteur d'un monstre
 */
#define MONSTER_HEIGHT 45

/**
 * \brief Largeur d'un diamant
 */
#define DIAMOND_WIDTH 20

/**
 * \brief Hauteur d'un diamant
 */
#define DIAMOND_HEIGHT 20


#endif
