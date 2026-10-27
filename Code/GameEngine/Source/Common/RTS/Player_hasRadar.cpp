// cl: /O1 /GX /DNDEBUG /MD
//
// ?hasRadar@Player@@QBE_NXZ, retail 0x002AA08E, 35 bytes. Dedicated TU.
//
// BFME1 Player::hasRadar logic verbatim
// (reference/open-bfme-1/Code/GameEngine/Source/Common/RTS/Player.cpp:4034):
// disabled plus zero disable-proof count denies radar, otherwise the radar
// count decides. BFME2 keeps the radar fields at +0xA0/+0xA4/+0xA8.

typedef bool Bool;

class AsciiString
{
	void *m_data;
};

// BFME 2's audio event (0x88 bytes on this frame): the rowed virtual dtor at 0x002D9A43 and
// the (name, owner) ctor at 0x002D97D6 that ZH spells
// AudioEventRTS(const AsciiString &, ObjectID). The setter at 0x0033F15D
// stores +0x6C, ZH setPlayerIndex. Named after the record the dtor row uses.
class BfmeStringTailRecord144
{
public:
	BfmeStringTailRecord144(const AsciiString &eventName, int ownerID);
	virtual ~BfmeStringTailRecord144();
	void setPlayerIndex(int playerIndex);
private:
	char m_data[0x84];
};

struct MiscAudio
{
	char m_pad[0x0C];
	AsciiString m_radarOnlineSound;
	AsciiString m_radarOfflineSound;
};

class AudioManager
{
public:
	virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0C();
	virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1C();
	virtual void f20(); virtual void f24(); virtual void f28(); virtual void f2C();
	virtual void f30(); virtual void f34(); virtual void f38(); virtual void f3C();
	virtual void f40(); virtual void f44(); virtual void f48(); virtual void f4C();
	virtual void f50(); virtual void f54(); virtual void f58(); virtual void f5C();
	virtual void f60();
	virtual void addAudioEvent(const BfmeStringTailRecord144 *eventToAdd);
	virtual void f68(); virtual void f6C(); virtual void f70(); virtual void f74();
	virtual void f78(); virtual void f7C(); virtual void f80(); virtual void f84();
	virtual void f88(); virtual void f8C(); virtual void f90(); virtual void f94();
	virtual void f98(); virtual void f9C(); virtual void fA0(); virtual void fA4();
	virtual void fA8(); virtual void fAC(); virtual void fB0(); virtual void fB4();
	virtual void fB8(); virtual void fBC(); virtual void fC0(); virtual void fC4();
	virtual void fC8(); virtual void fCC(); virtual void fD0(); virtual void fD4();
	virtual void fD8(); virtual void fDC(); virtual void fE0(); virtual void fE4();
	virtual void fE8(); virtual void fEC(); virtual void fF0(); virtual void fF4();
	virtual void fF8(); virtual void fFC(); virtual void f100(); virtual void f104();
	virtual void f108(); virtual void f10C(); virtual void f110(); virtual void f114();
	virtual void f118(); virtual void f11C(); virtual void f120(); virtual void f124();
	virtual void f128(); virtual void f12C(); virtual void f130(); virtual void f134();
	virtual MiscAudio *getMiscAudio();
};

extern AudioManager *TheAudio;

class Player
{
	char m_pad[0x54];
	int m_playerIndex;
	char m_pad58[0xA0 - 0x58];
	int m_radarCount;
	int m_disableProofRadarCount;
	unsigned char m_radarDisabled;

public:
	Bool hasRadar() const;
	void disableRadar();
	void enableRadar();
	int getPlayerIndex() const { return m_playerIndex; }

private:
	Bool okToPlayRadarEdgeSound();
};

// ?hasRadar@Player@@QBE_NXZ
Bool Player::hasRadar() const
{
	if (m_radarDisabled && (m_disableProofRadarCount == 0))
		return false;

	return m_radarCount > 0;
}

// ?disableRadar@Player@@QAEXXZ @0x002AAA65 and ?enableRadar@Player@@QAEXXZ
// @0x002AAAF9 (148B each), addresses from the existing symbols.csv pins. ZH
// Player.cpp verbatim apart from the event built from MiscAudio's sound
// name. They live in hasRadar's TU because retail calls hasRadar twice
// without reloading ecx, which MSVC does only when it can see hasRadar.
// okToPlayRadarEdgeSound (0x002AA04C) is pinned under its ZH name.
void Player::disableRadar()
{
	Bool hadRadar = hasRadar();
	m_radarDisabled = 1;

	if (hadRadar && !hasRadar() && okToPlayRadarEdgeSound())
	{
		BfmeStringTailRecord144 soundToPlay(TheAudio->getMiscAudio()->m_radarOfflineSound, 0);
		soundToPlay.setPlayerIndex(getPlayerIndex());
		TheAudio->addAudioEvent(&soundToPlay);
	}
}

void Player::enableRadar()
{
	Bool hadRadar = hasRadar();
	m_radarDisabled = 0;

	if (!hadRadar && hasRadar() && okToPlayRadarEdgeSound())
	{
		BfmeStringTailRecord144 soundToPlay(TheAudio->getMiscAudio()->m_radarOnlineSound, 0);
		soundToPlay.setPlayerIndex(getPlayerIndex());
		TheAudio->addAudioEvent(&soundToPlay);
	}
}
