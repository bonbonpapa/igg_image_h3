// Copyright Igor Bogoslavskyi, year 2018.
// In case of any problems with the code please contact me.
// Email: igor.bogoslavskyi@uni-bonn.de.

#include "igg_image/io_strategies/ppm_strategy.h"

#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

namespace igg
{

  bool PpmIoStrategy::Write(const std::string &file_name,
                            const ImageData &data) const
  {
    ofstream ofs;
    try
    {
      ofs.open(file_name, ios_base::out);
      if (ofs.fail())
        throw("Can't open the file");
      ofs << "P3\n"
          << data.cols << " " << data.rows << "\n"
          << data.max_val << "\n";
      size_t size = data.cols * data.rows;

    std::vector<int> p_red = data.data.at(0);
    std::vector<int> p_green = data.data.at(1);
    std::vector<int> p_blue = data.data.at(2);

    size_t line_count = 0;

      for (size_t i = 0; i < size ; i++)
      {

        ofs << p_red.at(i) << " ";
        line_count++;
        if(line_count % 70 == 0)  ofs << "\n";        
        ofs << p_green.at(i) << " "; 
        line_count++;
        if(line_count % 70 == 0)  ofs << "\n";   
        ofs << p_blue.at(i) << " ";    
        line_count++;
        if(line_count % 70 == 0)  ofs << "\n";             
      }
      ofs.close();
    }
    catch (const char *err)
    {
      fprintf(stderr, "%s\n", err);
      ofs.close();
      return false;
    }
    return true;
  }

  ImageData PpmIoStrategy::Read(const std::string &file_name) const
  {

    ifstream ifs;
    string line;
    ifs.open(file_name, ios_base::in);

    ImageData image_data;
    image_data.max_val = 255;

    try
    {
      if (ifs.fail())
      {
        throw("cannot open input file");
      }
      string header;
      int w, h, max_p;
      ifs >> header;

      if (header.compare("P3") != 0)
        throw("Can't read input file");
      getline(ifs, line); // just read line to skip the first line
      while (getline(ifs, line))
      {
        if (line.substr(0, 1) == "#")
          continue;
        else
        {
          istringstream record(line);
          record >> w >> h;
          break;
        }
      }
      while (getline(ifs, line))
      {
        if (line.substr(0, 1) == "#")
          continue;
        else
        {
          istringstream record(line);
          record >> max_p;
          break;
        }
      }
      image_data.cols = w;
      image_data.rows = h;
      image_data.max_val = max_p;

      // std::vector<int> red(image_data.rows * image_data.cols, 0);
      // std::vector<int> green(image_data.rows * image_data.cols, 0);
      // std::vector<int> blue(image_data.rows * image_data.cols, 0);
      std::vector<int> red;
      red.reserve(image_data.rows * image_data.cols);
      std::vector<int> green;
      green.reserve(image_data.rows * image_data.cols);
      std::vector<int> blue;
      blue.reserve(image_data.rows * image_data.cols);

      cout << image_data.cols << endl;
      cout << image_data.rows << endl;
      cout << image_data.max_val << endl;
      
      size_t size = image_data.cols * image_data.rows * 3;

      for (size_t i = 0; i < size ; i+=3)
      {
        int r,g,b;
        ifs >> r >> g >> b;
        red.push_back(r);
        green.push_back(g);
        blue.push_back(b);        
      }

      image_data.data = {red, green, blue};
      ifs.close();
      
      
    }
    catch (const char *err)
    {
      fprintf(stderr, "%s\n", err);
      
      ifs.close();
      return ImageData{0, 0, 0, {{}}};
    }

  return image_data;
  }
 
     

} // namespace igg
