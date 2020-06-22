#include <string>

#include "image.h"
#include "igg_image/io_strategies/strategy.h"
#include "igg_image/io_strategies/png_strategy.h"
#include "igg_image/io_strategies/dummy_strategy.h"
#include "igg_image/io_strategies/ppm_strategy.h"

int main(){
    std::string file_name = "../data/pbmlib.ascii.ppm";
    std::string file_name_new = "../data/pbmlib.ascii-new.ppm";


    std::string png_name = "../data/Lenna.png";
    std::string new_png_name = "../data/Lenna-new.png";

    igg::PpmIoStrategy strategy;
    

    // igg::Image image(512, 512, strategy);
    // image.ReadFromDisk(png_name);
    // image.WriteToDisk(new_png_name);

    igg::Image image(300, 300, strategy);
    image.ReadFromDisk(file_name);
    image.WriteToDisk(file_name_new);

    return 0;
}