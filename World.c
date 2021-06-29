/**
 * \file World.c
 * \brief monde du jeu
 * \author Anna Béranger, Reen Martini
 * \date 5 novembre 2020
 */

#include "World.h"


/**
 * \brief initialise un univers de jeu
 * \param w un monde
 */
void init_data(world_t* w){
    //allocation de la mémoire pour les platformes
    for(int nb = 0; nb < NB_PLATFORMS; nb++){
        w->platform[nb] = malloc(sizeof(platform_t));
    }
    w->state = 0; //au début l'écran est un menu 
    w->power_mode = 0; //pouvoir du joueur
    w->score = 0; //le score est initialisé à 0 
    w->jump_time=0; // le temps du saut 
    w->power_time = 0; //le temps du pouvoir
    //initialisation des platformes
    init_platforms(w->platform, NB_PLATFORMS); 
    //initialisation du player
    init_player(&w->player, SCREEN_WIDTH/2 - PLAYER_WIDTH/2 ,w->platform[NB_PLATFORMS/2]->y - PLAYER_HEIGHT - PLATFORM_HEIGHT  , PLAYER_HEIGHT, PLAYER_WIDTH, 0, 0 , 0, 0, 4, 0, 0);
}

/**
 * \brief fonction qui dit si le joueur est sur la plateforme
 * \param w un monde
 * \return 1 si le joueur est sur une platforme. 0 sinon 
 */
int is_on_platform(world_t* w){
  //tester yBas du joueur avec yHaut de la platform
    for(int nb = 0; nb < NB_PLATFORMS; nb++){
        if( w->player.y - PLAYER_HEIGHT== w->platform[nb]->y +PLATFORM_HEIGHT){
            return 1;
        }
    }
    return 0;
}

