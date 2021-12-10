#include "../include/dft.h"
#include "../include/lbp.h"
#include "../include/file.h"
#include "../include/euclid.h"
int main(int argc, char *argv[]){
    String path(argv[1]);
    read_image(path);
    waitKey(0);
    return 0;
}