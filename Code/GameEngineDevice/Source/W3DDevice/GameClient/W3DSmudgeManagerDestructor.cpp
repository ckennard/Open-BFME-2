// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1W3DSmudgeManager@@UAE@XZ, retail 0x000A6454, 56 bytes, at the existing
// ??1Rva00A6454 pin. ZH W3DSmudge.cpp, verbatim: release the device
// resources through the rowed ReleaseResources (0x000A6135), then the rowed
// SmudgeManager dtor (0x002D29F7). The vtable is the one the rowed ctor
// (W3DSmudgeManagerConstructor.cpp) installs.

class SmudgeManager
{
public:
	virtual ~SmudgeManager();
private:
	char m_pad[0x20];
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	virtual ~W3DSmudgeManager();
	virtual void ReleaseResources(void);
};

W3DSmudgeManager::~W3DSmudgeManager()
{
	ReleaseResources();
}
