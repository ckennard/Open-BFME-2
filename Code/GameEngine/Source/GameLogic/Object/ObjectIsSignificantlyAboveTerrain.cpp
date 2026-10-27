// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?isSignificantlyAboveTerrain@Object@@QBE_NXZ @0x0030ADDC (12B, address from
// the existing symbols.csv pin) and its float overload at 0x0030AD8B (60B,
// the wrapper's only callee). ZH's predicate is
// getHeightAboveTerrain() > -(3 * TheGlobalData->m_gravity). BFME 2 adds a
// height offset, scales gravity by -9, and first rejects objects whose
// template kind byte at +0x11F has bit 0x01 or 0x80 set (the kinds are not
// identified). getHeightAboveTerrain is the rowed Thing body at 0x0030A12D.
// TheGlobalData is VA 0x00DFE758 with gravity at +0xC4.

typedef float Real;
typedef bool Bool;

struct ThingTemplate
{
	unsigned char m_pad[0x11F];
	unsigned char m_kind11F;
};

struct GlobalData
{
	unsigned char m_pad[0xC4];
	Real m_gravity;
};

extern GlobalData *TheGlobalData;

class Thing
{
public:
	Real getHeightAboveTerrain() const;

protected:
	void *m_vtbl;
	const ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	Bool isSignificantlyAboveTerrain() const;
	Bool isSignificantlyAboveTerrain(Real heightOffset) const;
};

Bool Object::isSignificantlyAboveTerrain(Real heightOffset) const
{
	if ((m_template->m_kind11F & 0x81) == 0)
		return getHeightAboveTerrain() + heightOffset > TheGlobalData->m_gravity * -9.0f;
	return false;
}

Bool Object::isSignificantlyAboveTerrain() const
{
	return isSignificantlyAboveTerrain(0.0f);
}
