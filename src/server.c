#include<stdio.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define num 1000//配列の個数
#define readnum1 500//配列の何番目を読むか

typedef struct Vec3
{
    double x;
    double y;
    double z;
}Vec3;


int main()
{

    /*********変数宣言************************************************/
    int fd;
    char rdbuf[num*sizeof(Vec3)];//char型だが、この領域をサイズnumのVec3配列として解釈する
    /****************************************************************/

    /*********fifoを作成**************/
    char  buf[10];
    sprintf(buf,"%d",getpid());
    if(mkfifo(buf,0660) == -1)
    perror("mkfifo");
    /******************************/

    

    /****************PID表示, ファイルのオープン*************/
    printf("Server(PID-%d): Waiting for input..\n",getpid());
    fd = open(buf,O_RDONLY);
    /*****************************************************/


    /********Vec3配列として解釈するためのポインタを準備************/
    Vec3* array = (Vec3*)rdbuf; //rdbufの先頭アドレスを格納
    /*******************************************************/

    while(1)
    {
        sleep(0.1);//ポーリング間隔を開ける(cpuを休める)
        /*************fifoからの読み取り********************************/
        int xxx = read(fd, rdbuf, num*sizeof(Vec3));//Vec3の配列num個分相当のバイト数を受け取る
        /************************************************************/


        if((xxx != -1) && (xxx != 0))//データを受け取れたら
        {
            printf("(%f, %f, %f)\n", array[readnum1].x, array[readnum1].y, array[readnum1].z);
            break;
        }
    }

    close(fd);

    /*********fifoのファイルの消去***************************/
    sprintf(rdbuf, "rm %d", getpid());
    system(rdbuf);
    /*****************************************************/

    return 0;


}