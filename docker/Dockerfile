# Ubuntu 22.04 LTS以降を想定
FROM ubuntu:latest

# 必要なパッケージをインストール
RUN apt update
RUN sudo apt install build-essential git make \
pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev \
libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev

# 公式からソースを取得
RUN git clone https://github.com/libsdl-org/SDL.git /SDL
WORKDIR /SDL/build-scripts
RUN cmake ../CMakeLists.txt -B .
RUN make
RUN make install

CMD ["/bin/bash"]