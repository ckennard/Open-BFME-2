// cl: /O1 /DNDEBUG /MD /EHsc
//
// Five small member-unwind destructors at existing ??1RvaXXXX symbols.csv
// pins; classes unidentified, names address-derived. From retail:
//   0x000B6DD2 58B  three 0x18-byte elements at +4 (rowed virtual element dtor
//                   ??1Rva00B6971, EH vector dtor), then Snapshot g_00BBB554
//   0x00104DB0 54B  own vptr; the Render2DSentenceClass member at +4 (pinned
//                   dtor 0x00157C70); then the inline base dtor's vptr
//   0x00102188 54B  two 0x10-byte members at +0x14 and +4 (dtor 0x000B0254,
//                   pinned opaque)
//   0x000FF4D6 55B  an unnamed member call (0x000FF448), clear +8, then the
//                   AsciiString at +0x28
//   0x000B9AC2 61B  release the tree-hint ref at +0x28 of the +0x14 object
//                   (rowed fastcall ReleaseTreeHintRef00217D4C), then the
//                   AsciiString at +0x10

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

class Rva00B6971
{
public:
	virtual ~Rva00B6971();
private:
	char m_data[0x14];
};

class __declspec(novtable) Rva00B6DD2 : public Snapshot
{
public:
	virtual ~Rva00B6DD2();
private:
	Rva00B6971 m_04[3];
};

Rva00B6DD2::~Rva00B6DD2()
{
}

class Render2DSentenceClass
{
public:
	~Render2DSentenceClass();
private:
	char m_data[0x10];
};

class Rva00104DB0Base
{
public:
	virtual ~Rva00104DB0Base() {}
};

class Rva00104DB0 : public Rva00104DB0Base
{
public:
	virtual ~Rva00104DB0();
private:
	Render2DSentenceClass m_04;
};

Rva00104DB0::~Rva00104DB0()
{
}

class Rva000B0254Member
{
public:
	~Rva000B0254Member();
private:
	char m_data[0x10];
};

class __declspec(novtable) Rva00102188
{
public:
	virtual ~Rva00102188();
private:
	Rva000B0254Member m_04;
	Rva000B0254Member m_14;
};

Rva00102188::~Rva00102188()
{
}

class __declspec(novtable) Rva00FF4D6
{
public:
	virtual ~Rva00FF4D6();
private:
	void rva000FF448();

	int m_04;
	int m_08;
	char m_pad0C[0x28 - 0x0C];
	AsciiString m_28;
};

Rva00FF4D6::~Rva00FF4D6()
{
	rva000FF448();
	m_08 = 0;
}

struct TargetRef00217D4C;

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

struct Rva00B9AC2Held
{
	char m_pad[0x28];
	TargetRef00217D4C *refSlot() { return reinterpret_cast<TargetRef00217D4C *>(m_ref); }
	char m_ref[4];
};

class __declspec(novtable) Rva00B9AC2
{
public:
	virtual ~Rva00B9AC2();
private:
	char m_pad04[0x10 - 0x04];
	AsciiString m_10;
	Rva00B9AC2Held *m_14;
};

Rva00B9AC2::~Rva00B9AC2()
{
	if (m_14)
		ReleaseTreeHintRef00217D4C(m_14->refSlot());
}
