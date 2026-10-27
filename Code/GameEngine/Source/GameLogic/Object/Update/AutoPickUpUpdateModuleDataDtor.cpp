// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1AutoPickUpUpdateModuleData@@UAE@XZ @0x0049647C (63B), address from the
// existing symbols.csv pin. The destructor only unwinds the members the
// rowed ctor (AutoPickUpUpdateModuleDataCtor.cpp, 0x00496308) builds: the
// EatObjectEntry vector at +0x14 (its own dtor instantiation at 0x004962AB,
// pinned opaque because the element type is unproven) and the pick-up filter
// at +0x0C (the pinned ??1Rva003623E5Member, 0x00360D26). The Snapshot base
// then restores its vtable 0x00BBB554 (g_00BBB554), as in
// Rva002560E3ModuleDataDtor.cpp.

class Rva003623E5Member
{
public:
	~Rva003623E5Member();
private:
	int m_x;
};

class Rva004962ABVector
{
public:
	~Rva004962ABVector();
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

class __declspec(novtable) AutoPickUpUpdateModuleData : public Snapshot
{
public:
	virtual ~AutoPickUpUpdateModuleData();

private:
	int m_unused04;
	int m_scanDelayTime;
	Rva003623E5Member m_pickUpFilter;
	float m_scanDistance;
	Rva004962ABVector m_eatObjectEntries;
};

AutoPickUpUpdateModuleData::~AutoPickUpUpdateModuleData()
{
}
