#include "Team.h"
#include "NPC.h"

Team::Team(int TeamId) {
	setTeamId(TeamId);
}

void Team::addMember(NPC* s) {
	members.push_back(s);
	if (s->getType() == SQUIRE) {
		squire = (Squire*)s;
	}
	TeamSize += 1;
}