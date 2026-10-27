// ?clear@ScriptList@@QAEXXZ
// partial score=0.97 date=2026-10-27
// Ref-to-temporary spelling with the real polymorphic layout (virtual ~ScriptList,
// no explicit vptr member): frame, esi save and every call match retail; the
// only diff is lea ecx,[ebp-0x4C] where retail swaps on the ctor's eax.
// cl: /O1 /MD /GX-
class Rva003B761E
{
public:
	Rva003B761E();

private:
	char m_data[0x20];
};

class ScriptListBase
{
public:
private:
	void *m_firstGroup;
	void *m_firstScript;
};

class ScriptList : public ScriptListBase
{
public:
	ScriptList();
	virtual ~ScriptList();
	void clear();
	void swap(ScriptList *other);

private:
	Rva003B761E m_first;
	Rva003B761E m_second;
};

void ScriptList::clear()
{
	ScriptList &tmp = ScriptList();
	tmp.swap(this);
}
