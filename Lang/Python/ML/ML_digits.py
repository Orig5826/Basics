import matplotlib.pyplot as plt
from sklearn import datasets

digits = datasets.load_digits()

images_and_labels = list(zip(digits.images, digits.target))
plt.figure(figsize=(8, 6), dpi=200)
for index, (image, label) in enumerate(images_and_labels[:8]):
    plt.subplot(2, 4, index + 1)
    plt.axis('off')
    plt.imshow(image, cmap=plt.cm.gray_r, interpolation='nearest')
    plt.title('Digit:%i' % label, fontsize=20)
# plt.show()

print("shape of raw image data:{0}".format(digits.images.shape))
print("shape of raw image data:{0}".format(digits.data.shape))

