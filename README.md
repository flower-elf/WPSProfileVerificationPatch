# WPS Office 配置文件哈希校验补丁

本补丁用于跳过 WPS Office 安装程序和主程序的配置文件哈希校验（oem.ini/product.dat）。

## 使用方式

> 本补丁可以配合 [WPSProfileCipher](https://github.com/YukiIsait/WPSProfileCipher) 使用以实现更方便的配置文件自定义。

1. 根据不同架构的安装程序和主程序选择相应的补丁：
    - 安装程序：
        1. 解压缩安装包以提取出 `$_11_\$EXEFILE` 并添加 `.exe` 拓展名。
        2. 根据架构选择 `msi64.dll` 或 `msi32.dll` 并重命名为 `msi.dll` 后放置于 `$EXEFILE.exe` 的同目录下。

    - 主程序：
        1. 安装完成主程序。
        2. 根据架构选择 `ncrypt64.dll` 或 `ncrypt32.dll` 并重命名为 `ncrypt.dll` 后放置于安装目录的 `<最新版本号>\office6` 目录下。

2. 将自定义的配置文件结尾的数字签名部分全部置为 `0`，数字签名部分要以分号开头且独占最后一行（无换行符）。
3. 将自定义的配置文件放置于指定位置：
    - 安装程序：将 `oem.ini` 放置于 `$EXEFILE.exe` 的同目录下。
    - 主程序：将 `oem.ini` 或 `product.dat` 放置于 `<最新版本号>\office6\cfgs` 目录下。

4. 运行安装程序或主程序即可正确加载自定义的配置文件。

## 使用示例

以下是一个自定义的 `oem.ini` 示例，使用安装程序加载后可以看到 WPS365 的样式：

```
;/DWPS_SETUP /DSETUP_ICON=setup_wps365
[setup]
X5tQ2374HX-wdsrBl5Q1Ow..=65QqmQkW9V4GP3AYSyX88g..
tzB-HAHJJxzGdJoZU4_SVQ..=4xKSRWOe3866uImVPSkVew..
DVNf4VC4rmVLjsRLf4zlaQ..=5Cg7NICz9dOjthrFulp2ZA..
MpT0xTZ8VBLk8DLrxqv_s2KyGtSK22KrUkpP2VqDsx0.=WHfH10HHgeQrW2N48LfXrA..
GV1jE2lI9Sy13oHl75HonuDZX3jHffNL8URU1NpO4tE.=Qn-yJAod--J_Qfwhk7UeVwfFbZoHqxt3D5qDqvsWbeQ.
;PipeNumber=51.703

;00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
```

## 相关技术

本项目使用 [ProxyPESourceGenerator](https://github.com/YukiIsait/ProxyPESourceGenerator) 生成用于代理 `ncrypt.dll` 和 `msi.dll` 的源代码。

## 开源许可

本项目根据 MIT 许可证授权，详见 [LICENSE](LICENSE.md) 文件。
