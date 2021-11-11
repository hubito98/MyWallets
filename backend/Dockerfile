FROM ubuntu:20.04

COPY . /app
WORKDIR /app
ARG DEBIAN_FRONTEND=noninteractive
RUN apt update
RUN apt -y install make=4.2.1-1.2 cmake=3.16.3-1ubuntu1 g++=4:9.3.0-1ubuntu2 git=1:2.25.1-1ubuntu3.2
RUN apt -y install libmysqlcppconn-dev=1.1.12-4ubuntu2
RUN apt -y install libboost-all-dev=1.71.0.0ubuntu2
RUN bash ./setup_json.sh
RUN bash ./setup_served.sh
RUN make compile
RUN /sbin/ldconfig -v

CMD ["./main"]
