NAME := $(shell cat NAME)
PORT := $(shell cat PORT)
URL  := https://forms.office.com/r/k2fZRWpBDL

help:
	@echo "dist   : build the target and distribute to docker/release"
	@echo "build  : build the docker image"
	@echo "run    : run the docker container"
	@echo "exploit: launch the exploit"
	@echo "test   : test the docker/exploit"
	@echo "submit : zip for submission"

dist:
	(cd source/src; rm -f target; make)
	cp -f source/src/target docker/

build:
	(cd docker; docker build -t $(NAME) .)

run:
	docker run -p $(PORT):9999 --rm -i -t $(NAME)

submit:
	zip -r ../$(NAME).zip .
	@echo "Please upload ../$(NAME).zip to a shareable link and submit to $(URL)"

exploit:
	chmod +x source/exploit.py
	PORT=$(PORT) REMOTE=1 source/exploit.py

test:
	chmod +x source/test.sh
	@source/test.sh

.PHONY: dist build run submit exploit test help
