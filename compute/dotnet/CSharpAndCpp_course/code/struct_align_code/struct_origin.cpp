#include <iostream>

//gcc struct_align_code/struct_origin.cpp -o ./test.out && ./test.out
// 查看结构提偏移量的神器 0 可以转为任意类型NULL指针 用于查看结构体的偏移位置  建议使用size_t  而非int避免精度报错
#define FIELDOFFSET(TYPE, MEMBER) (size_t)(&(((TYPE *)0)->MEMBER))

struct Info
{
    double userscore;
    char username[10];
    double userdata;
}; 

/*
    //规则1：起始为0位，结构体每个数据成员存储位置要从自己的大小整数倍开始
    //规则2：子结构体中的第一个成员偏移量应该是子结构体的最大成员整数倍
    //规则3：结构体总大小是内部成员整数倍
*/
struct Frame
{
    unsigned char id;    // 占用1--0
    int width;           // 占用4--4567 整数倍从4开始
    long long height;    // 占用8--89ABCDEF  正好从8开始
    unsigned char *data; // 占用4--0123  正好从16开始

    // 作为Frame的子结构体其第一偏移量为自己中最大者的整数倍
    Info info;           // Info内最大者double占据8位 故从24开始 
};
// 全部分配后时指针到了20 ，但是20非long long 8的整数倍 ，因此向后扩展到24 ， 也就是说 Frame结构体占用 24位

int main()
{
    printf("hello\n");

    printf("%d\n", sizeof(Frame));

    printf("--------------------Frame--------------------\n");
    printf("offset_id    : %d\n", FIELDOFFSET(Frame, id));
    printf("offset_width : %d\n", FIELDOFFSET(Frame, width));
    printf("offset_height: %d\n", FIELDOFFSET(Frame, height));
    printf("offset_data  : %d\n", FIELDOFFSET(Frame, data));
    printf("offset_info  : %d\n", FIELDOFFSET(Frame, info));
    printf("--------------------info---------------------\n");
    printf("offset_username: %d\n", FIELDOFFSET(Info, username));
    printf("offset_userdata: %d\n", FIELDOFFSET(Info, userdata));

    return 0;
}