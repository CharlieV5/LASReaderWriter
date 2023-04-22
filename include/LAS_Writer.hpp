#pragma once
#include "laswriter.hpp"
#include <string>
#include <array>
using namespace std;

class LAS_Writer
{
public:
	LAS_Writer()
	{
		m_header.x_offset = m_header.y_offset = m_header.z_offset = 0.001;

		m_p.init(&m_header, m_header.point_data_format, m_header.point_data_record_length);

	};

	~LAS_Writer() {};

	bool open(const string& str_las, array<double, 3> scales = { 0.001,0.001,0.001 }, array<double, 3> offsets = {0,0,0})
	{
		m_header.x_offset = offsets[0];
		m_header.y_offset = offsets[1];
		m_header.z_offset = offsets[2];

		m_header.x_scale_factor = scales[0];
		m_header.y_scale_factor = scales[1];
		m_header.z_scale_factor = scales[2];

		m_p.init(&m_header, m_header.point_data_format, m_header.point_data_record_length);


		m_las_opener.set_file_name(str_las.data());

		m_las_writer =  m_las_opener.open(&m_header);
		if (m_las_writer == nullptr)
		{
			return false;
		}

		return true;
	}

	bool write_point(double x, double y, double z )
	{
		if (m_las_writer == nullptr)
			return false;

		m_p.set_x(x);
		m_p.set_y(y);
		m_p.set_z(z);

		if (m_las_writer->write_point(&m_p) == FALSE)
			return false;

		return true;
	}

	void close()
	{		
		if (m_las_writer)
		{
			m_las_writer->update_header(&m_header, FALSE, TRUE);

			m_las_writer->close();
			delete m_las_writer;
			m_las_writer = nullptr;
		}
	}

private:
	LASwriteOpener m_las_opener;
	LASwriter* m_las_writer = nullptr;
	LASheader m_header;
	LASpoint m_p;

};
