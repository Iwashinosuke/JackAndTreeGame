FROM ubuntu:latest

RUN apt update
RUN apt -y install build-essential git make cmake

# 公式からソースを取得
RUN git clone https://github.com/libsdl-org/SDL.git /SDL
WORKDIR /SDL/build-scripts
RUN cmake ../CMakeLists.txt -B .
RUN make
RUN make install

CMD ["/bin/bash"]