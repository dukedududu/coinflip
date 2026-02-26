# Coin Flip Game (Qt/C++)

![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![Framework](https://img.shields.io/badge/framework-Qt-green)
![License](https://img.shields.io/badge/license-MIT-lightgrey)

## 📖 Introduction / 项目简介

This is a classic **Coin Flip** puzzle game developed using **C++** and the **Qt Framework**. The goal is to flip all the coins to the same side (or a specific pattern) to win the level. It features a graphical user interface with animations and sound effects.

这是一个使用 **C++** 和 **Qt 框架** 开发的经典 **翻金币** 益智游戏。玩家需要通过点击金币将其翻转，最终使所有金币达到指定状态即可过关。游戏包含完整的图形界面、动画效果和音效。

## ✨ Features / 功能特性

*   **Level Selection**: Multiple levels with increasing difficulty.
*   **Game Mechanics**: Flipping a coin also flips its neighbors.
*   **GUI**: Rich graphical interface using Qt Widgets.
*   **Animation**: Smooth coin flipping animations.
*   **Sound**: Background music and sound effects.

## 🛠️ Tech Stack / 技术栈

*   **Language**: C++
*   **Framework**: Qt 5 (Widgets)
*   **Tools**: Qt Creator, qmake

## ⚡ Installation & Build / 安装与构建

### Prerequisites / 前置要求
*   **Qt 5.x** or higher (with Qt Creator recommended)
*   **C++ Compiler** (MinGW, MSVC, or GCC)

### Steps / 步骤

1.  **Clone the repository**:
    ```bash
    git clone https://github.com/dukedududu/coinflip.git
    ```

2.  **Open Project**:
    *   Launch **Qt Creator**.
    *   Open the `coinflip.pro` file.

3.  **Build & Run**:
    *   Configure the project kit (Select your installed Qt kit).
    *   Click the **Run** button (green arrow) or press `Ctrl+R`.

## 📂 Project Structure / 项目结构

*   `coinflip.pro`: Project configuration file.
*   `main.cpp`: Application entry point.
*   `mainscene.cpp/h`: Main menu scene.
*   `chooselevelscene.cpp/h`: Level selection screen.
*   `playscene.cpp/h`: Core gameplay scene.
*   `mycoin.cpp/h`: Custom coin widget with animation logic.
*   `dataconfig.cpp/h`: Level data configuration.
*   `res.qrc`: Resource collection (images, sounds).

## 🤝 Contributing / 贡献指南

Contributions are welcome! If you find any bugs or want to add new levels, please submit a Pull Request.
欢迎提交 PR 修复 Bug 或添加新关卡！

## 📄 License / 许可证

This project is licensed under the MIT License.
