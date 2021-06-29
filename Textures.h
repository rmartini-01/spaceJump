/**
 * \file Textures.h
 * \brief header des plateformes
 * \author Anna Béranger, Reen Martini
 * \date 5 novembre 2020
 */

#ifndef TEXTURES_H
#define TEXTURES_H

#include "Sdl2-light.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "Platforms.h"
#include "Player.h"


/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    //SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    
    SDL_Texture* background_menu; /*!< Texture liée à l'image du fond de l'écran. */
    
    SDL_Texture* background_game; /*!< Texture liée à l'image du fond de l'écran. */
    
    SDL_Texture* background_rich; /*!< Texture liée à l'image du fond de l'écran. */
    
    SDL_Texture* background_warrior; /*!< Texture liée à l'image du fond de l'écran. */
    
    SDL_Texture* platform; /*!< Texture liée à l'image des plateformes. */
    
    SDL_Texture* player; /*!< Texture liée à l'image du joueur */
    
    SDL_Texture* player_rich; /*!< Texture liée à l'image du joueur */
    
    SDL_Texture* player_warrior; /*!< Texture liée à l'image du joueur */
    
    SDL_Texture* diamond; /*!< Texture liée à l'image des diamants */
    
    SDL_Texture* monster; /*!< Texture liée à l'image des monstres */
    
    SDL_Texture* walking_monster; /*!< Texture liée à l'image des monstres */
    
    SDL_Texture* super_rich; /*!< Texture liée à l'image du pouvoir diamant */
    
    SDL_Texture* super_warrior; /*!< Texture liée à l'image du pouvoir invincible */

    SDL_Texture* lives; /*!< Texture liée aux vies du joueur */

    TTF_Font *font; /*!< Texture liée à la police du texte affiché à l'écran */
    //TTF_Font *rules; /*!< Texture liée aux consignes du jeu*/

};


/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures);

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void init_textures(SDL_Renderer *renderer, textures_t *textures);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
 * \param state état du jeu
 * \param mode mode pouvoir
*/

void apply_background(SDL_Renderer *renderer, textures_t *textures, int state, int mode);

/**
 * \brief La fonction applique la texture des vies
 * \param renderer le renderer
 * \param textures les textures du jeu
*/

void apply_lives(SDL_Renderer *renderer, textures_t *textures);

/**
 * \brief La fonction applique la texture du joueur sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
 * \param player les informations du joueur
*/

void apply_player(SDL_Renderer *renderer, SDL_Texture* texture, player_t *player);

/**
 * \brief La fonction applique la texture des plateformes sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
 * \param platform les informations des plateformes
*/

void apply_platform(SDL_Renderer *renderer, SDL_Texture* texture, platform_t* platform);

/**
 * \brief La fonction applique la texture des monstres et diamants aux bonnes coordonnées sur l'écran de jeu
 * \param renderer le renderer
 * \param texture les différentes textures 
 * \param super les informations du monstre ou du diamant
 */
void apply_super(SDL_Renderer *renderer, SDL_Texture* texture, super_t* super);

#endif

