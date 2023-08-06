# WiFi 密码字典

## 弱密码字典

这里提供的文本文件来源于网络，是一般的弱密码。  

## 密码生成工具

passwordGeneration.c 是我用 Bing AI 生成的代码，可以用于生成密码字典，注意 WiFi 密码至少 8 位起步。  
Linux 下编译  
```bash
gcc passwordGeneration.c -o passwordGeneration

```

命令行执行生成示例
```bash
# l 小写字母
# u 大写字母
# d 数字
# s 特殊符号
# 生成 3 位密码，含有小写字母或数字或两者混合
./passwordGeneration 3 l d

# 生成 9 位密码，纯数字
./passwordGeneration 9 d
```

小心爆硬盘，谨慎使用！  
8 位小写字母+数字的密码就有 (26+10)^8 即接近 3 万亿个，一个字符占一个字节，大约就是二十几万亿字节，差不多二十几 TB（1TB=1024GB）

## 爆破方案

1.连接尝试：https://blog.iyatt.com/?p=10615  
这种方案速度较慢，相当于一个一个去连接尝试  

2.抓包匹配：https://blog.iyatt.com/?p=10677  
锁定目标 WiFi 扫描，攻击干扰 WiFi 让处于连接状态的设备断开，设备尝试重新连接时会发送包含加密密码的握手包，抓取这个握手包，再用字典中的密码尝试按照相同方式加密去匹配，速度完虐方案 1。