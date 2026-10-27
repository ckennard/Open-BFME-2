// cl: /O1 /DNDEBUG /MD /GX-
//
// Two small Win32-resource destructors, both at existing symbols.csv pins,
// classes unidentified (address-derived names):
//   ??1Rva0040EDB@@UAE@XZ @0x00040EDB (29B): closes the kernel handle at +4 if
//     one is open (CloseHandle import) and clears it.
//   ??1Rva0040FE5@@UAE@XZ @0x00040FE5 (31B): a subclass that deletes the
//     critical section at +8 (DeleteCriticalSection import), sets the flag at
//     +0x20, then tail-jumps into the base destructor above.

extern "C" {
__declspec(dllimport) int __stdcall CloseHandle(void *handle);
__declspec(dllimport) void __stdcall DeleteCriticalSection(void *criticalSection);
}

struct Rva0040FE5CriticalSection
{
	unsigned char m_bytes[0x18];
};

class Rva0040EDB
{
public:
	virtual ~Rva0040EDB();

private:
	void *m_handle;
};

Rva0040EDB::~Rva0040EDB()
{
	if (m_handle)
	{
		CloseHandle(m_handle);
		m_handle = 0;
	}
}

class Rva0040FE5 : public Rva0040EDB
{
public:
	virtual ~Rva0040FE5();

private:
	Rva0040FE5CriticalSection m_criticalSection;
	bool m_20;
};

Rva0040FE5::~Rva0040FE5()
{
	DeleteCriticalSection(&m_criticalSection);
	m_20 = true;
}
