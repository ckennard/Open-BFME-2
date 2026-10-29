// cl: /O1 /DNDEBUG /MD
//
// Three small methods at existing symbols.csv pins; classes unidentified,
// names carried from their pins. From retail:
//   0x00362437 42B   null object -> false; else an unnamed query (0x003618B9)
//                    on the object's +4 field, its controlling player (rowed
//                    Object::getControllingPlayer) and the second argument
//   0x003F6388 43B   memberwise assignment of a 28-byte record: dword, a
//                    12-byte member (assign 0x003F5FD0) and a vector<Int>
//                    (pinned STLport assign 0x0021C21B)
//   0x005DE926 44B   over the 8-byte-element sequence at +4 (iterators
//                    passed by value): an unnamed range call on [begin, end)
//                    (0x00381B1F), then an unnamed call
//                    with the old element count (0x005DE84E); clear +0x14
// Unnamed callees are pinned under address-derived names.

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> > class vector
	{
	public:
		vector &operator=(const vector &other);
	private:
		T *m_start;
		T *m_finish;
		T *m_end;
	};
}

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
private:
	int m_0;
public:
	int m_4;
};

class BfmeTab1026
{
public:
	char bfmeHas1026(int object, int value);
private:
	char rva003618B9(int field, Player *player, int value);
};

char BfmeTab1026::bfmeHas1026(int object, int value)
{
	Object *obj = (Object *)object;
	if (obj == 0)
		return 0;
	int field = obj->m_4;
	return rva003618B9(field, obj->getControllingPlayer(), value);
}

struct Rva003F5FD0Member
{
	Rva003F5FD0Member &operator=(const Rva003F5FD0Member &other);
	int m_data[3];
};

struct BfmeAssignRecord28
{
	int m_0;
	Rva003F5FD0Member m_4;
	_STL::vector<int> m_10;
	BfmeAssignRecord28 &operator=(const BfmeAssignRecord28 &other);
};

BfmeAssignRecord28 &BfmeAssignRecord28::operator=(const BfmeAssignRecord28 &other)
{
	m_0 = other.m_0;
	m_4 = other.m_4;
	m_10 = other.m_10;
	return *this;
}

struct Rva005DE926Pair
{
	int m_data[2];
};

struct Rva005DE926Iter
{
	Rva005DE926Pair *m_ptr;
};

struct Rva005DE926Vector
{
	void rva00381B1F(Rva005DE926Iter first, Rva005DE926Iter last);
	void rva005DE84E(int count);
	Rva005DE926Iter m_start;
	Rva005DE926Iter m_finish;
	Rva005DE926Iter m_end;
	int m_C;
	__forceinline void reset()
	{
		int count = m_finish.m_ptr - m_start.m_ptr;
		rva00381B1F(m_start, m_finish);
		rva005DE84E(count);
	}
};

class Rva005DE5B5
{
public:
	void rva005DE926();
private:
	int m_0;
	Rva005DE926Vector m_4;
	bool m_14;
};

void Rva005DE5B5::rva005DE926()
{
	m_4.reset();
	m_14 = false;
}
