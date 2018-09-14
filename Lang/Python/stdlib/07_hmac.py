#!/usr/bin/python
# -*- coding: utf-8 -*-
import hmac

# ---------------------------------------------------------------
#                 HMAC
# [Message]
# "12345678"   -> 31 32 33 34 35 36 37 38
# [Key]
#              -> 11 22 33 44 55 66 77 88
# [hmac_md5]      a8a22c7fa0dbdd7b16f34a3b51f15a92
# [hmac_sha1]     5cf0a5ba4298b9f219b764295991a69ba5493c51
# [hmac_sha224]   875f4116fab43393ce81084af024ea111c2d5e8ae2e2c6d363e0467d
# [hmac_sha256]   f4a3053b8398dd380d1c1df7332bbf9767909d91f78b150fd2bf591f129140b5
# [hmac_sha384]   b45d41ce3a87d70b0b9e5167911ca06ddf1451630a564fb49cee9cc3cee7a6b39f9bd4980e8deeb4c990646c0f1d02a7
# [hmac_sha512]   7ee6a681baf67bf5464d4dd73018d7cea7c0ca16924d66362092da514bc242c1fb933afd7704184c606c87bf4087a32d7c046830d15bd58fc0bc56d0e89169cb
# ---------------------------------------------------------------

def hmac_sha(mod):
	message = b"12345678"
	key = b"\x11\x22\x33\x44\x55\x66\x77\x88"
	h = hmac.new(key, message, digestmod=mod)
	print("[hmac_{0:6s}]： {1}".format(mod,h.hexdigest()) )

hmac_sha("md5")
hmac_sha("sha1")
hmac_sha("sha224")
hmac_sha("sha256")
hmac_sha("sha384")
hmac_sha("sha512")
