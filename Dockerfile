FROM ghcr.io/qmk/qmk_cli

WORKDIR /qmk_firmware

COPY requirements.txt .

RUN pip install -r requirements.txt
