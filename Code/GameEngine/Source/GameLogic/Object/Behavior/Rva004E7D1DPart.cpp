// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004E7D1D@Rva004E7D1DPart@@QAEXXZ @0x004E7D1D (7B), the TheInGameUI
// +0x58C callee of the rowed TerrainResourceClientBehavior destructor
// (0x004CC5AA): forwards to the object the part points at (0x004E7CEF,
// address-derived name) with a tail jump.

class Rva004E7C1CMember { public: void rva004E7C1C(); private: int m_data; };
class Rva004E7BAFMember { public: void rva004E7BAF(); private: int m_data[3]; };
class Rva004E551EMember { public: void rva004E551E(); };

// ?rva004E7CEF@Rva004E7CEFTarget@@QAEXXZ @0x004E7CEF (39B): drops a count and,
// once it is no longer positive, resets the three members through unnamed
// calls (0x004E7C1C, 0x004E7BAF, then a tail jump to 0x004E551E).
class Rva004E7CEFTarget
{
public:
	void rva004E7CEF();

private:
	void *m_vtbl;
	int m_count;
	int m_08;
	Rva004E7C1CMember m_0C;
	Rva004E7BAFMember m_10;
	Rva004E551EMember m_1C;
};

void Rva004E7CEFTarget::rva004E7CEF()
{
	--m_count;
	if (m_count <= 0)
	{
		m_0C.rva004E7C1C();
		m_10.rva004E7BAF();
		m_1C.rva004E551E();
	}
}

class Rva004E7D1DPart
{
public:
	void rva004E7D1D();

private:
	Rva004E7CEFTarget *m_target;
};

void Rva004E7D1DPart::rva004E7D1D()
{
	m_target->rva004E7CEF();
}
