// cl: /O1 /DNDEBUG /MD
//
// Two MeshModelClass teardown helpers at their existing symbols.csv pins,
// both called from the rowed MeshModelClass dtor and Reset. From retail:
//   0x00199FA5 39B  cdecl: if the material descriptor's +0xC is set, clear
//                   the +0xB8 pass slot (rowed Set_Single_Rva0015A800 with
//                   0, 0) and an unnamed second slot (0x0015D5B0 with 0),
//                   returning whether it did
//   0x001732E2 40B  delete the model's +0xBC gap filler (dtor 0x0018C57C,
//                   scalar operator delete) and clear the slot; the context
//                   object is unused
// Identities and layouts beyond these offsets are unproven; names come from
// the pins.

class MeshMatDescClass
{
public:
	void Set_Single_Rva0015A800(void *entry, int pass);
	void rva0015D5B0(int pass);
private:
	char m_pad[0xC];
	void *m_C;
	friend bool __cdecl Rva00199FA5TeardownMeshMatDescRenderers(MeshMatDescClass *matdesc);
};

bool __cdecl Rva00199FA5TeardownMeshMatDescRenderers(MeshMatDescClass *matdesc)
{
	if (matdesc->m_C == 0)
		return false;
	matdesc->Set_Single_Rva0015A800(0, 0);
	matdesc->rva0015D5B0(0);
	return true;
}

class Rva0018C57CGapFiller
{
public:
	~Rva0018C57CGapFiller();
};

class MeshModelClass
{
public:
	char m_pad[0xBC];
	Rva0018C57CGapFiller *m_gapFiller;
};

class Rva00DF6F94GapFillerContext
{
public:
	void DeleteModelGapFiller(MeshModelClass *model);
};

void Rva00DF6F94GapFillerContext::DeleteModelGapFiller(MeshModelClass *model)
{
	delete model->m_gapFiller;
	model->m_gapFiller = 0;
}
