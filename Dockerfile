# Build
FROM ubuntu:latest AS dev
ARG TARGET_FOLDER
ARG TARGET_FILE

RUN apt update && apt install -y g++ gcc

COPY ${TARGET_FOLDER}/${TARGET_FILE} /app/
WORKDIR /app
RUN g++ ${TARGET_FILE} -o a

# Run
FROM ubuntu:latest AS prod
WORKDIR /app
COPY --from=dev /app/a /app/a 
# Install required packages if you need
#RUN apk add --quiet --no-cache \
#  hoge 

CMD ["./a"]