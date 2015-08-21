#pragma once


class Enemy
{
public:
	Enemy(void);
	~Enemy(void);

	enum GEOMETRY_TYPE
	{
		GEO_TILEENEMY_FRAME0,
		GEO_TILEENEMY_FRAME1,
		GEO_TILEENEMY_FRAME2,
		GEO_TILEENEMY_FRAME3,
		NUM_GEOMETRY,
	};

	
	// Set position x of the player
	void SetPos(int pos_x, int pos_y);
	// Set the destination of this enemy
	void SetDestination(const int pos_x, const int pos_y);

	// Get position x of the player
	int GetPos_x(void);
	// Get position y of the player
	int GetPos_y(void);
	// Set the destination of this enemy
	int GetDestination_x(void);
	// Set the destination of this enemy
	int GetDestination_y(void);



	//// Set Animation Invert status of the player
	//void SetAnimationInvert(bool ENEMYAnimationInvert);
	//// Get Animation Invert status of the player
	//bool GetAnimationInvert(void);
	//// Set Animation Counter of the player
	//void SetAnimationCounter(int ENEMYAnimationCounter);
	//// Get Animation Counter of the player
	//int GetAnimationCounter(void);

	void KILL(int D_x, int D_y);

	int CalculateDistance();

	int CalculateDistance_x();

	int CalculateDistance_y();


private:
	// ENEMY's information
	int theEnemyPosition_x;
	int theEnemyPosition_y;

	/*bool enemyAnimationInvert;
	int enemyAnimationCounter;*/

	// The Destination is the position of the Hero
	int theDestination_x;
	int theDestination_y;

};
