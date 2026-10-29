// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1W3DSnowManager@@UAE@XZ, retail 0x000938C4, 75 bytes, at the existing
// ??1Rva00938C4 pin. ZH W3DSnow.cpp: ReleaseResources() (rowed, 0x000931D3),
// then the SnowManager base (rowed dtor 0x0020156B). BFME 2 adds a texture
// reference holder at +0x78 whose destructor releases it through the rowed
// TextureClass::Release_Ref (0x0061ED10).

class TextureClass
{
public:
	void Release_Ref();
};

class TextureRefHolder
{
public:
	~TextureRefHolder()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
private:
	TextureClass *m_texture;
};

class SnowManager
{
public:
	virtual ~SnowManager();
private:
	char m_pad04[0x78 - 0x04];
};

class W3DSnowManager : public SnowManager
{
public:
	virtual ~W3DSnowManager();
	void ReleaseResources(void);

private:
	TextureRefHolder m_texture;
};

W3DSnowManager::~W3DSnowManager()
{
	ReleaseResources();
}
