FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive
RUN apt update
RUN apt -y install openjdk-11-jdk
RUN apt -y install wait-for-it=0.0~git20180723-1

COPY . /app
WORKDIR /app
RUN ./mvnw compile
RUN ./mvnw package -Dmaven.test.skip
CMD ["/usr/bin/java", "-jar" , "target/wallettimeline-1.0.0.jar"]
