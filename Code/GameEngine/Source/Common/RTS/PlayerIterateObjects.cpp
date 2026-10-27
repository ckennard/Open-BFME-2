// cl: /O1 /MD /GX-
//
// Player::iterateObjects @0x002AB08B (58B). Address from the symbols.csv pin
// a byte-verified caller (0x002AB8D0) produced; that caller spells it
// ?iterateObjects@Player@@QBEXP6AXPAVObject@@PAX@Z1@Z and ignores the result.
// ZH Player.cpp walks m_playerTeamPrototypes (the list at +0x32C, as in
// addTeamToList) and calls each prototype's object iterator. BFME 2 stops
// at the first prototype whose call returns 0 and returns 0/1, so this
// definition returns Int. The per-prototype callee at 0x0039ED9C is unnamed
// here.

typedef int Int;

class Object;
typedef void (*ObjectIterateFunc)(Object *obj, void *userData);

class TeamPrototype
{
public:
	Int rva0039ED9C(ObjectIterateFunc func, void *userData) const;
};

template <class T> struct ListNode
{
	ListNode *next;
	ListNode *prev;
	T data;
};

class Player
{
public:
	Int iterateObjects(ObjectIterateFunc func, void *userData) const;

private:
	char m_pad[0x32C];
	ListNode<TeamPrototype *> *m_playerTeamPrototypes;
};

Int Player::iterateObjects(ObjectIterateFunc func, void *userData) const
{
	for (ListNode<TeamPrototype *> *it = m_playerTeamPrototypes->next;
		it != m_playerTeamPrototypes; it = it->next)
	{
		if (!it->data->rva0039ED9C(func, userData))
			return 0;
	}
	return 1;
}
