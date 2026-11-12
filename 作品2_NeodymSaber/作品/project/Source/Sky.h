#pragma once
#include "../Library/gameObject.h"

class Sky : public GameObject {
public:
	Sky();
	~Sky();
	void Update();
	void Draw();

private:

	int hModel;
	VECTOR pos;	//ç¿ïW
	VECTOR sca;		//ägëÂó¶
	VECTOR rot;
};

