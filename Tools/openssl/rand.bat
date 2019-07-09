@echo off
openssl rand -out random.bin 16
openssl rand -hex -out random.txt 16
openssl rand -base64 -out random.pem 16
