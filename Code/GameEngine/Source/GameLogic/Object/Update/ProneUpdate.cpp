// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ZH ProneUpdate.cpp update and goProne, verbatim, at the retail addresses
// after the rowed ProneUpdate ctor (0x0049FF06):
//   0x0049FFA0 update  (25B)
//   0x0049FFB9 goProne (62B, address from the symbols.csv pin)
// m_proneFrames is at +0x20, and update enters through the +0x10
// UpdateModuleInterface sub-object, so it reads +0x10 and adjusts this by
// -0x10 for stopProneEffects. The damage amount is DamageInfo +0x70, the
// frames ratio ProneUpdateModuleData +0x08.
//
// startProneEffects (0x0049FF50) and stopProneEffects (0x0049FF78) are
// pinned, not defined: these call sites are their only ZH callers. BFME 2's
// bodies toggle bit 0x80 of the object byte at +0x114, refresh through
// 0x0028AE6D when it changes, then set or clear object status 5. No spelling
// tried reproduces retail's two separate [esi+0x114] memory operands; MSVC
// 7.1 /O1 hoists the address into a register.

typedef int Int;
typedef float Real;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_PRONE_EFFECTS = 5
};

class Thing;
class ModuleData;

class Object;

class DamageInfo
{
public:
	char m_pad[0x70];
	Real m_actualDamageDealt;
};

struct ProneUpdateModuleData
{
	char m_pad[8];
	Real m_damageToFramesRatio;
};

class Rva0049B47C004978A3
{
public:
	virtual ~Rva0049B47C004978A3();
protected:
	const ProneUpdateModuleData *m_moduleData;
	Object *m_object;
};

class MiBase1004978A3
{
public:
	virtual void f1();
};

class PrimaryP004978A3 : public Rva0049B47C004978A3, public MiBase1004978A3
{
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
private:
	char m_pad04[12];
};

class UpdateModule : public PrimaryP004978A3, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
};

class ProneUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void goProne(const DamageInfo *damageInfo);

protected:
	void startProneEffects();
	void stopProneEffects();

private:
	Object *getObject() const { return m_object; }
	const ProneUpdateModuleData *getProneUpdateModuleData() const { return m_moduleData; }

	Int m_proneFrames;
};

UpdateSleepTime ProneUpdate::update(void)
{
	if (m_proneFrames > 0)
	{
		m_proneFrames--;
		if (m_proneFrames == 0)
			stopProneEffects();
	}
	return UPDATE_SLEEP_NONE;
}

void ProneUpdate::goProne(const DamageInfo *damageInfo)
{
	Bool wasProne = (m_proneFrames > 0);
	Int damageTaken = damageInfo->m_actualDamageDealt;
	m_proneFrames += damageTaken * getProneUpdateModuleData()->m_damageToFramesRatio;

	if (!wasProne && (m_proneFrames > 0))
		startProneEffects();
}
