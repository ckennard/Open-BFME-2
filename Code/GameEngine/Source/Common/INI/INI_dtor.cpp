// cl: /O1 /EHsc /DNDEBUG /MD
//
// ??1INI@@QAE@XZ @0x0002CE5B (90B), address from the existing symbols.csv
// pin. ZH INI.cpp's destructor body is empty; retail only unwinds the
// members in reverse order: the AsciiString vector at +0x870 (the rowed
// vector dtor 0x0002CC70, pinned as ??1RvaVecAscii), the AsciiString at
// +0x86C, the polymorphic member at +0x838 (dtor 0x00601BF3, pinned under an
// address-derived name), and the AsciiString at +0x04. AsciiString's
// destructor inlines to the rowed StringBase<char>::releaseBuffer.

template <typename T> class StringBase
{
	friend class AsciiString;
private:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	~AsciiString() {}
};

class Rva00601BF3Member
{
public:
	~Rva00601BF3Member();
private:
	char m_data[0x34];
};

class RvaVecAscii
{
public:
	~RvaVecAscii();
private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class INI
{
public:
	~INI();

private:
	void *m_file;
	AsciiString m_filename;
	char m_pad08[0x838 - 0x08];
	Rva00601BF3Member m_838;
	AsciiString m_86C;
	RvaVecAscii m_870;
};

INI::~INI()
{
}
