// cl: /O1 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1ImageCollection@@UAE@XZ @0x002D9283 (115B), the destructor the audited
// ??_GImageCollection wrapper (0x002D9362) calls. ZH Image.cpp's destructor
// frees every mapped image, then the map and SubsystemInterface bases unwind.
//
// Each image is freed with ::delete. Retail calls the virtual destructor
// with flag 0 and then the global operator delete (0x0002FD60) on its
// returned pointer, which is what MSVC 7.1 emits for a scope-qualified
// delete of a polymorphic object. Starting point: the banked 0.93 attempt.

#include <map>

class Image { public: virtual ~Image(); };
typedef _STL::map<unsigned int, Image *> ImageNameMap;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
private:
	unsigned char m_bfmeBasePad[8];
};

class ImageCollection : public SubsystemInterface
{
public:
	virtual ~ImageCollection();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	ImageNameMap m_imageMap;
};

ImageCollection::~ImageCollection(void)
{
	for (ImageNameMap::iterator i = m_imageMap.begin(); i != m_imageMap.end(); ++i)
		::delete i->second;
}
