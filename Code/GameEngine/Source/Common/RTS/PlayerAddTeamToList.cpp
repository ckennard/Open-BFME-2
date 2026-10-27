// cl: /O1 /MD /GX-
//
// ?addTeamToList@Player@@QAEXPAVTeamPrototype@@@Z @0x002AE228 (42B), address
// from the existing symbols.csv pin. ZH Player.cpp: skip a team prototype the
// player already lists, otherwise append it. m_playerTeamPrototypes is the
// STLport list at +0x32C (node: next, prev, data at +8). Its out-of-line
// push_back at 0x002ADCC7 forwards end() and the value to insert.

class TeamPrototype;

namespace _STL
{
template <class T> class allocator
{
};

template <class T> struct _List_node
{
	_List_node *_M_next;
	_List_node *_M_prev;
	T _M_data;
};

template <class T, class A = allocator<T> > class list
{
public:
	void push_back(const T &value);
	_List_node<T> *_M_node;
};
}

typedef _STL::list<TeamPrototype *> PlayerTeamList;

class Player
{
public:
	void addTeamToList(TeamPrototype *team);

private:
	char m_pad[0x32C];
	PlayerTeamList m_playerTeamPrototypes;
};

void Player::addTeamToList(TeamPrototype *team)
{
	_STL::_List_node<TeamPrototype *> *head = m_playerTeamPrototypes._M_node;
	for (_STL::_List_node<TeamPrototype *> *it = head->_M_next; it != head; it = it->_M_next)
	{
		if (team == it->_M_data)
			return;
	}
	m_playerTeamPrototypes.push_back(team);
}
