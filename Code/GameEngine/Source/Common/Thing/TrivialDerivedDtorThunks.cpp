// cl: /O1 /DNDEBUG /MD
//
// Six 5-byte destructors that are a single jump to their base destructor:
// the derived class adds nothing to destroy and its vptr store is dead, so
// MSVC 7.1 tail-jumps into the out-of-line base dtor. Each address comes from
// its existing symbols.csv pin; each base resolves to the row or pin at the
// jump target.
//
//   ??1W3DSailModelDraw@@UAE@XZ        0x000D08BE -> W3DScriptedModelDraw 0x000C79C9 (pin)
//   ??1RiderChangeContain@@UAE@XZ      0x0047E51B -> SiegeEngineContain   0x0047BF43 (row)
//   ??1LevelGrantSpecialPower@@UAE@XZ  0x004C2C76 -> Rva00451F45          0x00451F45 (pin)
//   ??1RebuildHoleExposeDie@@UAE@XZ    0x004867F9 -> DieModule            0x0045CE54 (row)
//   ??1CallHelpOnDamage@@UAE@XZ        0x004BB4D1 -> DamageModule         0x004B96CC (pin)
//   ??1Rva004D7B93@@UAE@XZ             0x004D7B93 -> ObjectModule         0x0049B47C (pin)
//
// The base class names come from those rows and pins; the layouts behind them
// are not modelled because none of these bodies touches a member.

class W3DScriptedModelDraw
{
public:
	virtual ~W3DScriptedModelDraw();
};

class __declspec(novtable) W3DSailModelDraw : public W3DScriptedModelDraw
{
public:
	virtual ~W3DSailModelDraw();
};

W3DSailModelDraw::~W3DSailModelDraw()
{
}

class SiegeEngineContain
{
public:
	virtual ~SiegeEngineContain();
};

class __declspec(novtable) RiderChangeContain : public SiegeEngineContain
{
public:
	virtual ~RiderChangeContain();
};

RiderChangeContain::~RiderChangeContain()
{
}

class Rva00451F45
{
public:
	virtual ~Rva00451F45();
};

class __declspec(novtable) LevelGrantSpecialPower : public Rva00451F45
{
public:
	virtual ~LevelGrantSpecialPower();
};

LevelGrantSpecialPower::~LevelGrantSpecialPower()
{
}

class DieModule
{
protected:
	virtual ~DieModule();
};

class __declspec(novtable) RebuildHoleExposeDie : public DieModule
{
public:
	virtual ~RebuildHoleExposeDie();
};

RebuildHoleExposeDie::~RebuildHoleExposeDie()
{
}

class DamageModule
{
public:
	virtual ~DamageModule();
};

class __declspec(novtable) CallHelpOnDamage : public DamageModule
{
public:
	virtual ~CallHelpOnDamage();
};

CallHelpOnDamage::~CallHelpOnDamage()
{
}

class ObjectModule
{
protected:
	virtual ~ObjectModule();
};

class __declspec(novtable) Rva004D7B93 : public ObjectModule
{
public:
	virtual ~Rva004D7B93();
};

Rva004D7B93::~Rva004D7B93()
{
}
