#include <iostream>

//gcc struct_align_code/struct_stack.cpp -o ./test.out && ./test.out

// 查看结构提偏移量的神器 0 可以转为任意类型NULL指针 用于查看结构体的偏移位置  建议使用size_t  而非int避免精度报错
#define FIELDOFFSET(TYPE, MEMBER) (size_t)(&(((TYPE *)0)->MEMBER))

//-----------------------------------
//默认动态字节对齐
struct FrameDefault
{
    unsigned char id;    // 占用1--0
    int width;           // 占用4--4567 整数倍从4开始
    long long height;    // 占用8--89ABCDEF  正好从8开始
    unsigned char *data; // 占用4--0123  正好从16开始
};

//-----------------------------------
#pragma pack(push)
#pragma pack(1) // 采用1字节对齐  即为中间没有取倍数导致的空位
struct FramePack1
{
    unsigned char id;
    int width;
    long long height;
    unsigned char *data;
};
#pragma pack(pop)
//-----------------------------------

//-----------------------------------
#pragma pack(push)
#pragma pack(2) // 采用2字节对齐  即为取2倍数导致空位
struct FramePack2
{
    unsigned char id;
    int width;
    long long height;
    unsigned char *data;
};
#pragma pack(pop)
//-----------------------------------

//-----------------------------------
#pragma pack(push)
#pragma pack(4) // 采用4字节对齐  即为取4倍数导致空位
struct FramePack4
{
    unsigned char id;
    int width;
    long long height;
    unsigned char *data;
};
#pragma pack(pop)
//-----------------------------------

int main()
{
    printf("hello\n");

    printf("%d\n", sizeof(FrameDefault));

    printf("--------------------Default\n");
    printf("offset_FrameDefault_id    : %d\n", FIELDOFFSET(FrameDefault, id));
    printf("offset_FrameDefault_width : %d\n", FIELDOFFSET(FrameDefault, width));
    printf("offset_FrameDefault_height: %d\n", FIELDOFFSET(FrameDefault, height));
    printf("offset_FrameDefault_data  : %d\n", FIELDOFFSET(FrameDefault, data));

    printf("--------------------Pack1\n");

    printf("offset_FramePack1_id    : %d\n", FIELDOFFSET(FramePack1, id));
    printf("offset_FramePack1_width : %d\n", FIELDOFFSET(FramePack1, width));
    printf("offset_FramePack1_height: %d\n", FIELDOFFSET(FramePack1, height));
    printf("offset_FramePack1_data  : %d\n", FIELDOFFSET(FramePack1, data));

    printf("--------------------Pack2\n");

    printf("offset_FramePack2_id    : %d\n", FIELDOFFSET(FramePack2, id));
    printf("offset_FramePack2_width : %d\n", FIELDOFFSET(FramePack2, width));
    printf("offset_FramePack2_height: %d\n", FIELDOFFSET(FramePack2, height));
    printf("offset_FramePack2_data  : %d\n", FIELDOFFSET(FramePack2, data));

    printf("--------------------Pack4\n");

    printf("offset_FramePack4_id    : %d\n", FIELDOFFSET(FramePack4, id));
    printf("offset_FramePack4_width : %d\n", FIELDOFFSET(FramePack4, width));
    printf("offset_FramePack4_height: %d\n", FIELDOFFSET(FramePack4, height));
    printf("offset_FramePack4_data  : %d\n", FIELDOFFSET(FramePack4, data));

    return 0;
}