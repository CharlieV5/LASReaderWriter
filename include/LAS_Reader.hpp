#pragma once
#include "lasreader.hpp"
#include <string>
#include <array>

using namespace std;

class LAS_Reader
{
public:
	LAS_Reader()
	{
	};

	~LAS_Reader() {};

	bool open(const string& str_las)
	{
		m_las_reader = m_las_opener.open(str_las.data());
		if (m_las_reader == nullptr)
		{
			return false;
		}

		m_point_count = m_las_reader->npoints;
		return true;
	}

	uint64_t get_point_count()
	{
		return m_point_count;
	}

	array<double, 3> get_scales()
	{
		array<double, 3> scales = {1,1,1};
		if (m_las_reader != nullptr)
		{
			scales[0] = m_las_reader->header.x_scale_factor;
			scales[1] = m_las_reader->header.y_scale_factor;
			scales[2] = m_las_reader->header.z_scale_factor;
		}

		return scales;
	}

	array<double, 3> get_offsets()
	{
		array<double, 3> offsets = { 0,0,0 };
		if (m_las_reader != nullptr)
		{
			offsets[0] = m_las_reader->header.x_offset;
			offsets[1] = m_las_reader->header.y_offset;
			offsets[2] = m_las_reader->header.z_offset;
		}

		return offsets;
	}

	bool read_point(double& x, double& y, double& z )
	{
		if (m_las_reader == nullptr)
			return false;

		if (m_las_reader->read_point() == FALSE)
			return false;

		x = m_las_reader->get_x();
		y = m_las_reader->get_y();
		z = m_las_reader->get_z();

		return true;
	}

	void close()
	{
		m_las_opener.reset();
		if (m_las_reader)
		{
			m_las_reader->close();
			delete m_las_reader;
			m_las_reader = nullptr;
		}
	}

private:
	LASreadOpener m_las_opener;
	LASreader* m_las_reader = nullptr;
	uint64_t m_point_count = 0;
};
