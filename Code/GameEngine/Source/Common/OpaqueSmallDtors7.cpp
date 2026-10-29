// cl: /O1 /DNDEBUG /MD /EHsc
//
// Four destructors at existing ??1RvaXXXX symbols.csv pins; classes
// unidentified, names address-derived. From retail:
//   0x000E59D3 82B   own vptr; an unnamed cleanup call (0x000E473F); then the
//                    AudioEventRTS member at +0x18 (pinned virtual dtor
//                    0x004EC395) and the texture holder at +0x14 (rowed
//                    TextureClass::Release_Ref); then the Snapshot base
//   0x000E9BAC 99B   own vptr; an unnamed cleanup call (0x000E7016); then the
//                    0x40-element array of 0x5C-byte records at +0x4FB70
//                    (element dtor 0x000E86B8) and the +0x4FB60 member
//                    (dtor 0x0008B470); then the pinned base dtor 0x000E6C6F
//   0x000A8E0A 111B  own vptr; if TheAudio is up, an unnamed call on it
//                    (0x000600BA); then the rowed Rva00690FF0Handle (+0x20),
//                    the +0x88 ref holder (+0x1C) and the rowed
//                    BfmeStringTailRecord156 (+0x0C); then the inline base's
//                    vptr (the Rva0051D93Sub vtable)
//   0x0006ED6F 116B  a SimpleSceneClass subclass with a SubsystemInterface at
//                    +0x108: remove the +0x114 render object from the scene,
//                    release and clear it, then both bases' rowed dtors
// Unnamed callees are pinned under address-derived names.

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

class TextureClass
{
public:
	void Release_Ref();
};

class TextureRefHolder
{
public:
	~TextureRefHolder()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
private:
	TextureClass *m_texture;
};

class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
private:
	char m_data[0x84];
};

class Rva000E59D3 : public Snapshot
{
public:
	virtual ~Rva000E59D3();
private:
	void rva000E473F();

	char m_pad04[0x14 - 0x04];
	TextureRefHolder m_14;
	AudioEventRTS m_18;
};

Rva000E59D3::~Rva000E59D3()
{
	rva000E473F();
}

class Rva000E86B8Record
{
public:
	~Rva000E86B8Record();
private:
	char m_data[0x5C];
};

class Rva0008B470Member
{
public:
	~Rva0008B470Member();
private:
	char m_data[0x10];
};

class Rva000E6C6F
{
public:
	virtual ~Rva000E6C6F();
private:
	char m_pad04[0x4FB60 - 0x04];
};

class Rva000E9BAC : public Rva000E6C6F
{
public:
	virtual ~Rva000E9BAC();
private:
	void rva000E7016();

	Rva0008B470Member m_4FB60;
	Rva000E86B8Record m_4FB70[0x40];
};

Rva000E9BAC::~Rva000E9BAC()
{
	rva000E7016();
}

class AudioManager
{
public:
	void rva000600BA(void *owner);
};

extern AudioManager *TheAudio;

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

struct BfmeStringTailRecord156
{
	~BfmeStringTailRecord156();
	int m_data[4];
};

class Rva0051D93Sub
{
public:
	virtual ~Rva0051D93Sub() {}
};

class Rva00A8E0A : public Rva0051D93Sub
{
public:
	virtual ~Rva00A8E0A();
private:
	char m_pad04[0x0C - 0x04];
	BfmeStringTailRecord156 m_0C;
	RefHolder88 m_1C;
	Rva00690FF0Handle m_20;
};

Rva00A8E0A::~Rva00A8E0A()
{
	if (TheAudio)
		TheAudio->rva000600BA(this);
}

class RenderObjClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		--m_numRefs;
		if (m_numRefs == 0)
			Delete_This();
	}
private:
	int m_numRefs;
};

class SimpleSceneClass
{
public:
	virtual ~SimpleSceneClass();
	virtual void Remove_Render_Object(RenderObjClass *obj);
private:
	char m_pad04[0x108 - 0x04];
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[8];
};

class Rva006ED6F : public SimpleSceneClass, public SubsystemInterface
{
public:
	virtual ~Rva006ED6F();
private:
	RenderObjClass *m_114;
};

Rva006ED6F::~Rva006ED6F()
{
	SimpleSceneClass::Remove_Render_Object(m_114);
	if (m_114)
	{
		m_114->Release_Ref();
		m_114 = 0;
	}
}
