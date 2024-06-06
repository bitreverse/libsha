#ifndef HASHTESTS_H
#define	HASHTESTS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha1.h"
#include "sha224.h"
#include "sha256.h"
#include "sha384.h"
#include "sha512.h"
#include "sha512_224.h"
#include "sha512_256.h"

void test_sha1();
void test_sha224();
void test_sha256();
void test_sha384();
void test_sha512();
void test_sha512_224();
void test_sha512_256();
#endif