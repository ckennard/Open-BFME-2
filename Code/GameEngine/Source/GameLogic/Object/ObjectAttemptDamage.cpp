// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
//
// Object::attemptDamage, retail 0x0029848E, 70 bytes, at the pin added with
// Object::kill (its only call there). From retail: when the object has status
// bit 0x48 (rowed Object::testStatus), the DamageInfo float at +0x28 is forced
// to 1.0; then a positive +0x28 queues a copy of the whole 0x7C-byte info on
// the object's list at +0x440 (rowed STLport list<BfmePod124>::push_back --
// BfmePod124 is that 124-byte record) and anything else goes straight to the
// unnamed handler at 0x002975AC. The status bit's name, the +0x28 field and
// the list's purpose are not proven; names are descriptive or address-derived.

enum ObjectStatusTypes
{
	OBJECT_STATUS_BIT_48 = 0x48
};

struct BfmePod124
{
	char m_pad00[0x28];
	float m_28;
	char m_pad2C[0x50];
};

class DamageInfo : public BfmePod124
{
};

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> > class list
	{
	public:
		void push_back(const T &value);
	private:
		void *m_node;
	};
}

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	void attemptDamage(DamageInfo *damageInfo);
private:
	void rva002975AC(DamageInfo *damageInfo);
	char m_pad[0x440];
	_STL::list<BfmePod124> m_queuedDamage;
};

void Object::attemptDamage(DamageInfo *damageInfo)
{
	if (testStatus(OBJECT_STATUS_BIT_48))
		damageInfo->m_28 = 1.0f;
	if (damageInfo->m_28 > 0.0f)
		m_queuedDamage.push_back(*damageInfo);
	else
		rva002975AC(damageInfo);
}
