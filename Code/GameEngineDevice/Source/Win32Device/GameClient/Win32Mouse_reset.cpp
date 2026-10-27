// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?reset@Win32Mouse@@UAEXXZ @0x000419F5 (17B), address from the existing
// symbols.csv pin. ZH Win32Mouse::reset extends Mouse::reset (pinned at
// 0x001EE4DC under that name); BFME 2 then sets the Mouse byte at +0x4F9C,
// whose meaning is unrecovered.

class Mouse
{
public:
	virtual void reset(void);

protected:
	char m_pad04[0x4F9C - 4];
	unsigned char m_rva4F9C;
	char m_pad4F9D[0x5010 - 0x4F9D];
};

class Win32Mouse : public Mouse
{
public:
	virtual void reset(void);
};

void Win32Mouse::reset(void)
{
	// extend
	Mouse::reset();
	m_rva4F9C = 1;
}
