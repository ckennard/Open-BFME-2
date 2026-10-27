// cl: /O1 /DNDEBUG /MD
//
// ?notifyScriptEngine@SpecialPowerCompletionDie@@QAEXXZ @0x00486B01 (55B),
// address from the existing symbols.csv pin. ZH SpecialPowerCompletionDie.cpp,
// verbatim: when a creator is recorded (+0x14), tell TheScriptEngine (VA
// 0x00DFE16C) which player completed which special power. The template's
// getName reads m_name (+0x10) of its final override through the rowed
// Overridable::friend_getFinalOverride. getControllingPlayer is rowed, and
// ScriptEngine::notifyOfCompletedSpecialPower (0x00357EDF) is pinned under
// its ZH name.

typedef int Int;

enum ObjectID
{
	INVALID_ID = 0
};

class AsciiString
{
	void *m_data;
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class SpecialPowerTemplate : public Overridable
{
public:
	const AsciiString &getName() const
	{
		return static_cast<const SpecialPowerTemplate *>(friend_getFinalOverride())->m_name;
	}

private:
	char m_pad[0x10];
	AsciiString m_name;
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	char m_pad[0x54];
	Int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class ScriptEngine
{
public:
	void notifyOfCompletedSpecialPower(Int playerIndex, const AsciiString &specialPowerName, ObjectID sourceObj);
};

extern ScriptEngine *TheScriptEngine;

struct SpecialPowerCompletionDieModuleData
{
	char m_pad[0x38];
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

class SpecialPowerCompletionDie
{
public:
	void notifyScriptEngine(void);

private:
	Object *getObject() const { return m_object; }
	const SpecialPowerCompletionDieModuleData *getSpecialPowerCompletionDieModuleData() const
	{
		return m_moduleData;
	}

	void *m_vtbl;
	const SpecialPowerCompletionDieModuleData *m_moduleData;
	Object *m_object;
	char m_pad0C[0x14 - 0x0C];
	ObjectID m_creatorID;
};

void SpecialPowerCompletionDie::notifyScriptEngine(void)
{
	if (m_creatorID != INVALID_ID)
	{
		TheScriptEngine->notifyOfCompletedSpecialPower(
			getObject()->getControllingPlayer()->getPlayerIndex(),
			getSpecialPowerCompletionDieModuleData()->m_specialPowerTemplate->getName(),
			m_creatorID);
	}
}
