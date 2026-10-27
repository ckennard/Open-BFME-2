// cl: /O1 /DNDEBUG /MD /EHsc
// ??1TerrainResourceClientBehavior@@UAE@XZ @0x004CC5AA 80B, address from the
// existing symbols.csv pin. Client-behavior dtor in the
// AnimationSoundClientBehaviorDtor.cpp shape: own primary vtable 0x00BEFF20,
// then the intermediate PrimaryP vtable 0x00BEFE48 and the fold base
// 0x0049B47C. Body: when the +0x0C flag (zeroed by the rowed ctor 0x00252DEB)
// is set, the TheInGameUI sub-object at +0x58C is told through an unnamed
// member at 0x004E7D1D (address-derived name).

class Rva004E7D1DPart
{
public:
	void rva004E7D1D();
};

class InGameUI
{
public:
	char m_pad[0x58C];
	Rva004E7D1DPart m_part58C;
};

extern InGameUI *TheInGameUI;

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class PrimaryP : public Rva0049B47C
{
public:
	~PrimaryP() {}
};

class TerrainResourceClientBehavior : public PrimaryP
{
public:
	virtual ~TerrainResourceClientBehavior();

private:
	unsigned char m_0C;
};

TerrainResourceClientBehavior::~TerrainResourceClientBehavior()
{
	if (m_0C)
		TheInGameUI->m_part58C.rva004E7D1D();
}
