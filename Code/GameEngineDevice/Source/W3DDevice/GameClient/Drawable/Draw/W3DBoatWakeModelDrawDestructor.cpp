// cl: /O1 /DNDEBUG /MD /EHsc
// ??1W3DBoatWakeModelDraw@@UAE@XZ @0x000D0B69 90B, address from the existing
// symbols.csv pin. BFME 2 draw-module destructor in the W3DLightDraw shape
// (W3DLightDrawDestructor.cpp): own vtable 0x00BCDD70, then the DrawModule
// base vtable 0x00BC9690 and the folded base dtor 0x0049B47C (pinned
// ??1DrawableModule@@MAE@XZ). Body: if the +0x18 owner is set, it is told
// about this module through an unnamed member at 0x00082C88 (address-derived
// name); then the render object at +0x14 is released and cleared.

class RefCountClass
{
public:
	virtual void Delete_This();

	void Release_Ref() const
	{
		--m_numRefs;
		if (m_numRefs == 0)
			const_cast<RefCountClass *>(this)->Delete_This();
	}

protected:
	virtual ~RefCountClass();

private:
	mutable int m_numRefs; // +0x04
};

class RenderObjClass : public RefCountClass
{
protected:
	virtual ~RenderObjClass();
};

class W3DBoatWakeModelDraw;

class Rva00082C88Owner
{
public:
	void rva00082C88(W3DBoatWakeModelDraw *draw);
};

class DrawableModule
{
protected:
	virtual ~DrawableModule();

	void *m_moduleData; // +0x04
	void *m_drawable; // +0x08
};

class DrawModule : public DrawableModule
{
protected:
	virtual ~DrawModule() {}
};

class W3DBoatWakeModelDraw : public DrawModule
{
public:
	virtual ~W3DBoatWakeModelDraw();

private:
	int m_0C;
	int m_10;
	RenderObjClass *m_renderObject; // +0x14
	Rva00082C88Owner *m_owner; // +0x18
};

W3DBoatWakeModelDraw::~W3DBoatWakeModelDraw()
{
	if (m_owner)
		m_owner->rva00082C88(this);
	if (m_renderObject)
	{
		m_renderObject->Release_Ref();
		m_renderObject = 0;
	}
}
