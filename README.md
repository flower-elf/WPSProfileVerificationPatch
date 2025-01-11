# WPS Office 配置文件校验补丁

本程序用于跳过 WPS Office 主程序的配置文件校验（oem.ini/product.dat）。

## 使用方式

1. 根据 64 位或 32 位的软件选择相应的补丁，并将其重命名为 `version.dll` 后放置于 `office6` 目录下。
2. 将自定义的配置文件结尾的数字签名全部置为 `0`。
3. 运行程序即可正确加载自定义的配置文件。

## 开源许可

本项目根据 MIT 许可证授权，详见 [LICENSE](LICENSE.md) 文件。
