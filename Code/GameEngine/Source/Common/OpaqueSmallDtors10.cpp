// cl: /O1 /DNDEBUG /MD /EHsc
//
// Two destructors at existing symbols.csv pins; classes unidentified, names
// address-derived. Both run an unnamed cleanup in EH state 0 so a throw still
// destroys the trailing member. From retail:
//   0x005CD0FE 51B  cleanup 0x005CCFD1, then the rowed STLport
//                   _List_base<Rva005F8F96> dtor for the list at +8
//   0x005CCFD1 34B  that cleanup: until the list is empty, call 0x005CCA57
//                   on the back element's +4 pointer, then 0x005CCEBE on the
//                   list (removes the back node)
//   0x005CCEBE 23B  that removal: the rowed list<Rva005F8F96>::erase
//                   (0x004F7731) on an iterator to
//                   the back node (STLport pop_back: decrement end(), pass
//                   the copy-constructed iterator, result through a hidden
//                   pointer)
//   0x0060D031 57B  cleanup 0x0060CFB6 (the rowed FXList hashtable clear's
//                   address), then free the buffer at +4 through the
//                   C++-declared free
// Unnamed callees are pinned under address-derived names.

void __cdecl free(void *block);

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class _List_base
	{
	public:
		~_List_base();
	protected:
		struct Node
		{
			Node *m_next;
			Node *m_prev;
			T m_data;
		};
		Node *m_node;
	};
}

struct Rva005CCA57Target
{
	void rva005CCA57();
};

struct Rva005F8F96
{
	void *m_00;
	Rva005CCA57Target *m_04;
};

class Rva005CD0FEList : public _STL::_List_base<Rva005F8F96, _STL::allocator<Rva005F8F96> >
{
public:
	bool empty() const { return m_node->m_next == m_node; }
	Rva005F8F96 &back() { return m_node->m_prev->m_data; }
	void rva005CCEBE();

	struct Iterator
	{
		Iterator(Node *node) : m_node(node) {}
		Iterator(const Iterator &other) : m_node(other.m_node) {}
		Iterator &operator--() { m_node = m_node->m_prev; return *this; }
		Node *m_node;
	};
	Iterator rva004F7731(Iterator position);
};

void Rva005CD0FEList::rva005CCEBE()
{
	Iterator last(m_node);
	rva004F7731(--last);
}

struct Rva005CD0FEElem
{
	int m_0;
	int m_4;
	Rva005CD0FEList m_8;
	void rva005CCFD1();
	~Rva005CD0FEElem();
};

void Rva005CD0FEElem::rva005CCFD1()
{
	while (!m_8.empty())
	{
		m_8.back().m_04->rva005CCA57();
		m_8.rva005CCEBE();
	}
}

Rva005CD0FEElem::~Rva005CD0FEElem()
{
	rva005CCFD1();
}

struct Rva0060D031Buffer
{
	void *m_start;
	~Rva0060D031Buffer()
	{
		if (m_start)
			free(m_start);
	}
};

struct Rva0060D031Member
{
	int m_0;
	Rva0060D031Buffer m_4;
	void rva0060CFB6();
	~Rva0060D031Member();
};

Rva0060D031Member::~Rva0060D031Member()
{
	rva0060CFB6();
}
