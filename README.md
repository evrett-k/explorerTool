# ExplorerBgTool
Let your Explorer have a custom background image for Windows 11 and WIndows 10

* 自定义文件资源管理器背景图片
* 支持多个图片随机
* 可调整图片透明度
* 可自定义图片显示位置
* 支持单独为某个路径设置背景图片

#
* Customize Explorer ItemView background image
* Supports random switching of multiple pictures
* Adjustable picture alpha
* Customizable image display position
* Support setting background image for a path separately

## 目录
1. [预览 (Overview)](#预览-overview)
2. [使用方法 (How to use)](#使用方法-how-to-use)
3. [配置文件 (Config)](#配置文件-config)
4. [自定义路径 (Custom)](#自定义路径-custom)
5. [其他 (Other)](#其他-other)
## 预览 (Overview)
### Windows 11

> 右下角 (Bottom right)
```ini
posType=3
```
![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/083434.jpg)

> 居中 (Center)
```ini
posType=4
```
![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/084016.jpg)

> 缩放和填充 (Zoom and fill)

```ini
posType=6
imgAlpha=140
```
![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/085051.jpg)

### Windows 10
```ini
posType=3
```
![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/085552.jpg)

### 文件对话框 (File Dialog)
```ini
[load]
folderExt=true
...
```
![image](https://github.com/Maplespe/explorerTool/blob/main/Screenshot/163113.jpg)

## 使用方法 (How to use)
从Release页面下载最新版本压缩包并解压

将图像放入 "`Image`" 文件夹

> 运行 "`注册_Register.cmd`" 文件

然后重新打开您的文件资源管理器窗口即可

要卸载请运行 "`卸载_Uninstall.cmd`" 文件

您也可以使用命令提示符手动注册/卸载

> `regsvr32 (/u) "你的路径/ExplorerBgTool.dll"`
#
Download the latest version of the zip from the Release page and unzip it

Put your image in the `"image"` folder

> Run the "`注册_Register.cmd`" file

Just reopen your file explorer window

To uninstall run the "`卸载_Uninstall.cmd`" file

You can also use the command to register or uninstall

> `regsvr32 (/u) "you path/ExplorerBgTool.dll"`

## 配置文件 (Config)
您可以通过修改 "`config.ini`"来修改一些样式

You can modify some styles by modifying "`config.ini`"
```ini
[load]
#指定是否在文件对话框中启用
#Specify whether or not to enable in the file dialog.
folderExt=false
#指定是否忽略错误(即出现错误不显示错误弹窗)
#Specify whether or not to ignore errors (i.e. not show error popups when errors occur).
noerror=false
[image]
#指定图片是否随机显示 您必须放入至少两张图像
#Specifies whether the image is displayed randomly, you need to put at least 2 images
random=true
#是否启用指定自定义文件夹的图片
#Enable custom specified folder pictures
custom=false
#图片显示位置 0=左上角 1=右上角 2=左下角 3=右下角 4=居中 5=缩放 6=缩放并填充; 默认为3 右下角
#Image display position
#0=Left top 1=Right top 2=Left right 3=Right bottom 4=Center 5=Stretch 6=Zoom and fill
posType=0
#图片的不透明度 范围0-255
#Alpha 0-255 of image
imgAlpha=255
#自定义图片目录绝对路径 (为空则默认 ./image)
#Custom image folder absolute path (empty defaults to . /image)
folder=
```

修改后 您无需重启文件资源管理器 只需重新打开当前窗口即可

After modification you don't need to restart file explorer, just reopen the current window

## 自定义路径 (Custom)
示例 (Example)

Config.ini
```ini
[image]
custom=true

#括号内填入路径 请先将图片放入Image文件夹然后 img= 指定Image文件夹里的文件名 是文件名不是完整路径!
#Please put the picture in the Image folder first, and then img=specify the file name in the Image folder Is the file name, not the full path!
#某些特殊文件夹路径是CLSID 例如:
#Some special folder paths are CLSID For example:
#此电脑 This PC
#::{20D04FE0-3AEA-1069-A2D8-08002B30309D}
#快速访问 Quick access
#::{679F85CB-0220-4080-B29B-5540CC05AAB6}
#网络 Network
#::{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}

#示例 (Example)
[::{20D04FE0-3AEA-1069-A2D8-08002B30309D}]
img=myimage.png

[C:\Users\admin\Pictures\Camera Roll]
img=mypic.png
#保存文件后 刷新 立即生效(Takes effect as soon as the file is saved)
```
## 注意事项 (Attention)
图片仅支持`png、jpg`格式 请确保为有效的图片 否则可能引发崩溃!

如果出现崩溃 请按住`ESC`键再打开文件资源管理器(这不会加载图像) 然后卸载本工具或删除不兼容的图像
#
The image only supports `png, jpg` format, please make sure it is a valid image, otherwise it may cause a crash!

If there is a crash hold down the `ESC` key and open the file explorer (this will not load the image) then uninstall the tool or delete the incompatible image
## 其他 (Other)
有关工具和介绍请访问：

For tools and introductions, please visit:

[winmoes.com](https://winmoes.com/tools/12556.html)

## Compatibility

* Works on modern x64 Windows 10 and Windows 11 (including 24H2 reported working).
* This project targets Windows Explorer and Explorer-hosted file dialogs.
* ARM64 is not the primary target for this repository's x64 release package.

### After reboot

You do not need to run Register.cmd after every reboot.

Registration is persistent through COM and Explorer extension registry entries. Run Register.cmd again only if:

* the DLL path changed,
* you unregistered the component,
* system policy or cleanup removed registry entries.

## Build from source

Requirements:

* Visual Studio 2022 with C++ Desktop Development workload
* MSBuild v143 toolset

Build command:

```powershell
msbuild ExplorerBgTool.sln /m /p:Configuration=Release /p:Platform=x64
```

Output directory:

```text
Build/Release/x64/
```

## GitHub Actions

This repo now includes:

* `.github/workflows/ci.yml`
	Builds `Release|x64` on push to `main` and on pull requests.
	Uploads `Build/Release/x64` as a workflow artifact.

* `.github/workflows/release.yml`
	Triggers on tags matching `v*`.
	Builds `Release|x64`.
	Creates `ExplorerBgTool-<tag>-win-x64.zip` from `Build/Release/x64`.
	Publishes/updates the GitHub Release and uploads the zip.

## Release process

1. Commit changes and update `CHANGELOG.md`.
2. Create and push a version tag, for example:

```powershell
git tag v1.1.1
git push origin v1.1.1
```

3. Wait for the `Release` workflow to complete.
4. Verify the Release page includes the generated zip asset.

## Security and deployment notes

* Shell extensions can be blocked by enterprise security policies (WDAC/AppLocker/Smart App Control).
* If loading fails only on managed devices, verify policy and code-signing requirements.
