// cl: /O1 /DNDEBUG /MD
//
// ?pointInTrigger@PolygonTrigger@@QAE_NABVICoord3D@@@Z @0x002E3A13 (38B),
// address from the existing symbols.csv pin; the mangled name is the one the
// rowed callers (PartitionManager, Bridge::isPointOnBridge, ScriptConditions)
// already call. BFME 2 drops ZH's inline crossing-count loop: the body copies
// the point's x/y into a 2-D local and hands it, with the trigger's +8
// sub-object, to an unnamed cdecl test at 0x00285B66 (address-derived name).

typedef int Int;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

class ICoord3D
{
public:
	Int x;
	Int y;
	Int z;
};

struct Rva00285B66Polygon;

Bool rva00285B66PointInPolygon(const ICoord2D *point, const Rva00285B66Polygon *polygon);

class PolygonTrigger
{
public:
	Bool pointInTrigger(const ICoord3D &point);

private:
	char m_pad[8];
	const Rva00285B66Polygon *polygon() const
	{
		return reinterpret_cast<const Rva00285B66Polygon *>(m_polygon);
	}
	char m_polygon[4];
};

Bool PolygonTrigger::pointInTrigger(const ICoord3D &point)
{
	ICoord2D pt;
	pt.x = point.x;
	pt.y = point.y;
	return rva00285B66PointInPolygon(&pt, polygon());
}
