//New Player script that is closer to TRON (header)
#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Object.h"


#include "EventCollision.h"

class Player : public df::Object {

	float PLAYER_SPEED = .5f;
private:
    int m_player_id;                // 1 or 2

private:
    bool m_alive;

public:
    Player(int id, df::Vector start_pos);
    df::Vector m_target_dir;        // current moving direction
	df::Vector m_target_pos;		// current target grid cell
    df::Vector m_prev_pos;		// previous target grid cell

    int eventHandler(const df::Event* p_e) override;
    //int draw() override;

    int handleInput(const df::Event* p_e);
    void update();
    int handleCollision(const df::Event* p_e);
    

    bool isAlive() const { return m_alive; }
    void updateTarget();

    void leaveMarker();

    df::Vector multiplyVector(const df::Vector& v, float scalar);

    void die();
    void spawnParticle(const df::Vector& pos);
};
