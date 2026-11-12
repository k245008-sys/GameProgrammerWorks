#pragma once
#include"../Library/gameObject.h"
class Fade : public GameObject
{
	public:
	Fade();
	~Fade() {}
	void Update() override;
	void Draw() override;

	private:
	float time;
	float alpha;
	unsigned int color;
};

