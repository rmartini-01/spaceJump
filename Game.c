/**
*\file Player.h
*\brief Header des joueurs
*\author Reen MARTINI , Anna Beranger
*\date 05/11/2020
*/

#include "World.h"
#include "Player.h"
#include "Textures.h"
#include "Platforms.h"
#include "Sdl2-light.h"


/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t *world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */
void init(SDL_Window **window, SDL_Renderer **renderer, textures_t *textures, world_t * world){
    init_sdl(window, renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_ttf();
    init_data(world);
    init_textures(*renderer,textures);  
}

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){ 
    /*on crée une chaine de caractères pour l'affichage du score à l'écran*/
    char message[200] = "";
    //on vide le renderer
    clear_renderer(renderer);
    apply_background(renderer, textures, world->state, world->player.power);
    
    //écran d'accueil
    if(world->state == 0){
        
        sprintf(message , "SKY JUMPER");
        apply_text(renderer, 195, 203, 219, message , textures->font, SCREEN_WIDTH/4 + SCREEN_WIDTH/8 +15, SCREEN_HEIGHT/3 +30 , 150, 70);

        sprintf(message, "Press ENTER to play ");
        if(textures->font != 0){
            apply_text(renderer, 195, 203, 219, message , textures->font, SCREEN_WIDTH/4 +2 , SCREEN_HEIGHT -200 , 350, 80);
        }
        sprintf(message , "Score 200 in 2 minutes to win !");
        apply_text(renderer, 195, 203, 219, message , textures->font, SCREEN_WIDTH/4 -10, SCREEN_HEIGHT -300 , 370, 70);

    }else{
        
    //application des textures dans le renderer
    if(world->player.power == 0)
        apply_player(renderer, textures->player, &world->player);
    if(world->player.power == 1)
        apply_player(renderer, textures->player_rich, &world->player);
    if(world->player.power == 2)
        apply_player(renderer, textures->player_warrior, &world->player);

    //application des textures des objets super  
    for(int nb = 0; nb < NB_PLATFORMS; nb++){
        apply_platform(renderer, textures->platform, world->platform[nb]);
        if(world->platform[nb]->super.type != 0){
            if(world->platform[nb]->super.type == 1)
                apply_super(renderer, textures->monster, &world->platform[nb]->super);
            if(world->platform[nb]->super.type == 2)
                apply_super(renderer, textures->diamond, &world->platform[nb]->super);
            if(world->platform[nb]->super.type == 3)
                apply_super(renderer, textures->walking_monster, &world->platform[nb]->super);
            if(world->platform[nb]->super.type == 4)
                apply_super(renderer, textures->super_rich, &world->platform[nb]->super);
            if(world->platform[nb]->super.type == 5)
                apply_super(renderer, textures->super_warrior, &world->platform[nb]->super);
        }
    }
    
    //le jeu
    if(world->state == 1){
        
        //affichage score
        sprintf(message , "SCORE = %i ", world->score);
        apply_text(renderer, 195, 203, 219, message, textures->font, 10, 10, 120, 40);
        //affichage vies
        apply_lives(renderer, textures);
        sprintf(message, " %i",  world->player.lives);
        apply_text(renderer, 195, 203, 219, message, textures->font, 60 , 60, 20, 40);
        //affichage chrono
        sprintf(message, "%i min %is " , world->minutes, world->secondes);
        apply_text(renderer, 195, 203, 219, message, textures->font, SCREEN_WIDTH-110 , 10, 100, 40);

    }else if (world->state ==2){ //fin
        //gagné
        apply_background(renderer, textures, world->state, world->player.power);
        sprintf(message , "Congratulations! ");
        apply_text(renderer, 195, 203, 219, message , textures->font, SCREEN_WIDTH/3- 30, SCREEN_HEIGHT/3+ SCREEN_HEIGHT/4.5 , 300, 70);
        sprintf(message , " You made it to %i!", world->score);
        apply_text(renderer, 195, 203, 219, message , textures->font, SCREEN_WIDTH/3 +15, SCREEN_HEIGHT/3 +SCREEN_HEIGHT/3 , 200, 70);
    }else if (is_gameover(world)==1){
        //perdu
        apply_background(renderer, textures, world->state, world->player.power);
        sprintf(message , "Better luck next time :(");
        apply_text(renderer, 195, 203, 219, message , textures->font, SCREEN_WIDTH/3- 30, SCREEN_HEIGHT/3+ SCREEN_HEIGHT/4.5 , 300, 70);
        sprintf(message , " Your score is %i", world->score);
        apply_text(renderer, 195, 203, 219, message , textures->font, SCREEN_WIDTH/3 +15, SCREEN_HEIGHT/3 +SCREEN_HEIGHT/3 , 200, 70);
        }
    } 
    update_screen(renderer);
    //à la fin afficher le résultat pendant 3 secondes
    if(is_gameover(world)==1){
        SDL_Delay(3000);
    }
}

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main(){

    SDL_Event event; // déclaration des évenements
    world_t world;
    textures_t textures; 
    SDL_Renderer *screen; 
    SDL_Window *window;
    world.gameover = 0;

    //mise en place du jeu (l'écran, le monde de jeu et les textures. )
    init(&window,&screen, &textures, &world);
    //Boucle principale du programme
    while(is_gameover(&world)==0){      
        //réalisation des événements
        handle_events(&event, &world);
        //mise à jour des données du jeu 
        update_data(&world);     
        //mise à jour de l'affichage 
        refresh_graphics(screen, &world, &textures);
    }

    // Nettoyer et quitter SDL
    clean(window, screen, &textures, &world);
    return 0;
}
