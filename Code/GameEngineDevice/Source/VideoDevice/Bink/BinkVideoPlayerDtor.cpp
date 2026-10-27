// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1BinkVideoPlayer@@UAE@XZ, retail 0x0009111B, 56 bytes, at the existing
// ??1Rva009111B pin. ZH BinkVideoPlayer.cpp, verbatim: deinit() (called
// directly, as any virtual is from a destructor; 0x000907A7, pinned under
// its ZH name), then the rowed VideoPlayer dtor (0x00689350).

class VideoPlayer
{
public:
	virtual ~VideoPlayer();
};

class BinkVideoPlayer : public VideoPlayer
{
public:
	virtual ~BinkVideoPlayer();
	virtual void deinit(void);
};

BinkVideoPlayer::~BinkVideoPlayer()
{
	deinit();
}
