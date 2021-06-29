/**
 * \file Textures.c
 * \brief Textures
 * \author Anna Béranger, Reen Martini
 * \date 5 novembre 2020
 */

#include "Textures.h"

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures){
    if(textures->background_menu != NULL){
        clean_texture(textures->background_menu);
        textures->background_menu = NULL;
    }
    if(textures->background_game != NULL){
        clean_texture(textures->background_game);
        textures->background_game = NULL;
    }
    if(textures->background_rich != NULL){
        clean_texture(textures->background_rich);
        textures->background_rich = NULL;
    }
    if(textures->background_warrior != NULL){
        clean_texture(textures->background_warrior);
        textures->background_warrior = NULL;
    }
    if(textures->player != NULL){
        clean_texture(textures->player);
        textures->player = NULL;
    }
    if(textures->player_rich != NULL){
        clean_texture(textures->player_rich);
        textures->player_rich = NULL;
    }
    if(textures->player_warrior != NULL){
        clean_texture(textures->player_warrior);
        textures->player_warrior = NULL;
    }
    if(textures->platform != NULL){
        clean_texture(textures->platform);
        textures->platform = NULL;
    }
    if(textures->monster != NULL){
        clean_texture(textures->monster);
        textures->monster = NULL;
    }
    if(textures->walking_monster != NULL){
        clean_texture(textures->walking_monster);
        textures->walking_monster = NULL;
    }
    if(textures->super_rich != NULL){
        clean_texture(textures->super_rich);
        textures->super_rich = NULL;
    }
    if(textures->super_warrior != NULL){
        clean_texture(textures->super_warrior);
        textures->super_warrior = NULL;
    }
    if(textures->diamond != NULL){
        clean_texture(textures->diamond);
        textures->diamond = NULL;
    }
    if(textures->lives != NULL){
        clean_texture(textures->lives);
        textures->lives = NULL;
    }
    if(textures->font != NULL){
        clean_font(textures->font);
        textures->font = NULL;
    }
}

/**
 * \brief La fonction initialise les textures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background_menu = load_image( "ressources/background_menu.bmp",renderer);
    textures->background_game = load_image( "ressources/background_game.bmp",renderer);
    textures->background_rich = load_image( "ressources/background_rich.bmp",renderer);
    textures->background_warrior = load_image( "ressources/background_warrior.bmp",renderer);
    textures->player = load_image( "ressources/player.bmp",renderer);
    textures->player_rich = load_image( "ressources/player_rich.bmp",renderer);
    textures->player_warrior = load_image( "ressources/player_warrior.bmp",renderer);
    textures->platform = load_image( "ressources/platform.bmp", renderer);
    textures->monster = load_image( "ressources/flying_monster.bmp", renderer);
    textures->super_warrior = load_image( "ressources/super_warrior.bmp", renderer);
    textures->walking_monster = load_image( "ressources/walking_monster.bmp", renderer);
    textures->super_rich = load_image( "ressources/super_rich.bmp", renderer);
    textures->diamond = load_image( "ressources/diamond.bmp", renderer);
    textures->lives = load_image( "ressources/life.bmp", renderer);
    textures->font = apply_font("ressources/ka1.ttf", 30);
}

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
 * \param state état du jeu
 * \param mode mode pouvoir
*/
void apply_background(SDL_Renderer *renderer, textures_t *textures, int state, int mode){
        if(state == 1 ){
            if(mode == 0 ){
              apply_texture(textures->background_game, renderer, 0, 0);
            } else if(mode == 1 ){
              apply_texture(textures->background_rich, renderer, 0, 0);
            } else if(mode == 2 ){
              apply_texture(textures->background_warrior, renderer, 0, 0);
            }
        }else{
            apply_texture(textures->background_menu, renderer, 0, 0);
        }
}

/**
 * \brief La fonction applique la texture des vies
 * \param renderer le renderer
 * \param textures les textures du jeu
*/
void apply_lives(SDL_Renderer *renderer, textures_t *textures){
    apply_texture(textures->lives, renderer, 20, 70);
}

/**
 * \brief La fonction applique la texture du joueur aux bonnes coordonnées sur l'écran de jeu
 * \param renderer le renderer
 * \param texture les différentes textures 
 * \param player les informations du joueur
 */
void apply_player(SDL_Renderer *renderer, SDL_Texture* texture, player_t* player){
    apply_texture(texture, renderer, player->x, player->y);
}

/**
 * \brief La fonction applique la texture des plateformes aux bonnes coordonnées sur l'écran de jeu
 * \param renderer le renderer
 * \param texture les différentes textures 
 * \param platform les informations des plateformes
 */
void apply_platform(SDL_Renderer *renderer, SDL_Texture* texture, platform_t* platform){
    apply_texture(texture, renderer, platform->x, platform->y); 
}

/**
 * \brief La fonction applique la texture des monstres et diamants aux bonnes coordonnées sur l'écran de jeu
 * \param renderer le renderer
 * \param texture les différentes textures 
 * \param super les informations du monstre ou du diamant
 */
void apply_super(SDL_Renderer *renderer, SDL_Texture* texture, super_t* super){
    apply_texture(texture, renderer, super->x, super->y);
}
