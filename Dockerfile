FROM ghcr.io/userver-framework/ubuntu-24.04-userver:latest
RUN apt update
RUN apt install -y make
RUN apt install -y g++
RUN apt install -y git
RUN apt install -y gcc
RUN apt install -y valgrind
RUN apt install -y bash
RUN apt install -y cmake

ENTRYPOINT ["usr/bin/bash"]
