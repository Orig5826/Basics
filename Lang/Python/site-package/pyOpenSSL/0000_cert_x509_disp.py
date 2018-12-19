from OpenSSL.crypto import dump_certificate, load_certificate
from OpenSSL.crypto import FILETYPE_PEM, FILETYPE_TEXT
import sys


def cert_x509_disp(cert_fname):
    # cert_fname = 'x.509.cer'
    with open(cert_fname, 'r') as pf:
        cert_cont = pf.read()

    cert = load_certificate(FILETYPE_PEM, cert_cont)
    # print(cert)
    cert_context = dump_certificate(FILETYPE_TEXT, cert)
    # print(cert_context)

    cert_display = str(
        cert_context, encoding='utf-8')
    print(cert_display)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print('argv is error!')
    cert_x509_disp(sys.argv[1])
