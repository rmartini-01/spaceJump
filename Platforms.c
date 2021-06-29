/**
 * \file Platforms.c
 * \brief plateformes
 * \author Anna Béranger, Reen Martini
 * \date 5 novembre 2020
 */

#include "Platforms.h"
#include "World.h"

//renvoie un nombre aléatoirement entre a et b: [a,b[
int randint(int a,int b) {
  if(a >= b)
  {
    return a;
  }
  else
  {
    return rand()%(b-a) + a;
  }
}

/**
 * \brief initialise une plateforme en haut de l'écran
 * \param p structure platform_t 
 */

void init_platform(platform_t* p){
    p->x = randint(0, SCREEN_WIDTH - PLATFORM_WIDTH) ;
    p->y = -PLATFORM_HEIGHT ;
    p->h = PLATFORM_HEIGHT ;
    p->w = PLATFORM_WIDTH ;
    p->v = PLATFORM_SPEED ;
    p->super.x = -100 ;
    p->super.y = -100 ;
    p->super.h = 0 ;
    p->super.w = 0 ;
    p->super.v = MONSTER_SPEED ;
    p->super.type = 0 ;
    p->super.direction = 'd' ;
    
    //placement des diamants et monstres aléatoirement
    int random = randint(0, 100) ;
    if(random < 5) {
        p->super.type = 1 ; // 5/100 proba d'apparition d'un monstre qui vole
        p->super.x = p->x + PLATFORM_WIDTH/2 - MONSTER_WIDTH/2 ;
        p->super.y = p->y - MONSTER_HEIGHT - 0.2 * PLATFORM_HEIGHT ;
        p->super.h = MONSTER_HEIGHT ;
        p->super.w = MONSTER_WIDTH ;
    } else if(random > 4 && random < 65) {
        p->super.type = 2 ; // 6/10 proba d'appariton d'n diamant
        p->super.x = p->x + PLATFORM_WIDTH/2 - DIAMOND_WIDTH/2 ;
        p->super.y = p->y - DIAMOND_HEIGHT - 0.2 * PLATFORM_HEIGHT ;
        p->super.h = DIAMOND_HEIGHT ;
        p->super.w = DIAMOND_WIDTH ;
    } else if(random > 64 && random < 75) {
        p->super.type = 3 ; // 1/10 proba d'appariton d'un monstre qui marche
        p->super.x = p->x + PLATFORM_WIDTH/2 - MONSTER_WIDTH/2 ;
        p->super.y = p->y - MONSTER_HEIGHT - 0.2 * PLATFORM_HEIGHT ;
        p->super.h = MONSTER_HEIGHT ;
        p->super.w = MONSTER_WIDTH ;
    } else if(random > 74 && random < 77) {
        p->super.type = 4 ; // 0.2/10 proba d'appariton d'un pouvoir rich
        p->super.x = p->x + PLATFORM_WIDTH/2 - MONSTER_WIDTH/2 ;
        p->super.y = p->y - MONSTER_HEIGHT - 0.2 * PLATFORM_HEIGHT ;
        p->super.h = MONSTER_HEIGHT ;
        p->super.w = MONSTER_WIDTH ;
    }
     else if(random > 76 && random < 79) {
        p->super.type = 5 ; // 0.2/10 proba d'appariton d'un pouvoir warrior
        p->super.x = p->x + PLATFORM_WIDTH/2 - MONSTER_WIDTH/2 ;
        p->super.y = p->y - MONSTER_HEIGHT - 0.2 * PLATFORM_HEIGHT ;
        p->super.h = MONSTER_HEIGHT ;
        p->super.w = MONSTER_WIDTH ;
    }
}

/**
 * \brief initialise les plateformes du début du jeu
 *  \param p tableau de platform_t
 * \param nb_p nb de plateformes dans le jeu
 */

void init_platforms(platform_t** p, int nb_p){
    int distance_entre_p = randint(1*PLATFORM_HEIGHT, 3*PLATFORM_HEIGHT) ;
    for(int i = 0; i < nb_p; i++){
        init_platform(p[i]) ;
        p[i]->y = p[i]->y + distance_entre_p ;
        p[i]->super.y = p[i]->super.y + distance_entre_p ;
        distance_entre_p = distance_entre_p + randint(1*PLATFORM_HEIGHT, 3*PLATFORM_HEIGHT) ;
        p[i]->super.type = 0;
        if(i == nb_p/2){
            p[i]->x = SCREEN_WIDTH/2 - PLATFORM_WIDTH/2;
        }
    }
}

/**
 * \brief met à jour les plateformes
 * \param p tableau de platform_t
 * \param nb_p nb de plateformes dans le jeu
 * \param player joueur qui saute sur les plateformes
 */

void update_platforms(platform_t** p, int nb_p, player_t* player){
    for(int i = 0; i < nb_p; i++){
        int en_mouvement = 0;
        //si le joueur saute sur une plateforme de la partie spérieure de l'écran
        if(player->y < SCREEN_HEIGHT/3){
            p[i]->y = p[i]->y + p[i]->v ;
            en_mouvement = 1;
        }
        //si il y a un monstre ou un diamant, les mettre à jour
        if(p[i]->super.type != 0){
            //si les plateformes sont en mouvement
            if(en_mouvement == 1){
                //les super sont en mouvement
                p[i]->super.y = p[i]->super.y + p[i]->v ;
            }
            //si c'est un monstre gérer son déplacement horizontal
            if(p[i]->super.type == 1){
                    if(p[i]->super.direction == 'd' &&
                        p[i]->super.x + p[i]->super.v + p[i]->super.w <= SCREEN_WIDTH) {
                        //si il va à droite et qu'il peut continuer dans ce sens sans sortir de l'écran
                        p[i]->super.x = p[i]->super.x + p[i]->super.v ;
                    } else if(p[i]->super.direction == 'g' &&
                        p[i]->super.x - p[i]->super.v >= 0) {
                        //si il va à gauche et qu'il peut continuer dans ce sens sans sortir de l'écran
                        p[i]->super.x = p[i]->super.x - p[i]->super.v ;
                    } else if(p[i]->super.direction == 'd'){
                        //arrivé a côté droit
                        p[i]->super.direction = 'g' ;
                    } else if(p[i]->super.direction == 'g'){
                        //arrivé au côté gauche
                        p[i]->super.direction = 'd' ;
                    }
            }
            if(p[i]->super.type == 3){
                    if(p[i]->super.direction == 'd' &&
                        p[i]->super.x + p[i]->super.v + p[i]->super.w < p[i]->x + p[i]->w) {
                        //si il va à droite et pas au bout de la plateforme
                        p[i]->super.x = p[i]->super.x + p[i]->super.v ;
                    } else if(p[i]->super.direction == 'g' &&
                        p[i]->super.x - p[i]->super.v > p[i]->x) {
                        //si il va à gauche et pas au bout de la plateforme
                        p[i]->super.x = p[i]->super.x - p[i]->super.v ;
                    } else if(p[i]->super.direction == 'd'){
                        //arrivé a côté droit
                        p[i]->super.direction = 'g' ;
                    } else if(p[i]->super.direction == 'g'){
                        //arrivé au côté gauche
                        p[i]->super.direction = 'd' ;
                    }
            }
        }
        if(p[i]->y >= PLATFORM_HEIGHT + SCREEN_HEIGHT)
            init_platform(p[i]) ;
    }
}
