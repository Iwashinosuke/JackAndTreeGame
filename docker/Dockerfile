#! bin/bash

# Ubuntu 22.04 LTS以降を想定
FROM ubuntu:latest

# 必要なパッケージをインストール
RUN apt update && \
    apt install -y build-essential git make mingw-w64 unzip wget \
    pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
    libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
    libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
    libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
    libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev \
    libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev \
    libfreetype6-dev libglib2.0-dev libcairo2-dev meson gtk-doc-tools

# 公式からcloneしてビルド
# (Linux向けビルドや、テストファイル、公式のサンプルのコンパイルに使用)
WORKDIR /SDL
RUN wget https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.2.6.zip -O SDL3.zip && \
    unzip SDL3.zip && \
    mv SDL-release-3.2.6/ SDL3/ && \
    wget https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-3.2.2.zip -O SDL3_image.zip && \
    unzip SDL3_image.zip && \
    mv SDL_image-release-3.2.2/ SDL3_image/ && \
    # wget https://github.com/libsdl-org/SDL_ttf/archive/refs/tags/release-3.2.0.zip -O SDL3_ttf.zip && \
    # unzip SDL3_ttf.zip && \
    # mv SDL_ttf-release-3.2.0/ SDL3_ttf/ && \
    wget https://github.com/libsdl-org/SDL_ttf/releases/download/release-3.2.0/SDL3_ttf-3.2.0.zip -O SDL3_ttf.zip && \
    unzip SDL3_ttf.zip && \
    mv SDL3_ttf-3.2.0/ SDL3_ttf/
WORKDIR /SDL/SDL3/build-scripts
RUN cmake ../CMakeLists.txt -B . && \
    make && \
    make install
WORKDIR /SDL/SDL3_image/build-scripts
RUN cmake ../CMakeLists.txt -B . && \
    make && \
    make install
WORKDIR /SDL/SDL3_ttf/build-scripts
RUN cmake ../CMakeLists.txt -B . && \
    make && \
    make install

# RUN git clone https://github.com/libsdl-org/SDL.git /SDL/SDL3
# WORKDIR /SDL/SDL3/build-scripts
# RUN cmake ../CMakeLists.txt -B . && \
#     make && \
#     make install

# RUN git clone https://github.com/libsdl-org/SDL_image.git /SDL/SDL3_image
# WORKDIR /SDL/SDL3_image/build-scripts
# RUN cmake ../CMakeLists.txt -B . && \
#     make && \
#     make install

# RUN git clone https://github.com/libsdl-org/SDL_ttf.git /SDL/SDL3_ttf
# WORKDIR /SDL/SDL3_ttf/build-scripts
# RUN cmake ../CMakeLists.txt -B . && \
#     make && \
#     make install

# Windows向けクロスコンパイル用ライブラリ取得
WORKDIR /SDL
RUN wget https://www.libsdl.org/release/SDL3-devel-3.2.8-mingw.zip -O SDL3-mingw.zip && \
     unzip SDL3-mingw.zip && \
    mv SDL3-3.2.8/ SDL3-mingw/ && \
    cp -r SDL3-mingw/x86_64-w64-mingw32/* /usr/x86_64-w64-mingw32/

RUN wget https://github.com/libsdl-org/SDL_image/releases/download/release-3.2.2/SDL3_image-devel-3.2.2-mingw.zip -O SDL3image-mingw.zip && \
    unzip SDL3image-mingw.zip && \
   mv SDL3_image-3.2.2/ SDL3image-mingw/ && \
   cp -r SDL3image-mingw/x86_64-w64-mingw32/* /usr/x86_64-w64-mingw32/

RUN wget https://github.com/libsdl-org/SDL_ttf/releases/download/release-3.2.0/SDL3_ttf-devel-3.2.0-mingw.zip -O SDL3ttf-mingw.zip && \
   unzip SDL3ttf-mingw.zip && \
  mv SDL3_ttf-3.2.0/ SDL3ttf-mingw/ && \
  cp -r SDL3ttf-mingw/x86_64-w64-mingw32/* /usr/x86_64-w64-mingw32/

CMD ["/bin/bash"]