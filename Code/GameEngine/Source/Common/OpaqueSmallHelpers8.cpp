// cl: /O1 /DNDEBUG /MD
//
// Small helpers at existing symbols.csv pins; classes unidentified, names
// address-derived or carried from their pins. From retail:
//   0x003B3F5E 8B    destroy the member at +4 (dtor 0x003B35B1), tail jump
//   0x000A8AC0 12B   null-guarded tail call 0x0010FB64 on the held pointer
//   0x000A8B4B 14B   same with one dword argument (0x0010FEF3)
//   0x002572D7 23B   unnamed cleanup (0x00256F84), then free the buffer at +0
//   0x005F7736 26B   detach the pointer at +0 and delete it (element dtor
//                    0x005F75C9, scalar operator delete)
//   0x005FA146 26B   same shape (element dtor 0x005F9877)
//   0x002E0648 32B   forward the argument to the +0x4C member (with this) and
//                    assign it to the +0x48 string (rowed StringBase set)
// Unnamed callees are pinned under address-derived names.

void __cdecl free(void *block);

struct Rva003B35B1Member
{
	~Rva003B35B1Member();
};

struct BfmeNodeZ
{
	int m_0;
	Rva003B35B1Member m_4;
	~BfmeNodeZ();
};

BfmeNodeZ::~BfmeNodeZ()
{
}

struct Rva0010FB64Stream
{
	void rva0010FB64();
	void rva0010FEF3(unsigned int value);
};

struct MilesStreamRef
{
	Rva0010FB64Stream *m_stream;
	void rva000A8AC0();
	void rva000A8B4B(unsigned int value);
};

void MilesStreamRef::rva000A8AC0()
{
	if (m_stream)
		m_stream->rva0010FB64();
}

void MilesStreamRef::rva000A8B4B(unsigned int value)
{
	if (m_stream)
		m_stream->rva0010FEF3(value);
}

struct Rva002572D7Member
{
	void *m_start;
	void rva00256F84();
	~Rva002572D7Member();
};

Rva002572D7Member::~Rva002572D7Member()
{
	rva00256F84();
	if (m_start)
		free(m_start);
}

struct Rva005F75C9Element
{
	~Rva005F75C9Element();
};

struct Rva005F7736
{
	Rva005F75C9Element *m_ptr;
	void clear();
};

void Rva005F7736::clear()
{
	Rva005F75C9Element *ptr = m_ptr;
	m_ptr = 0;
	if (ptr)
		delete ptr;
}

struct Rva005F9877Element
{
	~Rva005F9877Element();
};

struct Rva005FA146
{
	Rva005F9877Element *m_ptr;
	void clear();
};

void Rva005FA146::clear()
{
	Rva005F9877Element *ptr = m_ptr;
	m_ptr = 0;
	if (ptr)
		delete ptr;
}

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);
private:
	void *m_data;
};

class Rva002E2903Player;

struct Rva004FB222Member
{
	void rva004FB222(Rva002E2903Player *player, void *value);
};

class Rva002E2903Player
{
public:
	void attach(void *value);
private:
	char m_pad[0x48];
	AsciiString m_48;
	Rva004FB222Member m_4C;
};

void Rva002E2903Player::attach(void *value)
{
	m_4C.rva004FB222(this, value);
	m_48 = *(const AsciiString *)value;
}
