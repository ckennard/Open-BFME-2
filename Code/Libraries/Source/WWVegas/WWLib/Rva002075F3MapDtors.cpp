// cl: /O1 /G7 /EHsc /MD
//
// The eight ScriptEngine map-member destructors (+0x190A0 .. +0x190F4) at
// their existing ??1Rva00XXXXMap symbols.csv pins. Each has the STLport
// _Rb_tree destructor shape: clear the tree (an out-of-line clear per map,
// pinned at the call target), then the inline base destructor frees the
// header node through the C++-declared free; the clear runs in EH state 0 so
// the base still frees the header if it throws. From retail, map -> clear:
//   0x002075F3 -> 0x00206EC7   0x00207630 -> 0x00206EF0
//   0x0020766D -> 0x00206F19   0x002076AA -> 0x00206F42
//   0x002076E7 -> 0x00206F6B   0x00207724 -> 0x00206F94
//   0x00207761 -> 0x00206FBD   0x0020779E -> 0x00206FE6
// Key and value types are not modelled; names are address-derived.

void __cdecl free(void *block);

struct MapHeaderHolder
{
	void *m_header;
	~MapHeaderHolder()
	{
		if (m_header)
			free(m_header);
	}
};

#define RVA_MAP(map, clearRva) \
	class map : public MapHeaderHolder \
	{ \
	public: \
		~map(); \
		void clearRva(); \
	}; \
	map::~map() \
	{ \
		clearRva(); \
	}

RVA_MAP(Rva002075F3Map, rva00206EC7)
RVA_MAP(Rva00207630Map, rva00206EF0)
RVA_MAP(Rva0020766DMap, rva00206F19)
RVA_MAP(Rva002076AAMap, rva00206F42)
RVA_MAP(Rva002076E7Map, rva00206F6B)
RVA_MAP(Rva00207724Map, rva00206F94)
RVA_MAP(Rva00207761Map, rva00206FBD)
RVA_MAP(Rva0020779EMap, rva00206FE6)
