// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD
//
// ??0BattlePlanUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00497ED0
// (263B), address from the existing symbols.csv pin. ZH BattlePlanUpdate.cpp
// constructor (BFME 1 donor, same file): zero the plan state, then build the
// bonuses record with unit scalars and the module data's valid/invalid kind
// masks.
//
// Target facts. The base call is the rowed UpdateModule ctor (0x00253390).
// Retail then installs the four vptrs (+0, +0x0C, +0x10, +0x20) that the
// rowed destructor at 0x004978A3 (??1Rva004978A3) restores, after the +0x20
// interface's own inline vptr (0x00C6F248, the rowed Rva00C6F248Iface). The
// sixteen 4-byte members at +0x44 are built through the EH vector ctor with
// ctor 0x00326BE6 and dtor 0x0010F149, the same element the destructor
// tears down. The 0x4C bonuses record is the rowed Rva002AA14DBonuses.
// Structural inference: the scalar fields follow ZH's order, which retail's
// store order matches (+0x30, +0x24, +0x28, +0x2C, +0x34, +0x3C, +0x3D). The
// +0x84 member starts at 1 and is the handle the destructor releases.
//
// The bonuses ctor is declared throw(): retail's new-expression has no EH
// state for freeing the record if construction throws, and the rowed ctor
// only builds two kind masks.

class Thing;
class ModuleData;

struct BfmeStringTailRecord156
{
	BfmeStringTailRecord156();
	~BfmeStringTailRecord156();
	int m_data;
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

	unsigned char m_data[0x1C];
};

class Rva002AA14DBonuses
{
public:
	Rva002AA14DBonuses() throw();

	float m_armorScalar;
	int m_bombardment;
	int m_searchAndDestroy;
	int m_holdTheLine;
	float m_sightRangeScalar;
	Rva0024C7B3Member m_validKindOf;
	Rva0024C7B3Member m_invalidKindOf;
};

struct BattlePlanUpdateModuleData
{
	unsigned char m_pad[0x54];
	Rva0024C7B3Member m_validMemberKindOf;
	Rva0024C7B3Member m_invalidMemberKindOf;
};

class Rva0049B47C004978A3
{
public:
	virtual ~Rva0049B47C004978A3();
private:
	char m_pad04[8];
};

class MiBase1004978A3
{
public:
	virtual void f1();
};

class PrimaryP004978A3 : public Rva0049B47C004978A3, public MiBase1004978A3
{
};

class Rva0024A797_B2004978A3
{
public:
	virtual void f2();
private:
	char m_pad04[12];
};

class UpdateModule : public PrimaryP004978A3, public Rva0024A797_B2004978A3
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
};

class Rva00C6F248Iface
{
public:
	virtual void m_iface() = 0;
};

class BattlePlanUpdate : public UpdateModule, public Rva00C6F248Iface
{
public:
	BattlePlanUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~BattlePlanUpdate();
	virtual void m_iface();

private:
	const BattlePlanUpdateModuleData *getBattlePlanUpdateModuleData() const
	{
		return *reinterpret_cast<const BattlePlanUpdateModuleData * const *>(
			reinterpret_cast<const char *>(this) + 4);
	}

	int m_currentPlan;          // +0x24
	int m_desiredPlan;          // +0x28
	int m_planAffectingArmy;    // +0x2C
	int m_status;               // +0x30
	unsigned int m_nextReadyFrame; // +0x34
	void *m_specialPowerModule; // +0x38
	bool m_invalidSettings;     // +0x3C
	bool m_centeringTurret;     // +0x3D
	Rva002AA14DBonuses *m_bonuses; // +0x40
	BfmeStringTailRecord156 m_strings[0x10]; // +0x44
	int m_84;                   // +0x84
	unsigned int m_visionObjectID; // +0x88
};

BattlePlanUpdate::BattlePlanUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	  m_bonuses(0),
	  m_84(1)
{
	const BattlePlanUpdateModuleData *data = getBattlePlanUpdateModuleData();

	m_status = 0;
	m_currentPlan = 0;
	m_desiredPlan = 0;
	m_planAffectingArmy = 0;
	m_nextReadyFrame = 0;
	m_invalidSettings = false;
	m_centeringTurret = false;

	m_bonuses = new Rva002AA14DBonuses;
	m_bonuses->m_armorScalar = 1.0f;
	m_bonuses->m_sightRangeScalar = 1.0f;
	m_bonuses->m_bombardment = 0;
	m_bonuses->m_searchAndDestroy = 0;
	m_bonuses->m_holdTheLine = 0;
	m_bonuses->m_validKindOf = data->m_validMemberKindOf;
	m_bonuses->m_invalidKindOf = data->m_invalidMemberKindOf;

	m_visionObjectID = 0;
	m_specialPowerModule = 0;
}
