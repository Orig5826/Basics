from OpenSSL.crypto import dump_certificate, load_certificate
from OpenSSL.crypto import FILETYPE_PEM, FILETYPE_TEXT, FILETYPE_ASN1
import sys
import OpenSSL

def cert_x509_base64(cert_fname):
    with open(cert_fname, 'r') as pf:
        cert_cont = pf.read()

    cert = load_certificate(FILETYPE_PEM, cert_cont)
    cert_context = dump_certificate(FILETYPE_TEXT, cert)

    cert_display = str(
        cert_context, encoding='utf-8')
    print(cert_display)

def cert_x509_der(cert_fname):
    with open(cert_fname, 'rb') as pf:
        cert_cont = pf.read()

    cert = load_certificate(FILETYPE_ASN1, cert_cont)
    cert_context = dump_certificate(FILETYPE_TEXT, cert)

    cert_display = str(
        cert_context, encoding='utf-8')
    print(cert_display)


if __name__ == "__main__":
    if len(sys.argv) != 3 :
        print('[cmd] cert_fname code_type\r\ncode_type=0: base64\r\ncode_type=1: der')
        sys.exit(-1)
    if sys.argv[2] == '0':
        cert_x509_base64(sys.argv[1])
    elif sys.argv[2] == '1':
        cert_x509_der(sys.argv[1])
    else:
        print('@param is error!')
