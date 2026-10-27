// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1Rva0072AED@@UAE@XZ, retail 0x00072AED, 56 bytes, at the existing
// symbols.csv pin; class unidentified. A RefCountClass-derived holder: drop
// the reference to the object at +8 (inline ReleaseRef: Delete_This at zero),
// then the RefCountClass base's inline dtor restores its vtable 0x00BC650C.
// That base is spelled as in bfmedynamicvertexbuffer.cpp, which installs the
// same vtable.

class BfmeDynamicVBRefCount
{
public:
	virtual void DeleteThis();
	virtual ~BfmeDynamicVBRefCount() {}
	int references;
	void ReleaseRef() { --references; if (references == 0) DeleteThis(); }
};

class __declspec(novtable) Rva0072AED : public BfmeDynamicVBRefCount
{
public:
	virtual ~Rva0072AED();
private:
	BfmeDynamicVBRefCount *m_held;
};

Rva0072AED::~Rva0072AED()
{
	if (m_held)
		m_held->ReleaseRef();
}
