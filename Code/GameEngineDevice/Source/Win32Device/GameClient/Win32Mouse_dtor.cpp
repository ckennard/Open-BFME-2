// cl: /O1 /DNDEBUG /MD /GX-
//
// ??1Win32Mouse@@UAE@XZ, retail 0x000419E3, 18 bytes, at the existing
// ??1Rva00419E3 pin (its scalar deleting dtor 0x00041B69 is rowed). ZH
// Win32Mouse.cpp, verbatim: clear TheWin32Mouse (VA 0x00DE1B18, defined in
// WinMain.cpp), then tail-jump to Mouse::~Mouse. That base dtor is rowed at
// 0x001EE3DE as ??1Rva001EE3DE, next to the pinned Mouse::reset, and is
// pinned here under its ZH name.

class Mouse
{
public:
	virtual ~Mouse();
};

class Win32Mouse : public Mouse
{
public:
	virtual ~Win32Mouse();
};

extern Win32Mouse *TheWin32Mouse;

Win32Mouse::~Win32Mouse()
{
	// remove our global reference
	TheWin32Mouse = 0;
}
