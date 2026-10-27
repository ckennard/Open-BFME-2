// cl: /O1 /DNDEBUG /MD /EHsc
// ??1AttributeModifierAuraUpdate@@UAE@XZ @0x0049B6DD 115B, address from the
// existing symbols.csv pin. Update-module destructor in the
// EmotionTrackerUpdateDtor.cpp shape (four vptr restores, then the rowed
// UpdateModule base dtor 0x0024A797). Body: when the object's template kind
// byte at +0x11B has bit 0x01 set, TheTerrainLogic (VA 0x00DFEC50) is given
// the object's position (+0x38), the module data's float at +0x1C and the
// object's +0x74 field through an unnamed member at 0x00282CFB
// (address-derived name).

typedef float Real;

struct Coord3D
{
	Real x, y, z;
};

struct ThingTemplate
{
	unsigned char m_pad[0x11B];
	unsigned char m_kind11B;
};

struct Object
{
	void *m_vtbl;
	const ThingTemplate *m_template;
	char m_pad08[0x38 - 0x08];
	Coord3D m_position;
	char m_pad44[0x74 - 0x44];
	int m_74;
};

struct AttributeModifierAuraUpdateModuleData
{
	char m_pad[0x1C];
	Real m_range;
};

class TerrainLogic
{
public:
	void rva00282CFB(const Coord3D *pos, Real range, int value);
};

extern TerrainLogic *TheTerrainLogic;

class Rva0049B47C004978A3
{
public:
	virtual ~Rva0049B47C004978A3();
protected:
	const AttributeModifierAuraUpdateModuleData *m_moduleData;
	Object *m_object;
};

class MiBase1004978A3
{
public:
	virtual void f1();
};

class PrimaryP004978A3 : public Rva0049B47C004978A3, public MiBase1004978A3
{
public:
	~PrimaryP004978A3() {}
};

class Rva0024A797_B2004978A3
{
public:
	virtual void f2();
private:
	char m_pad04[12];
};

class Rva0024A797 : public PrimaryP004978A3, public Rva0024A797_B2004978A3
{
public:
	virtual ~Rva0024A797();
};

class __declspec(novtable) SecondBase004978A3
{
public:
	virtual ~SecondBase004978A3() {}
};

class AttributeModifierAuraUpdate : public Rva0024A797, public SecondBase004978A3
{
public:
	virtual ~AttributeModifierAuraUpdate();
};

AttributeModifierAuraUpdate::~AttributeModifierAuraUpdate()
{
	Object *obj = m_object;
	const ThingTemplate *tmpl = obj->m_template;
	const AttributeModifierAuraUpdateModuleData *data = m_moduleData;
	if (tmpl->m_kind11B & 1)
		TheTerrainLogic->rva00282CFB(&obj->m_position, data->m_range, obj->m_74);
}
