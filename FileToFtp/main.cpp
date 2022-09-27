#include <iostream>
#include "ftptool.h"

int main()
{
    std::string resultFolder="/home/lab3/ZYC/UpLoad";
    //std::string FtpFolder="C:\\Users\\zmx\\Desktop\\ServeData\\DoubleCamera";
    const char *folder_name=resultFolder.c_str();        //需要遍历的本地文件夹的名字
    //const char *ftp_folder=FtpFolder.c_str();           //ftp上的目录
    //获取目录下所有文件和目录的列表,如果是文件则返回NULL

    DIR *dir=opendir(folder_name);
    int total=0;
    if(!dir)
    {
        perror("opendir");
        return -1;
    }
    else
    {
        struct dirent *ptr=NULL;
        char npath[1024];
        while((ptr=readdir(dir))!=NULL)
        {
            if(!strcmp(ptr->d_name,".")||!strcmp(ptr->d_name,".."))
                continue;
            //如果文件类型是普通文件，进行上传
            if(ptr->d_type != DT_DIR)
            {
                std::string file_name(folder_name);
                file_name.append("/");
                file_name.append(ptr->d_name);
                //ftp(ftpIp, ftpPort, username, password, local_filename, ftpFilename, ftpFolder)
                //前四个参数是ftp的服务器的ip,端口,用户名和密码,第五个参数是上传的本地文件的绝对路径.第六个参数是把此文件上传至ftp服务器之后的名称,第七个是上传至ftp的哪个文件夹下
                ftp_upload_file("10.193.77.105", 21, "LukeJia", "JBY250QMPZWSAD", file_name.c_str(), ptr->d_name);
            }
        }
    }

}
