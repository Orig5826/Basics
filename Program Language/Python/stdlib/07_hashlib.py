import hashlib

# ---------------------------------------------------------------
# [Message]
# "12345678"
# [Sha256]
# ef797c8118f02dfb649607dd5d3f8c7623048c9c063d532cc95c5ed7a898a64f
# ---------------------------------------------------------------
plain = b"12345678"
m = hashlib.sha256()
m.update(plain)
ret = m.digest()
print(m.hexdigest())
