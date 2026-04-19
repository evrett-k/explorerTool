# ExplorerBgTool

Windows 10/11 资源管理器背景图工具 (Explorer background image tool for Windows 10/11)

---

## 中文文档

### 功能

* 自定义文件资源管理器背景图片
* 支持多个图片随机切换
* 可调整图片透明度
* 可自定义图片显示位置
* 支持为指定路径单独设置背景图片

### 目录

1. 预览
2. 使用方法
3. 配置文件
4. 自定义路径
5. 兼容性与重启说明
6. 从源码构建
7. GitHub Actions 与发布流程
8. 注意事项

### 预览

#### Windows 11 示例

右下角:

```ini
posType=3
```

![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/083434.jpg)

居中:

```ini
posType=4
```

![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/084016.jpg)

缩放并填充:

```ini
posType=6
imgAlpha=140
```

![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/085051.jpg)

#### Windows 10 示例

```ini
posType=3
```

![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/085552.jpg)

#### 文件对话框

```ini
[load]
folderExt=true
...
```

![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/163113.jpg)

### 使用方法

1. 从 Release 页面下载最新压缩包并解压。
2. 将图片放入 Image 文件夹。
3. 运行 Register.cmd。
4. 重新打开资源管理器窗口。

卸载:

* 运行 Uninstall.cmd。
* 或手动执行 regsvr32 /u "你的路径/ExplorerBgTool.dll"。

### 配置文件

通过修改 config.ini 调整样式。

```ini
[load]
# 在文件对话框中启用扩展
folderExt=false

# 发生错误时不弹窗
noerror=false

[image]
# 随机图片模式 (至少需要 2 张图)
random=false

# 启用按路径匹配自定义图片
custom=false

# 位置模式:
# 0=左上 1=右上 2=左下 3=右下
# 4=居中 5=拉伸 6=缩放填充
# 7=左中 8=右中 9=上中 10=下中
posType=3

# 透明度 0-255
imgAlpha=255

# 在定位后追加像素偏移
offsetX=0
offsetY=0

# 尺寸控制 (posType=5/6 时忽略)
# imgScale: 百分比缩放 (100=原尺寸)
# imgWidth/imgHeight: 像素强制尺寸 (0=自动)
# 优先级: 宽高都设 > 仅宽 > 仅高 > 缩放百分比
imgScale=100
imgWidth=0
imgHeight=0

# 自定义图片目录绝对路径 (为空则默认 ./Image)
folder=
```

修改配置后一般无需重启 Explorer，只需重新打开当前窗口。

### 自定义路径

示例:

```ini
[image]
custom=true

# 某些特殊文件夹路径是 CLSID，例如:
# 此电脑: ::{20D04FE0-3AEA-1069-A2D8-08002B30309D}
# 快速访问: ::{679F85CB-0220-4080-B29B-5540CC05AAB6}
# 网络: ::{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}

[::{20D04FE0-3AEA-1069-A2D8-08002B30309D}]
img=myimage.png

[C:\Users\admin\Pictures\Camera Roll]
img=mypic.png
```

保存配置后刷新即可生效。

### 兼容性与重启说明

* 已支持现代 x64 Windows 10 / Windows 11 (包含 24H2 已验证可用)
* 主要目标是 Windows Explorer 与 Explorer 托管的文件对话框
* 当前发布包为 x64，不是 ARM64 主目标

重启后是否需要重新注册:

* 通常不需要，注册信息是持久化写入注册表的
* 只有在以下情况需要再次运行 Register.cmd:
* DLL 路径改变
* 你执行了卸载
* 系统策略或清理工具移除了注册信息

### 从源码构建

要求:

* Visual Studio 2022 (Desktop development with C++)
* MSBuild v143 工具集

命令:

```powershell
msbuild ExplorerBgTool.sln /m /p:Configuration=Release /p:Platform=x64
```

输出目录:

```text
Build/Release/x64/
```

### GitHub Actions 与发布流程

仓库包含:

* .github/workflows/ci.yml
  在 main push 和 PR 时构建 Release|x64，并上传构建产物。

* .github/workflows/release.yml
  在推送 v* 标签时自动构建并打包 ExplorerBgTool-{tag}-win-x64.zip，随后发布到 GitHub Release。

发布步骤:

* 提交代码并更新 CHANGELOG.md。
* 创建并推送标签，例如:

```powershell
git tag v1.1.1
git push origin v1.1.1
```

* 等待 Release 工作流完成。
* 在 Release 页面确认 zip 资源已上传。

### 注意事项

