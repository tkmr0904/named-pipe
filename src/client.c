#include<stdio.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define num 1000//配列の個数

typedef struct Vec3
{
    double x;
    double y;
    double z;
}Vec3;


int main()
{
    int fd;
    char wrbuf[num*sizeof(Vec3)];//char型だが、この領域をサイズnumのVec3配列として解釈する

    /***fifoのオープン****************/
    char buf[10];
    printf("Enter server process: ");
    scanf("%s",buf);
    getchar();
    fd = open(buf,O_WRONLY);
    /*********************************/


    /*****wrbufの領域をVec3配列と解釈して数値を入力**********/
    Vec3* array = (Vec3*)wrbuf;//wrbufの先頭アドレスを格納

    for(int i = 0; i<num; i++)
    {
        array[i].x = 2*i;
        array[i].y = 2*i;
        array[i].z = 2*i;
    }
    /***************************************************/


    /*****charとしてfifoに書き込む******/
    write(fd, wrbuf, num*sizeof(Vec3));
    /********************************/

    close(fd);
}