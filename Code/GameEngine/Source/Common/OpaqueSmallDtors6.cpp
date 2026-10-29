// cl: /O1 /DNDEBUG /MD /EHsc
//
// Two destructors at existing ??1RvaXXXX symbols.csv pins; classes
// unidentified, names address-derived. From retail:
//   0x004EDCE9 100B  own vptr; an unnamed cleanup call with (0, true)
//                    (0x004ED748); then the AsciiString at +0x2C and the
//                    trivially-typed vectors at +0x14 and +4 (free only)
//   0x0009045E 108B  own vptr; release each of ten slots at +0x14 and the slot
//                    at +0x3C through an unnamed member (0x00090381), clearing
//                    each; then the out-of-line base dtor 0x0026201C (rowed)

void __cdecl free(void *block);

template <typename T> class StringBase
{
	friend class AsciiString;
private:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	~AsciiString() {}
};

class PodVector
{
public:
	~PodVector()
	{
		if (m_start)
			free(m_start);
	}
private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class Rva004EDCE9
{
public:
	virtual ~Rva004EDCE9();
private:
	void rva004ED748(int which, bool flag);

	PodVector m_04;
	int m_10;
	PodVector m_14;
	char m_pad20[0x2C - 0x20];
	AsciiString m_2C;
};

Rva004EDCE9::~Rva004EDCE9()
{
	rva004ED748(0, true);
}

class Rva0026201C
{
public:
	virtual ~Rva0026201C();
private:
	char m_pad04[0x14 - 0x04];
};

class Rva009045E : public Rva0026201C
{
public:
	virtual ~Rva009045E();
private:
	void rva00090381(void *slot);

	void *m_slots[10];
	void *m_3C;
};

Rva009045E::~Rva009045E()
{
	for (int i = 0; i < 10; ++i)
	{
		if (m_slots[i])
			rva00090381(m_slots[i]);
		m_slots[i] = 0;
	}
	if (m_3C)
		rva00090381(m_3C);
	m_3C = 0;
}
