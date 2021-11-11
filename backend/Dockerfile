FROM ubuntu:20.04

COPY . /app
WORKDIR /app
ARG DEBIAN_FRONTEND=noninteractive
RUN rm -rf nlohmann
RUN rm -rf served served.build
RUN apt update
RUN apt -y install make cmake g++ wget git
RUN apt -y install libmysqlcppconn-dev
RUN apt -y install libboost-all-dev
RUN bash ./setup_json.sh
RUN bash ./setup_served.sh
RUN make compile
RUN /sbin/ldconfig -v
ENV EXECUTE_TYPE=rest

CMD ["./main"]
