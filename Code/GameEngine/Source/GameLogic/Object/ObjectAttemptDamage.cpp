// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
//
// Object::attemptDamage, retail 0x0029848E, 70 bytes, at the pin added with
// Object::kill (its only call there). From retail: when the object has status
// bit 0x48 (rowed Object::testStatus), the DamageInfo float at +0x28 is forced
// to 1.0; then a positive +0x28 queues a copy of the whole 0x7C-byte info on
// the object's list at +0x440 (rowed STLport list<BfmePod124>::push_back --
// BfmePod124 is that 124-byte record) and anything else goes straight to the
// unnamed handler at 0x002975AC.
//
// That handler (0x002975AC, 102 bytes): unless flag bit 0 at +0x438 is set,
// the body module at +0x254 gets the info through its first virtual slot
// (ZH's BodyModuleInterface::attemptDamage); then the info goes to 0x00296065
// when the flag is clear or the info's +0x40 float is positive; finally, if
// the +0x84 object exists and has its +0x43C byte set, 0x0027295B is called
// on it with the result of 0x00290FC9 on this. That call (0x0027295B,
// 22 bytes) forwards the value to virtual slot 26 of the object held through
// the holder at +0x14C, when there is one. The status bit's name, the +0x28 field and
// the list's purpose are not proven; names are descriptive or address-derived.

enum ObjectStatusTypes
{
	OBJECT_STATUS_BIT_48 = 0x48
};

struct BfmePod124
{
	char m_pad00[0x28];
	float m_28;
	char m_pad2C[0x14];
	float m_40;
	char m_pad44[0x38];
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

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};

class Rva0027295BListener
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual void notify(int value);
};

struct Rva0027295BHolder
{
	Rva0027295BListener *m_listener;
};

class Rva0027295BOwner
{
public:
	void rva0027295B(int value);
	char m_pad[0x14C];
	Rva0027295BHolder *m_holder;
	char m_pad150[0x43C - 0x150];
	bool m_43C;
};

void Rva0027295BOwner::rva0027295B(int value)
{
	Rva0027295BHolder *holder = m_holder;
	if (holder->m_listener != 0)
		holder->m_listener->notify(value);
}

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	void attemptDamage(DamageInfo *damageInfo);
private:
	void rva002975AC(DamageInfo *damageInfo);
	void rva00296065(DamageInfo *damageInfo);
	int rva00290FC9();
	char m_pad000[0x84];
	Rva0027295BOwner *m_84;
	char m_pad088[0x254 - 0x88];
	BodyModuleInterface *m_bodyModule;
	char m_pad258[0x438 - 0x258];
	unsigned char m_438;
	char m_pad439[7];
	_STL::list<BfmePod124> m_queuedDamage;
};

void Object::rva002975AC(DamageInfo *damageInfo)
{
	if (!(m_438 & 1))
	{
		BodyModuleInterface *body = m_bodyModule;
		if (body)
			body->attemptDamage(damageInfo);
	}
	if (!(m_438 & 1) || damageInfo->m_40 > 0.0f)
		rva00296065(damageInfo);
	Rva0027295BOwner *owner = m_84;
	if (owner && owner->m_43C)
		owner->rva0027295B(rva00290FC9());
}

void Object::attemptDamage(DamageInfo *damageInfo)
{
	if (testStatus(OBJECT_STATUS_BIT_48))
		damageInfo->m_28 = 1.0f;
	if (damageInfo->m_28 > 0.0f)
		m_queuedDamage.push_back(*damageInfo);
	else
		rva002975AC(damageInfo);
}
