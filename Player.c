/**
*\file Player.h
*\brief Header des joueurs
*\author Reen MARTINI , Anna Beranger
*\date 05/11/2020
*/
#include "Player.h"



/*
 * \brief initialise un joueur
 * \param un joueur
 */
void init_player(player_t *player, double pos_x, double pos_y,int height, int width,  int speed, int is_on, int is_jumping, int diamonds, int lives , int collided_with_super, int power){
	//initialisation des paramètres.
	player->x = pos_x; /*!< abscisse*/
	player->y =  pos_y; /*!< ordonnée*/
	player->height =  height; /*!< hauteur*/
	player->width = width; /*!< largeur*/
	player->speed = speed;/*!< vitesse horizontale*/
	player->is_on = is_on;
	player->is_jumping = is_jumping; // par défaut il saute pas.*
	player->diamonds = diamonds;
    player->lives = lives;
    player->collided_with_super = collided_with_super;
    player->power = power;
	

}

/*
 * \brief Le joueur se déplace vers la droite
 * \param un joueur
 */
void move_right(player_t* player){
	if(player->x>SCREEN_WIDTH- PLAYER_WIDTH	){
		player->x =0;
	}
	else{
		player->x += PLAYER_STEP;
	}
}
/*
 * \brief Le joueur se déplace vers la gauche
 * \param un joueur
 */
void move_left(player_t* player){
	if(player->x<0){
		player->x = SCREEN_WIDTH -PLAYER_WIDTH;
	}
	else{
		player->x -= PLAYER_STEP;
	}
}

/**
 * \brief Fonction qui gère le saut du joueur 
 * \param player un joueur
 */
void jump(player_t* player){
	if (player->y  <= 0 ){ //s'il est en haut de l'écran
		player->y = 1;
	}
	
	player->y -= 1.2*PLAYER_STEP - 2*PLAYER_STEP*PLAYER_SPEED;
    if(player->is_jumping != 2 && player->is_on != 0){
        player->is_jumping = 1;
    }
	
}

/*
 * \brief mise à jour du placement du joueur, par défaut il tombe vers le bas
 * \param un joueur
 */
void update_player(player_t* player){
	// initialiser len joueur
	//s'il n'est pas sur une platforme, il est en chute libre
	if(player->is_on != 1){
		init_player(player, player->x, player->y + 4*PLAYER_SPEED , player->height, player->width, player->speed, player->is_on, player->is_jumping, player->diamonds, player->lives, player->collided_with_super, player->power);

	}
	//sinon il prend la position de la platform. 
	else{
	 	init_player(player, player->x, player->y, player->height, player->width, player->speed, player->is_on, player->is_jumping, player->diamonds, player->lives, player->collided_with_super, player->power);
	}
	

}








