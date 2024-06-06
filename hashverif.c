#include "hashtests.h"

int main(int argc, char *argv[]) {
    /*
    test_sha1();
	test_sha224();
	test_sha256();
	test_sha384();
	test_sha512();
	test_sha512_224();
	test_sha512_256();
    */

    fprintf(stderr, "Usage %s <filename> <hash> <hashtype>\n", argv[0]);
    fprintf(stderr, "hashtype: sha1, sha224, sha256, sha384, sha512, sha512_224, sha512_256\n\n");
    if(argc != 4) {
        fprintf(stderr, "Usage %s <filename> <hash> <hashtype>\n", argv[0]);
        return 1;
    }

    printf("Opening file\n");
    FILE *fp = fopen(argv[1], "rb");
    if(fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long file_size  = ftell(fp);
    rewind(fp);

    unsigned char *file_data = malloc(file_size);
    if(file_data == NULL) {
        perror("Malloc filed");
        fclose(fp);
        return 1;
    }

    printf("Reading file\n");
    size_t bytes_read = fread(file_data, 1, file_size, fp);
    if((long) bytes_read != file_size) {
        fprintf(stderr, "Failed to read full file");
        fclose(fp);
        free(file_data);
        return 1;
    }

    int HASH_SIZE = 0;
    int STRING_HASH_SIZE = 0;
    void (*hashfp)() = NULL;
    void (*hash2strfp)() = NULL;
    char *sfp = NULL;
    if (strcmp("sha1", argv[3]) == 0) {
        HASH_SIZE = SHA1_HASH_SIZE;
        STRING_HASH_SIZE = SHA1_STRING_HASH_SIZE;
        hashfp = sha1;
        hash2strfp = sha1_hash_to_string;
        sfp = "SHA1";
    } else if (strcmp("sha224", argv[3]) == 0) {
        HASH_SIZE = SHA224_HASH_SIZE;
        STRING_HASH_SIZE = SHA224_STRING_HASH_SIZE;
        hashfp = sha224;
        hash2strfp = sha224_hash_to_string;
        sfp = "SHA224";
    } else if (strcmp("sha256", argv[3]) == 0) {
        HASH_SIZE = SHA256_HASH_SIZE;
        STRING_HASH_SIZE = SHA256_STRING_HASH_SIZE;
        hashfp = sha256;
        hash2strfp = sha256_hash_to_string;
        sfp = "SHA256";
    } else if (strcmp("sha384", argv[3]) == 0) {
        HASH_SIZE = SHA384_HASH_SIZE;
        STRING_HASH_SIZE = SHA384_STRING_HASH_SIZE;
        hashfp = sha384;
        hash2strfp = sha384_hash_to_string;
        sfp = "SHA384";
    } else if (strcmp("sha512", argv[3]) == 0) {
        HASH_SIZE = SHA512_HASH_SIZE;
        STRING_HASH_SIZE = SHA512_STRING_HASH_SIZE;
        hashfp = sha512;
        hash2strfp = sha512_hash_to_string;
        sfp = "SHA512";
    } else if (strcmp("sha512_224", argv[3]) == 0) {
        HASH_SIZE = SHA512_224_HASH_SIZE;
        STRING_HASH_SIZE = SHA512_224_STRING_HASH_SIZE;
        hashfp = sha512_224;
        hash2strfp = sha512_224_hash_to_string;
        sfp = "SHA512_224";
    } else if (strcmp("sha512_256", argv[3]) == 0) {
        HASH_SIZE = SHA512_256_HASH_SIZE;
        STRING_HASH_SIZE = SHA512_256_STRING_HASH_SIZE;
        hashfp = sha512_256;
        hash2strfp = sha512_256_hash_to_string;
        sfp = "SHA512_256";
    } else {
        fprintf(stderr, "Failed to read hashtype");
    }

    printf("Calculating hash\n\n");
    unsigned char hash[HASH_SIZE];
    char string[STRING_HASH_SIZE];
    hashfp(file_data, file_size, hash);
    hash2strfp(hash, string);
    printf("=============================================================================================\n");
    printf("Path: \t\t\t%s\n", argv[1]);
    printf("Algorithm: \t\t%s\n", sfp);
    printf("Calculated hash: \t%s\n", string);
    printf("Given hash: \t\t%s\n\n", argv[2]);
    if (strcmp(string, argv[2]) == 0) {
        printf("=> Hash is matching!!! [O]\n");
    }
    else {
        printf("=> Hash is not matching. [X]\n");
    }
    printf("=============================================================================================\n");

    free(file_data);
    fclose(fp);
    return 0;
    
}