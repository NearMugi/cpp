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