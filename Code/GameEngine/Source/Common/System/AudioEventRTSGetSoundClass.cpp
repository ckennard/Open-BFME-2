// cl: /O1 /DNDEBUG /MD
//
// ?getSoundClass@AudioEventRTS@@QBEIXZ @0x002D9D39 (67B), address from the
// existing symbols.csv pin. BFME 1 donor AudioEventRTSClassification.cpp
// (Open-BFME-1 071013b3): map the event info's sound class to ST_* flags,
// asking isPositionalAudio for class 2. BFME 2 moves the class to info +0xB0
// and has an explicit sixth class (5) that maps to 0 like the default.
// isPositionalAudio (0x002D9C37) is pinned under its donor name.

struct AudioEventInfo
{
	unsigned char m_pad00[0xB0];
	unsigned int m_soundClass;
};

class AudioEventRTS
{
public:
	unsigned int getSoundClass(void) const;
	bool isPositionalAudio(void) const;

private:
	void *m_vftable;
	void *m_filenameToLoad;
	const AudioEventInfo *m_eventInfo;
};

unsigned int AudioEventRTS::getSoundClass(void) const
{
	if (!m_eventInfo)
		return 0;

	switch (m_eventInfo->m_soundClass)
	{
	case 0:
		return 1;
	case 3:
		return 16;
	case 1:
		return 8;
	case 4:
		return 2;
	case 2:
		return isPositionalAudio() ? 4 : 2;
	case 5:
		return 0;
	default:
		return 0;
	}
}
