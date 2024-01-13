#define API_IMPORT __declspec(dllimport)
#define API_EXPORT __declspec(dllexport)
 
#ifdef BUILD_DLL  
    #define MY_LIB_API  API_EXPORT //如果是生成dll工程，那么导出
#else
    #define MY_LIB_API  API_IMPORT //如果是生成使用dll的工程，那么导入
#endif