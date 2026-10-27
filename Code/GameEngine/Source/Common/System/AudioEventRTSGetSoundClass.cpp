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
	unsigned char m_pad00[0x48];
	unsigned char m_type;
	unsigned char m_pad49[0xB0 - 0x49];
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
	char m_pad0C[0x34 - 0x0C];
	unsigned int m_ownerID;
	int m_ownerType;
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

// ?isPositionalAudio@AudioEventRTS@@QBE_NXZ @0x002D9C37 (67B). The donor's
// owner-type test, preceded in BFME 2 by a class gate: only class 2 with
// type bit 2 set, or class 3, reaches the owner test; classes 4 and 5 (tested
// explicitly) and every other class are not positional. Owner types 1..5 need a live owner ID.
bool AudioEventRTS::isPositionalAudio() const
{
	if (m_eventInfo)
	{
		switch (m_eventInfo->m_soundClass)
		{
		case 2:
			if ((m_eventInfo->m_type & 2) == 0)
				goto not_positional;
			break;
		case 3:
			break;
		case 4:
			goto not_positional;
		case 5:
			goto not_positional;
		default:
			goto not_positional;
		}
	}

	switch (m_ownerType)
	{
	case 0:
		return true;
	case 1:
		if (m_ownerID == 0)
			goto not_positional;
		return true;
	case 2:
		if (m_ownerID == 0)
			goto not_positional;
		return true;
	case 3:
		if (m_ownerID == 0)
			goto not_positional;
		return true;
	case 4:
		if (m_ownerID == 0)
			goto not_positional;
		return true;
	case 5:
		if (m_ownerID == 0)
			goto not_positional;
		return true;
	default:
		goto not_positional;
	}

not_positional:
	return false;
}
