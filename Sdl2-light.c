/**
*\file Sdl2-light.c
*\brief gère la sdl et l'affichage de text
*\authors Reen MARTINI , Anna Beranger
*\date 05/11/2020
*/

#include "Sdl2-light.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include "World.h"


/**
 * \brief La fonction initialise la SDL.
 * Elle crée la fenêtre du jeu ainsi que le renderer
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param width largeur de l'écran de jeu
 * \param height hauteur de l'écran de jeu
 * \return -1 en cas d'erreur, 0 sinon
 */
int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)){
        fprintf(stderr, "Erreur initialisation de la SDL : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer)){
        fprintf(stderr, "Erreur lors de la creation de l'image et du renderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}
/**
 * \brief initialisation de la ttf
 */
void init_ttf(){
    if(TTF_Init() < 0){
        TTF_GetError();
    }
}

/**
 * \brief l'écriture sur l'écran
 * \param  const char* fileName le nom du fichier et la taille de la police 
*/
TTF_Font* apply_font(const char* fileName, int size){
    //charger la police 
    TTF_Font *font = TTF_OpenFont(fileName, size);
    if(font == NULL){
        printf("Erreur chargement font: %s\n", SDL_GetError());
    }
    return font;
}
/*
 * \brief appliquer la couleur et la texture du text
 * \param SDL_Renderer pour le rendu de du text 
 * \param int r, g , b  pour la couleur de l'écriture
 * \param const char* text pour le texte à afficher
 * \param TTF_font* font pour la police du text
 * \param int x,y,w,h pour la position et la taille de l'encadré du text.
 */
void apply_text(SDL_Renderer *renderer, int r, int g, int b , const char* text, TTF_Font* font, int x, int y, int w, int h){
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    //gérer la couleur
    SDL_Color color = { r,g,b,255 };
    surface = TTF_RenderText_Solid(font, text, color);

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect2 = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
    SDL_DestroyTexture(texture);
    texture = NULL;
    SDL_FreeSurface(surface);
    surface = NULL;
}
/**
 * \brief La fonction charge une image  et renvoie la texture correspondante
 * \param path est le chemin du fichier image. Le fichier doit être obligatoirement du BMP.
 * \param renderer le renderer
 * \return la surface SDL contenant l'image. Elle renvoie NULL si le chargement a échoué
 * (ex. le fichier path n'existe pas)
*/

SDL_Texture* load_image(const char* nomfichier, SDL_Renderer* renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(nomfichier);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur pendant chargement image BMP: %s", SDL_GetError());
        return NULL;
    }
    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 255, 0, 255));
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    tmp = NULL;
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur pendant creation de la texture liee a l'image chargee: %s", SDL_GetError());
        return NULL;
    }
    if(tmp != NULL)
    {
        fprintf(stderr, "Erreur freesurface: %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

/**
 * \brief La fonction permet d'appliquer une texture sur le renderer à une position donnée. La hauteur et la largeur est la même que celle de la texture.
 * \param texture  la texture que l'on va appliquer
 * \param renderer le renderer qui va recevoir la texture
 * \param x l'abscisse sur le renderer de l'endroit où est appliquée texture (point en haut à gauche de la surface)
 * \param y l'ordonnée sur le renderer de l'endroit où est appliquée texture (point en haut à gauche de la surface)
*/

void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y){
    SDL_Rect dst = {0, 0, 0, 0};
    
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    dst.x = x; dst.y=y;
    
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    
}


/**
 * \brief La fonction nettoie une texture en mémoire
 * \param texture la texture à nettoyer
*/

void clean_texture(SDL_Texture *texture){
    if(NULL != texture){
        SDL_DestroyTexture(texture);
    }
}

/**
 * \brief La fonction ferme la police et quitte la ttf
 * \param la police à fermer
*/

void clean_font(TTF_Font *font){
    if(font != NULL){
        TTF_CloseFont(font);
    }
    TTF_Quit();
}
/**
 * \brief La fonction vide le contenu graphique du renderer lié à l'écran de jeu
 * \param renderer le renderer de l'écran
*/

void clear_renderer(SDL_Renderer *renderer){
    SDL_RenderClear(renderer);
}


/**
 * \brief La fonction met à jour l'écran avec le contenu du renderer
 * \param renderer le renderer de l'écran
*/

void update_screen(SDL_Renderer *renderer){
    SDL_RenderPresent(renderer);
}


/**
 * \brief La fonction nettoie le renderer et la fenêtre du jeu en mémoire
 * \param renderer le renderer à nettoyer
 * \param window la fenêtre à nettoyer
*/

void clean_sdl(SDL_Renderer *renderer,SDL_Window *window){
    if(NULL != renderer){
        SDL_DestroyRenderer(renderer);
    }
    if(NULL != window){
        SDL_DestroyWindow(window);
    }
    
    SDL_Quit();    
}