/**
* \brief fonction pour positionner le jouuer sur une platform
* \param world_t* w un monde de jeu.
*/
void collision_player_platform(world_t* w){
    int on_platform = 0;
    for(int nb = 0; nb < NB_PLATFORMS; nb++){
        /*y dessus plateforme: platform->y - platform->h
        x dessus plateforme: entre platform->x et platform->x + platform->w
        x coin en bas à droite du player: player->x + player->width
        si le joueur est sur une plateforme
        player.y + player.h - (platform.y - platform.h) >= 0
        player.y = platform.y - platform.h - player.h*/
        if (w->player.y +w->player.height - w->platform[nb]->y  >=0 && 
            w->player.y +w->player.height - w->platform[nb]->y <=1 &&
            w->player.x + 0.5*w->player.width > w->platform[nb]->x  && w->player.x + 0.5*w->player.width < w->platform[nb]->x + w->platform[nb]->w
            ){ 
                w->player.is_on = 1;
                w->player.y = w->platform[nb]->y+ w->platform[nb]->v - w->player.height;
                on_platform = 1;
            }
    }
    if(on_platform == 0)
        w->player.is_on = 0;
}
/**
* \brief fonction qui gère la collision entre le joueur et les créatures super 
* \param world_t* w un monde de jeu.
*/
void handle_collision(world_t* w){
    for(int nb = 0; nb < NB_PLATFORMS; nb++){
        
        //collision avec les super_t (monster/diamond)
        /*  x milieu player   =   w->player.x + (w->player.width/2) 
            y milieu payer = w->player.y + (w->player.height)/2)
            x milieu super = w->platform[nb]->super.x + (w->platform[nb]->super.w)/2)
            y milieu super = w->platform[nb]->super.y + (w->platform[nb]->super.h)/2 )
            distance entre 2 points = (x2 - x1)² + (y2 - y1)²*/
        if(w->platform[nb]->super.type != 0 &&
            w->player.width/2 + w->platform[nb]->super.w/2 >
            sqrt(((w->player.x + (w->player.width)/2) - (w->platform[nb]->super.x + (w->platform[nb]->super.w)/2)) *
            ((w->player.x + (w->player.width)/2) - (w->platform[nb]->super.x + (w->platform[nb]->super.w)/2)) +
            ((w->player.y + (w->player.height)/2) - (w->platform[nb]->super.y + (w->platform[nb]->super.h)/2)) *
            ((w->player.y + (w->player.height)/2) - (w->platform[nb]->super.y + (w->platform[nb]->super.h)/2)))){
            
            
            //collision avec les diamants
            if(w->platform[nb]->super.type == 2){
                //ajout d'un diamant
                w->player.diamonds += w->player.diamonds;
                //on retire le diamant de la plateforme
                w->platform[nb]->super.type = 0;
                w->platform[nb]->super.x = -100;
                w->platform[nb]->super.y = -100;
                w->platform[nb]->super.h = 0;
                w->platform[nb]->super.w = 0;
                w->player.collided_with_super = 2; //ajoute au score
            }
            //collision avec un monstre
            if(w->platform[nb]->super.type == 1 || w->platform[nb]->super.type == 3){
                //si arrive du dessous joueur perd une vie, si le joueur atteri sur le monstre, monster dead
                if(w->player.y < w->platform[nb]->super.y - w->platform[nb]->super.h + 1 && 
                    w->player.is_jumping == 0){
                    //on retire le monstre
                    w->platform[nb]->super.type = 0;
                    w->platform[nb]->super.x = -100;
                    w->platform[nb]->super.y = -100;
                    w->platform[nb]->super.h = 0;
                    w->platform[nb]->super.w = 0;
                    w->player.collided_with_super = 3; //ajoute au score
                    w->state = 1; 
                    w->player.is_on = 2;
                    //le joueur saute 
                    jump(&w->player); 
                }else if(w->player.power != 2) {
                    //si le joueur arrive de côté ou par dessous il meurt sauf si mode warrior
                    w->player.lives -= 1; //on enlève une vie
                    w->platform[nb]->super.type = 0;
                    w->player.collided_with_super = 1;
                    if(w->player.lives == 0)
                        w->state = 3;
                } 
            }
            //collision avec pouvoir rich
            if(w->platform[nb]->super.type == 4){
                //on retire le pouvoir de la plateforme
                w->platform[nb]->super.type = 0;
                w->platform[nb]->super.x = -100;
                w->platform[nb]->super.y = -100;
                w->platform[nb]->super.h = 0;
                w->platform[nb]->super.w = 0;
                //le pouvoir est enclenché dans le monde du jeu
                w->power_mode = 1;
            }
            //collision avec pouvoir warrior
            if(w->platform[nb]->super.type == 5){
                //on retire le pouvoir de la plateforme
                w->platform[nb]->super.type = 0;
                w->platform[nb]->super.x = -100;
                w->platform[nb]->super.y = -100;
                w->platform[nb]->super.h = 0;
                w->platform[nb]->super.w = 0;
                //le pouvoir est enclenché dans le monde du jeu
                w->power_mode = 2;
            }
        }
        //si le pouvoir rich a été enclenché
        if(w->player.power == 1 && w->platform[nb]->super.type == 2){
            //ajout de tous les diamants présents sur l'écran
            w->player.diamonds += w->player.diamonds;
            //on retire le diamant des plateformes
            w->platform[nb]->super.type = 0;
            w->platform[nb]->super.x = -100;
            w->platform[nb]->super.y = -100;
            w->platform[nb]->super.h = 0;
            w->platform[nb]->super.w = 0;
            w->player.collided_with_super = 2; //ajoute au score
        }
    }
}

/**
 * \brief fonction qui met à jour l'état du jeu
 * \param w un monde
 */
