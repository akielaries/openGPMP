FROM ubuntu:latest
RUN apt-get update -y
WORKDIR /app
COPY . /app
CMD chmod +x test.sh
CMD ./test

