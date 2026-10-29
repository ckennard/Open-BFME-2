// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1Rva006422F@@UAE@XZ @0x0006422F (90B), at the existing symbols.csv pin;
// class unidentified. Own vptr; an unnamed cleanup call (0x00063C48, pinned
// opaque); then every node of the list headed at +0x0C (next link at +0xE0)
// is freed with ::delete (flag-0 virtual dtor, then global operator delete);
// then the pinned ObjectModule base dtor (0x0049B47C).

class Rva006422FNode
{
public:
	virtual ~Rva006422FNode();
	char m_pad04[0xE0 - 0x04];
	Rva006422FNode *m_next;
};

class ObjectModule
{
protected:
	virtual ~ObjectModule();
	char m_pad04[0x0C - 0x04];
};

class Rva006422F : public ObjectModule
{
public:
	virtual ~Rva006422F();
private:
	void rva00063C48();

	Rva006422FNode *m_first;
};

Rva006422F::~Rva006422F()
{
	rva00063C48();
	for (Rva006422FNode *node = m_first; node; )
	{
		Rva006422FNode *next = node->m_next;
		::delete node;
		node = next;
	}
}
