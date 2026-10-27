// cl: /O1 /DNDEBUG /MD
//
// ?getFont@FontLibrary@@QAEPAVGameFont@@PBVAsciiString@@M_N@Z @0x002189E1
// (66B), address from the existing symbols.csv pin. BFME 1 donor
// FontLibraryBFMERetail_getFont.cpp (Open-BFME-1 071013b3), unchanged in
// shape: the rowed record lookup rva002186A6 (FontLibraryFindRecord.cpp)
// supplies the byte at +8, which picks weight 4 or 1 (1 when no record),
// then the font is fetched through 0x0021857E (pinned, address-derived name).

typedef int Int;
typedef float Real;
typedef bool Bool;

class AsciiString;
class GameFont;

struct BfmeFontRecord
{
	unsigned char m_bfmeHead[0x08];
	unsigned char m_bfmeWeighted;
};

class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, Real size, Bool bold);
	void *rva002186A6(const AsciiString *name, Real size);

private:
	GameFont *rva0021857E(const AsciiString *name, Real size, Bool bold, Int weight);
};

GameFont *FontLibrary::getFont(const AsciiString *name, Real size, Bool bold)
{
	unsigned char weighted = 1;

	BfmeFontRecord *record = static_cast<BfmeFontRecord *>(rva002186A6(name, size));

	if (record)
		weighted = record->m_bfmeWeighted;

	return rva0021857E(name, size, bold, weighted ? 4 : 1);
}
