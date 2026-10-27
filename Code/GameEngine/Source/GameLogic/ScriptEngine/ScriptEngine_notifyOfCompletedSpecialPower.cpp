// cl: /O1 /DNDEBUG /MD
//
// ?notifyOfCompletedSpecialPower@ScriptEngine@@QAEXHABVAsciiString@@W4ObjectID@@@Z
// @0x00357EDF (50B), pinned from the rowed SpecialPowerCompletionDie
// caller. ZH ScriptEngine.cpp appends (power name, source object) to the
// player's m_finishedSpecialPowers list. BFME 2 keys the pair by the rowed
// AsciiString CRC (0x003ECA13) instead of the name. The per-player lists
// are 4-byte STLport list heads at +0x1A308, and their push_back
// (0x004DE74D) is pinned under this TU's spelling.

typedef int Int;

enum ObjectID
{
	INVALID_ID = 0
};

class AsciiString
{
	void *m_data;
};

unsigned long Rva003ECA13Get(const AsciiString &text);

struct NameCRCObjectIDPair
{
	NameCRCObjectIDPair(unsigned long crc, ObjectID id) : m_crc(crc), m_id(id) {}

	unsigned long m_crc;
	ObjectID m_id;
};

class NameCRCObjectIDPairList
{
public:
	void push_back(const NameCRCObjectIDPair &value);

private:
	void *m_node;
};

class ScriptEngine
{
public:
	void notifyOfCompletedSpecialPower(Int playerIndex, const AsciiString &completedPower, ObjectID sourceObj);

private:
	char m_pad[0x1A308];
	NameCRCObjectIDPairList m_finishedSpecialPowers[16];
};

void ScriptEngine::notifyOfCompletedSpecialPower(Int playerIndex, const AsciiString &completedPower, ObjectID sourceObj)
{
	m_finishedSpecialPowers[playerIndex].push_back(NameCRCObjectIDPair(Rva003ECA13Get(completedPower), sourceObj));
}
