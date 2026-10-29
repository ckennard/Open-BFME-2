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
// Each clear is the STLport _Rb_tree::clear body: when the tree is not
// empty, erase from the root (an out-of-line _M_erase per map, pinned at the
// call target), then reset the header links and the node count. From retail,
// clear -> erase: 0x00206EC7 -> 0x00206593, then clears every 0x29 bytes
// and erases every 0x35.
// Key and value types are not modelled; names are address-derived.

void __cdecl free(void *block);

struct MapNode
{
	int m_color;
	MapNode *m_parent;
	MapNode *m_left;
	MapNode *m_right;
};

struct MapHeaderHolder
{
	MapNode *m_header;
	int m_nodeCount;
	~MapHeaderHolder()
	{
		if (m_header)
			free(m_header);
	}
};

#define RVA_MAP(map, clearRva, eraseRva) \
	class map : public MapHeaderHolder \
	{ \
	public: \
		~map(); \
		void clearRva(); \
		void eraseRva(MapNode *node); \
	}; \
	map::~map() \
	{ \
		clearRva(); \
	} \
	void map::clearRva() \
	{ \
		if (m_nodeCount != 0) \
		{ \
			eraseRva(m_header->m_parent); \
			m_header->m_left = m_header; \
			m_header->m_parent = 0; \
			m_header->m_right = m_header; \
			m_nodeCount = 0; \
		} \
	}

RVA_MAP(Rva002075F3Map, rva00206EC7, rva00206593)
RVA_MAP(Rva00207630Map, rva00206EF0, rva002065C8)
RVA_MAP(Rva0020766DMap, rva00206F19, rva002065FD)
RVA_MAP(Rva002076AAMap, rva00206F42, rva00206632)
RVA_MAP(Rva002076E7Map, rva00206F6B, rva00206667)
RVA_MAP(Rva00207724Map, rva00206F94, rva0020669C)
RVA_MAP(Rva00207761Map, rva00206FBD, rva002066D1)
RVA_MAP(Rva0020779EMap, rva00206FE6, rva00206706)
