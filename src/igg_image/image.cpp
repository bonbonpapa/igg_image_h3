#include <iostream>
#include "image.h"
using std::cout;
using std::endl;

igg::Image::Image(const IoStrategy & io_strategy) : io_strategy_ {io_strategy} {}
igg::Image::Image(int rows, int cols, const IoStrategy & io_strategy) : rows_{rows}, cols_{cols}, io_strategy_ {io_strategy } {}
int igg::Image::rows() const
{
  return rows_;
}
int igg::Image::cols() const
{
  return cols_;
}
const igg::Image::Pixel &igg::Image::at(int row, int col)
{
  return data_.at(cols_ * row + col);
}

bool igg::Image::ReadFromDisk(const std::string& file_name)
{
    igg::ImageData img_data = io_strategy_.Read(file_name);
    
    data_.reserve(img_data.cols * img_data.rows);

    std::vector<int> p_red =img_data.data.at(0);
    std::vector<int> p_green =img_data.data.at(1);
    std::vector<int> p_blue =img_data.data.at(2);

    for (int i = 0 ; i < img_data.cols * img_data.rows ; i ++)
    {
        data_.push_back({p_red.at(i), p_green.at(i), p_blue.at(i)});
    }
    
    cout << "Read data from disk " << file_name << endl;

    return true;
}
void igg::Image::WriteToDisk(const std::string& file_name)
{
    igg::ImageData img_data;
    img_data.cols = cols_;
    img_data.rows = rows_;
    img_data.max_val = 255;

    std::vector<int> vec_red, vec_green, vec_blue;
    vec_red.reserve(cols_ * rows_);
    vec_green.reserve(cols_ * rows_);
    vec_blue.reserve(cols_ * rows_);

    for (int i = 0 ; i < img_data.cols * img_data.rows ; i ++)
    { 
        auto px = data_.at(i);

        vec_red.push_back(px.red);
        vec_green.push_back(px.green);
        vec_blue.push_back(px.blue);      
    }
    img_data.data = {vec_red, vec_green, vec_blue};

    io_strategy_.Write(file_name, img_data);

    cout << "Write data to disk " << file_name << endl;
}