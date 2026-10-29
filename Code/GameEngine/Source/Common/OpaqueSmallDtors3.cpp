// cl: /O1 /DNDEBUG /MD /EHsc
//
// Six small destructors at existing ??1RvaXXXX symbols.csv pins; classes
// unidentified, names address-derived. From retail:
//   0x000A86CE 64B  members: the rowed Rva00690FF0Handle at +0x0C, then the
//                   ref holder at +4 (rowed OpaqueRefCounted::Release_Ref on
//                   pointee +0x88)
//   0x000A897D 68B  members: the rowed Rva0040FE5 at +0x38 and the 0x000A8879
//                   member at +0x30, then the out-of-line base dtor 0x0073F4F3
//   0x002D0588 71B  own vptr; an unnamed cleanup call (0x002D0469); the
//                   0x002CFF2D member at +0x14; then the SubsystemInterface base
//   0x004E3CD0 72B  own vptr; an unnamed cleanup call (0x004E2199); the
//                   0x004E3C32 member at +0x14 and the pinned RvaVec002B80CE at +4
//   0x005AFE3F 71B  own vptr; unregister this from the global object the
//                   0x00381452 getter returns (0x002B7250), clear +8/+0x0C/+0x10; then the inline base
//                   dtor's vptr
//   0x0010F83E 53B  the AsciiString at +0x10, then the out-of-line base dtor
//                   0x001164F5
// Unnamed callees are pinned under address-derived names.

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

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct HeldRef88
{
	char m_pad[0x88];
	OpaqueRefCounted m_ref;
};

class RefHolder88
{
public:
	~RefHolder88()
	{
		if (m_ptr)
			m_ptr->m_ref.Release_Ref();
	}
private:
	HeldRef88 *m_ptr;
};

class Rva00690FF0Handle
{
public:
	~Rva00690FF0Handle();
private:
	int m_data[2];
};

class __declspec(novtable) Rva00A86CE
{
public:
	virtual ~Rva00A86CE();
private:
	RefHolder88 m_04;
	int m_08;
	Rva00690FF0Handle m_0C;
};

Rva00A86CE::~Rva00A86CE()
{
}

class Rva0040FE5
{
public:
	virtual ~Rva0040FE5();
private:
	char m_data[0x20];
};

class Rva000A8879Member
{
public:
	~Rva000A8879Member();
private:
	int m_data[2];
};

class Rva0073F4F3
{
public:
	virtual ~Rva0073F4F3();
private:
	char m_pad04[0x30 - 0x04];
};

class __declspec(novtable) Rva00A897D : public Rva0073F4F3
{
public:
	virtual ~Rva00A897D();
private:
	Rva000A8879Member m_30;
	Rva0040FE5 m_38;
};

Rva00A897D::~Rva00A897D()
{
}

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[8];
};

class Rva002CFF2DMember
{
public:
	~Rva002CFF2DMember();
private:
	int m_data;
};

class Rva002D0588 : public SubsystemInterface
{
public:
	virtual ~Rva002D0588();
private:
	void rva002D0469();

	char m_pad0C[0x14 - 0x0C];
	Rva002CFF2DMember m_14;
};

Rva002D0588::~Rva002D0588()
{
	rva002D0469();
}

class RvaVec002B80CE
{
public:
	~RvaVec002B80CE();
private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class Rva004E3C32Member
{
public:
	~Rva004E3C32Member();
private:
	int m_data;
};

class Rva004E3CD0
{
public:
	virtual ~Rva004E3CD0();
private:
	void rva004E2199();

	RvaVec002B80CE m_04;
	int m_10;
	Rva004E3C32Member m_14;
};

Rva004E3CD0::~Rva004E3CD0()
{
	rva004E2199();
}

class Rva005AFE3F;

class Rva002B7250Target
{
public:
	void rva002B7250(Rva005AFE3F *owner);
};

Rva002B7250Target *Rva00381452GetObject();

class Rva005AFE3FBase
{
public:
	virtual ~Rva005AFE3FBase() {}
};

class Rva005AFE3F : public Rva005AFE3FBase
{
public:
	virtual ~Rva005AFE3F();
private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

Rva005AFE3F::~Rva005AFE3F()
{
	Rva00381452GetObject()->rva002B7250(this);
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
}

class Rva001164F5
{
public:
	virtual ~Rva001164F5();
private:
	char m_pad04[0x10 - 0x04];
};

class __declspec(novtable) Rva0010F83E : public Rva001164F5
{
public:
	virtual ~Rva0010F83E();
private:
	AsciiString m_10;
};

Rva0010F83E::~Rva0010F83E()
{
}
