FROM alpine:3.13.2

RUN apk add thttpd

RUN adduser -D static
USER static
WORKDIR /home/static

COPY . app

CMD ["thttpd", "-D", "-h", "0.0.0.0", "-p", "3000", "-d", "/home/static/app/", "-u", "static", "-l", "-", "-M", "60"]