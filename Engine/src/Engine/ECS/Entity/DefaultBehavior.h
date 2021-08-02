#pragma once
#include <Engine/ECS/Entity/Behavior.h>

using namespace ArcanaTools;

class DefaultBehavior : public Behavior {

public:
	virtual void Start() override;
	virtual void Update(TimeStep ts) override;


};

