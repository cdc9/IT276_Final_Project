#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__


// for the game state machine
enum gameState
{
	GSTATE_MENU,
	GSTATE_LEVELEDIT,
	GSTATE_LEVEL1,
	GSTATE_LEVEL2,
	GSTATE_GAMEOVER,
	GSTATE_BOSS,
	GSTATE_PLAYEDIT
};

typedef struct game_s
{
	int gameState;
	int levelState;

}game_t;


// for beginning and end of game
void begin();
void end();

// for setting the game state and setup
void setGameState (int gameState, bool setup);
void setLvlState (int levelState);

// for loading levels
void loadLevel(char * level);
#endif