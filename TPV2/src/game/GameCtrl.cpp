// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrl.h"

#include "../sdlutils/InputHandler.h"
#include "GameManager.h"

GameCtrl::GameCtrl() {
}

GameCtrl::~GameCtrl() {
}

void GameCtrl::handleInput(Container *o) {

	auto gm = static_cast<GameManager*>(o);
	auto state_ = gm->getState();

	auto& inhdlr = ih();
	if (state_ != GameManager::RUNNING) {

		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case GameManager::NEWGAME:
				gm->moveBall();
				gm->setState(GameManager::RUNNING);
				break;
			case GameManager::PAUSED:
				gm->moveBall();
				gm->setState(GameManager::RUNNING);
				break;
			case GameManager::GAMEOVER:
				gm->setState(GameManager::NEWGAME);
				gm->setScore(0, 0);
				gm->setScore(1, 0);
				break;
			default:
				break;
			}
		}
		
	}
	else {
		if (inhdlr.isKeyDown(SDLK_LEFT)) {
			gm->setRotation(-5.0f);
		}
		if (inhdlr.isKeyDown(SDLK_RIGHT)) {
			gm->setRotation(5.0f);
		}

		if (inhdlr.isKeyDown(SDLK_UP)) {
			float thrust = 0.2f;
			float speedLimit = 3.0f;
			Vector2D vel = gm->getVel();
			float r = gm->getRotation();
			Vector2D newVel = vel + Vector2D(0, -1).rotate(r) * thrust;
			if (newVel.getX() > speedLimit || newVel.getY() > speedLimit) {
				newVel.normalize()* speedLimit;
			}
		}
	}
}
