#include <Semi_ThreadLocal.h>
#include <Windows.h>
#include <malloc.h>

using namespace Semi;
using namespace _Base;

_ThreadLocalBase::NodeBase& Semi_vectorcall _ThreadLocalBase::Bucket::Find(Uint32 key, const NodeBase& basic_value, Void(*increse)(Bucket*, const NodeBase&, NodeBase*), Size nodesize, Size nodealign)
{
	register NodeBase* i;
	register NodeBase* end = Data + Unum;

	for (i = Data; i < end; i++)
	{
		if (i->Key == key) return *i;
	}

	if (Unum == Tnum)
	{
		Size index = i - Data;

		Size  new_tnum = Tnum << 1;
		NodeBase* new_buffer = (NodeBase*)_aligned_malloc(new_tnum * nodesize, nodealign);
		increse(this, basic_value, new_buffer);
		_aligned_free(Data);

		Data = new_buffer;
		Tnum = new_tnum;
		i = Data + index;
	}
	Unum++;

	i->Key = key;
	return *i;
}

Uint32 _ThreadLocalBase::GetThreadID()
{
	return GetCurrentThreadId();
}

Void _ThreadLocalBase::InitTable(Bucket*& table)
{
	static constexpr Size n = (Size)1 << TableBit;
	table = (Bucket*)_aligned_malloc(n * sizeof(Bucket), alignof(Bucket));
}

Void _ThreadLocalBase::Bucket::InitInternal(Size nodesize, Size nodealign)
{
	Unum = 0;
	Tnum = 1;

	Data = (NodeBase*)_aligned_malloc(Tnum * nodesize, nodealign);
}
