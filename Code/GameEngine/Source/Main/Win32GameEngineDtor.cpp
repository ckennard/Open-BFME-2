// cl: /O1 /DNDEBUG /MD /GX-
//
// ??1Win32GameEngine@@UAE@XZ, retail 0x00041E9F, 26 bytes, at the existing
// ??1Rva0041E9F pin (its scalar deleting dtor 0x00042105 is rowed). ZH
// Win32GameEngine.cpp, verbatim: restore the error mode the rowed ctor
// (0x00041D41) saved at +0x60, then the rowed GameEngine dtor (0x00225B9B).

extern "C" __declspec(dllimport) unsigned int __stdcall SetErrorMode(unsigned int mode);

class GameEngine
{
public:
	virtual ~GameEngine();

private:
	char m_padAfterVtable[0x60 - 4];
};

class Win32GameEngine : public GameEngine
{
public:
	virtual ~Win32GameEngine();

private:
	unsigned int m_previousErrorMode;
};

Win32GameEngine::~Win32GameEngine()
{
	SetErrorMode(m_previousErrorMode);
}
