#pragma once
#include "laswriter.hpp"
#include <string>
#include <array>

struct sRGBA
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	sRGBA()
	{ 
		r = g = b = 0;
		a = 255; 
	}

	sRGBA(unsigned char r_, unsigned char g_, unsigned char b_)
	{
		r = r_; g = g_; b = b_;
		a = 255;
	}

	sRGBA(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_)
	{
		r = r_; g = g_; b = b_; a = a_;
	}
};

class Las_Writer
{
public:

	Las_Writer()
	{
		m_laswriter = nullptr;
	}

	~Las_Writer()
	{
		close();
	}

	bool open(const std::string& str_las_file, std::array<double, 3> offset = {0,0,0})
	{
		m_laswrite_opener.set_file_name(str_las_file.data());
		// init header	
		m_lasheader.x_scale_factor = 0.0001;
		m_lasheader.y_scale_factor = 0.0001;
		m_lasheader.z_scale_factor = 0.0001;

		m_lasheader.x_offset = offset[0];
		m_lasheader.y_offset = offset[1];
		m_lasheader.z_offset = offset[2];

		//m_lasheader.point_data_format = 1;
		//m_lasheader.point_data_record_length = 28;
		m_lasheader.point_data_format = 3;
		m_lasheader.point_data_record_length = 34;

		// init point 	
		m_laspoint.init(&m_lasheader, m_lasheader.point_data_format, m_lasheader.point_data_record_length, 0);

		// open laswriter
		m_laswriter = m_laswrite_opener.open(&m_lasheader);

		return (m_laswriter != nullptr);
	}

	void write_point(double bigX, double bigY, double bigZ)
	{
		I32 x = I32(1.0 / m_lasheader.x_scale_factor * (bigX - m_lasheader.x_offset));
		I32 y = I32(1.0 / m_lasheader.y_scale_factor * (bigY - m_lasheader.y_offset));
		I32 z = I32(1.0 / m_lasheader.z_scale_factor * (bigZ - m_lasheader.z_offset));
		m_laspoint.set_X(x);
		m_laspoint.set_Y(y);
		m_laspoint.set_Z(z);

		m_laswriter->write_point(&m_laspoint);
	}

	void write_point(double bigX, double bigY, double bigZ, double time, unsigned short intensity, unsigned char wave_num, unsigned  char wave_count)
	{
		I32 x = I32(1.0 / m_lasheader.x_scale_factor * (bigX - m_lasheader.x_offset));
		I32 y = I32(1.0 / m_lasheader.y_scale_factor * (bigY - m_lasheader.y_offset));
		I32 z = I32(1.0 / m_lasheader.z_scale_factor * (bigZ - m_lasheader.z_offset));
		m_laspoint.set_X(x);
		m_laspoint.set_Y(y);
		m_laspoint.set_Z(z);

		m_laspoint.set_intensity(intensity);
		m_laspoint.set_gps_time(time);

		m_laspoint.set_return_number(wave_num);
		m_laspoint.set_number_of_returns(wave_count);

		m_laswriter->write_point(&m_laspoint);
	}

	void write_point(double bigX, double bigY, double bigZ, double time, unsigned short intensity)
	{
		I32 x = I32(1.0 / m_lasheader.x_scale_factor * (bigX - m_lasheader.x_offset));
		I32 y = I32(1.0 / m_lasheader.y_scale_factor * (bigY - m_lasheader.y_offset));
		I32 z = I32(1.0 / m_lasheader.z_scale_factor * (bigZ - m_lasheader.z_offset));
		m_laspoint.set_X(x);
		m_laspoint.set_Y(y);
		m_laspoint.set_Z(z);

		m_laspoint.set_intensity(intensity);
		m_laspoint.set_gps_time(time);

		m_laswriter->write_point(&m_laspoint);
	}

	void write_point(double bigX, double bigY, double bigZ, double time, unsigned short intensity, unsigned short source_id)
	{
		I32 x = I32(1.0 / m_lasheader.x_scale_factor * (bigX - m_lasheader.x_offset));
		I32 y = I32(1.0 / m_lasheader.y_scale_factor * (bigY - m_lasheader.y_offset));
		I32 z = I32(1.0 / m_lasheader.z_scale_factor * (bigZ - m_lasheader.z_offset));
		m_laspoint.set_X(x);
		m_laspoint.set_Y(y);
		m_laspoint.set_Z(z);

		m_laspoint.set_intensity(intensity);
		m_laspoint.set_gps_time(time);

		m_laspoint.set_point_source_ID(source_id);

		m_laswriter->write_point(&m_laspoint);
	}

