#include <string>

#include "LAS_Reader.hpp"
#include "LAS_Writer.hpp"

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		return 0;
	}

	string str_in_cloud = argv[1];
	string str_out_cloud = argv[2];

	LAS_Reader las_in;
	if (las_in.open(str_in_cloud) == false)
		return 0;

	LAS_Writer las_out;
	las_out.open(str_out_cloud, las_in.get_scales());
	
	uint64_t count = las_in.get_point_count();

	double x, y, z;
	x = y = z = 0.0;
	for (uint64_t i = 0; i < count; i++)
	{
		las_in.read_point(x, y, z);

		// add some offset
		las_out.write_point(x+10, y+10, z+10);
	}

	las_in.close();
	las_out.close();	

	getchar();

    return 0;
}