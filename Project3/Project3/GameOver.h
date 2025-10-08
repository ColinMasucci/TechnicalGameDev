#include "ViewObject.h"

class GameOver : public df::ViewObject {

private:

public:
	GameOver(int winner);
	~GameOver();
	int eventHandler(const df::Event* p_e) override;
	int draw() override;
};