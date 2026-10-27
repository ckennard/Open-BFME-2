// cl: /O1 /DNDEBUG /MD
//
// ?newMap@TerrainLogic@@UAEX_N@Z @0x00284290 (61B), address from the existing
// symbols.csv pin. ZH TerrainLogic.cpp newMap: once the height map is loaded,
// lift every waypoint by the ground height under it (getGroundHeight is
// virtual slot 0x18), then finish the water setup.
//
// BFME 2 differences, read from the retail body: the waypoint list head is
// a global (VA 0x00DFEC54, here a static member), the height is ADDED to the
// waypoint's z rather than stored, and the WaveGuide1/enableWaterGrid tail is
// one call to an unnamed TerrainLogic member at 0x00283E9C (address-derived
// name). Waypoint location sits at +0x0C, the next link at +0x1C.

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Waypoint
{
public:
	Waypoint *getNext() const { return m_next; }

	char m_pad[0x0C];
	Coord3D m_location;
	char m_pad18[0x1C - 0x18];
	Waypoint *m_next;
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	virtual void newMap(Bool saveGame);

private:
	void rva00283E9C();

	static Waypoint *m_waypointListHead;
};

void TerrainLogic::newMap(Bool saveGame)
{
	for (Waypoint *way = m_waypointListHead; way; way = way->getNext())
	{
		way->m_location.z += getGroundHeight(way->m_location.x, way->m_location.y);
	}
	rva00283E9C();
}
