// cl: /O1 /DNDEBUG /MD /EHsc
//
// Four small destructors at existing ??1RvaXXXX symbols.csv pins; classes
// unidentified, names address-derived. From retail:
//   0x0007C454 75B  a CameraClass subclass (two vptrs, +0/+8): free the
//                   trivially-typed vector at +0x3FC, then the rowed
//                   CameraClass dtor 0x00133A00
//   0x0005813E 77B  a subclass of the rowed Rva0051D93 (vptrs +0/+0x88): if
//                   TheAudio is up, hand it this object through an unnamed
//                   member (0x00057948)
//   0x0004EFE9 78B  own vptr; call 0x005CB265 on the +0x20 object, whose
//                   holder then releases it (rowed RadarEventRef::release),
//                   then the pinned base dtor ??1Rva00539926Base
//   0x0004CE36 79B  two vptrs (+0/+0x0C); two 0x0C-byte elements at +0xAC (EH
//                   vector dtor, element dtor 0x0004CDAF), then the base dtor
//                   0x001F9D98
// Unnamed callees are pinned under address-derived names.

void __cdecl free(void *block);

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

class RefCountBase7C454
{
public:
	virtual ~RefCountBase7C454();
private:
	int m_refs;
};

class PersistBase7C454
{
public:
	virtual void slot();
};

class CameraClass : public RefCountBase7C454, public PersistBase7C454
{
public:
	virtual ~CameraClass();
private:
	char m_pad0C[0x3FC - 0x0C];
};

class Rva007C454 : public CameraClass
{
public:
	virtual ~Rva007C454();
private:
	PodVector m_3FC;
};

Rva007C454::~Rva007C454()
{
}

class Rva0051D93Head
{
public:
	virtual ~Rva0051D93Head();
private:
	char m_data[0x84];
};

class Rva0051D93Sub
{
public:
	virtual void slot();
};

class Rva0051D93 : public Rva0051D93Head, public Rva0051D93Sub
{
public:
	virtual ~Rva0051D93();
};

class Rva005813E;

class AudioManager
{
public:
	void rva00057948(Rva005813E *owner);
};

extern AudioManager *TheAudio;

class Rva005813E : public Rva0051D93
{
public:
	virtual ~Rva005813E();
};

Rva005813E::~Rva005813E()
{
	if (TheAudio)
		TheAudio->rva00057948(this);
}

class RadarEventRef
{
public:
	void release();
	void rva005CB265();
};

class RadarEventRefHolder
{
public:
	~RadarEventRefHolder()
	{
		if (m_ref)
			m_ref->release();
	}
	RadarEventRef *get() const { return m_ref; }
private:
	RadarEventRef *m_ref;
};

class Rva00539926Base
{
public:
	virtual ~Rva00539926Base();
private:
	char m_pad04[0x20 - 0x04];
};

class Rva004EFE9 : public Rva00539926Base
{
public:
	virtual ~Rva004EFE9();
private:
	RadarEventRefHolder m_20;
};

Rva004EFE9::~Rva004EFE9()
{
	m_20.get()->rva005CB265();
}

class Rva0004CDAFElement
{
public:
	~Rva0004CDAFElement();
private:
	int m_data[3];
};

class Rva001F9D98Primary
{
public:
	virtual ~Rva001F9D98Primary();
private:
	char m_pad04[8];
};

class Rva001F9D98Second
{
public:
	virtual void slot();
};

class Rva001F9D98 : public Rva001F9D98Primary, public Rva001F9D98Second
{
public:
	virtual ~Rva001F9D98();
private:
	char m_pad10[0xAC - 0x10];
};

class Rva004CE36 : public Rva001F9D98
{
public:
	virtual ~Rva004CE36();
private:
	Rva0004CDAFElement m_AC[2];
};

Rva004CE36::~Rva004CE36()
{
}
