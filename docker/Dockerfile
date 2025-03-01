#! bin/bash

# Ubuntu 22.04 LTS以降を想定
FROM ubuntu:latest

# 必要なパッケージをインストール
RUN apt update && \
    apt install build-essential git make mingw-w64 unzip wget \
    pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
    libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
    libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
    libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
    libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev \
    libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev

# 公式からcloneしてビルド
# (Linux向けビルドではこちらを使用)
RUN git clone https://github.com/libsdl-org/SDL.git /SDL/SDL3
WORKDIR /SDL/SDL3/build-scripts
RUN cmake ../CMakeLists.txt -B . && \
    make && \
    make install

# Windows向けクロスコンパイル用ライブラリ取得
RUN wget https://www.libsdl.org/release/SDL3-devel-3.2.4-mingw.zip -O SDL3-mingw.zip -P /SDL
WORKDIR /SDL
RUN unzip SDL3-mingw.zip && \
    mv SDL3-3.2.4/ SDL3-mingw/ && \
    cp -r SDL3-mingw/x86_64-w64-mingw32/* /usr/x86_64-w64-mingw32/

CMD ["/bin/bash"]