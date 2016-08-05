/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#define MAX_UINT_STR_SIZE 12

#define ENROLL_CMD "enroll"
#define REENROLL_CMD "reenroll"
#define CERTS_CMD "crls"
#define REVOKE_CERT_CMD "revoke"

#define CERT_AUTH_TYPE  "PeerCert"

#define CERT_SUBJECT_HDR  "Subject"
#define CERT_ISSUER_HDR  "Issuer"
#define CERT_KEY_HDR  "Key"
#define CERT_SIG_HDR  "Signature"
#define CERT_EXP_HDR "Expiration"
#define CERT_STATUS_HDR "Status"
#define CERT_USE_HDR "Use"
#define CERT_EXP_WDOW_HDR "ExpWindow"

#define CERT_STATUS_REVOKED "Revoked"

#define RESPONSE_ERR_NO_CERT "Invalid Certificate!"
#define RESPONSE_ERR_EXP_CERT "Expired Certificate!"

#define ISSUER_STR "Secure Registers Inc."

typedef struct {
	char* subject;
	char* issuer;
	char* key;
	char* use;
	char* revoked;
	unsigned int signature;
	unsigned int expiration;
	unsigned int exp_window;
	void* next;
} Certificate;

static char private_key[1024];
static char* issuer;
Certificate *CRL;

void enroll(int id, char* body, unsigned int* expiration_date);
void crls(int id, char* body, unsigned int* expiration_date);
void reenroll(int id, char* body, unsigned int* expiration_date);
void revokeCert(int id, char* body, unsigned int* expiration_date);

Certificate *parseCertificate(char* body);
int validateCert(Certificate *cert, char* use, unsigned int* expiration_date);
int checkCertUse(char* command, char* useList);
int isCertCommand(char* command);