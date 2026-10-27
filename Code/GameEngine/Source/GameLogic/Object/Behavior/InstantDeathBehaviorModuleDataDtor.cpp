// cl: /O1 /DNDEBUG /MD /EHsc
// ??1InstantDeathBehaviorModuleData@@UAE@XZ @0x0045D28D 105B, address from the
// existing symbols.csv pin. Module-data destructor in the
// AutoPickUpUpdateModuleDataDtor.cpp shape: unwind the members in reverse,
// then restore the Snapshot base vtable g_00BBB554. Members (retail order of
// destruction): a vector with element destruction at +0x5C (its own dtor at
// 0x0045D137, pinned opaque) and three vectors of trivially destructible
// elements at +0x50, +0x44 and +0x38, whose inline STLport dtors only free the
// buffer through the C++-decorated free (0x00030830).

void __cdecl free(void *block);

class Rva0045D137Vector
{
public:
	~Rva0045D137Vector();
private:
	void *m_start;
	void *m_finish;
	void *m_end;
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

class __declspec(novtable) InstantDeathBehaviorModuleData : public Snapshot
{
public:
	virtual ~InstantDeathBehaviorModuleData();

private:
	char m_pad04[0x38 - 0x04];
	PodVector m_38;
	PodVector m_44;
	PodVector m_50;
	Rva0045D137Vector m_5C;
};

InstantDeathBehaviorModuleData::~InstantDeathBehaviorModuleData()
{
}
