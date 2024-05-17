#pragma once
#include "lasreader.hpp"
#include <string>
#include <array>

class Las_Reader
{
public:

	Las_Reader()
	{
		m_lasreader = nullptr;
	}

	~Las_Reader()
	{
		close();
	}

	bool open(const std::string& str_las_file)
	{
		m_lasread_opener.set_file_name(str_las_file.data());
		m_lasread_opener.set_decompress_selective(1);
		// open lasreader
		m_lasreader = m_lasread_opener.open();

		return (m_lasreader != nullptr);
	}

	int64_t point_count()
	{
		if (m_lasreader != nullptr)
			return m_lasreader->npoints;
		else
			return 0;
	}

	bool read_point(double& X, double& Y, double& Z)
	{
		if (m_lasreader->read_point() == FALSE)
			return false;

		X = m_lasreader->point.get_x();
		Y = m_lasreader->point.get_y();
		Z = m_lasreader->point.get_z();

		return true;
	}

	bool read_point(double& X, double& Y, double& Z, double& time, unsigned short& intensity)
	{
		if (m_lasreader->read_point() == FALSE)
			return false;

		X = m_lasreader->point.get_x();
		Y = m_lasreader->point.get_y();
		Z = m_lasreader->point.get_z();
		time = m_lasreader->point.get_gps_time();
		intensity = m_lasreader->point.get_intensity();

		return true;
	}

	bool read_point(double& X, double& Y, double& Z, unsigned short& intensity)
	{
		if (m_lasreader->read_point() == FALSE)
			return false;

		X = m_lasreader->point.get_x();
		Y = m_lasreader->point.get_y();
		Z = m_lasreader->point.get_z();

		intensity = m_lasreader->point.get_intensity();

		return true;
	}

	bool read_point(double& X, double& Y, double& Z, double& time, unsigned short& intensity, unsigned short& Red, unsigned short& Green, unsigned short &Blue)
	{
		if (m_lasreader->read_point() == FALSE)
			return false;

		X = m_lasreader->point.get_x();
		Y = m_lasreader->point.get_y();
		Z = m_lasreader->point.get_z();
		time = m_lasreader->point.get_gps_time();
		intensity = m_lasreader->point.get_intensity();
		Red = m_lasreader->point.get_R();
		Green = m_lasreader->point.get_B();
		Blue = m_lasreader->point.get_B();
		return true;
	}

	void close()
	{		
		if (m_lasreader)
		{
			m_lasreader->close();
			delete m_lasreader;
			m_lasreader = nullptr;
		}
	}	

protected:
	LASreadOpener m_lasread_opener;
	LASheader m_lasheader;
	LASpoint m_laspoint;
	LASreader* m_lasreader;
};
