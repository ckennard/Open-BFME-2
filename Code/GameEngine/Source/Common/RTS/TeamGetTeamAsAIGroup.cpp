// cl: /O1 /DNDEBUG /MD
//
// Team::getTeamAsAIGroup, retail 0x003A0F62, 112 bytes, at its existing
// symbols.csv pin (TEAM_SET_ATTITUDE passes its team and a new AIGroup).
// Donor logic (ZH/BFME1): skip a null group, then walk the team member list
// and add each member that passes the filters to the group.
//
// The filters are read from retail rather than the donor: a member is left
// out when the rowed Object::rva002931BA reports true, when it has status
// bit 2 (rowed Object::testStatus), or when the object named by its +0x78 id
// (rowed GameLogic::findObjectByID) exists and has bit 0x20 of byte +0x115 of
// the structure at its +4 set. The group add is the call at 0x0036E5F1; the
// iterator calls are the rowed iterate_TeamMemberList and advance.

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BIT_2 = 2
};

struct Rva003A0F62Flags
{
	char m_pad[0x115];
	unsigned char m_115;
};

class Object
{
public:
	bool rva002931BA();
	Bool testStatus(ObjectStatusTypes bit) const;
private:
	int m_0;
public:
	Rva003A0F62Flags *m_4;
private:
	char m_pad08[0x70];
public:
	ObjectID m_78;
};

template <class OBJCLASS> class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class AIGroup
{
public:
	void rva0036E5F1(Object *obj);
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void getTeamAsAIGroup(AIGroup *aiGroup);
};

void Team::getTeamAsAIGroup(AIGroup *aiGroup)
{
	if (!aiGroup)
		return;

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (obj->rva002931BA())
			continue;
		if (obj->testStatus(OBJECT_STATUS_BIT_2))
			continue;
		if (obj->m_78)
		{
			Object *other = TheGameLogic->findObjectByID(obj->m_78);
			if (other && (other->m_4->m_115 & 0x20))
				continue;
		}
		aiGroup->rva0036E5F1(obj);
	}
}
