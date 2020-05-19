FROM ubuntu:18.04
RUN apt-get update && apt-get install -y \
        xz-utils \
        libstdc++-8-dev \
        cmake \
        curl \
   && rm -rf /var/lib/apt/lists/* \
RUN mkdir /usr/vendor
WORKDIR /usr/vendor
RUN curl -SL https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz \
    | tar -xJC . \
    && mv clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04 clang10
    && rm -rf
ENV PATH="/usr/vendor/clang10/bin:${PATH}"
COPY . /usr/src/plasmaconduit
WORKDIR /usr/src/plasmaconduit
RUN find . -iwholename '*cmake*' -not -name CMakeLists.txt -delete
RUN cmake -DCMAKE_BUILD_TYPE=Release .
RUN make -j
ENTRYPOINT ["./scripts/entrypoint.sh"]
