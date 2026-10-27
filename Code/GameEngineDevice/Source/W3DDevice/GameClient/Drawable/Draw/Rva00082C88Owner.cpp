// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00082C88@Rva00082C88Owner@@QAEXPAVW3DBoatWakeModelDraw@@@Z @0x00082C88
// 13B, the owner callback the rowed W3DBoatWakeModelDraw destructor
// (0x000D0B69) makes with itself. It forwards the module pointer by
// reference to the container at +0x58 through 0x00082536 (address-derived
// name). Neither the owner nor the container is identified.

class W3DBoatWakeModelDraw;

class Rva00082536Container
{
public:
	void rva00082536(W3DBoatWakeModelDraw *const &draw);
};

class Rva00082C88Owner
{
public:
	void rva00082C88(W3DBoatWakeModelDraw *draw);

private:
	char m_pad[0x58];
	Rva00082536Container m_container;
};

void Rva00082C88Owner::rva00082C88(W3DBoatWakeModelDraw *draw)
{
	m_container.rva00082536(draw);
}
