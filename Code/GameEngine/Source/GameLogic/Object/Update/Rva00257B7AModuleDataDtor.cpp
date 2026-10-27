// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva00257B7AModuleData@@UAE@XZ @0x00257B7A 109B. Module-data destructor
// called by the rowed deleting dtor at 0x00257B5E. That row and a
// symbols.csv pin spell this body ??1StructureCollapseUpdateModuleData, but
// the rowed StructureCollapseUpdateModuleData dtor is 0x00256B94 (its own
// vtable 0x00BF3E30), so this class keeps an address-derived name until the
// owner is identified. Shape: AutoPickUpUpdateModuleDataDtor.cpp. Members in
// retail destruction order: a trivially-typed vector at +0xAC (buffer freed
// through the C++-decorated free 0x00030830), the rowed RvaPair00257544
// vector at +0xA0 (dtor 0x00257544), three 12-byte strings at +0x70 torn down
// by the EH vector dtor with element dtor 0x0007FAB3 (the folded narrow
// basic_string dtor, pinned under this TU's spelling), and an AsciiString at
// +0x64 (inline releaseBuffer). The Snapshot base then restores g_00BBB554.

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

class Rva0007FAB3String
{
public:
	~Rva0007FAB3String();
private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

struct RvaPair00257544;

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	~vector();
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

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

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

extern const void *const g_00BBB554[];
inline Snapshot::~Snapshot()
{
	*(const void **)this = g_00BBB554;
}

class __declspec(novtable) Rva00257B7AModuleData : public Snapshot
{
public:
	virtual ~Rva00257B7AModuleData();

private:
	char m_pad04[0x64 - 0x04];
	AsciiString m_64;
	char m_pad68[0x70 - 0x68];
	Rva0007FAB3String m_70[3];
	char m_pad94[0xA0 - 0x94];
	_STL::vector<RvaPair00257544> m_A0;
	PodVector m_AC;
};

Rva00257B7AModuleData::~Rva00257B7AModuleData()
{
}
