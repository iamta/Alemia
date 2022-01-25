FROM python:3.8-slim-buster

WORKDIR /app

COPY . .
WORKDIR /app/backend

RUN pip3 install -r requirements.txt
RUN pip3 install cpplint gunicorn

EXPOSE 3001
CMD [ "gunicorn", "-b" , ":3001", "server:app"]