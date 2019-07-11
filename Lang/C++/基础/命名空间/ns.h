

namespace Outer
{
	int i;
	namespace Inter
	{
		int i;
		void f() { i++; }
		void g() { i--; }
	}
	void f() { i++; }
}