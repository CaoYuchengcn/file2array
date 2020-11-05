#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* fpin = NULL;
    FILE* fpout = NULL;
    char in_path[512] = { 0 };
    char out_path[] = "out_array.h";
    unsigned char tmp[1];
    unsigned int ret = 0;

    fpout = fopen(out_path,"wb");
    if (fpout == NULL)
    {
        printf("输出文件:%s,创建失败！\r\n");
    }
    for (unsigned int i = 0; ; i++)
    {
        printf("请输入文件路径");
        scanf("%s", in_path);
        fpin = fopen(in_path,"rb");
        if (fpin == NULL)
        {
            printf("打开文件:%s，失败",in_path);
        }
        else
        {
            unsigned int file_len = 0;
            fflush(fpout);

            fseek(fpin, 0, SEEK_END);
            file_len = ftell(fpin);
            fseek(fpin, 0, SEEK_SET);
            printf("file_len;%d\r\n", file_len);
            fprintf(fpout, "char %s[] = {\r\n",in_path);

            for(long j = 0; j < file_len; j++)
            {
                fread(tmp,1,1,fpin);
                fprintf(fpout,"0x%02X,",*tmp);
                if (j % 16 == 15)
                {
                    fprintf(fpout, "\r");
                }
                fflush(fpout);
            }
            fprintf(fpout, "\r\n};\r\n");
            fflush(fpout);
            printf("完成！\r\n");


            fclose(fpin);
        }
    }

    fclose(fpout);
    return 0;
}
