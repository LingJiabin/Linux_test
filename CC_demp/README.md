#### lib 文件库

##### 构造MIME格式的PKCS7签名 库文件
p7_sign.cc && p7_sign.h

##### 验证MIME格式的PKCS7签名 库文件
p7_verify.cc && p7_verify.h

##### 构造MIME格式的数字信封
s_encrypt.cc && s_encrypt.h

##### 解密MIME格式的数字信封
s_decrypt.cc && s_decrypt.h

#### cmake 便携运行脚本
mcmake.sh

#### 主程序
main.cc

#### 相关文件
test 测试文件
my.pem 签名文件
private.key 私钥

#### 生成文件使用方法
例：
`./Demo --sign -k private.key -c my.pem -i test -o test.sign` 

`--sign` 签名
`--verify` 验证签名
`--encrypt` 信封加密
`--decrypt` 解密

`-i` 输入
`-k` 密钥
`-c` 证书
`-o` 输出
