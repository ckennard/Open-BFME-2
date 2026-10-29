// cl: /O1 /DNDEBUG /MD /GX-
//
// Object::kill, retail 0x002984D4, 67 bytes, at its existing symbols.csv pin
// (read from the REL32 in SpawnBehavior::onSpawnDeath; a BFME1-donor name).
// Same logic as the ZH/BFME1 Object::kill: build a DamageInfo for the given
// damage and death types with no source, the owner's full max health as the
// amount and the kill flag set, and hand it to attemptDamage.
//
// Target evidence, separately from the donor: the 0x7C-byte local is built by
// the shared ctor at 0x00263895 (pinned there as Rva00263895Member::init and
// as the AICommandParmsTail ctor); retail writes the source id at +8, the
// damage type at +0x10, the death type at +0x1C, the amount at +0x20 and the
// kill byte at +0x24. The amount comes from virtual slot 6 (a float) of the
// object at +0x254, read here as the body module's max health per the donor;
// attemptDamage is the call at 0x0029848E. Neither the +0x254 field name nor
// the DamageInfo field names are independently proven.

enum DamageType;
enum DeathType;
enum ObjectID
{
	INVALID_ID = 0
};

class DamageInfo
{
public:
	DamageInfo();
	char m_pad00[8];
	ObjectID m_sourceID;
	int m_pad0C;
	DamageType m_damageType;
	char m_pad14[8];
	DeathType m_deathType;
	float m_amount;
	bool m_kill;
	char m_pad25[0x57];
};

class BodyModuleInterface
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual float getMaxHealth() const;
};

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);
	void attemptDamage(DamageInfo *damageInfo);
private:
	char m_pad[0x254];
	BodyModuleInterface *m_bodyModule;
};

void Object::kill(DamageType damageType, DeathType deathType)
{
	DamageInfo damageInfo;
	damageInfo.m_damageType = damageType;
	damageInfo.m_deathType = deathType;
	damageInfo.m_sourceID = INVALID_ID;
	damageInfo.m_amount = m_bodyModule->getMaxHealth();
	damageInfo.m_kill = true;
	attemptDamage(&damageInfo);
}
