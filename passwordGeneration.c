#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义密码的字符集
#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DIGITS "0123456789"
#define SYMBOLS "!@#$%^&*()_+-=[]{};:'\"\\|,./<>?"

// 定义每次写入文件的密码数量
#define BATCH_SIZE 1000

// 定义文件名
#define FILE_NAME "passwords.txt"

// 定义命令行参数的标志
#define FLAG_LOWERCASE "l"
#define FLAG_UPPERCASE "u"
#define FLAG_DIGITS "d"
#define FLAG_SYMBOLS "s"

// 定义一个全局变量，存储密码的字符集
char charset[256];

// 定义一个函数，根据命令行参数设置字符集
void set_charset(int argc, char *argv[]) {
    // 初始化字符集为空字符串
    charset[0] = '\0';
    // 遍历命令行参数，如果有对应的标志，就将相应的字符集追加到charset中
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], FLAG_LOWERCASE) == 0) {
            strcat(charset, LOWERCASE);
        } else if (strcmp(argv[i], FLAG_UPPERCASE) == 0) {
            strcat(charset, UPPERCASE);
        } else if (strcmp(argv[i], FLAG_DIGITS) == 0) {
            strcat(charset, DIGITS);
        } else if (strcmp(argv[i], FLAG_SYMBOLS) == 0) {
            strcat(charset, SYMBOLS);
        } else {
            printf("无效的参数：%s\n", argv[i]);
            exit(1);
        }
    }
    // 如果字符集为空，就提示用户输入有效的参数，并退出程序
    if (charset[0] == '\0') {
        printf("请至少指定一个有效的字符集：-l（小写字母），-u（大写字母），-d（数字），-s（特殊符号）\n");
        exit(1);
    }
}

// 定义一个函数，生成指定长度的密码，并保存到文件中
void generate_passwords(int length) {
    // 打开文件，如果失败，就提示错误信息，并退出程序
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("无法打开文件：%s\n", FILE_NAME);
        exit(1);
    }
    // 获取字符集的长度
    int charset_len = strlen(charset);
    // 定义一个数组，存储当前生成的密码
    char password[length + 1];
    // 初始化密码为全0
    memset(password, '0', length);
    password[length] = '\0';
    // 定义一个变量，记录已经生成的密码数量
    int count = 0;
    // 定义一个循环，不断生成密码，直到最后一种可能的组合
    while (1) {
        // 将当前生成的密码写入文件中，并换行
        fprintf(fp, "%s\n", password);
        // 增加已经生成的密码数量
        count++;
        // 如果已经生成了一定数量的密码，就刷新文件缓冲区，避免内存占用过多
        if (count % BATCH_SIZE == 0) {
            fflush(fp);
        }
        // 定义一个变量，记录当前需要进位的位置，初始为最后一位
        int carry = length - 1;
        // 定义一个循环，从后往前遍历密码的每一位，进行进位操作
        while (carry >= 0) {
            // 找到当前位在字符集中对应的索引
            int index = strchr(charset, password[carry]) - charset;
            // 如果当前位已经是字符集中的最后一个字符，就将其置为字符集中的第一个字符，并将进位位置前移一位
            if (index == charset_len - 1) {
                password[carry] = charset[0];
                carry--;
            } else {
                // 否则，就将当前位替换为字符集中的下一个字符，并结束进位操作
                password[carry] = charset[index + 1];
                break;
            }
        }
        // 如果进位位置已经超出了密码的长度，说明已经生成了所有可能的组合，就结束循环
        if (carry < 0) {
            break;
        }
    }
    // 关闭文件
    fclose(fp);
}

// 定义主函数
int main(int argc, char *argv[]) {
    // 检查命令行参数的个数，如果少于3个，就提示用户输入正确的参数，并退出程序
    if (argc < 3) {
        printf("用法：%s <密码长度> <字符集选项>\n", argv[0]);
        printf("字符集选项：l（小写字母），u（大写字母），d（数字），s（特殊符号）\n");
        exit(1);
    }
    // 获取密码的长度，如果不是正整数，就提示用户输入有效的长度，并退出程序
    int length = atoi(argv[1]);
    if (length <= 0) {
        printf("请输入一个正整数作为密码长度\n");
        exit(1);
    }
    // 根据命令行参数设置字符集
    set_charset(argc, argv);
    // 生成指定长度的密码，并保存到文件中
    generate_passwords(length);
    // 提示用户密码已经生成完毕，并显示文件名
    printf("密码已经生成完毕，保存在文件：%s\n", FILE_NAME);
    return 0;
}