	void write_point(double bigX, double bigY, double bigZ, unsigned short intensity)
	{
		I32 x = I32(1.0 / m_lasheader.x_scale_factor * (bigX - m_lasheader.x_offset));
		I32 y = I32(1.0 / m_lasheader.y_scale_factor * (bigY - m_lasheader.y_offset));
		I32 z = I32(1.0 / m_lasheader.z_scale_factor * (bigZ - m_lasheader.z_offset));
		m_laspoint.set_X(x);
		m_laspoint.set_Y(y);
		m_laspoint.set_Z(z);

		m_laspoint.set_intensity(intensity);

		m_laswriter->write_point(&m_laspoint);
	}

	void write_point(double bigX, double bigY, double bigZ, unsigned short intensity, sRGBA color)
	{
		I32 x = I32(1.0 / m_lasheader.x_scale_factor * (bigX - m_lasheader.x_offset));
		I32 y = I32(1.0 / m_lasheader.y_scale_factor * (bigY - m_lasheader.y_offset));
		I32 z = I32(1.0 / m_lasheader.z_scale_factor * (bigZ - m_lasheader.z_offset));
		m_laspoint.set_X(x);
		m_laspoint.set_Y(y);
		m_laspoint.set_Z(z);

		m_laspoint.set_R(color.r);
		m_laspoint.set_G(color.g);
		m_laspoint.set_B(color.b);
		m_laspoint.set_I(color.a);

		m_laspoint.set_intensity(intensity);

		m_laswriter->write_point(&m_laspoint);
	}

	void write_point(double bigX, double bigY, double bigZ, sRGBA color)
	{
		I32 x = I32(1.0 / m_lasheader.x_scale_factor * (bigX - m_lasheader.x_offset));
		I32 y = I32(1.0 / m_lasheader.y_scale_factor * (bigY - m_lasheader.y_offset));
		I32 z = I32(1.0 / m_lasheader.z_scale_factor * (bigZ - m_lasheader.z_offset));
		m_laspoint.set_X(x);
		m_laspoint.set_Y(y);
		m_laspoint.set_Z(z);

		m_laspoint.set_R(color.r);
		m_laspoint.set_G(color.g);
		m_laspoint.set_B(color.b);
		m_laspoint.set_I(color.a);

		m_laswriter->write_point(&m_laspoint);
	}

	void write_point(double bigX, double bigY, double bigZ, double time, unsigned  short intensity, sRGBA color)
	{
		I32 x = I32(1.0 / m_lasheader.x_scale_factor * (bigX - m_lasheader.x_offset));
		I32 y = I32(1.0 / m_lasheader.y_scale_factor * (bigY - m_lasheader.y_offset));
		I32 z = I32(1.0 / m_lasheader.z_scale_factor * (bigZ - m_lasheader.z_offset));
		m_laspoint.set_X(x);
		m_laspoint.set_Y(y);
		m_laspoint.set_Z(z);

		m_laspoint.set_R(color.r);
		m_laspoint.set_G(color.g);
		m_laspoint.set_B(color.b);
		m_laspoint.set_I(color.a);

		m_laspoint.set_gps_time(time);
		m_laspoint.set_intensity(intensity);

		m_laswriter->write_point(&m_laspoint);
	}

	void write_point(double bigX, double bigY, double bigZ, unsigned char class_id, unsigned char return_number)
	{
		I32 x = I32(1.0 / m_lasheader.x_scale_factor * (bigX - m_lasheader.x_offset));
		I32 y = I32(1.0 / m_lasheader.y_scale_factor * (bigY - m_lasheader.y_offset));
		I32 z = I32(1.0 / m_lasheader.z_scale_factor * (bigZ - m_lasheader.z_offset));
		m_laspoint.set_X(x);
		m_laspoint.set_Y(y);
		m_laspoint.set_Z(z);

		m_laspoint.set_classification(class_id);
		m_laspoint.set_return_number(return_number);

		m_laswriter->write_point(&m_laspoint);
	}

	void close()
	{
		if (m_laswriter)
		{
			m_laswriter->update_header(&m_lasheader, TRUE);// update the header
			I64 total_bytes = m_laswriter->close();
			delete m_laswriter;
			m_laswriter = nullptr;
		}
	}	

protected:
	LASwriteOpener m_laswrite_opener;
	LASheader m_lasheader;
	LASpoint m_laspoint;
	LASwriter* m_laswriter;
};