* 仅支持 png/jpg 图片，请确保图片有效，否则可能崩溃。
* 若出现崩溃，按住 ESC 再打开资源管理器可临时跳过加载，然后卸载或删除不兼容图片。
* 在企业环境下，WDAC/AppLocker/Smart App Control 可能阻止 shell 扩展加载。

其他信息:

[winmoes.com](https://winmoes.com/tools/12556.html)

---

## English Documentation

### Features

* Customize File Explorer background images
* Random switching between multiple images
* Adjustable image alpha
* Custom image position modes
* Per-path custom image mapping

### Contents

1. Overview
2. How to use
3. Config file
4. Custom paths
5. Compatibility and reboot behavior
6. Build from source
7. GitHub Actions and release flow
8. Notes

### Overview

#### Windows 11 Preview

Bottom-right:

```ini
posType=3
```

![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/083434.jpg)

Center:

```ini
posType=4
```

![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/084016.jpg)

Zoom and fill:

```ini
posType=6
imgAlpha=140
```

![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/085051.jpg)

#### Windows 10 Preview

```ini
posType=3
```

![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/085552.jpg)

#### File dialog

```ini
[load]
folderExt=true
...
```

![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/163113.jpg)

### How to use

1. Download the latest zip from Releases and extract it.
2. Put images into the Image folder.
3. Run Register.cmd.
4. Reopen Explorer windows.

Uninstall:

* Run Uninstall.cmd.
* Or run regsvr32 /u "your-path/ExplorerBgTool.dll" manually.

### Config file

Edit config.ini to control behavior:

```ini
[load]
# Enable extension in file dialogs
folderExt=false

# Suppress error popups
noerror=false

[image]
# Random image mode (requires at least 2 images)
random=false

# Enable per-path custom images
custom=false

# Position mode:
# 0=left-top 1=right-top 2=left-bottom 3=right-bottom
# 4=center 5=stretch 6=zoom-fill
# 7=left-center 8=right-center 9=top-center 10=bottom-center
posType=3

# Alpha from 0 to 255
imgAlpha=255

# Pixel offsets applied after position calculation
offsetX=0
offsetY=0

# Size controls (ignored in posType=5/6)
# imgScale: percent size (100 = original)
# imgWidth/imgHeight: pixel override (0 = auto)
# Priority: width+height > width only > height only > scale
imgScale=100
imgWidth=0
imgHeight=0

# Absolute image folder path (empty means ./Image)
folder=
```

Usually you do not need to restart Explorer after config changes; reopening the current window is enough.

### Custom paths

Example:

```ini
[image]
custom=true

# Some special folders use CLSID paths, for example:
# This PC: ::{20D04FE0-3AEA-1069-A2D8-08002B30309D}
# Quick Access: ::{679F85CB-0220-4080-B29B-5540CC05AAB6}
# Network: ::{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}

[::{20D04FE0-3AEA-1069-A2D8-08002B30309D}]
img=myimage.png

[C:\Users\admin\Pictures\Camera Roll]
img=mypic.png
```

Changes apply after saving and refreshing.

### Compatibility and reboot behavior

* Works on modern x64 Windows 10 and Windows 11 (including 24H2 reported working)
* Targets Windows Explorer and Explorer-hosted dialogs
* Current release package targets x64, not ARM64-first

Do I need to run Register.cmd again after reboot?

* Normally no. Registration is persistent.
* Re-register only if:
* DLL location changed
* You ran uninstall
* Policy/cleanup removed registry entries

### Build from source

Requirements:

* Visual Studio 2022 with Desktop development with C++
* MSBuild v143 toolset

Build:

```powershell
msbuild ExplorerBgTool.sln /m /p:Configuration=Release /p:Platform=x64
```

Output:

```text
Build/Release/x64/
```

### GitHub Actions and release flow

Included workflows:

* .github/workflows/ci.yml
  Builds Release|x64 on main pushes and pull requests. Uploads build artifacts.

* .github/workflows/release.yml
  Runs on v* tags, builds Release|x64, packages ExplorerBgTool-{tag}-win-x64.zip, and publishes a GitHub Release.

Release steps:

* Commit changes and update CHANGELOG.md.
* Create and push a version tag, for example:

```powershell
git tag v1.1.1
git push origin v1.1.1
```

* Wait for the Release workflow.
* Verify the uploaded zip in the Release page.

### Notes

* Only png/jpg are supported. Invalid images can crash Explorer.
* If Explorer crashes, hold ESC while opening Explorer to skip image loading, then uninstall or remove bad images.
* In managed enterprise environments, WDAC/AppLocker/Smart App Control may block shell extensions.

More info:

[winmoes.com](https://winmoes.com/tools/12556.html)
