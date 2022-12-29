/*

Modifications Copyright (C) 2019-2020 SKALE Labs

Copyright 2018 Intel Corporation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef SGXD_SGXD_COMMON_H
#define SGXD_SGXD_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include <stdbool.h>

extern bool useHTTPS;
extern bool enterBackupKey;
extern bool autoconfirm;

#define BUF_LEN 4096

#define MAX_KEY_LENGTH 128
#define MAX_COMPONENT_LENGTH 80
#define MAX_COMPONENT_HEX_LENGTH MAX_COMPONENT_LENGTH * 2
#define MAX_ENCRYPTED_KEY_LENGTH 1024
#define MAX_SIG_LEN 1024
#define MAX_ERR_LEN 1024
#define SHA_256_LEN 32

#define ADD_ENTROPY_SIZE 32

#define SECRET_SHARE_NUM_BYTES 96

#define ECDSA_SKEY_LEN 65
#define ECDSA_SKEY_BASE 16
#define ECDSA_ENCR_LEN 93
#define ECDSA_BIN_LEN 33


#define PLAINTEXT_KEY_TOO_LONG -2
#define UNPADDED_KEY -3
#define NULL_KEY -4
#define INCORRECT_STRING_CONVERSION -5
#define ENCRYPTED_KEY_TOO_LONG -6
#define KEY_SHARE_DOES_NOT_EXIST -7
#define KEY_SHARE_ALREADY_EXISTS -8
#define COULD_NOT_ACCESS_DATABASE -9
#define NULL_DATABASE -10
#define BLS_SIGN_INVALID_KS_NAME -11
#define BLS_SIGN_INVALID_PARAMS -12
#define INVALID_SECRET_SHARES_LENGTH -13
#define CERT_REQUEST_DOES_NOT_EXIST -14
#define BLS_IMPORT_INVALID_KEY_NAME -15
#define SEAL_KEY_FAILED -16
#define GET_VV_INVALID_POLY_HEX -17
#define GET_SS_INVALID_HEX -18
#define DECRYPT_DH_KEY_INVALID_KEY_HEX -19
#define INVALID_ECDSA_KEY_NAME -20
#define VERIFY_SHARES_INVALID_KEY_HEX -21
#define INVALID_ECSDA_SIGNATURE -22
#define KEY_NAME_ALREADY_EXISTS -23
#define BLS_IMPORT_EMPTY_ENCRYPTED_KEY_SHARE -24
#define BLS_IMPORT_INVALID_KEY_SHARE -25
#define INVALID_BLS_HEX -26
#define INVALID_ECDSA_HEX -27
#define COULD_NOT_BLS_SIGN -28
#define INVALID_ECDSA_IMPORT_KEY_NAME -29
#define INVALID_ECDSA_IMPORT_HEX -30
#define ECDSA_GEN_EMPTY_KEY -31
#define INVALID_ECDSA_SIGN_KEY_NAME -32
#define ERROR_IN_ENCLAVE -33
#define INVALID_ECDSA_SIGN_HASH -34
#define INVALID_ECDSA_SIGN_BASE -35
#define INVALID_ECSDA_SIGN_SIGNATURE -36
#define INVALID_ECDSA_GETPKEY_KEY_NAME -37
#define INVALID_GEN_DKG_POLY_NAME -38
#define INVALID_GEN_DKG_PARAM_T -39
#define INVALID_VERIFY_DKG_PARAM_T -40
#define INVALID_DKG_GETVV_POLY_NAME -41
#define INVALID_DKG_GETVV_PARAMS -42
#define INVALID_DKG_GETSS_POLY_NAME -43
#define FILE_NOT_FOUND -44
#define INVALID_DKG_GETSS_PARAMS -45
#define INVALID_DKG_GETSS_PUB_KEY_COUNT -46
#define INVALID_DKG_GETSS_KEY_HEX -47
#define INVALID_DKG_VERIFY_ECDSA_KEY_NAME -48
#define INVALID_DKG_VERIFY_PARAMS -49
#define INVALID_DKG_VERIFY_SS_HEX -50
#define INVALID_DKG_VERIFY_PUBSHARES_LENGTH -51
#define INVALID_CREATE_BLS_KEY_SECRET_SHARES_LENGTH -52
#define INVALID_CREATE_BLS_ECDSA_KEY_NAME -53
#define INVALID_CREATE_BLS_POLY_NAME -54
#define FAIL_TO_CREATE_CERTIFICATE -55
#define INVALID_CREATE_BLS_KEY_NAME -56
#define INVALID_CREATE_BLS_DKG_PARAMS -57
#define INVALID_CREATE_BLS_SHARE -58
#define INVALID_GET_BLS_PUBKEY_NAME -59
#define INVALID_DKG_CALCULATE_ALL_PARAMS -60
#define INVALID_DKG_CALCULATE_ALL_PUBSHARES -61
#define INVALID_DKG_CALCULATE_ALL_PUBSHARES_SIZE -62
#define INVALID_DKG_CALCULATE_ALL_PUBSHARES_STRING -63
#define INVALID_DKG_CALCULATE_ALL_STRING_PUBSHARES_SLENGTH -64
#define INVALID_DKG_CALCULATE_ALL_STRING_PUBKEYS_SIZE -65
#define INVALID_COMPLAINT_RESPONSE_POLY_NAME -66
#define INVALID_DKG_GETSS_V2_PARAMS -63
#define INVALID_DKG_GETSS_V2_POLY_NAME -64
#define INVALID_DKG_GETSS_V2_PUBKEY_COUNT -65
#define INVALID_DKG_GETSS_V2_PUBKEY_HEX -66
#define INVALID_DKG_VV_V2_ECDSA_KEY_NAME -67
#define INVALID_DKG_VV_V2_PARAMS -68
#define INVALID_DKG_VV_V2_SS_HEX -69
#define INVALID_DKG_VV_V2_SS_COUNT  -70
#define EXCEPTION_IN_CONVERT_HEX_TO_DEC -71
#define GET_SS_V2_INVALID_HEX -72
#define EXCEPTION_IN_CONVERT_G2_STRING -73
#define CONVERT_G2_INCORRECT_STRING_CONVERSION -74
#define DELETE_BLS_KEY_INVALID_KEYNAME -75
#define DELETE_BLS_KEY_NOT_FOUND -76
#define VERIFY_SHARES_INVALID_PUBLIC_SHARES -77
#define VERIFY_SHARES_V2_INVALID_POLY_HEX -78
#define VERIFY_SHARES_V2_INVALID_PUBLIC_SHARES -79
#define CREATE_BLS_SHARE_INVALID_KEY_HEX -80
#define GET_BLS_PUBKEY_INVALID_KEY_HEX -81
#define GENERATE_DKG_POLY_INVALID_PARAMS -82
#define SIGN_FUNCTION_INVALID_HEX -83
#define SIGN_AES_INVALID_HASH -84
#define GET_ECDSA_PUB_KEY_INVALID_KEY_HEX -85
#define ECDSA_SIGN_INVALID_KEY_HEX -86
#define SET_SEK_INVALID_SEK_HEX -87
#define TEST_INVALID_HEX -88
#define ZMQ_SERVER_ERROR -89
#define ZMQ_COULD_NOT_PARSE -90
#define ZMQ_INVALID_MESSAGE -91
#define ZMQ_COULD_NOT_GET_SOCKOPT -92
#define ZMQ_INVALID_MESSAGE_SIZE -93
#define ZMQ_NO_TYPE_IN_MESSAGE -94
#define ZMQ_NO_SIG_IN_MESSAGE -95
#define ZMQ_NO_CERT_IN_MESSAGE -96
#define ZMQ_COULD_NOT_VERIFY_SIG -97
#define ZMQ_COULD_NOT_BIND_FRONT_END -98
#define ZMQ_COULD_NOT_BIND_BACK_END -99
#define ZMQ_COULD_NOT_CREATE_WORKERS -100
#define ZMQ_COULD_NOT_CREATE_PROXY -101
#define REGISTRATION_SERVER_FAILED_TO_START -102
#define CSR_MANAGER_SERVER_FAILED_TO_START -103
#define SGX_INFO_SERVER_FAILED_TO_START -104
#define COULD_NOT_GET_WORKING_DIRECTORY -105
#define ERROR_CREATING_SGX_DATA_FOLDER -106
#define EXECUTION_ULIMIT_FAILED -107
#define WRONG_ULIMIT -108
#define COULD_NOT_INIT_ENCLAVE -109
#define FAIL_TO_VERIFY_CERTIFICATE -110
#define SGX_SERVER_FAILED_TO_START -111
#define CORRUPT_DATABASE -112
#define INVALID_SEK -113
#define INVALID_DECRYPTION_VALUE_FORMAT -114
#define INVALID_KEY_FORMAT -115
#define KEY_ALREADY_REGISTERED -116
#define POP_PROVE_INVALID_KEY_NAME -117
#define COULD_NOT_CREATE_POP_PROVE -118
#define GENERATE_BLS_KEY_INVALID_NAME -119
#define INVALID_CREATE_BLS_AGGREGATED_KEY -120

#define SGX_ENCLAVE_ERROR -666

#define MAX_CSR_NUM 1000

#define BASE_PORT 1026

#define WALLETDB_NAME "sgxwallet.db"
#define ENCLAVE_NAME "secure_enclave.signed.so"
#define SGXDATA_FOLDER "sgx_data/"

#define TEST_VALUE "1234567890"



#endif //SGXWALLET_SGXWALLET_COMMON_H
