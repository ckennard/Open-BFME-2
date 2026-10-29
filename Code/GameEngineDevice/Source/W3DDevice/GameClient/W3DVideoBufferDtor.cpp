// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1W3DVideoBuffer@@UAE@XZ, retail 0x0007280A, 92 bytes, at the existing
// ??1Rva007280A pin; the vtable it restores (0x00BC64D8) is the one the rowed
// ctor (W3DVideoBufferCtorBfme.cpp, 0x000726B0) installs. ZH's destructor is
// free(); BFME 2 calls the rowed state reset rva00072583 instead, then hands
// this to TheDisplay through an unnamed member (0x000480ED, the counterpart of the
// ctor's registration), then unwinds the one-element state array at +0x2C
// (element dtor 0x0007251F). The VideoBuffer base dtor is inline and
// restores 0x00BC64B0. Layout follows the ctor TU.

class Rva00739C70State
{
public:
	~Rva00739C70State();
private:
	char m_data[0x14];
};

class VideoBuffer;

class Display
{
public:
	void rva000480ED(VideoBuffer *buffer);
};

extern Display *TheDisplay;

class VideoBuffer
{
public:
	virtual ~VideoBuffer() {}
protected:
	char m_pad04[0x2C - 0x04];
};

class W3DVideoBuffer : public VideoBuffer
{
public:
	virtual ~W3DVideoBuffer();
	void rva00072583();

private:
	Rva00739C70State m_states[1];
	Rva00739C70State *m_state_40;
	Rva00739C70State *m_state_44;
	bool m_flag_48;
	bool m_flag_49;
	bool m_flag_4a;
};

W3DVideoBuffer::~W3DVideoBuffer()
{
	rva00072583();
	if (TheDisplay)
		TheDisplay->rva000480ED(this);
}
