// cl: /O1 /DNDEBUG /MD /EHsc
// ??1EmotionTrackerUpdate@@UAE@XZ @0x004B1322 107B, address from the audited
// symbols.csv pin. Update-module destructor in the
// BattlePlanUpdateRva004978A3Dtor.cpp shape: restore the four vptrs (+0,
// +0x0C, +0x10, +0x20), unwind the +0xA4 member (dtor 0x002F0B52, pinned
// opaque) and the trivially-typed vector at +0x90 (buffer freed through the
// C++-decorated free 0x00030830), then call the rowed UpdateModule base
// dtor 0x0024A797.

void __cdecl free(void *block);

class Rva002F0B52Member
{
public:
	~Rva002F0B52Member();
private:
	int m_data[3];
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

class Rva0049B47C004978A3
{
public:
	virtual ~Rva0049B47C004978A3();
private:
	char m_pad04[8];
};

class MiBase1004978A3
{
public:
	virtual void f1();
};

class PrimaryP004978A3 : public Rva0049B47C004978A3, public MiBase1004978A3
{
public:
	~PrimaryP004978A3() {}
};

class Rva0024A797_B2004978A3
{
public:
	virtual void f2();
private:
	char m_pad04[12];
};

class Rva0024A797 : public PrimaryP004978A3, public Rva0024A797_B2004978A3
{
public:
	virtual ~Rva0024A797();
};

class __declspec(novtable) SecondBase004978A3
{
public:
	virtual ~SecondBase004978A3() {}
};

class EmotionTrackerUpdate : public Rva0024A797, public SecondBase004978A3
{
public:
	virtual ~EmotionTrackerUpdate();

private:
	char m_pad24[0x90 - 0x24];
	PodVector m_90;
	char m_pad9C[0xA4 - 0x9C];
	Rva002F0B52Member m_A4;
};

EmotionTrackerUpdate::~EmotionTrackerUpdate()
{
}
