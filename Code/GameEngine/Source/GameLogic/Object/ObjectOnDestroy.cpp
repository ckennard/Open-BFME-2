// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// ?onDestroy@Object@@QAEXXZ @0x0028FC1D (98B), address from the existing
// symbols.csv pin. ZH Object::onDestroy (BFME 1 donor Object.cpp:789): say
// goodbye to the container, then run onDelete on every behavior module.
//
// BFME 2 differences, read from the retail body:
//  * getContain() is the inline cached ContainModuleInterface at +0x250 and
//    removeFromContain(this, false) is its slot 0xA4.
//  * Before the behaviors run it calls an unnamed Object helper at 0x0028DAB9,
//    then calls an unnamed member of the object at +0x84 with (i, true) for
//    i = 1..8. Both callees are opaque here; their names are address-derived.
//  * m_behaviors is at +0x244; onDelete is behavior slot 0x20.
// The donor's trailing handlePartitionCellMaintenance call is absent.

typedef bool Bool;
typedef int Int;

class Object;

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6C(); virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7C(); virtual void slot80();
	virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98();
	virtual void slot9C(); virtual void slotA0();
	virtual void removeFromContain(Object *obj, Bool exposeStealthUnits = false);
};

class BehaviorModule
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void onDelete();
};

class Rva00271BCCOwner
{
public:
	void rva00271BCC(Int index, Bool flag);
};

class Object
{
public:
	void onDestroy();
	ContainModuleInterface *getContain() const { return m_contain; }

private:
	void rva0028DAB9();

	char m_pad00[0x84];
	Rva00271BCCOwner *m_rva84;
	char m_pad88[0x244 - 0x88];
	BehaviorModule **m_behaviors;
	char m_pad248[0x250 - 0x248];
	ContainModuleInterface *m_contain;
	char m_pad254[0x274 - 0x254];
	Object *m_containedBy;
};

void Object::onDestroy()
{
	if (m_containedBy && m_containedBy->getContain())
	{
		m_containedBy->getContain()->removeFromContain(this);
	}

	rva0028DAB9();

	Rva00271BCCOwner *owner = m_rva84;
	if (owner)
	{
		for (Int i = 1; i < 9; ++i)
			owner->rva00271BCC(i, true);
	}

	for (BehaviorModule **b = m_behaviors; *b; ++b)
	{
		(*b)->onDelete();
	}
}
