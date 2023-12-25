# LibraryMS
 
一个 vue3 + cpp + vcpkg的前后端的图书馆管理系统

该项目为课程设计的一部分


仅测试支持ninja/msbuild
由于手动编译第三方库引入的原因,请使用Release

cpp后端部分为自建简单框架,使用soci作为数据库操作库,libhv作为http网络库

### 文件夹结构
framework/
后端部分

frontnd/
前端部分,使用vue3开发

mysql/
mysql connecter c的头文件和链接库

soci/
soci的头文件和链接库,backend选择mysql