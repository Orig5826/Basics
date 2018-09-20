/*
 * @breaf ecc demo
 *     
 */

#include "alg_demo.h"
#include <openssl/ecdsa.h>
#include <openssl/sha.h>

void ecdh_demo(void)
{
	EC_KEY *key1, *key2;
	const EC_POINT *pubkey1, *pubkey2;
	EC_GROUP *group1, *group2;
	unsigned int ret, nid;
	BIO *berr;
	EC_builtin_curve *curves;
	int crv_len;
	uint8_t shareKey1[128], shareKey2[128];
	int len1, len2;
	/* 构造 EC_KEY 数据结构 */
	key1 = EC_KEY_new();
	if (key1 == NULL)
	{
		printf("EC_KEY_new err!\n");
		return;
	}
	key2 = EC_KEY_new();
	if (key2 == NULL)
	{
		printf("EC_KEY_new err!\n");
		return;
	}
	/* 获取实现的椭圆曲线个数 */
	crv_len = EC_get_builtin_curves(NULL, 0);
	curves = (EC_builtin_curve *)malloc(sizeof(EC_builtin_curve) * crv_len);
	/* 获取椭圆曲线列表 */
	EC_get_builtin_curves(curves, crv_len);
	/*
    nid=curves[0].nid;会有错误，原因是密钥太短
    */
	/* 选取一种椭圆曲线 */
	nid = curves[25].nid;
	/* 根据选择的椭圆曲线生成密钥参数 group */
	group1 = EC_GROUP_new_by_curve_name(nid);
	if (group1 == NULL)
	{
		printf("EC_GROUP_new_by_curve_name err!\n");
		return;
	}
	group2 = EC_GROUP_new_by_curve_name(nid);
	if (group1 == NULL)
	{
		printf("EC_GROUP_new_by_curve_name err!\n");
		return;
	}
	/* 设置密钥参数 */
	ret = EC_KEY_set_group(key1, group1);
	if (ret != 1)
	{
		printf("EC_KEY_set_group err.\n");
		return;
	}
	ret = EC_KEY_set_group(key2, group2);
	if (ret != 1)
	{
		printf("EC_KEY_set_group err.\n");
		return;
	}
	/* 生成密钥 */
	ret = EC_KEY_generate_key(key1);
	if (ret != 1)
	{
		printf("EC_KEY_generate_key err.\n");
		return;
	}
	ret = EC_KEY_generate_key(key2);
	if (ret != 1)
	{
		printf("EC_KEY_generate_key err.\n");
		return;
	}
	/* 检查密钥 */
	ret = EC_KEY_check_key(key1);
	if (ret != 1)
	{
		printf("check key err.\n");
		return;
	}
	ret = EC_KEY_check_key(key2);
	if (ret != 1)
	{
		printf("check key err.\n");
		return;
	}

	/* ... */
	berr = BIO_new(BIO_s_file());

	/* 获取对方公钥，不能直接引用 */
	pubkey2 = EC_KEY_get0_public_key(key2);
	/* 生成一方的共享密钥 */
	len1 = ECDH_compute_key(shareKey1, 128, pubkey2, key1, NULL);
	pubkey1 = EC_KEY_get0_public_key(key1);
	/* 生成另一方共享密钥 */
	len2 = ECDH_compute_key(shareKey2, 128, pubkey1, key2, NULL);
	if (len1 != len2)
	{
		printf("共享密钥长度不相等？\n");
	}
	else
	{
		ret = memcmp(shareKey1, shareKey2, len1);
		if (ret == 0)
		{
			printf("共享密钥为\n");
			display(shareKey1,len1);
		}
		else
		{
			printf("生成共享密钥失败\n");
		}
	}
	BIO_free(berr);
	EC_KEY_free(key1);
	EC_KEY_free(key2);
	free(curves);
}

void ecdsa_demo(void)
{
	EC_KEY * key;
	EC_builtin_curve *curves;
	EC_GROUP * group;
	BIO *berr;

	size_t crv_len;
	int nid,ret,size;

	// 待签名的数据
	const uint8_t data[] = "12345678";
	const uint32_t len = 8;
	uint8_t digest[32];
	uint8_t * signature;
	uint32_t sig_len;

	// SHA256_CTX
	SHA256_CTX sha256_ctx;
	printf("Data:\n");
	display(data,len);

	/* 构造 EC_KEY 数据结构 */
	key = EC_KEY_new();

	/* 获取实现的椭圆曲线个数 */
	crv_len = EC_get_builtin_curves(NULL, 0);
	curves = (EC_builtin_curve *)malloc(sizeof(EC_builtin_curve) * crv_len);
	/* 获取椭圆曲线列表 */
	EC_get_builtin_curves(curves, crv_len);

	/* 选取一种椭圆曲线 */
	nid = curves[25].nid;
	/* 根据选择的椭圆曲线生成密钥参数 group */
	group = EC_GROUP_new_by_curve_name(nid);
	if (group == NULL)
	{
		printf("EC_GROUP_new_by_curve_name err!\n");
		return;
	}

	/* 设置密钥参数 */
	ret = EC_KEY_set_group(key, group);
	if (ret != 1)
	{
		printf("EC_KEY_set_group err.\n");
		return;
	}

	/* 生成密钥 */
	ret = EC_KEY_generate_key(key);
	if (ret != 1)
	{
		printf("EC_KEY_generate_key err.\n");
		return;
	}

	/* 检查密钥 */
	ret = EC_KEY_check_key(key);
	if (ret != 1)
	{
		printf("check key err.\n");
		return;
	}

	// 计算sha256 Hash值
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx,data,len);
	SHA256_Final(digest,&sha256_ctx);
	printf("Digest:\n");
	display(digest,32);

	/* 获取密钥大小 */
	size = ECDSA_size(key);
	printf("密钥size = %d \n", size);
	signature = (unsigned char *)malloc(size);
	/* ... */
	berr = BIO_new(BIO_s_file());

	ret = ECDSA_sign(0, digest, 32, signature, &sig_len, key);
	if (ret != 1)
	{
		printf("ECDSA_sign err!\n");
		return;
	}
	printf("signature:\n");
	display(signature,sig_len);

	/* 验证签名 */
	ret = ECDSA_verify(0, digest, 32, signature, sig_len, key);
	if (ret != 1)
	{
		printf("ECDSA_verify err!\n");
		return;
	}
	printf("ECDSA Sign & Verify Succeed!\n");

	BIO_free(berr);
	EC_KEY_free(key);
	free(signature);
	free(curves);
}