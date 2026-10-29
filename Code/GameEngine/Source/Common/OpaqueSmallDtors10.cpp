// cl: /O1 /DNDEBUG /MD /EHsc
//
// Two destructors at existing symbols.csv pins; classes unidentified, names
// address-derived. Both run an unnamed cleanup in EH state 0 so a throw still
// destroys the trailing member. From retail:
//   0x005CD0FE 51B  cleanup 0x005CCFD1, then the rowed STLport
//                   _List_base<Rva005F8F96> dtor for the list at +8
//   0x0060D031 57B  cleanup 0x0060CFB6 (the rowed FXList hashtable clear's
//                   address), then free the buffer at +4 through the
//                   C++-declared free
// Unnamed callees are pinned under address-derived names.

void __cdecl free(void *block);

struct Rva005F8F96;

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class _List_base
	{
	public:
		~_List_base();
	private:
		void *m_node;
	};
}

struct Rva005CD0FEElem
{
	int m_0;
	int m_4;
	_STL::_List_base<Rva005F8F96, _STL::allocator<Rva005F8F96> > m_8;
	void rva005CCFD1();
	~Rva005CD0FEElem();
};

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
