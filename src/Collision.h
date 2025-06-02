#pragma once
#include "ZaWorldo.h"

class Collision {
	void static CreateContacts(const bodies_t& bodies, contacts_t& contacts);
	void static SeperateContacts(contacts_t& contacts);
private:
	bool static Intersects(Body* bodyA, Body* bodyB);

};