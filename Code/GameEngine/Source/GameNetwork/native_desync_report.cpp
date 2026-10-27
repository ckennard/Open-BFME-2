// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /EHsc
//
// BFME1 GameNetwork/native_desync_report.cpp donor for the per-frame client CRC
// guard's constructor: when CRC checking is enabled and the game mode passes the
// 0x42219 gate, snapshot the current CRC, otherwise start from zero. The
// zeroing arm wants /O1's and-form compaction (retail `and [esi],0`).

class GameLogic
{
public:
    bool rva0042219(void);
    bool isInMultiplayerGame(void);
    unsigned int getCRC(int mode);
    unsigned int getFrame(void) const
    {
        return *reinterpret_cast<const unsigned int *>(
            reinterpret_cast<const char *>(this) + 0x40);
    }
};

template <typename T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;
private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
    struct Header
    {
        int refCount;
        unsigned short length;
        unsigned short capacity;
        T text[1];
    };
    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    const char *str() const { return m_data ? m_data->text : ""; }
    int getLength() const { return m_data ? m_data->length : 0; }
    void __cdecl format(const char *fmt, ...);
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
};

class IPEnumeration
{
public:
    IPEnumeration();
    ~IPEnumeration();
    AsciiString getMachineName();
private:
    void *m_ipList;
    bool m_isWinsockInitialized;
};

class InGameUI
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38();
    virtual void slot3C();
    virtual void message(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;

struct DesyncSystemTime
{
    unsigned short year, month, dayOfWeek, day, hour, minute, second,
        milliseconds;
};
struct DesyncFile;
extern "C" {
    __declspec(dllimport) DesyncFile *__cdecl fopen(const char *, const char *);
    __declspec(dllimport) unsigned int __cdecl fwrite(const void *,
        unsigned int, unsigned int, DesyncFile *);
    __declspec(dllimport) int __cdecl fclose(DesyncFile *);
    __declspec(dllimport) void __stdcall GetLocalTime(DesyncSystemTime *);
}

class BFMEDesyncCheck
{
public:
    BFMEDesyncCheck();
    void writeReportIfMismatched();

private:
    unsigned int m_crcBeforeClientUpdate;
};

extern unsigned char BfmeClientCRCCheckEnabled;
// BfmeClientCRCCheckEnabled: matched references place it at VA 0xe02d85 (zero-filled .bss).
unsigned char BfmeClientCRCCheckEnabled;
extern GameLogic *TheGameLogic;

// ??0BFMEDesyncCheck@@QAE@XZ
BFMEDesyncCheck::BFMEDesyncCheck()
{
    if (BfmeClientCRCCheckEnabled != 0)
    {
        GameLogic *logic = TheGameLogic;
        if (logic->rva0042219())
        {
            m_crcBeforeClientUpdate = logic->getCRC(0);
            return;
        }
    }
    m_crcBeforeClientUpdate = 0;
}

// ?writeReportIfMismatched@BFMEDesyncCheck@@QAEXXZ, retail 0x002CEA55 (409B).
// BFME 1 donor body (Open-BFME-1 071013b3, same file). BFME 2 reuses the
// constructor's mode gate (0x00042219) and checks isInMultiplayerGame
// (0x00042235), where the donor compares game modes inline. Both CRCs come
// from this machine.
void BFMEDesyncCheck::writeReportIfMismatched()
{
    if (BfmeClientCRCCheckEnabled == 0)
        return;
    GameLogic *logic = TheGameLogic;
    if (!logic->rva0042219())
        return;
    unsigned int crc = logic->getCRC(0);
    if (TheGameLogic->isInMultiplayerGame() && m_crcBeforeClientUpdate != crc)
    {
        if (TheInGameUI)
            TheInGameUI->message(
                UnicodeString(L"GameLogic changed outside of GameLogic::update()!"));
        AsciiString filename;
        AsciiString report;
        IPEnumeration enumeration;
        filename.format("CLIENT_DESYNC_%s.txt", enumeration.getMachineName().str());
        DesyncFile *file = fopen(filename.str(), "a");
        DesyncSystemTime time;
        GetLocalTime(&time);
        report.format("Desync detected on frame %d on %u-%u-%u %u:%u:%u\n\n",
            TheGameLogic->getFrame(),
            time.month, time.day, time.year, time.hour, time.minute, time.second);
        fwrite(report.str(), 1, report.getLength(), file);
        fclose(file);
    }
}
