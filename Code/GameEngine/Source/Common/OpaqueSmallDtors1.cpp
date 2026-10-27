// cl: /O1 /DNDEBUG /MD /GX-
//
// Six small destructors at existing ??1RvaXXXX symbols.csv pins, each with a
// rowed scalar deleting dtor in OpaqueScalarDeletingDtors.cpp. Classes are
// unidentified, so the names stay address-derived. Shapes, from retail:
//   0x0005333F 19B  release the ref held at +0x88 of the +4 object (rowed
//                   OpaqueRefCounted::Release_Ref, tail call)
//   0x0006DD51 18B  restore both vptrs (+0, +8), then tail-call the rowed
//                   CollectionClass dtor
//   0x00084CEF 18B  call an unnamed member (0x00083E87), clear +8 and +0x18
//   0x0005109D 22B  Snapshot second base at +0x0C: null-checked this adjust,
//                   inline Snapshot dtor (g_00BBB554), then the first base's
//                   rowed SubsystemInterface dtor
//   0x00051D93 29B  restore the +0 vptr and the +0x88 sub-object's vptr, which
//                   that sub-object's inline dtor resets once more, then the
//                   rowed BfmeStringTailRecord144 dtor
//   0x0054D2CF 14B  restore the vptr, then tail-call the +4 member's dtor
//                   (0x0054CC1B, pinned opaque)

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva005333FHeld
{
	char m_pad[0x88];
	OpaqueRefCounted m_ref;
};

class __declspec(novtable) Rva005333F
{
public:
	virtual ~Rva005333F();
private:
	Rva005333FHeld *m_held;
};

Rva005333F::~Rva005333F()
{
	if (m_held)
		m_held->m_ref.Release_Ref();
}

class CollectionClass
{
public:
	virtual ~CollectionClass();
private:
	int m_04;
};

class Rva006DD51Iface
{
public:
	virtual void ifaceSlot();
};

class Rva006DD51 : public CollectionClass, public Rva006DD51Iface
{
public:
	virtual ~Rva006DD51();
};

Rva006DD51::~Rva006DD51()
{
}

class __declspec(novtable) Rva0084CEF
{
public:
	virtual ~Rva0084CEF();
private:
	void rva00083E87();

	int m_04;
	int m_08;
	char m_pad0C[0x18 - 0x0C];
	int m_18;
};

Rva0084CEF::~Rva0084CEF()
{
	rva00083E87();
	m_08 = 0;
	m_18 = 0;
}

class Xfer;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[8];
};

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

class __declspec(novtable) Rva005109D : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Rva005109D();
};

Rva005109D::~Rva005109D()
{
}

class BfmeStringTailRecord144
{
public:
	virtual ~BfmeStringTailRecord144();
private:
	char m_data[0x84];
};

class Rva0051D93Sub
{
public:
	virtual ~Rva0051D93Sub() {}
};

class Rva0051D93 : public BfmeStringTailRecord144, public Rva0051D93Sub
{
public:
	virtual ~Rva0051D93();
};

Rva0051D93::~Rva0051D93()
{
}

class Rva0054CC1BMember
{
public:
	~Rva0054CC1BMember();
private:
	int m_data;
};

class Rva0054D2CF
{
public:
	virtual ~Rva0054D2CF();
private:
	Rva0054CC1BMember m_04;
};

Rva0054D2CF::~Rva0054D2CF()
{
}
