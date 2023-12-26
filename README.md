# cpp
cppの知識

## Setting

DockerでC++をビルドできる環境を用意する。  

サンプルDockerfile

``` docker
# Build
FROM ubuntu:latest AS dev
ARG FILE_NAME

RUN apt update && apt install -y g++ gcc

COPY ${FILE_NAME} /app/
WORKDIR /app
RUN g++ ${FILE_NAME} -o a

# Run
FROM ubuntu:latest AS prod
WORKDIR /app
COPY --from=dev /app/a /app/a 
# Install required packages if you need
#RUN apk add --quiet --no-cache \
#  hoge 

CMD ["./a"]
```

build & Run & delete container

``` bash
cd helloWorld
docker build -t cpp-env:1.0 --build-arg FILE_NAME=helloWorld.cpp .
docker run  --name helloworld -it cpp-env:1.0
docker rm -f helloworld
```

実行ログ

``` sh
niamu@home-workspace MINGW64 ~/_work
$ cd cpp/helloWorld/

niamu@home-workspace MINGW64 ~/_work/cpp/helloWorld (create-docker-env)
$ docker build -t cpp-env:1.0 --build-arg FILE_NAME=helloWorld.cpp .
[+] Building 131.4s (13/13) FINISHED                                                                                                                                                         docker:default 
 => [internal] load .dockerignore                                                                                                                                                                      0.0s 
 => => transferring context: 2B                                                                                                                                                                        0.0s 
 => [internal] load build definition from Dockerfile                                                                                                                                                   0.0s 
 => => transferring dockerfile: 384B                                                                                                                                                                   0.0s 
 => [internal] load metadata for docker.io/library/ubuntu:latest                                                                                                                                       1.4s
 => [auth] library/ubuntu:pull token for registry-1.docker.io                                                                                                                                          0.0s
 => [internal] load build context                                                                                                                                                                      0.0s
 => => transferring context: 35B                                                                                                                                                                       0.0s
 => CACHED [dev 1/5] FROM docker.io/library/ubuntu:latest@sha256:6042500cf4b44023ea1894effe7890666b0c5c7871ed83a97c36c76ae560bb9b                                                                      0.0s
 => [dev 2/5] RUN apt update && apt install -y g++ gcc                                                                                                                                               128.9s
 => [dev 3/5] COPY helloWorld.cpp /app/                                                                                                                                                                0.0s
 => [dev 4/5] WORKDIR /app                                                                                                                                                                             0.0s
 => [dev 5/5] RUN g++ helloWorld.cpp -o a                                                                                                                                                              0.9s
 => CACHED [prod 2/3] WORKDIR /app                                                                                                                                                                     0.0s
 => CACHED [prod 3/3] COPY --from=dev /app/a /app/a                                                                                                                                                    0.0s
 => exporting to image                                                                                                                                                                                 0.0s
 => => exporting layers                                                                                                                                                                                0.0s
 => => writing image sha256:06bf04fa2397daca13ec68499f04b198ff9010df04ca62f43cb6697578f44429                                                                                                           0.0s
 => => naming to docker.io/library/cpp-env:1.0                                                                                                                                                         0.0s 

What's Next?
  View a summary of image vulnerabilities and recommendations → docker scout quickview
  
niamu@home-workspace MINGW64 ~/_work/cpp/helloWorld (create-docker-env)
$ docker run  --name helloworld -it cpp-env:1.0 
Hello world !!!
niamu@home-workspace MINGW64 ~/_work/cpp/helloWorld (create-docker-env)
$ docker ps -a
CONTAINER ID   IMAGE         COMMAND   CREATED          STATUS                      PORTS     NAMES
642f57f155d9   cpp-env:1.0   "./a"     31 seconds ago   Exited (0) 30 seconds ago             helloworld

niamu@home-workspace MINGW64 ~/_work/cpp/helloWorld (create-docker-env)
$ docker rm -f helloworld
helloworld

niamu@home-workspace MINGW64 ~/_work/cpp/helloWorld (create-docker-env)
$ docker images
REPOSITORY   TAG       IMAGE ID       CREATED          SIZE
cpp-env      1.0       06bf04fa2397   13 minutes ago   77.9MB

niamu@home-workspace MINGW64 ~/_work/cpp/helloWorld (create-docker-env)
$
```