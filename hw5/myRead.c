#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>

//执行方式 ./test test.csv out
int main(int argc, char *argv[]) {
    int infile = open(argv[1], O_RDONLY, 0);
    if(infile < 0) {
        perror("error open file");
    }
    int outfile = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0777);

    if(outfile < 0) {
        perror("error open file");
    }
    char buffer[4096];
    int  bigEndian[4096];
    int offset = 8;
    ssize_t r_size, w_size;
    do {
        r_size = read(infile, buffer, 4096);
        if(r_size > 0) {
            for(int i = 0; i < r_size; ++i) {
                int val = buffer[i];
                // c++ 默认是小端， 为了让其变为大端 将各个字节进行逆序。
                int trans = 0;
                for(int j = 0; j < 4; ++j) {
                    trans <<= offset;
                    trans |= (val >> (j * offset)) & ((1 << offset) - 1);
                }
                bigEndian[i] = trans;
            }
            w_size = write(outfile, (char *)bigEndian, r_size * 4);
        }
    }while(r_size);
    
    close(infile);
    close(outfile);

    outfile = open(argv[2], O_RDONLY, 0);
    int out[4096];
    char t[4096] = {0};
    do {
        r_size = read(outfile, (char *)out, 4096);
        if(r_size > 0) {
            for(int i = 0; i < r_size / 4; i ++) {
                t[i] = out[i] >> (offset * 3);
            }
            printf("%s", t);
        }
    }while(r_size);
    return 0;
}
