FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -qy \
    && apt-get upgrade -qy \
    && apt-get install -y \
    git \
    bridge-utils \
    g++-12 \
    g++-10 \
    libperl-dev \
    linux-tools-generic \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /benchmarks
RUN git clone https://github.com/brendangregg/FlameGraph.git
RUN git clone https://github.com/jrfonseca/gprof2dot.git

COPY . /benchmarks

WORKDIR /benchmarks

RUN make
