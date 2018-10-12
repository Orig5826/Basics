/**
 * @brief ecc 算法Demo示例
 * 
 * @file ecc_demo.c
 * @author wenjf
 * @date 2018-09-20
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

/**
 * @brief 指定曲线参数，给定私钥生成相应的公钥
 * 
 */
void handleErrors()
{
	printf("ecc_generate 过程出错!\n");
}

void ecc_generate(void)
{
	BN_CTX *ctx;
	EC_GROUP *curve;
	BIGNUM *a, *b, *p, *order, *x, *y;
	EC_POINT *generator;

	/* 
		Binary data for the curve parameters 
		256bit 
		secp256k1 (bitcron) 参数
	*/
#define BYTES_CNT	32
	uint8_t p_bin[BYTES_CNT] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFC, 0x2F};
	uint8_t a_bin[BYTES_CNT] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t b_bin[BYTES_CNT] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07};
	uint8_t x_bin[BYTES_CNT] = {0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98};
	uint8_t y_bin[BYTES_CNT] = {0x48, 0x3A, 0xDA, 0x77, 0x26, 0xA3, 0xC4, 0x65, 0x5D, 0xA4, 0xFB, 0xFC, 0x0E, 0x11, 0x08, 0xA8, 0xFD, 0x17, 0xB4, 0x48, 0xA6, 0x85, 0x54, 0x19, 0x9C, 0x47, 0xD0, 0x8F, 0xFB, 0x10, 0xD4, 0xB8};
	uint8_t order_bin[BYTES_CNT] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B, 0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x41};


	/* Set up the BN_CTX */
	if(NULL == (ctx = BN_CTX_new())) handleErrors();
 
	/* Set the values for the various parameters */
	if(NULL == (a = BN_bin2bn(a_bin, BYTES_CNT, NULL))) handleErrors();
	if(NULL == (b = BN_bin2bn(b_bin, BYTES_CNT, NULL))) handleErrors();
	if(NULL == (p = BN_bin2bn(p_bin, BYTES_CNT, NULL))) handleErrors();
	if(NULL == (order = BN_bin2bn(order_bin, BYTES_CNT, NULL))) handleErrors();
	if(NULL == (x = BN_bin2bn(x_bin, BYTES_CNT, NULL))) handleErrors();
	if(NULL == (y = BN_bin2bn(y_bin, BYTES_CNT, NULL))) handleErrors();
 
	/* Create the curve */
	if(NULL == (curve = EC_GROUP_new_curve_GFp(p, a, b, ctx))) handleErrors();
 
	/* Create the generator */
	if(NULL == (generator = EC_POINT_new(curve))) handleErrors();
	if(1 != EC_POINT_set_affine_coordinates_GFp(curve, generator, x, y, ctx))
		handleErrors();
 
	/* Set the generator and the order */
	if(1 != EC_GROUP_set_generator(curve, generator, order, NULL))
		handleErrors();
	
	/*   使用指定私钥生成相应公钥   */
	{
		int ret;
		const EC_POINT *pubkey;
		const BIGNUM *prikey;
		BIGNUM *pub_x, *pub_y;
		EC_KEY * key;
		/* 构造 EC_KEY 数据结构 */
		key = EC_KEY_new();

		/* 设置密钥参数 */
		ret = EC_KEY_set_group(key, curve);
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

		prikey = EC_KEY_get0_private_key(key);
		printf("Prikey：\n");
		BN_print_fp(stdout,prikey);
		printf("\n");

		pubkey = EC_KEY_get0_public_key(key);
		pub_x = BN_new();
		pub_y = BN_new();
		if (EC_POINT_get_affine_coordinates_GFp(curve, pubkey,pub_x,pub_y, NULL))
		{
			printf("Pubkey  (x,y)：\n");
			BN_print_fp(stdout,pub_x);
			BN_print_fp(stdout,pub_y);
			printf("\n");
		}

		/*
			生成的公私钥已经在snp工具上进行了验证，没问题
		*/
	}


	EC_POINT_free(generator);
	BN_free(y);
	BN_free(x);
	BN_free(order);
	BN_free(p);
	BN_free(b);
	BN_free(a);
	BN_CTX_free(ctx);
}