void update_data(world_t* w){
    //mise à jour des plateformes et du joueur
    update_platforms(w->platform, NB_PLATFORMS, &w->player);
    update_player(&w->player);
    // gérer les événements temporaires
    w->chrono = SDL_GetTicks() ;

    w->secondes = (w->chrono -60000*w->minutes)/1000;
    if ( w->secondes ==60){
        w->minutes +=1; 
        w->secondes = 0;
    }
    //printf(" %i mins %i sec\n", w->minutes, w->secondes);
    if(w->player.is_jumping == 1){
            w->jump_time = w->chrono ; //initialisation du temps du début du saut
            w->player.is_jumping = 2;
        }
        if(w->chrono > w->jump_time + 500  && w->player.is_jumping == 2){
            w->player.is_jumping = 0; //fin du saut après 0.5 seconde
        }
        if(w->power_mode == 1 || w->power_mode == 2){
            w->power_time = w->chrono; //temps où le pouvoir est enclenché
            if(w->power_mode == 1)
                w->player.power = 1;
            if(w->power_mode == 2)
                w->player.power = 2;
            w->power_mode = 3;
        }
        if(w->chrono > w->power_time + 15000 && w->power_mode != 0){
            w->player.power = 0;
            w->power_mode = 0;
        }
    //mise à jour du score
    add_score(w);
    // si on tombe le jeu se termine
    fell(w);
    //si on gagne
    win(w);
}

/**
 * \brief fonction qui nettoie les données du monde
 * \param w un monde
 */
void clean_data(world_t* w){
    for(int nb = 0; nb < NB_PLATFORMS; nb++){
        free(w->platform[nb]);
    }

}

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event* event, world_t *world){
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    world->gameover = 0;

    if( keystates[SDL_SCANCODE_RETURN]){
        world->state = 1;
        world->chrono = 0;
        world->minutes = 0;
        world->secondes = 0;
    }
    if(keystates[SDL_SCANCODE_ESCAPE] ){
        world->gameover = 1; 
    }
    if(keystates[SDL_SCANCODE_LEFT]) {
        move_left(&world->player);
    }
    if(keystates[SDL_SCANCODE_RIGHT]){
        move_right(&world->player);
    }
    handle_collision(world);
    collision_player_platform(world);
    handle_jump(event, world);

    SDL_PumpEvents();
}

/**
 * \brief La fonction gère les évènements ayant eu lieu en rapport avec le saut du joueur et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_jump(SDL_Event *event,world_t *world){
     if(world->player.is_jumping == 2){
         jump(&world->player);

     }
     while(SDL_PollEvent( event )) {    
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
         //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est echap on quitte
            if(event->key.keysym.sym == SDLK_SPACE){
                   jump(&world->player);
            }        
        }
    }  
}
/**
 * \brief La fonction gère l'état du jeu si le joueur tombe
 * \param world les données du monde
 */
void fell(world_t *world){
    //si la tête du joueur sort de l'écran
    if(world->player.y >= SCREEN_HEIGHT){
        world->state =3;
    }
}
/**
 * \brief La fonction gère l'état du jeu 
 * \param world les données du monde
 */
int is_gameover(world_t* world){
    int gameover = world->gameover;//par défaut le jeu n'est pas fini
    // c'est la fin du jeu.
    if( world->state ==3 || world->minutes == 2){ 
         gameover = 1;
    }  
    return gameover;
}
/**
 * \brief La fonction gère le score du joueur
 * \param world les données du monde
 */
void add_score(world_t* world){
    if( world->player.collided_with_super == 2){
        world->score += 1; // les diamants rajoute 1 point au score 
        world->player.collided_with_super = 0;
    }else if(world->player.collided_with_super == 3){
        world->score+=5;
        world->player.collided_with_super = 0; //tuer un monstre fait gagner 5 points en score. 
    }
}
/**
 * \brief La fonction gère l'état du jeu si le joueur gagne
 * \param world les données du monde
 */
void win(world_t* world){
    if(world->score >= 100 && world->minutes < 2){
        world->state = 2; //gagner
    }
}



