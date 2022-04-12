FROM nginx
COPY build /usr/share/nginx/html
COPY config.conf /etc/nginx/conf.d/default.conf


RUN apt-get update
RUN apt-get install -y software-properties-common gnupg ca-certificates \
python3-acme python3-certbot python3-mock python3-openssl \
python3-pkg-resources python3-pyparsing python3-zope.interface
RUN apt install python3-certbot-nginx




